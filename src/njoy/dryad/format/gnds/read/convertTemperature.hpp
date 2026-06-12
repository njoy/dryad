#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTTEMPERATURE
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTTEMPERATURE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

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
                    "contact dryad developers", unit );
        throw std::exception();
      }
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
