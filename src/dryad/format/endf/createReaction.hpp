#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTION

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/ReactionInformation.hpp"
#include "dryad/format/endf/createTabulatedCrossSection.hpp"
#include "dryad/format/endf/createMultiplicity.hpp"
#include "dryad/format/endf/createReactionProducts.hpp"
#include "dryad/Reaction.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Add a reaction product if it is not in the list
   */
  void addProduct( const id::ParticleID& particle, int multiplicity,
                   std::vector< ReactionProduct >& products ) {

    if ( multiplicity != 0 ) {

      auto iter = std::find_if( products.begin(), products.end(),
                                [&particle] ( auto&& product )
                                            { return product.identifier() == particle; } );
      if ( iter == products.end() ) {

        Log::info( "Adding '{}' as an expected reaction product", particle.symbol() );
        products.emplace_back( particle, createMultiplicity( multiplicity ) );
      }
    }
  }

  /**
   *  @brief Create a Reaction from an unparsed ENDF material
   */
  Reaction createReaction( const id::ParticleID& projectile, const id::ParticleID& target,
                           const ENDFtk::tree::Material& material, int mt,
                           bool normalise ) {

    if ( material.hasSection( 3, mt ) ) {

      // metadata and miscellaneous information
      id::ReactionID id = std::to_string( mt );

      // cross section
      auto section = material.section( 3, mt ).parse< 3 >();
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // Q values
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = std::nullopt;

      // reaction products
      std::vector< ReactionProduct > products = createReactionProducts( projectile, target, material, mt, normalise );

      if ( endf::ReactionInformation::isPrimary( material, mt ) ) {

        // Q values
        if ( mt == 18 ) {

          //! @todo handle fission Q value defined on MT18 when no partials are defined
        }
        else {

          mass_q = section.massDifferenceQValue();
          reaction_q = section.massDifferenceQValue();
        }

        // add missing reaction products (n, p, d, t, h, a only)
        if ( ReactionInformation::hasSecondaryParticles( mt ) ) {

          addProduct( createProductIdentifier( 1, 0 ), ReactionInformation::neutrons( mt ), products );
          addProduct( createProductIdentifier( 1001, 0 ), ReactionInformation::protons( mt ), products );
          addProduct( createProductIdentifier( 1002, 0 ), ReactionInformation::deuterons( mt ), products );
          addProduct( createProductIdentifier( 1003, 0 ), ReactionInformation::tritons( mt ), products );
          addProduct( createProductIdentifier( 2003, 0 ), ReactionInformation::helions( mt ), products );
          addProduct( createProductIdentifier( 2004, 0 ), ReactionInformation::alphas( mt ), products );
        }

        // return the reaction data
        return Reaction( std::move( id ), std::move( xs ),
                         std::move( products ), std::move( mass_q ),
                         std::move( reaction_q ) );
      }
      else if ( endf::ReactionInformation::isSummation( material, mt ) ) {

        if ( mt == 18 ) {

          //! @todo handle fission Q value defined on MT18 if partials are defined
        }

        // partials
        std::vector< int > endf_partials = ReactionInformation::partials( material, 3, mt );
        std::vector< id::ReactionID > partials( endf_partials.size() );
        std::transform( endf_partials.begin(), endf_partials.end(), partials.begin(),
                        [] ( auto&& value ) { return std::to_string( value ); } );

        // return the reaction data
        return Reaction( std::move( id ), std::move( partials ), std::move( xs ) );
      }
      else {

        Log::error( "{} is not an MT number that designates a valid reaction", mt );
        throw std::exception();
      }
    }
    else if ( material.hasSection( 23, mt ) ) {

      // metadata and miscellaneous information
      id::ReactionID id = std::to_string( mt );

      // cross section
      auto section = material.section( 23, mt ).parse< 23 >();
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // q values
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = std::nullopt;

      // reaction products
      std::vector< ReactionProduct > products = createReactionProducts( projectile, target, material, mt, normalise );

      if ( endf::ReactionInformation::isPrimary( material, mt ) ) {

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
      else if ( endf::ReactionInformation::isSummation( material, mt ) ) {

        // partials
        std::vector< int > endf_partials = ReactionInformation::partials( material, 23, mt );
        std::vector< id::ReactionID > partials( endf_partials.size() );
        std::transform( endf_partials.begin(), endf_partials.end(), partials.begin(),
                        [] ( auto&& value ) { return std::to_string( value ); } );

        // return the reaction data
        return Reaction( std::move( id ), std::move( partials ), std::move( xs ) );
      }
      else {

        Log::error( "{} is not an MT number that designates a valid reaction", mt );
        throw std::exception();
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
