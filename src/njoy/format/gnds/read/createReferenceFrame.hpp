#ifndef NJOY_FORMAT_GNDS_READ_CREATEREFERENCEFRAME
#define NJOY_FORMAT_GNDS_READ_CREATEREFERENCEFRAME

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create the reference frame from a GNDS string
   *
   *  @param[in] frame   the reference frame string
   */
  inline dryad::ReferenceFrame createReferenceFrame( const std::string& frame ) {

    if ( frame == "lab" ) {

      return dryad::ReferenceFrame::Laboratory;
    }
    else if ( frame == "centerOfMass" ) {

      return dryad::ReferenceFrame::CentreOfMass;
    }
    else {

      Log::error( "GNDS product frame \'{}\' is not recognised", frame );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
