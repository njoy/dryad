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

      case     0 : return id::ParticleID( "g" );
      case     3 : return id::ParticleID( "g" );
      case    10 : return id::ParticleID( "n" );
      case   113 : return id::ParticleID( "e-" );
      case 10010 : return id::ParticleID( "p" );
      case 10020 : return id::ParticleID( "d" );
      case 10030 : return id::ParticleID( "t" );
      case 20030 : return id::ParticleID( "he3" );
      case 20040 : return id::ParticleID( "a" );
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
