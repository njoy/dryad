#ifndef NJOY_FORMAT_ACE_READ_CONTINUOUS_CREATEREACTIONS
#define NJOY_FORMAT_ACE_READ_CONTINUOUS_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "njoy/format/ace/read/continuous/createReaction.hpp"
#include "njoy/format/ace/read/continuous/createElasticTabulatedCrossSection.hpp"
#include "njoy/format/ace/read/continuous/createTotalTabulatedCrossSection.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace continuous {

  /**
   *  @brief Create the reactions for continuous energy data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  inline std::vector< dryad::Reaction >
  createReactions( const dryad::id::ParticleID& projectile,
                   const dryad::id::ParticleID& target,
                   const ACEtk::ContinuousEnergyTable& table,
                   bool normalise ) {

    std::vector< dryad::Reaction > reactions;
    std::vector< dryad::id::ReactionID > identifiers;

    // reactions are ordered in an ACE file:
    // - first all primary reactions
    // - some derived data
    // - potential summations like MT3 and MT4 for production or ptables

    // the max index (one-based) for what should be primary reactions
    auto isDerivedOrAuxiliary = [] ( auto&& mt ) {

      return endf::ReactionInformation::isDerived( mt ) || ( mt == 3 ) || ( mt == 4 );
    };
    std::size_t max = std::distance( table.reactionNumberBlock().reactionNumbers().begin(),
                                     std::find_if( table.reactionNumberBlock().reactionNumbers().begin(),
                                                   table.reactionNumberBlock().reactionNumbers().end(),
                                                   isDerivedOrAuxiliary ) ) + 1;

    // elastic scattering
    Log::info( "Reading data for MT2" );
    reactions.emplace_back( dryad::id::ReactionID( projectile, target, 2 ),
                            createElasticTabulatedCrossSection( table ),
                            std::vector< dryad::ReactionProduct >{},
                            std::nullopt, std::make_optional( 0. ),
                            normalise );
    identifiers.emplace_back( reactions.back().identifier() );

    // all primary reactions
    for ( std::size_t index = 1; index < max; ++index ) {

      reactions.emplace_back( createReaction( projectile, target, table, index, normalise ) );
      identifiers.emplace_back( reactions.back().identifier() );
    }

    // add the total reaction
    Log::info( "Reading data for MT1" );
    reactions.emplace( reactions.begin(),
                       dryad::id::ReactionID( projectile, target, 1 ),
                       std::move( identifiers ),
                       createTotalTabulatedCrossSection( table ) );

    // all derived or auxiliary reactions
    for ( std::size_t index = max; index < table.reactionNumberBlock().numberReactions(); ++index ) {

      auto mt = table.reactionNumberBlock().reactionNumber( index );
      Log::warning( "Skipping data for derived or auxiliary MT{}", mt );
    }

    return reactions;
  }

} // continuous namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
