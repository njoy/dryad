#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILEID
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILEID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the projectile identifier
   */
  ParticleID createParticleID( int sublibrary ) {

    switch ( sublibrary ) {

      case     0 : return ParticleID( "g" );
      case     3 : return ParticleID( "photoatomic" );
      case    10 : return ParticleID( "n" );
      case   113 : return ParticleID( "e" );
      case 10010 : return ParticleID( "p" );
      case 10020 : return ParticleID( "d" );
      case 10030 : return ParticleID( "t" );
      case 20030 : return ParticleID( "he3" );
      case 20040 : return ParticleID( "a" );
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
