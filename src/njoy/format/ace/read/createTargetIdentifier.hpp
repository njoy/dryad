#ifndef NJOY_FORMAT_ACE_READ_CREATETARGETIDENTIFIER
#define NJOY_FORMAT_ACE_READ_CREATETARGETIDENTIFIER

// system includes
#include <algorithm>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

  /**
   *  @brief Create a target identifier from a zaid
   *
   *  @param[in] zaid   the target zaid name
   */
  inline dryad::id::ParticleID createTargetIdentifier( const std::string& zaid ) {

    int number = std::stoi( std::string( zaid.begin(), std::find( zaid.begin(), zaid.end(), '.' ) ) );
    dryad::id::ElementID element( std::round( number / 1000 ) );
    int mass = number%1000;
    return dryad::id::ParticleID( std::move( element ), mass, dryad::id::LevelID( 0 ) );
  }

} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
