#ifndef NJOY_FORMAT_GNDS_READ_CONVERTENERGIES
#define NJOY_FORMAT_GNDS_READ_CONVERTENERGIES

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
   *  @brief Convert an energy range from GNDS into eV
   */
  inline void convertEnergies( std::vector< double >& energies, const std::string& unit ) {

    if ( unit != "eV" ) {

      if ( unit == "MeV" ) {

        std::for_each( energies.begin(), energies.end(),
                       [] ( double& energy ) { energy *= constants::mega; } );
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
