#ifndef NJOY_FORMAT_GNDS_READ_CONVERTRADIUS
#define NJOY_FORMAT_GNDS_READ_CONVERTRADIUS

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
   *  @brief Convert a radius value from GNDS into fm
   */
  inline void convertRadius( double& radius, const std::string& unit ) {

    if ( unit != "fm" ) {

      if ( unit == "nm" ) {

        radius *= constants::mega;
      }
      else {

        Log::error( "Cannot convert radius with unit \'{}\' to fm, "
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
