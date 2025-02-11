#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTINVERSELENGTHS
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTINVERSELENGTHS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Convert an inverse length range from GNDS into Angstrom
   */
  static void convertInverseLengths( std::vector< double >& energies, const std::string& unit ) {

    if ( unit != "1/Ang" ) {

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
