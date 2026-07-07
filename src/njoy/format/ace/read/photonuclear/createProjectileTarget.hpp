#ifndef NJOY_FORMAT_ACE_READ_PHOTONUCLEAR_CREATEPROJECTILETARGET
#define NJOY_FORMAT_ACE_READ_PHOTONUCLEAR_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/format/ace/read/createTargetIdentifier.hpp"
#include "njoy/format/ace/read/photonuclear/createReactions.hpp"
#include "njoy/format/ace/read/createParticleDatabase.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace photonuclear {

  /**
   *  @brief Create a ProjectileTarget for photonuclear data
   *
   *  @param[in] table       the ace table
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline dryad::ProjectileTarget
  createProjectileTarget( const ACEtk::PhotonuclearTable& table, bool normalise ) {

    auto projectile = dryad::id::ParticleID::photon();
    auto target = dryad::id::ParticleID::nuclide( table.Z() * 1000 + table.A(), table.S() );
    auto reactions = createReactions( projectile, target, table, normalise );
    auto particles = createParticleDatabase( target, reactions, table );

    return dryad::ProjectileTarget( projectile,
                                    target,
                                    dryad::InteractionType::Nuclear,
                                    std::move( reactions ),
                                    std::move( particles ) );
  }

} // photonuclear namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
