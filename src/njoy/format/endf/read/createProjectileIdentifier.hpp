#ifndef NJOY_FORMAT_ENDF_READ_CREATEPROJECTILEID
#define NJOY_FORMAT_ENDF_READ_CREATEPROJECTILEID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create the projectile identifier based of the sublibrary value
   */
  inline dryad::id::ParticleID createProjectileIdentifier( int sublibrary ) {

    switch ( sublibrary ) {

      case     0 : return dryad::id::ParticleID::photon();
      case     3 : return dryad::id::ParticleID::photon();
      case    10 : return dryad::id::ParticleID::neutron();
      case   113 : return dryad::id::ParticleID::electron();
      case 10010 : return dryad::id::ParticleID::proton();
      case 10020 : return dryad::id::ParticleID::deuteron();
      case 10030 : return dryad::id::ParticleID::triton();
      case 20030 : return dryad::id::ParticleID::helion();
      case 20040 : return dryad::id::ParticleID::alpha();
      default : {

        Log::error( "ENDF sublibrary {} does not define projectile-target data",
                    sublibrary );
        throw std::exception();
      }
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
