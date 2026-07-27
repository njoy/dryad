#ifndef NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATEREACTIONS
#define NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/ace/read/photoatomic/createReactionIdentifiers.hpp"
#include "njoy/format/ace/read/photoatomic/createPartialReactionIdentifiers.hpp"
#include "njoy/format/ace/read/photoatomic/createTabulatedCrossSections.hpp"
#include "njoy/format/ace/read/photoatomic/createReactionProducts.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace photoatomic {

  /**
   *  @brief Create the reactions for photoatomic data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   */
  inline std::vector< dryad::Reaction >
  createReactions( const dryad::id::ParticleID& projectile,
                   const dryad::id::ParticleID& target,
                   const ACEtk::PhotoatomicTable& table ) {

    std::vector< dryad::Reaction > reactions;

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
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
