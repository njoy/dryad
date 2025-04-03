#ifndef NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATESCALINGTYPE
#define NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATESCALINGTYPE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/covariance/ScalingType.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace covariance {

  /**
   *  @brief Create the scaling type from a GNDS string value
   */
  static dryad::covariance::ScalingType createScalingType( const std::string& type ) {

    if ( type == "inverse" ) {

      return dryad::covariance::ScalingType::Inverse;
    }
    else if ( type == "direct" ) {

      return dryad::covariance::ScalingType::Direct;
    }
    else {

      Log::error( "GNDS scaling type \'{}\' is not recognised", type );
      throw std::exception();
    }
  }

} // covariance namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
