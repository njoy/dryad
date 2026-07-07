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
   *  @brief Convert an cross section value from GNDS into b
   */
  inline void convertCrossSection( double& xs, const std::string& unit ) {

    if ( unit != "b" ) {

      if ( unit == "Mb" ) {

        xs *= constants::mega;
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
