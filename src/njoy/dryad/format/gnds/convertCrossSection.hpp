#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTENERGY
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTENERGY

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
   *  @brief Convert an cross section value from GNDS into b
   */
  inline void convertCrossSection( double& xs, const std::string& unit ) {

    if ( unit != "b" ) {

      if ( unit == "Mb" ) {

        xs *= constants::mega;
      }
      else {

        Log::error( "Cannot convert cross section with unit \'{}\' to b, "
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
