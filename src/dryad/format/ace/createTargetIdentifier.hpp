#ifndef NJOY_DRYAD_FORMAT_ACE_CREATETARGETIDENTIFIER
#define NJOY_DRYAD_FORMAT_ACE_CREATETARGETIDENTIFIER

// system includes
#include <algorithm>

// other includes
#include "dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a target identifier from a zaid
   *
   *  @param[in] zaid   the target zaid name
   */
  id::ParticleID createTargetIdentifier( const std::string& zaid ) {

    std::string za( zaid.begin(), std::find( zaid.begin(), zaid.end(), '.' ) );
    return id::ParticleID( std::stoi( za ) );
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
