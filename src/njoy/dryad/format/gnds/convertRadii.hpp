#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTRADII
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTRADII

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
   *  @brief Convert a range of radii from GNDS into fm
   */
  static void convertRadii( std::vector< double >& radii, const std::string& unit ) {

    if ( unit != "fm" ) {

      if ( unit == "nm" ) {

        std::for_each( radii.begin(), radii.end(),
                       [] ( double& radius ) { radius *= constants::mega; } );
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
