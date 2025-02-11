#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/Reaction.hpp"
#include "dryad/format/ace/electroatomic/createReactionNumbers.hpp"
#include "dryad/format/ace/electroatomic/createPartialReactionNumbers.hpp"
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
   */
  std::vector< Reaction > createReactions( const ACEtk::PhotoatomicTable& table ) {

    std::vector< Reaction > reactions;

    auto numbers = createReactionNumbers( table );
    auto partialNumbers = createPartialReactionNumbers( table );
    auto xs = createTabulatedCrossSections( table );
    auto products = createReactionProducts( table );
    auto size = numbers.size();

    for ( std::size_t index = 0; index < size; ++index ) {

      id::ReactionID id( std::to_string( numbers[index] ) );
      if ( partialNumbers[index].size() == 0 ) {

        reactions.emplace_back( std::move( id ), std::move( xs[index] ),
                                std::move( products[index] ) );
      }
      else {

        std::vector< id::ReactionID > partials( partialNumbers[index].size() );
        std::transform( partialNumbers[index].begin(), partialNumbers[index].end(),
                        partials.begin(),
                        [] ( auto&& number ) { return std::to_string( number ); } );

        reactions.emplace_back( std::move( id ), std::move( partials ), std::move( xs[index] ),
                                std::move( products[index] ) );
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
