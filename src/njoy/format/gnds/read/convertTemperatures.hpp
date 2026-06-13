#ifndef NJOY_FORMAT_GNDS_READ_CONVERTTEMPERATURES
#define NJOY_FORMAT_GNDS_READ_CONVERTTEMPERATURES

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Convert a temperature range from GNDS into K
   *
   *  @param[in] temperatures   the temperature values
   *  @param[in] unit           the unit
   */
  inline void convertTemperatures( std::vector< double >& temperatures, const std::string& unit ) {

    if ( unit != "K" ) {

      if ( unit == "degrees C" ) {

        std::for_each( temperatures.begin(), temperatures.end(),
                       [] ( double& temperature ) { temperature += 273.15; } );
      }
      else {

        Log::error( "Cannot convert temperature with unit \'{}\' to K, "
                    "contact njoy developers", unit );
        throw std::exception();
      }
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
