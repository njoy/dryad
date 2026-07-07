#ifndef NJOY_FORMAT_GNDS_READ_CONVERTMASS
#define NJOY_FORMAT_GNDS_READ_CONVERTMASS

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
   *  @brief Convert a mass value from GNDS into amu
   *
   *  @param[in] value   the value to convert
   *  @param[in] unit    the unit of the value
   */
  inline void convertMass( double& value, const std::string& unit ) {

    if ( unit != "amu" ) {

      if ( unit == "kg" ) {

        value /= constants::amu;
      }
      else if ( unit == "nmu" ) {

        value *= constants::neutron_mass;
      }
      else {

        Log::error( "Cannot convert mass with unit \'{}\' to amu, "
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
