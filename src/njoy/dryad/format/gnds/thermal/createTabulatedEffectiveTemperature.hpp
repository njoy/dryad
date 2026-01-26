#ifndef NJOY_DRYAD_FORMAT_GNDS_THERMAL_CREATETABULATEDEFFECTIVETEMPERATURE
#define NJOY_DRYAD_FORMAT_GNDS_THERMAL_CREATETABULATEDEFFECTIVETEMPERATURE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/format/gnds/createInterpolationType.hpp"
#include "njoy/dryad/format/gnds/readXYs1d.hpp"
#include "njoy/dryad/format/gnds/convertTemperatures.hpp"
#include "njoy/dryad/thermal/TabulatedEffectiveTemperature.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace thermal {

  /**
   *  @brief Create a TabulatedEffectiveTemperature from a GNDS T_effective node
   *
   *  @param[in] temperature   the GNDS effective temperature node
   */
  inline dryad::thermal::TabulatedEffectiveTemperature
  createTabulatedEffectiveTemperature( const pugi::xml_node& temperature ) {

    std::vector< double > temperatures;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< InterpolationType > interpolants;

    // check that this is a valid effective temperature node
    throwExceptionOnWrongNode( temperature, "T_effective" );

    auto node = temperature.first_child();
    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the effective temperature data
      auto data = readXYs1D( node );

      // get the interpolation type
      auto interpolant = createInterpolationType( std::get< 6 >( data ) );

      // convert units - if necessary
      convertTemperatures( std::get< 2 >( data ), std::get< 3 >( data ) );
      convertTemperatures( std::get< 4 >( data ), std::get< 5 >( data ) );

      // assign data
      temperatures = std::move( std::get< 2 >( data ) );
      values = std::move( std::get< 4 >( data ) );
      boundaries.emplace_back( temperatures.size() - 1 );
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
        convertTemperatures( std::get< 2 >( data ), std::get< 3 >( data ) );
        convertTemperatures( std::get< 4 >( data ), std::get< 5 >( data ) );

        // check for duplicate points at interpolation region boundaries
        std::size_t offset = 0;
        if ( temperatures.size() > 0 ) {

          if ( temperatures.back() == std::get< 2 >( data ).front() &&
               values.back() == std::get< 4 >( data ).front() ) {

            offset = 1;
          }
        }

        // grow the data accordingly
        temperatures.insert( temperatures.end(), std::get< 2 >( data ).begin() + offset, std::get< 2 >( data ).end() );
        values.insert( values.end(), std::get< 4 >( data ).begin() + offset, std::get< 4 >( data ).end() );
        boundaries.emplace_back( temperatures.size() - 1 );
        interpolants.emplace_back( interpolant );
      }
    }
    else {

      Log::error( "Expected either an XYs1d node or regions1d node with XYs1d nodes "
                  "for effective temperature data" );
      throw std::exception();
    }

    return dryad::thermal::TabulatedEffectiveTemperature(
             std::move( temperatures ), std::move( values ),
             std::move( boundaries ), std::move( interpolants ) );
  }

} // thermal namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
