#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTONUCLEAR_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_ACE_PHOTONUCLEAR_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photonuclear {

  /**
   *  @brief Create the reactions for photonuclear data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   */
  inline std::vector< Reaction >
  createReactions( const id::ParticleID& projectile,
                   const id::ParticleID& target,
                   const ACEtk::PhotonuclearTable& table ) {

    std::vector< Reaction > reactions;

    return reactions;
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
