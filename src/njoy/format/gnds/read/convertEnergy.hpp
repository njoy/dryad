#ifndef NJOY_FORMAT_GNDS_READ_CONVERTENERGY
#define NJOY_FORMAT_GNDS_READ_CONVERTENERGY

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
   *  @brief Convert an energy value from GNDS into eV
   */
  inline void convertEnergy( double& energy, const std::string& unit ) {

    if ( unit != "eV" ) {

      if ( unit == "MeV" ) {

        energy *= constants::mega;
      }
      else {

        Log::error( "Cannot convert energy with unit \'{}\' to eV, "
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
