#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTION

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
  Reaction createReaction( const id::ParticleID& projectile, const id::ParticleID& target,
                           const ENDFtk::tree::Material& material, int mt ) {

    if ( material.hasSection( 3, mt ) ) {

      // metadata and miscellaneous information
      id::ReactionID id = std::to_string( mt );
      ReactionType type = createReactionType( material, mt );

      // cross section
      auto section = material.section( 3, mt ).parse< 3 >();
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      if ( type == ReactionType::Primary ) {

        // Q values
        std::optional< double > mass_q = section.massDifferenceQValue();
        std::optional< double > reaction_q = section.massDifferenceQValue();

        // reaction products
        std::vector< ReactionProduct > products = createReactionProducts( projectile, target, material, mt );

        // return the reaction data
        return Reaction( std::move( id ), std::move( xs ),
                         std::move( products ), std::move( mass_q ),
                         std::move( reaction_q ) );
      }
      else {

        // return the reaction data
        return Reaction( std::move( id ), {}, std::move( xs ) );
      }
    }
    else if ( material.hasSection( 23, mt ) ) {

      // metadata and miscellaneous information
      id::ReactionID id = std::to_string( mt );
      ReactionType type = createReactionType( material, mt );

      // cross section
      auto section = material.section( 23, mt ).parse< 23 >();
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      if ( type == ReactionType::Primary ) {

        // q values
        std::optional< double > mass_q = std::nullopt;
        std::optional< double > reaction_q = -section.subshellBindingEnergy();

        // reaction products
        std::vector< ReactionProduct > products = createReactionProducts( projectile, target, material, mt );

        // return the reaction data
        return Reaction( std::move( id ), std::move( xs ),
                         std::move( products ), std::move( mass_q ),
                         std::move( reaction_q ) );
      }
      else {

        // return the reaction data
        return Reaction( std::move( id ), {}, std::move( xs ) );
      }
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
