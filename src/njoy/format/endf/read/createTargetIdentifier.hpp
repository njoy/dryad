#ifndef NJOY_FORMAT_ENDF_READ_CREATETARGETIDENTIFIER
#define NJOY_FORMAT_ENDF_READ_CREATETARGETIDENTIFIER

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create the target identifier
   *
   *  @param[in] za        the za value
   *  @param[in] level     the level number
   */
  inline dryad::id::ParticleID createTargetIdentifier( int za, int level ) {

    if ( za == 1 ) {

      return dryad::id::ParticleID::neutron();
    }
    else {

      return dryad::id::ParticleID::nuclide( za, level );
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
