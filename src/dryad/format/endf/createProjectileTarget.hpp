#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILETARGET

// system includes
#include <vector>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createProjectileIdentifier.hpp"
#include "dryad/format/endf/createTargetIdentifier.hpp"
#include "dryad/format/endf/createInteractionType.hpp"
#include "dryad/format/endf/createReactions.hpp"
#include "dryad/format/endf/createDocumentation.hpp"
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

    auto information = material.section( 1, 451 ).parse< 1, 451 >();

    Documentation documentation = createDocumentation( information );

    id::ParticleID projectile = createProjectileIdentifier( information.subLibrary() );
    id::ParticleID target = createTargetIdentifier( information.ZA(), information.excitedLevel() );
    InteractionType type = createInteractionType( information.subLibrary() );

    std::vector< Reaction > reactions = createReactions( projectile, target, material );

    return ProjectileTarget( std::move( documentation ), std::move( projectile ),
                             std::move( target ), type, std::move( reactions ) );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
