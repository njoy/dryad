#ifndef NJOY_DRYAD_FORMAT_ACE_CREATEPROJECTILEIDENTIFIER
#define NJOY_DRYAD_FORMAT_ACE_CREATEPROJECTILEIDENTIFIER

// system includes
#include <algorithm>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a projectile identifier from a zaid
   *
   *  This function cannot be used for atomic data
   *
   *  @param[in] zaid   the target zaid name
   */
  inline id::ParticleID createProjectileIdentifier( const std::string& zaid ) {

    switch ( zaid.back() ) {

      case 'u' : return id::ParticleID::photon();
      case 'c' : return id::ParticleID::neutron();
      case 'h' : return id::ParticleID::proton();
      case 'o' : return id::ParticleID::deuteron();
      case 'r' : return id::ParticleID::triton();
      case 's' : return id::ParticleID::helion();
      case 'a' : return id::ParticleID::alpha();
      default: {

        Log::error( "The zaid \'{}\' does not defined incident particle data", zaid );
        throw std::exception();
      }
    }
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
