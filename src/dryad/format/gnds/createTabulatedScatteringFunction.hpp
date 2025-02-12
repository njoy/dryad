#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDSCATTERINGFUNCTION
#define NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDSCATTERINGFUNCTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createInterpolationType.hpp"
#include "dryad/format/gnds/convertInverseLengths.hpp"
#include "dryad/format/gnds/readXYs1d.hpp"
#include "dryad/TabulatedScatteringFunction.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a TabulatedScatteringFunction from a GNDS node
   */
  static TabulatedScatteringFunction
  createTabulatedScatteringFunction( pugi::xml_node node ) {

    std::vector< double > x;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< InterpolationType > interpolants;

    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the scattering function data
      auto data = readXYs1D( node );

      // get the interpolation type
      auto interpolant = createInterpolationType( std::get< 6 >( data ) );

      // convert units - if necessary
      convertInverseLengths( std::get< 2 >( data ), std::get< 3 >( data ) );

      // assign data
      x = std::move( std::get< 2 >( data ) );
      values = std::move( std::get< 4 >( data ) );
      boundaries.emplace_back( x.size() - 1 );
      interpolants.emplace_back( interpolant );
    }
    else if ( strcmp( node.name(), "regions1d" ) == 0 ) {

      // get the units
      auto units = readAxes( node.child( "axes" ) );

      // loop over the children of function1ds
      pugi::xml_node function1ds = node.child( "function1ds" );
      for ( pugi::xml_node xys1d = function1ds.child( "XYs1d" );
            xys1d; xys1d = xys1d.next_sibling(  "XYs1d"  ) ) {

        // read the current interpolation region
        auto data = readXYs1D( xys1d, units );

        // get the interpolation type
        auto interpolant = createInterpolationType( std::get< 6 >( data ) );

        // convert units - if necessary
        convertInverseLengths( std::get< 2 >( data ), std::get< 3 >( data ) );

        // check for duplicate points at interpolation region boundaries
        std::size_t offset = 0;
        if ( x.size() > 0 ) {

          if ( x.back() == std::get< 2 >( data ).front() &&
               values.back() == std::get< 4 >( data ).front() ) {

            offset = 1;
          }
        }

        // grow the data accordingly
        x.insert( x.end(), std::get< 2 >( data ).begin() + offset, std::get< 2 >( data ).end() );
        values.insert( values.end(), std::get< 4 >( data ).begin() + offset, std::get< 4 >( data ).end() );
        boundaries.emplace_back( x.size() - 1 );
        interpolants.emplace_back( interpolant );
      }
    }
    else {

      Log::error( "Expected an XYs1d or regions1d node for tabulated scattering function data" );
      throw std::exception();
    }

    return TabulatedScatteringFunction(
             std::move( x ), std::move( values ),
             std::move( boundaries ), std::move( interpolants ) );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
