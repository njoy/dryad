#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTONUCLEAR_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ACE_PHOTONUCLEAR_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/format/ace/createTargetIdentifier.hpp"
#include "njoy/dryad/format/ace/photonuclear/createReactions.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photonuclear {

  /**
   *  @brief Create a ProjectileTarget for photonuclear data
   *
   *  @param[in] table   the ace table
   */
  inline ProjectileTarget
  createProjectileTarget( const ACEtk::PhotonuclearTable& table ) {

    auto projectile = id::ParticleID::photon();
    auto target = id::ParticleID::nuclide( table.Z() * 1000 + table.A(), table.S() );
    return ProjectileTarget( projectile,
                             target,
                             InteractionType::Nuclear,
                             createReactions( projectile, target, table ) );
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
