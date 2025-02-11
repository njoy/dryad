#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEPARTICLEID
#define NJOY_DRYAD_FORMAT_GNDS_CREATEPARTICLEID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create the particle identifier
   */
  id::ParticleID createParticleIdentifier( const char* str ) {

    std::string pid( str );
    if ( pid == "photon" ) {

      pid = "g";
    }
    return id::ParticleID( pid );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
