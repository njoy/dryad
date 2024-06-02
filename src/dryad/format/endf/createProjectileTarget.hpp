#ifndef NJOY_DRYAD_FORMAT_ENDF_PROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ENDF_PROJECTILETARGET

// system includes
#include <vector>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createParticleID.hpp"
#include "dryad/format/endf/createInteractionType.hpp"
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

    ParticleID projectile = createParticleID( mf1mt451.subLibrary() );
    ParticleID target = std::to_string( static_cast< int >( mf1mt451.ZA() ) )
                      + "_e" + std::to_string( mf1mt451.excitedLevel() );

    InteractionType type = createInteractionType( mf1mt451.subLibrary() );

    std::vector< Reaction > reactions = createReactions( material );

    return ProjectileTarget( std::move( projectile ), std::move( target ),
                             type, std::move( reactions ) );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
