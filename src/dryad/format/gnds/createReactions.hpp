#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createReaction.hpp"
#include "dryad/Reaction.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create every Reaction from a GNDS reaction suite
   */
  static std::vector< Reaction >
  createReactions( const id::ParticleID& projectile, const id::ParticleID& target,
                   pugi::xml_node suite, const std::string& style = "eval" ) {

    // check that this is a valid reaction node
    throwExceptionOnWrongNode( suite, "reactionSuite" );

    std::vector< Reaction > reactions;

    // get the children that contain the reaction data
    // there are primary reactions, summation reactions and incomplete reactions
    //! @todo there also are production reactions (e.g. MT3)
    pugi::xml_node primaries = suite.child( "reactions" );
    pugi::xml_node sums = suite.child( "sums" ).child( "crossSectionSums" );
    pugi::xml_node incomplete = suite.child( "incompleteReactions" );

    // treat primaries
    if ( primaries ) {

      // loop over reaction nodes
      for ( pugi::xml_node reaction = primaries.child( "reaction" );
            reaction; reaction = reaction.next_sibling( "reaction" ) ) {

        Log::info( "Reading data for MT{}", reaction.attribute( "ENDF_MT" ).as_string() );
        reactions.emplace_back( createReaction( projectile, target, suite, reaction, style ) );
      }
    }

    // treat summation
    if ( sums ) {

      // loop over crossSectionSum nodes
      for ( pugi::xml_node reaction = sums.child( "crossSectionSum" );
            reaction; reaction = reaction.next_sibling( "crossSectionSum" ) ) {

        Log::info( "Reading data for MT{}", reaction.attribute( "ENDF_MT" ).as_string() );
        reactions.emplace_back( createReaction( projectile, target, suite, reaction, style ) );
      }
    }

    // treat incomplete reactions
    if ( incomplete ) {

      // loop over reaction nodes
     for ( pugi::xml_node reaction = incomplete.child( "reaction" );
            reaction; reaction = reaction.next_sibling( "reaction" ) ) {

        Log::info( "Reading data for MT{}", reaction.attribute( "ENDF_MT" ).as_string() );
        reactions.emplace_back( createReaction( projectile, target, suite, reaction ) );
      }
    }

    // sort by MT
    std::sort( reactions.begin(), reactions.end(),
               [] ( auto&& left, auto&&right )
                  { return std::stoi( left.identifier() ) <
                           std::stoi( right.identifier() ); } );

    // calculate deficit reaction for elastic scattering in electro-atomic data
    if ( projectile == id::ParticleID( "e-" ) ) {

      auto total = std::find_if( reactions.begin(), reactions.end(),
                                 [] ( const auto& reaction )
                                    { return reaction.identifier() == id::ReactionID( "501" ); } );
      auto partial = std::find_if( reactions.begin(), reactions.end(),
                                   [] ( const auto& reaction )
                                      { return reaction.identifier() == id::ReactionID( "525" ); } );
      TabulatedCrossSection deficit = total->crossSection().linearise();
      deficit -= partial->crossSection().linearise();

      reactions.emplace_back( Reaction( "-526", deficit, {}, std::nullopt, 0. ) );
    }

    return reactions;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
