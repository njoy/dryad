#ifndef NJOY_DRYAD_FORMAT_ENDF_REACTION
#define NJOY_DRYAD_FORMAT_ENDF_REACTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createReactionType.hpp"
#include "dryad/format/endf/createTabulatedCrossSection.hpp"
#include "dryad/format/endf/createReactionProducts.hpp"
#include "dryad/Reaction.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a Reaction from an unparsed ENDF material
   */
  Reaction createReaction( const ParticleID& projectile, const ParticleID& target,
                           const ENDFtk::tree::Material& material, int mt ) {

    if ( material.hasSection( 3, mt ) ) {

      auto section = material.section( 3, mt ).parse< 3 >();

      // metadata and miscellaneous information
      ReactionID id = std::to_string( mt );
      ReactionType type = createReactionType( material, mt );
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = std::nullopt;
      if ( type == ReactionType::Primary ) {

        mass_q = section.massDifferenceQValue();
        reaction_q = section.reactionQValue();
      }

      // cross section
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // reaction products
      std::vector< ReactionProduct > products = {};
      if ( type == ReactionType::Primary ) {

        products = createReactionProducts( projectile, target, material, mt );
      }

      // return the reaction data
      return Reaction( std::move( id ), std::move( type ), std::move( xs ),
                       std::move( products ), std::move( mass_q ),
                       std::move( reaction_q ) );
    }
    else if ( material.hasSection( 23, mt ) ) {

      auto section = material.section( 23, mt ).parse< 23 >();

      // metadata and miscellaneous information
      ReactionID id = std::to_string( mt );
      ReactionType type = createReactionType( material, mt );
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = std::nullopt;
      if ( type == ReactionType::Primary ) {

        reaction_q = -section.subshellBindingEnergy();
      }

      // cross section
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // reaction products
      std::vector< ReactionProduct > products = {};
      if ( type == ReactionType::Primary ) {

        products = createReactionProducts( projectile, target, material, mt );
      }

      // return the reaction data
      return Reaction( std::move( id ), std::move( type ), std::move( xs ),
                       std::move( products ), std::move( mass_q ),
                       std::move( reaction_q ) );
    }
    else {

      Log::error( "The material does not have reaction data for MT{}", mt );
      throw std::exception();
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
