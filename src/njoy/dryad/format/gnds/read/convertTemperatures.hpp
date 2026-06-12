#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTTEMPERATURES
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTTEMPERATURES

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

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
