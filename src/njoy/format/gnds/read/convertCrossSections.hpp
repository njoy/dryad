#ifndef NJOY_FORMAT_GNDS_READ_CONVERTCROSSSECTIONS
#define NJOY_FORMAT_GNDS_READ_CONVERTCROSSSECTIONS

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
   *  @brief Convert a cross section range from GNDS into b
   *
   *  @param[in] values   the values to convert
   *  @param[in] unit     the unit of the values
   */
  inline void convertCrossSections( std::vector< double >& values, const std::string& unit ) {

    if ( unit != "b" ) {

      if ( unit == "Mb" ) {

        std::for_each( values.begin(), values.end(),
                       [] ( double& value ) { value *= constants::mega; } );
      }
      else {

        Log::error( "Cannot convert cross section with unit \'{}\' to b, "
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
