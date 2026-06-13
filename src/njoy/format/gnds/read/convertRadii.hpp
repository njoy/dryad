#ifndef NJOY_FORMAT_GNDS_READ_CONVERTRADII
#define NJOY_FORMAT_GNDS_READ_CONVERTRADII

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
   *  @brief Convert a range of radii from GNDS into fm
   */
  inline void convertRadii( std::vector< double >& radii, const std::string& unit ) {

    if ( unit != "fm" ) {

      if ( unit == "nm" ) {

        std::for_each( radii.begin(), radii.end(),
                       [] ( double& radius ) { radius *= constants::mega; } );
      }
      else {

        Log::error( "Cannot convert radius with unit \'{}\' to fm, "
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
