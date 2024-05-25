#ifndef NJOY_DRYAD_FORMAT_ENDF_PROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ENDF_PROJECTILETARGET

// system includes
#include <vector>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createReactions.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a ProjectileTarget from an unparsed ENDF material
   */
  ProjectileTarget createProjectileTarget( const ENDFtk::tree::Material& material ) {

    auto mf1mt451 = material.section( 1, 451 ).parse< 1, 451 >();

    // currently incident neutron only
    if ( mf1mt451.subLibrary() == 10 ) {

      ParticleID projectile( "n" );
      ParticleID target = std::to_string( static_cast< int >( mf1mt451.ZA() ) )
                        + "_e" + std::to_string( mf1mt451.excitedLevel() );

      std::vector< Reaction > reactions = createReactions( material );

      return ProjectileTarget( std::move( projectile ), std::move( target ),
                               std::move( reactions ) );
    }
    else {

      Log::error( "ENDF material does not represent a ProjectileTarget" );
      throw std::exception();
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
