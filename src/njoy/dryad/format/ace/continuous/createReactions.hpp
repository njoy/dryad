#ifndef NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/format/endf/ReactionInformation.hpp"
#include "njoy/dryad/format/ace/continuous/createReaction.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace continuous {

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
                   const ACEtk::ContinuousEnergyTable& table,
                   bool normalise ) {

    std::vector< Reaction > reactions;

    for ( std::size_t index = 1; index <= table.reactionNumberBlock().numberReactions(); ++index ) {

      // reactions are ordered in an ACE file:
      // - first all primary reactions
      // - some derived data
      // - potentially partials like MT3 and MT4

      auto mt = table.reactionNumberBlock().reactionNumber( index );
      if ( ! endf::ReactionInformation::isDerived( mt ) ) {

        Log::info( "Reading data for MT{}", mt );
        reactions.emplace_back( createReaction( projectile, target, table, index, normalise ) );
      }
      else {

        Log::warning( "Skipping data for derived MT{}", mt );
      }
    }

    return reactions;
  }

} // continuous namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
