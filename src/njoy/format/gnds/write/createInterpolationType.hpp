#ifndef NJOY_FORMAT_GNDS_WRITE_CREATEINTERPOLATIONTYPE
#define NJOY_FORMAT_GNDS_WRITE_CREATEINTERPOLATIONTYPE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InterpolationType.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Create the interpolation string from a dryad interpolation enum
   *
   *  @param[in] type   the interpolation type
   */
  inline std::string createInterpolationType( const dryad::InterpolationType& type ) {

    switch ( type ) {

      case dryad::InterpolationType::Histogram    : return "flat";
      case dryad::InterpolationType::LinearLinear : return "lin-lin";
      case dryad::InterpolationType::LinearLog    : return "lin-log";
      case dryad::InterpolationType::LogLinear    : return "log-lin";
      case dryad::InterpolationType::LogLog       : return "log-log";
      default : {

        throw std::runtime_error( "You have somehow reached unreachable code, "
                                  "contact an njoy developer to claim your prize - "
                                  "no prizes are guaranteed." );
      }
    }
  }

} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
