#ifndef NJOY_FORMAT_GNDS_READ_CONVERTVARIANCESCALINGFACTORS
#define NJOY_FORMAT_GNDS_READ_CONVERTVARIANCESCALINGFACTORS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Convert a variance scaling factor range from GNDS into b**2
   */
  inline void convertVarianceScalingFactors( std::vector< double >& factors, const std::string& unit ) {

    if ( unit != "b**2" ) {

      if ( unit == "Mb**2" ) {

        std::for_each( factors.begin(), factors.end(),
                       [] ( double& factor ) { factor *= 1e+12; } );
      }
      else {

        Log::error( "Cannot convert variance scaling factor with unit \'{}\' to b**2, "
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
