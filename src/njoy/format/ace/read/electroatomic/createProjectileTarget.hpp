#ifndef NJOY_FORMAT_ACE_READ_ELECTROATOMIC_CREATEPROJECTILETARGET
#define NJOY_FORMAT_ACE_READ_ELECTROATOMIC_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/format/ace/read/createTargetIdentifier.hpp"
#include "njoy/format/ace/read/electroatomic/createReactions.hpp"
#include "njoy/format/ace/read/createParticleDatabase.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace electroatomic {

  /**
   *  @brief Create a ProjectileTarget for electroatomic data
   *
   *  @param[in] table       the ace table
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline dryad::ProjectileTarget
  createProjectileTarget( const ACEtk::PhotoatomicTable& table, bool /* normalise */ ) {

    auto projectile = dryad::id::ParticleID::electron();
    auto target = createTargetIdentifier( table.ZAID() );
    auto reactions = createReactions( projectile, target, table );
    auto particles = createParticleDatabase( target, reactions, table );

    return dryad::ProjectileTarget( projectile,
                                    target,
                                    dryad::InteractionType::Atomic,
                                    std::move( reactions ),
                                    std::move( particles ) );
  }

} // electroatomic namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
