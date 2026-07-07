#ifndef NJOY_FORMAT_GNDS_READ_CREATEREACTIONS
#define NJOY_FORMAT_GNDS_READ_CREATEREACTIONS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/gnds/read/createReaction.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create every Reaction from a GNDS reaction suite
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] suite        the gnds xml reaction suite
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   *  @param[in] style        the gnds style to process (default is eval)
   */
  inline std::vector< dryad::Reaction >
  createReactions( const dryad::id::ParticleID& projectile,
                   const dryad::id::ParticleID& target,
                   pugi::xml_node suite, bool normalise,
                   const std::string& style = "eval" ) {

    // check that this is a valid reaction node
    throwExceptionOnWrongNode( suite, "reactionSuite" );

    std::vector< dryad::Reaction > reactions;

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

        reactions.emplace_back( createReaction( projectile, target, suite, reaction, normalise, style ) );
      }
    }

    // treat summation
    if ( sums ) {

      // loop over crossSectionSum nodes
      for ( pugi::xml_node reaction = sums.child( "crossSectionSum" );
            reaction; reaction = reaction.next_sibling( "crossSectionSum" ) ) {

        Log::info( "Reading data for MT{}", reaction.attribute( "ENDF_MT" ).as_string() );
        reactions.emplace_back( createReaction( projectile, target, suite, reaction, normalise, style ) );
      }
    }

    // treat incomplete reactions
    if ( incomplete ) {

      // loop over reaction nodes
     for ( pugi::xml_node reaction = incomplete.child( "reaction" );
           reaction; reaction = reaction.next_sibling( "reaction" ) ) {

        int mt = reaction.attribute( "ENDF_MT" ).as_int();
        if ( ( mt < 203 ) || ( mt > 207 ) ) {

          reactions.emplace_back( createReaction( projectile, target, suite, reaction, normalise ) );
        }
        else {

          //! @todo read production cross sections
        }
      }
    }

    // sort by MT
    std::sort( reactions.begin(), reactions.end(),
               [] ( auto&& left, auto&&right )
                  { return left.identifier().reactionType().mt()
                           < right.identifier().reactionType().mt(); } );

    // calculate deficit reaction for elastic scattering in electro-atomic data
    if ( projectile ==  dryad::id::ParticleID::electron() ) {

        auto total = std::find_if( reactions.begin(), reactions.end(),
                                   [] ( const auto& reaction )
                                      { return reaction.identifier().reactionType()
                                               ==  dryad::id::ReactionType( "total-scattering" ); } );
        auto partial = std::find_if( reactions.begin(), reactions.end(),
                                     [] ( const auto& reaction )
                                        { return reaction.identifier().reactionType()
                                                 ==  dryad::id::ReactionType( "large-angle-scattering" ); } );
      dryad::TabulatedCrossSection deficit = total->crossSection().linearise();
      deficit -= partial->crossSection().linearise();

      reactions.emplace_back( dryad::Reaction( dryad::id::ReactionID( projectile, target,
                                                                      dryad::id::ReactionType( "deficit-scattering" ) ),
                                               deficit, {}, std::nullopt, 0. ) );
    }

    return reactions;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
