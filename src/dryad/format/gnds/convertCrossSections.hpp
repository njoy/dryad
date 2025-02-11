#ifndef NJOY_DRYAD_FORMAT_GNDS_CONVERTCROSSSECTIONS
#define NJOY_DRYAD_FORMAT_GNDS_CONVERTCROSSSECTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Convert a cross section range from GNDS into b
   */
  void convertCrossSections( std::vector< double >& xs, const std::string& unit ) {

    if ( unit != "b" ) {

      if ( unit == "Mb" ) {

        std::for_each( xs.begin(), xs.end(), 
                      [] ( double& xs ) { xs *= 1e+6; } );
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
