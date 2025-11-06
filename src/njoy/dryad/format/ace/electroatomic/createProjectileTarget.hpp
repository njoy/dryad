#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "dryad/format/ace/createTargetIdentifier.hpp"
#include "dryad/format/ace/electroatomic/createReactions.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create a ProjectileTarget for electroatomic data
   *
   *  @param[in] table   the ace table
   */
  ProjectileTarget createProjectileTarget( const ACEtk::PhotoatomicTable& table ) {

    auto projectile = id::ParticleID::electron();
    auto target = createTargetIdentifier( table.ZAID() );
    return ProjectileTarget( projectile,
                             target,
                             InteractionType::Atomic,
                             createReactions( projectile, target, table ) );
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
