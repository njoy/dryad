#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTION

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/format/adjustScatterLevel.hpp"
#include "njoy/dryad/format/endf/ReactionInformation.hpp"
#include "njoy/dryad/format/endf/createTabulatedCrossSection.hpp"
#include "njoy/dryad/format/endf/createReactionProducts.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a Reaction from an unparsed ENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] masses       the particle mass values
   *  @param[in] material     the unparsed ENDF material
   *  @param[in] mt           the MT number to process
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  Reaction createReaction( const id::ParticleID& projectile,
                           const id::ParticleID& target,
                           const ENDFtk::tree::Material& material,
                           int mt,
                           bool normalise,
                           std::map< id::ParticleID, double >& masses ) {

                            // metadata and miscellaneous information
    id::ReactionID id( projectile, target, adjustScatterLevel( projectile, target, mt ) );
    Log::info( "Reading data for \'{}\' - MT{}", id.symbol(), mt );

    if ( material.hasSection( 3, mt ) ) {

      // cross section
      auto section = material.section( 3, mt ).parse< 3 >();
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // Q values
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = std::nullopt;

      if ( endf::ReactionInformation::isPrimary( material, mt ) ) {

        // reaction products
        std::vector< ReactionProduct > products = createReactionProducts( id, material, mt, normalise, masses );

        // Q values
        if ( mt == 18 ) {

          //! @todo handle fission Q value defined on MT18 when no partials are defined
        }
        else {

          mass_q = section.massDifferenceQValue();
          reaction_q = section.reactionQValue();
        }

        // return the reaction data
        return Reaction( std::move( id ), std::move( xs ),
                         std::move( products ), std::move( mass_q ),
                         std::move( reaction_q ) );
      }
      else if ( endf::ReactionInformation::isSummation( material, mt ) ) {

        //! @todo summation reactions sometimes have products - e.g. MT3

        if ( mt == 18 ) {

          //! @todo handle fission Q value defined on MT18 if partials are defined
        }

        // return the reaction data
        return Reaction( std::move( id ),
                         ReactionInformation::partials( projectile, target, material, 3, mt ),
                         std::move( xs ) );
      }
      else {

        Log::error( "{} is not an MT number that designates a valid reaction", mt );
        throw std::exception();
      }
    }
    else if ( material.hasSection( 23, mt ) ) {

      // cross section
      auto section = material.section( 23, mt ).parse< 23 >();
      TabulatedCrossSection xs = createTabulatedCrossSection( section );

      // q values
      std::optional< double > mass_q = std::nullopt;
      std::optional< double > reaction_q = std::nullopt;

      // reaction products
      std::vector< ReactionProduct > products = createReactionProducts( id, material, mt, normalise, masses );

      if ( endf::ReactionInformation::isPrimary( material, mt ) ) {

        // q values
        reaction_q = -section.subshellBindingEnergy();
        if ( mt == 515 || mt == 517 ) {

          // for pair production the photon needs
          // at minimum to be twice the electron rest mass energy
          // i.e. 2 * 511 keV
          reaction_q = - 2. * constants::electron_rest_mass;
        }

        // return the reaction data
        return Reaction( std::move( id ), std::move( xs ),
                         std::move( products ), std::move( mass_q ),
                         std::move( reaction_q ) );
      }
      else if ( endf::ReactionInformation::isSummation( material, mt ) ) {

        // return the reaction data
        return Reaction( std::move( id ),
                         ReactionInformation::partials( projectile, target, material, 23, mt ),
                         std::move( xs ) );
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
