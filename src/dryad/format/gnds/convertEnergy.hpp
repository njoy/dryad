#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTENERGY
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTENERGY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Convert an energy value GNDS into eV
   */
  void convertEnergy( double& energy, const std::string& unit ) {

    if ( unit != "eV" ) {

      if ( unit == "MeV" ) {

        energy *= 1e+6;
      }
      else {

        Log::error( "Cannot convert energy with unit \'{}\' to eV, "
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
