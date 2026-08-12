#ifndef NJOY_FORMAT_GNDS_READ_CONVERTINVERSEENERGY
#define NJOY_FORMAT_GNDS_READ_CONVERTINVERSEENERGY

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
   *  @brief Convert an inverse energy value from GNDS into 1/eV
   *
   *  @param[in] value   the value to convert
   *  @param[in] unit    the unit of the value
   */
  inline void convertInverseEnergy( double& value, const std::string& unit ) {

    if ( unit != "1/eV" ) {

      if ( unit == "1/MeV" ) {

        value *= constants::micro;
      }
      else {

        Log::error( "Cannot convert inverse energy with unit \'{}\' to 1/eV, "
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
