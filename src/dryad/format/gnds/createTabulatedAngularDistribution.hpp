#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDANGULARDISTRIBUTION
#define NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createInterpolationType.hpp"
#include "dryad/format/gnds/convertEnergy.hpp"
#include "dryad/format/gnds/readXYs1d.hpp"
#include "dryad/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a TabulatedAngularDistribution from a GNDS XYs1d node
   */
  std::pair< std::optional< double >, 
             TabulatedAngularDistribution >
  createTabulatedAngularDistribution( pugi::xml_node node,
                                      const std::vector< std::string > units ) {

    std::optional< double > outer = std::nullopt;
    std::vector< double > cosines;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< InterpolationType > interpolants;

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
             TabulatedAngularDistribution(
               std::move( cosines ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) ) };
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
