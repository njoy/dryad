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

      // Q values
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = std::nullopt;

      // reaction products
      std::vector< ReactionProduct > products = createReactionProducts( projectile, target, material, mt );

      if ( type == ReactionType::Primary ) {

        // Q values
        if ( mt == 18 ) {

          //! @todo handle fission Q value defined on MT18 when no partials are defined
        }
        else {

          mass_q = section.massDifferenceQValue();
          reaction_q = section.massDifferenceQValue();
        }

        // return the reaction data
        return Reaction( std::move( id ), std::move( xs ),
                         std::move( products ), std::move( mass_q ),
                         std::move( reaction_q ) );
      }
      else {

        if ( mt == 18 ) {

          //! @todo handle fission Q value defined on MT18 if partials are defined
        }

        // partials
        std::vector< int > endf_partials = ReactionIdentifiers::partials( material, 3, mt );
        std::vector< id::ReactionID > partials( endf_partials.size() );
        std::transform( endf_partials.begin(), endf_partials.end(), partials.begin(),
                        [] ( auto&& value ) { return std::to_string( value ); } );

        // return the reaction data
        return Reaction( std::move( id ), std::move( partials ), std::move( xs ) );
      }
    }
    else if ( material.hasSection( 23, mt ) ) {

      // metadata and miscellaneous information
      id::ReactionID id = std::to_string( mt );
      ReactionType type = createReactionType( material, mt );

      // cross section
      auto section = material.section( 23, mt ).parse< 23 >();
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // q values
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = std::nullopt;

      // reaction products
      std::vector< ReactionProduct > products = createReactionProducts( projectile, target, material, mt );

      if ( type == ReactionType::Primary ) {

        // q values
        reaction_q = -section.subshellBindingEnergy();
        if ( mt == 515 || mt == 517 ) {

          // for pair production the photon needs 
          // at minimum to be twice the electron rest mass energy
          // i.e. 2 * 511 keV
          reaction_q = -1.022e+6;
        }

        // return the reaction data
        return Reaction( std::move( id ), std::move( xs ),
                         std::move( products ), std::move( mass_q ),
                         std::move( reaction_q ) );
      }
      else {

        // partials
        std::vector< int > endf_partials = ReactionIdentifiers::partials( material, 23, mt );
        std::vector< id::ReactionID > partials( endf_partials.size() );
        std::transform( endf_partials.begin(), endf_partials.end(), partials.begin(),
                        [] ( auto&& value ) { return std::to_string( value ); } );

        // return the reaction data
        return Reaction( std::move( id ), std::move( partials ), std::move( xs ) );
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
