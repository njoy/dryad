#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTION
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/convertEnergy.hpp"
#include "dryad/format/gnds/readConstant1d.hpp"
#include "dryad/format/gnds/createReactionProducts.hpp"
#include "dryad/format/gnds/createTabulatedCrossSection.hpp"
#include "dryad/Reaction.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a Reaction from an unparsed ENDF material
   */
  Reaction createReaction( const id::ParticleID& projectile, const id::ParticleID& target,
                           pugi::xml_node suite, pugi::xml_node reaction ) {

    if ( strcmp( reaction.name(), "reaction" ) == 0 ) {

      // metadata and miscellaneous information
      id::ReactionID id = reaction.attribute( "ENDF_MT" ).as_string();

      // cross section
      auto section = reaction.child( "crossSection" );
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // Q values
      auto output = reaction.child( "outputChannel" );
      auto q = readConstant1d( output.child( "Q" ).child( "constant1d" ) );
      convertEnergy( q.first, q.second );
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = q.first;

      // reaction products
      std::vector< ReactionProduct > products = 
      createReactionProducts( projectile, target, suite, output.child( "products" ) );

      // special treatment for some incident electron data reactions
      if ( projectile == id::ParticleID( "e-" ) ) {

        if ( id == id::ReactionID( "526" ) ) {

          // GNDS classifies total elastic as a primary reaction
          // but we classify it as a summation with a deficit reaction
          std::vector< id::ReactionID > partials = { "525", "-526" };

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
      id::ReactionID id = reaction.attribute( "ENDF_MT" ).as_string();

      // partial identifiers
      std::vector< id::ReactionID > partials;
      auto summands = reaction.child( "summands" );
      for ( pugi::xml_node partial = summands.child( "add" ); 
            partial; partial = partial.next_sibling( "add" ) ) {

        std::string href = partial.attribute( "href" ).as_string();
        auto start = href.find( '\'' ) + 1;
        auto end = href.find( '\'', start );
        href = href.substr( start, end - start );
        href = suite.child( "reactions" ).find_child_by_attribute( "reaction", "label", href.c_str() ).attribute( "ENDF_MT" ).as_string();
        partials.push_back( href );
      }

      // special treatment for some incident electron data reactions
      if ( projectile == id::ParticleID( "e-" ) ) {

        if ( id == id::ReactionID( "501" ) ) {

          // replace 526 by 525 and -526
          auto iter = std::find( partials.begin(), partials.end(), id::ReactionID( "526" ) );
          *iter = "525";
          partials.insert( iter + 1, id::ReactionID( "-526" ) );
        }
      }

      // cross section
      auto section = reaction.child( "crossSection" );
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // return the reaction data
      return Reaction( std::move( id ), std::move( partials ), std::move( xs ) );
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
