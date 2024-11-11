#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREFERENCEFRAME
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREFERENCEFRAME

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ReferenceFrame.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create the reference frame
   */
  static ReferenceFrame createReferenceFrame( const std::string& frame ) {

    if ( frame == "lab" ) {

      return ReferenceFrame::Laboratory;
    }
    else if ( frame == "centerOfMass" ) {

      return ReferenceFrame::CentreOfMass;
    }
    else {

      Log::error( "GNDS product frame \'{}\' is not recognised", frame );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
