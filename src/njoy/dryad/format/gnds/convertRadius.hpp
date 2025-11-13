#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTRADIUS
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTRADIUS

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
   *  @brief Convert a radius value from GNDS into fm
   */
  inline void convertRadius( double& radius, const std::string& unit ) {

    if ( unit != "fm" ) {

      if ( unit == "nm" ) {

        radius *= constants::mega;
      }
      else {

        Log::error( "Cannot convert radius with unit \'{}\' to fm, "
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
