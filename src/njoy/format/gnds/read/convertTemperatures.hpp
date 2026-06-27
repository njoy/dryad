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
   *  @param[in] values   the values to convert
   *  @param[in] unit     the unit of the values
   */
  inline void convertTemperatures( std::vector< double >& values, const std::string& unit ) {

    if ( unit != "K" ) {

      if ( unit == "degrees C" ) {

        std::for_each( values.begin(), values.end(),
                       [] ( double& value ) { value += 273.15; } );
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
