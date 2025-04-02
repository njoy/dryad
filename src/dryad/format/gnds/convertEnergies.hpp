#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTENERGIES
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTENERGIES

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Convert an energy range from GNDS into eV
   */
  static void convertEnergies( std::vector< double >& energies, const std::string& unit ) {

    if ( unit != "eV" ) {

      if ( unit == "MeV" ) {

        std::for_each( energies.begin(), energies.end(),
                       [] ( double& energy ) { energy *= 1e+6; } );
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
