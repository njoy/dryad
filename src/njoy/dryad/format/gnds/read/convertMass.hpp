#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTMASS
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTMASS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

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
