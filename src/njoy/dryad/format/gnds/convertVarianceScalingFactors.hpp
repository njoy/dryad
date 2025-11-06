#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTVARIANCESCALINGFACTORS
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTVARIANCESCALINGFACTORS

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
   *  @brief Convert a variance scaling factor range from GNDS into b**2
   */
  static void convertVarianceScalingFactors( std::vector< double >& factors, const std::string& unit ) {

    if ( unit != "b**2" ) {

      if ( unit == "Mb**2" ) {

        std::for_each( factors.begin(), factors.end(),
                       [] ( double& factor ) { factor *= 1e+12; } );
      }
      else {

        Log::error( "Cannot convert variance scaling factor with unit \'{}\' to b**2, "
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
