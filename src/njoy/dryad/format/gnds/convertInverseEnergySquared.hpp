#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTINVERSEENERGYSQUARED
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTINVERSEENERGYSQUARED

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
   *  @brief Convert an inverse energy range from GNDS into 1/eV
   *
   *  @param[in] values   the inverse energy values
   *  @param[in] unit     the unit
   */
  inline void convertInverseEnergySquared( double& value, const std::string& unit ) {

    if ( unit != "1/eV**2" ) {

      if ( unit == "1/MeV**2" ) {

        value *= constants::pico;
      }
      else {

        Log::error( "Cannot convert inverse energy with unit \'{}\' to 1/eV**2, "
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
