#ifndef NJOY_FORMAT_GNDS_READ_CREATEINTERPOLATIONTYPE
#define NJOY_FORMAT_GNDS_READ_CREATEINTERPOLATIONTYPE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InterpolationType.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create the interpolation type from a GNDS string value
   */
  inline dryad::InterpolationType createInterpolationType( const std::string& type ) {

    // when no interpolation type is given, assume lin-lin
    if ( type == "" || type == "lin-lin" ) {

      return dryad::InterpolationType::LinearLinear;
    }
    else if ( type == "flat" ) {

      return dryad::InterpolationType::Histogram;
    }
    else if ( type == "log-log" ) {

      return dryad::InterpolationType::LogLog;
    }
    else if ( type == "lin-log" ) {

      return dryad::InterpolationType::LinearLog;
    }
    else if ( type == "log-lin" ) {

      return dryad::InterpolationType::LogLinear;
    }
    else {

      Log::error( "GNDS interpolation type \'{}\' is not recognised", type );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
