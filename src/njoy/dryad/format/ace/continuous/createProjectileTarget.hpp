#ifndef NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/format/ace/createTargetIdentifier.hpp"
#include "njoy/dryad/format/ace/createProjectileIdentifier.hpp"
#include "njoy/dryad/format/ace/createParticles.hpp"
#include "njoy/dryad/format/ace/continuous/createReactions.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace continuous {

  /**
   *  @brief Create a ProjectileTarget for photonuclear data
   *
   *  @param[in] table       the ace table
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline ProjectileTarget
  createProjectileTarget( const ACEtk::ContinuousEnergyTable& table, bool normalise ) {

    auto projectile = createProjectileIdentifier( table.ZAID() );
    auto target = id::ParticleID::nuclide( table.Z() * 1000 + table.A(), table.S() );
    auto particles = createParticles( projectile, target, table );
    auto reactions = createReactions( projectile, target, table, normalise );

    return ProjectileTarget( projectile,
                             target,
                             InteractionType::Nuclear,
                             std::move( reactions ),
                             ParticleDatabase( std::move( particles ) ) );
  }

} // continuous namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
