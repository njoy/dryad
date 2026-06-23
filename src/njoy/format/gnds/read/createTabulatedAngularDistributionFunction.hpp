#ifndef NJOY_FORMAT_GNDS_READ_CREATETABULATEDANGULARDISTRIBUTIONFUNCTION
#define NJOY_FORMAT_GNDS_READ_CREATETABULATEDANGULARDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"
#include "njoy/format/gnds/read/createInterpolationType.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"
#include "njoy/format/gnds/read/readXYs1d.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a TabulatedAngularDistribution from a GNDS XYs1d node
   *
   *  @todo is it possible to have a regions1d version?
   */
  inline std::pair< std::optional< double >,
                    dryad::TabulatedAngularDistributionFunction >
  createTabulatedAngularDistributionFunction( pugi::xml_node node, const Axes& units ) {

    std::optional< double > outer = std::nullopt;
    std::vector< double > cosines;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< dryad::InterpolationType > interpolants;

    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the cross section data
      auto data = readXYs1D( node, units );

      // get the interpolation type
      auto interpolant = createInterpolationType( std::get< 6 >( data ) );

      // cosine and probability data does not need to be converted
      // convert outer domain value if necessary
      if ( std::get< 0 >( data ).has_value() ) {

        convertEnergy( std::get< 0 >( data ).value(), std::get< 1 >( data ).value() );
      }

      // assign data
      outer = std::move( std::get< 0 >( data ) );
      cosines = std::move( std::get< 2 >( data ) );
      values = std::move( std::get< 4 >( data ) );
      boundaries.emplace_back( cosines.size() - 1 );
      interpolants.emplace_back( interpolant );
    }
    else {

      Log::error( "Expected an XYs1d node for tabulated angular distribution data" );
      throw std::exception();
    }

    return { std::move( outer ),
             dryad::TabulatedAngularDistributionFunction(
               std::move( cosines ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) ) };
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
