#ifndef NJOY_FORMAT_GNDS_READ_THERMAL_CREATETABULATEDDEBYEWALLERINTEGRAL
#define NJOY_FORMAT_GNDS_READ_THERMAL_CREATETABULATEDDEBYEWALLERINTEGRAL

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/DebyeWallerIntegralData.hpp"
#include "njoy/format/gnds/read/createInterpolationType.hpp"
#include "njoy/format/gnds/read/readXYs1d.hpp"
#include "njoy/format/gnds/read/convertTemperatures.hpp"
#include "njoy/format/gnds/read/convertInverseEnergies.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace thermal {

  /**
   *  @brief Create a DebyeWallerIntegralData from a GNDS DebyeWallerIntegral node
   *
   *  @param[in] debye_waller   the GNDS Debye-Waller node
   */
  inline dryad::thermal::DebyeWallerIntegralData
  createDebyeWallerIntegralData( const pugi::xml_node& debye_waller ) {

    std::vector< double > temperatures;
    std::vector< double > values;

    // check that this is a valid Debye-Waller integral node
    throwExceptionOnWrongNode( debye_waller, "DebyeWallerIntegral" );

    auto node = debye_waller.first_child();
    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the Debye-Waller integral data
      auto data = readXYs1D( node );

      // convert units - if necessary
      convertTemperatures( std::get< 2 >( data ), std::get< 3 >( data ) );
      convertInverseEnergies( std::get< 4 >( data ), std::get< 5 >( data ) );

      // assign data
      temperatures = std::move( std::get< 2 >( data ) );
      values = std::move( std::get< 4 >( data ) );
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

        // convert units - if necessary
        convertTemperatures( std::get< 2 >( data ), std::get< 3 >( data ) );
        convertInverseEnergies( std::get< 4 >( data ), std::get< 5 >( data ) );

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
      }
    }
    else {

      Log::error( "Expected either an XYs1d node or regions1d node with XYs1d nodes "
                  "for Debye-Waller integral data" );
      throw std::exception();
    }

    return dryad::thermal::DebyeWallerIntegralData( std::move( temperatures ), std::move( values ) );
  }

} // thermal namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
