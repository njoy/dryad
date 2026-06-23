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
   *  @brief Create a TabulatedAngularDistributionFunction from a GNDS XYs1d or regions1d node
   *
   *  @param[in] legendre   the gnds XYs1d or regions1d node
   *  @param[in] units      the unit information
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
    else if ( strcmp( node.name(), "regions1d" ) == 0 ) {

      // get the outer domain value
      auto attribute = node.attribute( "outerDomainValue" );
      if ( attribute ) {

        outer = attribute.as_double();
        convertEnergy( outer.value(), std::get< 1 >( units[0] ).value() );
      }

      // loop over the children of function1ds
      pugi::xml_node function1ds = node.child( "function1ds" );
      for ( pugi::xml_node xys1d = function1ds.child( "XYs1d" );
            xys1d; xys1d = xys1d.next_sibling(  "XYs1d"  ) ) {

        // read the current interpolation region
        auto data = readXYs1D( xys1d, units );

        // get the interpolation type
        auto interpolant = createInterpolationType( std::get< 6 >( data ) );

        // check for duplicate points at interpolation region boundaries
        std::size_t offset = 0;
        if ( cosines.size() > 0 ) {

          if ( cosines.back() == std::get< 2 >( data ).front() &&
               values.back() == std::get< 4 >( data ).front() ) {

            offset = 1;
          }
        }

        // grow the data accordingly
        cosines.insert( cosines.end(), std::get< 2 >( data ).begin() + offset, std::get< 2 >( data ).end() );
        values.insert( values.end(), std::get< 4 >( data ).begin() + offset, std::get< 4 >( data ).end() );
        boundaries.emplace_back( cosines.size() - 1 );
        interpolants.emplace_back( interpolant );
      }
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
