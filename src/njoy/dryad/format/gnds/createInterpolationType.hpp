#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEINTERPOLATIONTYPE
#define NJOY_DRYAD_FORMAT_GNDS_CREATEINTERPOLATIONTYPE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/type-aliases.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create the interpolation type from a GNDS string value
   */
  static InterpolationType createInterpolationType( const std::string& type ) {

    // when no interpolation type is given, assume lin-lin
    if ( type == "" || type == "lin-lin" ) {

      return InterpolationType::LinearLinear;
    }
    else if ( type == "flat" ) {

      return InterpolationType::Histogram;
    }
    else if ( type == "log-log" ) {

      return InterpolationType::LogLog;
    }
    else if ( type == "lin-log" ) {

      return InterpolationType::LinearLog;
    }
    else if ( type == "log-lin" ) {

      return InterpolationType::LogLinear;
    }
    else {

      Log::error( "GNDS interpolation type \'{}\' is not recognised", type );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
