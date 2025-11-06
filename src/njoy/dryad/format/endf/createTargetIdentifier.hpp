#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETARGETID
#define NJOY_DRYAD_FORMAT_ENDF_CREATETARGETID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the target identifier
   */
  id::ParticleID createTargetIdentifier( int za, int level ) {

    return id::ParticleID( za, level );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
