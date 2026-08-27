#ifndef NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPREACTIONS
#define NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPREACTIONS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MultigroupReaction.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/ndi/read/createMultigroupReaction.hpp"
#include "NDItk/MultigroupLibrary.hpp"

namespace njoy {
namespace format {
namespace ndi {
namespace read {

  /**
   *  @brief Create every MultigroupReaction from an NDI table
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the NDI multigroup table
   *  @param[in] boundaries   the energy group boundaries
   */
  inline std::vector< dryad::MultigroupReaction >
  createMultigroupReactions( const dryad::id::ParticleID& projectile,
                             const dryad::id::ParticleID& target,
                             const NDItk::MultigroupTable& table,
                             const std::vector< double >& boundaries ) {

    std::vector< dryad::MultigroupReaction > reactions;
    std::vector< dryad::id::ReactionID > identifiers;

    // get all the reactions
    for ( auto&& entry : table.reactionCrossSections().reactions() ) {

      if ( entry.identifier() < 1000 ) {

        reactions.emplace_back( createMultigroupReaction( projectile, target, table, entry.identifier(), boundaries ) );
        if ( reactions.back().isPrimaryReaction() ) {

          identifiers.emplace_back( reactions.back().identifier() );
        }
      }
      else {

        Log::info( "Skipping metastable production for MT{}", entry.identifier() );
      }
    }

    // add total
    dryad::id::ReactionID total( projectile, target, 1 );
    Log::info( "Reading data for \'{}\' - MT{}", total.symbol(), 1 );
    reactions.emplace( reactions.begin(),
                       total,
                       std::move( identifiers ),
                       createMultigroupCrossSection( boundaries, table.totalCrossSection() ) );

    // sort by MT
    std::sort( reactions.begin(), reactions.end(),
               [] ( auto&& left, auto&&right )
                  { return left.identifier().reactionType().mt()
                           < right.identifier().reactionType().mt(); } );
    reactions.shrink_to_fit();

    return reactions;
  }

} // read namespace
} // ndi namespace
} // format namespace
} // njoy namespace

#endif
