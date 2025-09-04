#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTION
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/convertEnergy.hpp"
#include "dryad/format/gnds/createQValue.hpp"
#include "dryad/format/gnds/createReactionProducts.hpp"
#include "dryad/format/gnds/createTabulatedCrossSection.hpp"
#include "dryad/Reaction.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a Reaction from GNDS node (reaction or crossSectionSum)
   */
  static Reaction
  createReaction( const id::ParticleID& projectile, const id::ParticleID& target,
                  pugi::xml_node suite, pugi::xml_node reaction,
                  bool normalise,
                  const std::string& style = "eval" ) {

    if ( strcmp( reaction.name(), "reaction" ) == 0 ) {

      // metadata and miscellaneous information
      id::ReactionType type( projectile, reaction.attribute( "ENDF_MT" ).as_int(), target.e() );
      id::ReactionID id( projectile, target, type );

      // cross section
      auto section = reaction.child( "crossSection" );
      TabulatedCrossSection xs = createTabulatedCrossSection( section, style );

      // Q values
      auto output = reaction.child( "outputChannel" );
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = createQValue( output.child( "Q" ), style );

      // reaction products
      std::vector< ReactionProduct > products;
      auto node = output.child( "products" );
      if ( node ) {

        products = createReactionProducts( projectile, target, suite, node, normalise );
      }

      // special treatment for some incident electron data reactions
      if ( projectile == id::ParticleID::electron() ) {

        if ( id.reactionType() == id::ReactionType( projectile, 526 ) ) {

          // GNDS classifies total elastic as a primary reaction
          // but we classify it as a summation with a deficit reaction
          std::vector< id::ReactionID > partials = { id::ReactionID( projectile, target, id::ReactionType( projectile, 525 ) ),
                                                     id::ReactionID( projectile, target, id::ReactionType( "deficit-scattering" ) ) };

          // return the reaction data
          return Reaction( std::move( id ), std::move( partials ), std::move( xs ) );
        }
      }

      // return the reaction data
      return Reaction( std::move( id ), std::move( xs ),
                       std::move( products ), std::move( mass_q ),
                       std::move( reaction_q ) );
    }
    else if ( strcmp( reaction.name(), "crossSectionSum" ) == 0 ) {

      // metadata and miscellaneous information
      id::ReactionID id( projectile, target, id::ReactionType( projectile, reaction.attribute( "ENDF_MT" ).as_int() ) );

      // Q values
      auto qvalue = reaction.child( "Q" );
      if ( qvalue ) {

        Log::info( "Ignoring reaction Q value for summation reaction" );
      }

      // partial identifiers
      std::vector< id::ReactionID > partials;
      auto summands = reaction.child( "summands" );
      for ( pugi::xml_node partial = summands.child( "add" );
            partial; partial = partial.next_sibling( "add" ) ) {

        std::string href = partial.attribute( "href" ).as_string();
        auto start = href.find( '\'' ) + 1;
        auto end = href.find( '\'', start );
        href = href.substr( start, end - start );
        int mt = suite.child( "reactions" ).find_child_by_attribute( "reaction", "label", href.c_str() ).attribute( "ENDF_MT" ).as_int();
        partials.emplace_back( projectile, target, id::ReactionType( projectile, mt ) );
      }

      // special treatment for some incident electron data reactions
      if ( projectile == id::ParticleID( "e-" ) ) {

        if ( id == id::ReactionID( projectile, target, id::ReactionType( projectile, 501 ) ) ) {

          // replace 526 by 525 and -526
          auto total_elastic = id::ReactionID( projectile, target, id::ReactionType( projectile, 526 ) );
          auto iter = std::find( partials.begin(), partials.end(), total_elastic );
          *iter = id::ReactionID( projectile, target, id::ReactionType( projectile, 525 ) );
          partials.insert( iter + 1, id::ReactionID( projectile, target, id::ReactionType( "deficit-scattering" ) ) );
        }
      }

      // cross section
      auto section = reaction.child( "crossSection" );
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // return the reaction data
      return Reaction( std::move( id ), std::move( partials ), std::move( xs ), {} );
    }
    else {

      Log::error( "The GNDS node named \'{}\' does not have reaction data", reaction.name() );
      throw std::exception();
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
