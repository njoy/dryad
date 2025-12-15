#ifndef NJOY_DRYAD_FORMAT_ACE_CREATETARGETIDENTIFIER
#define NJOY_DRYAD_FORMAT_ACE_CREATETARGETIDENTIFIER

// system includes
#include <algorithm>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a target identifier from a zaid
   *
   *  @param[in] zaid   the target zaid name
   */
  inline id::ParticleID createTargetIdentifier( const std::string& zaid ) {

    int number = std::stoi( std::string( zaid.begin(), std::find( zaid.begin(), zaid.end(), '.' ) ) );
    id::ElementID element( std::round( number / 1000 ) );
    int mass = number%1000;
    return id::ParticleID( std::move( element ), mass, id::LevelID( 0 ) );
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
