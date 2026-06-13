#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREFERENCEFRAME
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREFERENCEFRAME

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a reference frame from an ENDF reference frame value
   */
  inline ReferenceFrame createReferenceFrame( int lct ) {

    switch ( lct ) {

      case 1 : return ReferenceFrame::Laboratory;
      case 2 : return ReferenceFrame::CentreOfMass;
      default : {

        Log::error( "Cannot convert or handle ENDF reference frame value {}", lct );
        throw std::exception();
      }
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
