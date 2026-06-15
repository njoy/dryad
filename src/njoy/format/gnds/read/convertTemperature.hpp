#ifndef NJOY_FORMAT_GNDS_READ_CONVERTTEMPERATURE
#define NJOY_FORMAT_GNDS_READ_CONVERTTEMPERATURE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Convert a temperature value from GNDS into K
   *
   *  @param[in] temperature   the temperature value
   *  @param[in] unit          the unit
   */
  inline void convertTemperature( double& temperature, const std::string& unit ) {

    if ( unit != "K" ) {

      if ( unit == "degrees C" ) {

        temperature += 273.15;
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
