#ifndef NJOY_FORMAT_GNDS_READ_CREATEREACTION
#define NJOY_FORMAT_GNDS_READ_CREATEREACTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/adjustScatterLevel.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"
#include "njoy/format/gnds/read/createQValue.hpp"
#include "njoy/format/gnds/read/createReactionProducts.hpp"
#include "njoy/format/gnds/read/createTabulatedCrossSection.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a Reaction from GNDS node (reaction or crossSectionSum)
   */
  inline dryad::Reaction
  createReaction( const dryad::id::ParticleID& projectile,
                  const dryad::id::ParticleID& target,
                  pugi::xml_node suite,
                  pugi::xml_node reaction,
                  bool normalise,
                  const std::string& style = "eval" ) {

    if ( strcmp( reaction.name(), "reaction" ) == 0 ) {

      // metadata and miscellaneous information
      int mt = reaction.attribute( "ENDF_MT" ).as_int();
      dryad::id::ReactionID id( projectile, target, adjustScatterLevel( projectile, target, mt ) );
      Log::info( "Reading data for \'{}\' - MT{}", id.symbol(), mt );

      // cross section
      auto section = reaction.child( "crossSection" );
      dryad::TabulatedCrossSection xs = createTabulatedCrossSection( section, style );

      // Q values
      auto output = reaction.child( "outputChannel" );
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = createQValue( output.child( "Q" ), style );
      if ( mt == 515 || mt == 517 ) {

        reaction_q = -2. * constants::electron_rest_mass;
      }

      // reaction products
      std::vector< dryad::ReactionProduct > products;
      auto node = output.child( "products" );
      if ( node ) {

        products = createReactionProducts( id, suite, node, std::nullopt, 0, normalise );
      }

      // special treatment for some incident electron data reactions
      if ( projectile == dryad::id::ParticleID::electron() ) {

        if ( id.reactionType() == dryad::id::ReactionType( projectile, 526 ) ) {

          // GNDS classifies total elastic as a primary reaction
          // but we classify it as a summation with a deficit reaction
          std::vector< dryad::id::ReactionID > partials = { dryad::id::ReactionID( projectile, target, "large-angle-scattering" ),
                                                            dryad::id::ReactionID( projectile, target, "deficit-scattering" ) };

          // return the reaction data
          return dryad::Reaction( std::move( id ), std::move( partials ), std::move( xs ) );
        }
      }

      // return the reaction data
      return dryad::Reaction( std::move( id ), std::move( xs ),
                              std::move( products ), std::move( mass_q ),
                              std::move( reaction_q ) );
    }
    else if ( strcmp( reaction.name(), "crossSectionSum" ) == 0 ) {

      // metadata and miscellaneous information
      int mt = reaction.attribute( "ENDF_MT" ).as_int();
      dryad::id::ReactionID id( projectile, target, adjustScatterLevel( projectile, target, mt ) );
      Log::info( "Reading data for \'{}\' - MT{}", id.symbol(), mt );

      // Q values
      auto qvalue = reaction.child( "Q" );
      if ( qvalue ) {

        Log::info( "Ignoring reaction Q value for summation reaction" );
      }

      // partial identifiers
      std::vector< dryad::id::ReactionID > partials;
      auto summands = reaction.child( "summands" );
      for ( pugi::xml_node partial = summands.child( "add" );
            partial; partial = partial.next_sibling( "add" ) ) {

        auto reaction = resolveLink( partial ).parent();
        int mt = adjustScatterLevel( projectile, target, reaction.attribute( "ENDF_MT" ).as_int() );
        partials.emplace_back( projectile, target, mt );
      }

      // special treatment for some incident electron data reactions
      if ( projectile == dryad::id::ParticleID( "e-" ) ) {

        if ( id == dryad::id::ReactionID( projectile, target, 501 ) ) {

          // replace 526 by 525 and -526
          auto total_elastic = dryad::id::ReactionID( projectile, target, 526 );
          auto iter = std::find( partials.begin(), partials.end(), total_elastic );
          *iter = dryad::id::ReactionID( projectile, target, 525 );
          partials.insert( iter + 1, dryad::id::ReactionID( projectile, target, "deficit-scattering" ) );
        }
      }

      // cross section
      auto section = reaction.child( "crossSection" );
      dryad::TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // return the reaction data
      return dryad::Reaction( std::move( id ), std::move( partials ), std::move( xs ), {} );
    }
    else {

      Log::error( "The GNDS node named \'{}\' does not have reaction data", reaction.name() );
      throw std::exception();
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
