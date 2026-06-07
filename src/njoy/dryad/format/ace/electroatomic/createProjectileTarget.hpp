#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/format/ace/createTargetIdentifier.hpp"
#include "njoy/dryad/format/ace/createParticleDatabase.hpp"
#include "njoy/dryad/format/ace/electroatomic/createReactions.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create a ProjectileTarget for electroatomic data
   *
   *  @param[in] table       the ace table
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline ProjectileTarget
  createProjectileTarget( const ACEtk::PhotoatomicTable& table, bool /* normalise */ ) {

    auto projectile = id::ParticleID::electron();
    auto target = createTargetIdentifier( table.ZAID() );
    auto particles = createParticleDatabase( projectile, target, table );
    return ProjectileTarget( projectile,
                             target,
                             InteractionType::Atomic,
                             createReactions( projectile, target, table ),
                             std::move( particles ) );
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
