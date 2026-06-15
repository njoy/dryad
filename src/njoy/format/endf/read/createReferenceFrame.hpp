#ifndef NJOY_FORMAT_ENDF_READ_CREATEREFERENCEFRAME
#define NJOY_FORMAT_ENDF_READ_CREATEREFERENCEFRAME

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a reference frame from an ENDF reference frame value
   */
  inline dryad::ReferenceFrame createReferenceFrame( int lct ) {

    switch ( lct ) {

      case 1 : return dryad::ReferenceFrame::Laboratory;
      case 2 : return dryad::ReferenceFrame::CentreOfMass;
      default : {

        Log::error( "Cannot convert or handle ENDF reference frame value {}", lct );
        throw std::exception();
      }
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
