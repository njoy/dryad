#ifndef NJOY_FORMAT_GNDS_READ_CONVERTINVERSEENERGIES
#define NJOY_FORMAT_GNDS_READ_CONVERTINVERSEENERGIES

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
   *  @brief Convert an inverse energy range from GNDS into eV^1/2
   *
   *  @param[in] values   the inverse energy values
   *  @param[in] unit     the unit the values are given in
   */
  inline void convertSquareRootEnergies( std::vector< double >& values, const std::string& unit ) {

    if ( unit != "eV**(1/2)" ) {

      if ( unit == "MeV**(1/2)" ) {

        std::for_each( values.begin(), values.end(),
                       [] ( double& value ) { value *= constants::mili; } );
      }
      else {

        Log::error( "Cannot convert inverse energy with unit \'{}\' to eV**(1/2), "
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
