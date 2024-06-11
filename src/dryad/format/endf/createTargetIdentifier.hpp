#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETARGETID
#define NJOY_DRYAD_FORMAT_ENDF_CREATETARGETID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the target identifier
   */
  ParticleID createTargetIdentifier( int za, int level ) {

    return std::to_string( za ) + "_e" + std::to_string( level );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif