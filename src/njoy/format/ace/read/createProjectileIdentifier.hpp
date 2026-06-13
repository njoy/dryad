#ifndef NJOY_FORMAT_ACE_READ_CREATEPROJECTILEIDENTIFIER
#define NJOY_FORMAT_ACE_READ_CREATEPROJECTILEIDENTIFIER

// system includes
#include <algorithm>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

  /**
   *  @brief Create a projectile identifier from a zaid
   *
   *  This function cannot be used for atomic data
   *
   *  @param[in] zaid   the target zaid name
   */
  inline dryad::id::ParticleID createProjectileIdentifier( const std::string& zaid ) {

    switch ( zaid.back() ) {

      case 'u' : return dryad::id::ParticleID::photon();
      case 'c' : return dryad::id::ParticleID::neutron();
      case 'h' : return dryad::id::ParticleID::proton();
      case 'o' : return dryad::id::ParticleID::deuteron();
      case 'r' : return dryad::id::ParticleID::triton();
      case 's' : return dryad::id::ParticleID::helion();
      case 'a' : return dryad::id::ParticleID::alpha();
      default: {

        Log::error( "The zaid \'{}\' does not defined incident particle data", zaid );
        throw std::exception();
      }
    }
  }

} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
