#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTINVERSEENERGIES
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTINVERSEENERGIES

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
  inline void convertInverseEnergies( std::vector< double >& values, const std::string& unit ) {

    if ( unit != "1/eV" ) {

      if ( unit == "1/MeV" ) {

        std::for_each( values.begin(), values.end(),
                       [] ( double& value ) { value *= constants::micro; } );
      }
      else {

        Log::error( "Cannot convert inverse energy with unit \'{}\' to 1/eV, "
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
