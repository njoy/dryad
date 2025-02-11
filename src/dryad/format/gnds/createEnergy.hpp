#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEENERGY
#define NJOY_DRYAD_FORMAT_GNDS_CREATEENERGY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create an energy value in eV from a GNDS energy and unit
   */
  double createEnergy( double energy, const std::string& unit ) {

    if ( unit == "eV" ) {

      return energy;
    }
    else {

      Log::error( "Cannot convert energy with unit \'{}\' to eV, "
                  "contact dryad developers", unit );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
