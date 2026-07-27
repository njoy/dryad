#ifndef NJOY_FORMAT_GNDS_READ_CREATEPARTICLEIDENTIFIER
#define NJOY_FORMAT_GNDS_READ_CREATEPARTICLEIDENTIFIER

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create the particle identifier
   *
   *  @param[in] str   the particle identifier string
   */
  inline dryad::id::ParticleID createParticleIdentifier( const char* str ) {

    std::string pid( str );
    if ( pid == "photon" ) {

      pid = "g";
    }
    return dryad::id::ParticleID( pid );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
