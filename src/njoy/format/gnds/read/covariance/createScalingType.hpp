#ifndef NJOY_FORMAT_GNDS_READ_COVARIANCE_CREATESCALINGTYPE
#define NJOY_FORMAT_GNDS_READ_COVARIANCE_CREATESCALINGTYPE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/ScalingType.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace covariance {

  /**
   *  @brief Create the scaling type from a GNDS string value
   */
  inline dryad::covariance::ScalingType createScalingType( const std::string& type ) {

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
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
