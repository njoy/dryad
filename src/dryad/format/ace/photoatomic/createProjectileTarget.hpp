#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "dryad/format/ace/createTargetIdentifier.hpp"
#include "dryad/format/ace/photoatomic/createReactions.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create a ProjectileTarget for photoatomic data
   */
  ProjectileTarget createProjectileTarget( const ACEtk::PhotoatomicTable& table ) {

    auto projectile = id::ParticleID::photon();
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
