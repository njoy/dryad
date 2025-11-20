#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTONUCLEAR_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_ACE_PHOTONUCLEAR_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/format/endf/ReactionInformation.hpp"
#include "njoy/dryad/format/ace/photonuclear/createReaction.hpp"
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
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  inline std::vector< Reaction >
  createReactions( const id::ParticleID& projectile,
                   const id::ParticleID& target,
                   const ACEtk::PhotonuclearTable& table,
                   bool normalise ) {

    std::vector< Reaction > reactions;

    // reactions are ordered in an ACE file:
    // - first all primary reactions
    // - some derived data
    // - potential summations like MT3 and MT4 for production or ptables

    // the max index for what should be primary reactions
    auto isDerivedOrAuxiliary = [] ( auto&& mt ) {

      return endf::ReactionInformation::isDerived( mt ) || ( mt == 3 ) || ( mt == 4 );
    };
    auto max = std::distance( table.reactionNumberBlock().reactionNumbers().begin(),
                              std::find_if( table.reactionNumberBlock().reactionNumbers().begin(),
                                            table.reactionNumberBlock().reactionNumbers().end(),
                                            isDerivedOrAuxiliary ) );

    // all primary reactions
    for ( std::size_t index = 1; index < max; ++index ) {

      reactions.emplace_back( createReaction( projectile, target, table, index, normalise ) );
    }

    // all derived or auxiliary reactions
    for ( std::size_t index = max; index < table.reactionNumberBlock().numberReactions(); ++index ) {

      auto mt = table.reactionNumberBlock().reactionNumber( index );
      Log::warning( "Skipping data for derived or auxiliary MT{}", mt );
    }

    return reactions;
  }

} // photonuclear namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
