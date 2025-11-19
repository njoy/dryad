#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTONUCLEAR_CREATEREACTION
#define NJOY_DRYAD_FORMAT_ACE_PHOTONUCLEAR_CREATEREACTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/format/endf/ReactionInformation.hpp"
#include "njoy/dryad/format/ace/continuous/createTabulatedCrossSection.hpp"
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
   *  @param[in] index        the reaction index in the ACE file
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  inline Reaction
  createReaction( const id::ParticleID& projectile,
                  const id::ParticleID& target,
                  const ACEtk::PhotonuclearTable& table,
                  std::size_t index,
                  bool normalise ) {

    id::ReactionID id( projectile, target, table.reactionNumberBlock().reactionNumber( index ) );
    auto xs = continuous::createTabulatedCrossSection( table, index );

    return Reaction( std::move( id ), std::move( xs ) );
  }

} // photonuclear namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
