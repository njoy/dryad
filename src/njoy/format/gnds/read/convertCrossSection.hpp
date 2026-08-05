#ifndef NJOY_FORMAT_GNDS_READ_CONVERTCROSSSECTION
#define NJOY_FORMAT_GNDS_READ_CONVERTCROSSSECTION

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
   *  @brief Convert a cross section value from GNDS into b
   *
   *  @param[in] value   the value to convert
   *  @param[in] unit    the unit of the value
   */
  inline void convertCrossSection( double& value, const std::string& unit ) {

    if ( unit != "b" ) {

      if ( unit == "Mb" ) {

        value *= constants::mega;
      }
      else {

        Log::error( "Cannot convert cross section with unit \'{}\' to b, "
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
