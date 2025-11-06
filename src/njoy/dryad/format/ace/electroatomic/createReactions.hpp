#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/Reaction.hpp"
#include "dryad/format/ace/electroatomic/createReactionIdentifiers.hpp"
#include "dryad/format/ace/electroatomic/createPartialReactionIdentifiers.hpp"
#include "dryad/format/ace/electroatomic/createTabulatedCrossSections.hpp"
#include "dryad/format/ace/electroatomic/createReactionProducts.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create the reactions for electroatomic data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   */
  std::vector< Reaction > createReactions( const id::ParticleID& projectile,
                                           const id::ParticleID& target,
                                           const ACEtk::PhotoatomicTable& table ) {

    std::vector< Reaction > reactions;

    auto identifiers = createReactionIdentifiers( projectile, target, table );
    auto partialIdentifiers = createPartialReactionIdentifiers( projectile, target, table );
    auto xs = createTabulatedCrossSections( table );
    auto products = createReactionProducts( table );
    auto size = identifiers.size();

    for ( std::size_t index = 0; index < size; ++index ) {

      if ( partialIdentifiers[index].size() == 0 ) {

        reactions.emplace_back( std::move( identifiers[index] ), std::move( xs[index] ),
                                std::move( products[index] ) );
      }
      else {

        reactions.emplace_back( std::move( identifiers[index] ), std::move( partialIdentifiers[index] ),
                                std::move( xs[index] ), std::move( products[index] ) );
      }
    }

    return reactions;
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
