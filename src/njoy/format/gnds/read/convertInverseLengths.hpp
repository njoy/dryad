#ifndef NJOY_FORMAT_GNDS_READ_CONVERTINVERSELENGTHS
#define NJOY_FORMAT_GNDS_READ_CONVERTINVERSELENGTHS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Convert an inverse length range from GNDS into Angstrom
   *
   *  @param[in] values   the values to convert
   *  @param[in] unit     the unit of the values
   */
  inline void convertInverseLengths( std::vector< double >& /* values */, const std::string& unit ) {

    if ( unit != "1/Ang" ) {

      Log::error( "Cannot convert energy with unit \'{}\' to 1/Ang, "
                  "contact njoy developers", unit );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
