#ifndef NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPPROJECTILETARGET
#define NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPPROJECTILETARGET

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InteractionType.hpp"
#include "njoy/dryad/MultigroupProjectileTarget.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/ndi/read/createMultigroupReactions.hpp"
#include "NDItk/MultigroupLibrary.hpp"

namespace njoy {
namespace format {
namespace ndi {
namespace read {

  //! @todo can we determine projectile and target from the table itself?

  /**
   *  @brief Create a MultigroupProjectileTarget from an NDI table
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the NDI multigroup table
   */
  inline dryad::MultigroupProjectileTarget
  createMultigroupProjectileTarget( const dryad::id::ParticleID& projectile,
                                    const dryad::id::ParticleID& target,
                                    const NDItk::MultigroupTable& table ) {

    // function to convert MeV to eV
    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::mega;
    };

    std::vector< double > boundaries = createVector( table.primaryGroupBoundaries() );
    std::reverse( boundaries.begin(), boundaries.end() );
    std::transform( boundaries.begin(), boundaries.end(), boundaries.begin(), convertEnergy );

    // interaction type
    dryad::InteractionType type = dryad::InteractionType::Nuclear;

    // reaction data
    std::vector< dryad::MultigroupReaction > reactions =
    createMultigroupReactions( projectile, target, table, boundaries );

    return dryad::MultigroupProjectileTarget( projectile, target, type,
                                              std::move( reactions ) );
  }

} // read namespace
} // ndi namespace
} // format namespace
} // njoy namespace

#endif
