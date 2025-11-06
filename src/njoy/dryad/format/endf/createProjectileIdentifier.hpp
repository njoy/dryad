#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILEID
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILEID

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
   *  @brief Create the projectile identifier based of the sublibrary value
   */
  id::ParticleID createProjectileIdentifier( int sublibrary ) {

    switch ( sublibrary ) {

      case     0 : return id::ParticleID::photon();
      case     3 : return id::ParticleID::photon();
      case    10 : return id::ParticleID::neutron();
      case   113 : return id::ParticleID::electron();
      case 10010 : return id::ParticleID::proton();
      case 10020 : return id::ParticleID::deuteron();
      case 10030 : return id::ParticleID::triton();
      case 20030 : return id::ParticleID::helion();
      case 20040 : return id::ParticleID::alpha();
      default : {

        Log::error( "ENDF sublibrary {} does not define projectile-target data",
                    sublibrary );
        throw std::exception();
      }
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
