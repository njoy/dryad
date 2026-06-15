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
   */
  inline void convertMass( double& mass, const std::string& unit ) {

    if ( unit != "amu" ) {

      if ( unit == "kg" ) {

        mass /= constants::amu;
      }
      else if ( unit == "nmu" ) {

        mass *= constants::neutron_mass;
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
