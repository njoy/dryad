#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONPRODUCT
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONPRODUCT

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/format/endf/createProductIdentifier.hpp"
#include "njoy/dryad/format/endf/createReferenceFrame.hpp"
#include "njoy/dryad/format/endf/createMultiplicity.hpp"
#include "njoy/dryad/format/endf/createTabulatedEnergyDistributions.hpp"
#include "njoy/dryad/format/endf/createTabulatedAngularDistributions.hpp"
#include "njoy/dryad/format/endf/createLegendreAngularDistributions.hpp"
#include "njoy/dryad/format/endf/createTabulatedAverageEnergy.hpp"
#include "njoy/dryad/format/endf/createTabulatedFormFactor.hpp"
#include "njoy/dryad/format/endf/createTabulatedScatteringFunction.hpp"
#include "njoy/dryad/ReactionProduct.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "tools/overload.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a ReactionProduct from a parsed ENDF MF4 section
   *
   *  There is no associated MF5 section, so we use TwoBodyDistributionData.
   *
   *  @param[in] reaction    the reaction identifier
   *  @param[in] section     the MF4 section
   *  @param[in] normalise   the flag to indicate whether or not the distributions
   *                         need to be normalised
   */
  inline ReactionProduct
  createReactionProduct( const id::ReactionID& reaction,
                         const ENDFtk::section::Type< 4 >& section,
                         bool normalise ) {

    using Isotropic = ENDFtk::section::Type< 4 >::Isotropic;
    using LegendreDistributions = ENDFtk::section::Type< 4 >::LegendreDistributions;
    using TabulatedDistributions = ENDFtk::section::Type< 4 >::TabulatedDistributions;
    using MixedDistributions = ENDFtk::section::Type< 4 >::MixedDistributions;

    auto createDistributions = tools::overload{

      [&] ( const Isotropic& distributions ) -> TwoBodyDistributionData::AngularDistributions {

        return IsotropicAngularDistributions();
      },
      [&] ( const LegendreDistributions& distributions ) -> TwoBodyDistributionData::AngularDistributions {

        return createLegendreAngularDistributions( distributions, normalise );
      },
      [&] ( const TabulatedDistributions& distributions ) -> TwoBodyDistributionData::AngularDistributions {

        return createTabulatedAngularDistributions( distributions, normalise );
      },
      [&] ( const MixedDistributions& distributions ) -> TwoBodyDistributionData::AngularDistributions {

        throw std::runtime_error( "Any MF4 LTT = 3 is not implemented yet, contact a developer" );
      }
    };

    // should only be used for neutrons
    if ( reaction.particles()->size() > 1 ) {

      Log::error( "An MF4 section cannot be used for a reaction that emits more than one particle type" );
      throw std::exception();
    }

    // get the particle id and check for neutrons
    id::ParticleID id = reaction.particles()->begin()->first;
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    if ( id != id::ParticleID::neutron() ) {

      Log::warning( "An MF4 section should only be used for neutrons, but in this case we'll allow it." );
    }

    auto frame = createReferenceFrame( section.referenceFrame() );
    int multiplicity = reaction.particles()->at( id );

    if ( section.LTT() != 3 ) {

      auto distribution = TwoBodyDistributionData(
                            frame,
                            std::visit( createDistributions, section.distributions() ) );
      return ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
    }
    else {

      // temporary code: remove when we implement mixed distributions

      Log::info( "Any MF4 LTT = 3 is not implemented yet" );
      return ReactionProduct( std::move( id ), std::move( multiplicity ), std::nullopt );
    }
  }

  /**
   *  @brief Create a ReactionProduct from a parsed ENDF MF6 reaction product
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] product      the MF6 reaction product data
   *  @param[in] normalise    the flag to indicate whether or not the distributions
   *                          need to be normalised
   */
  inline ReactionProduct
  createReactionProduct( const id::ReactionID& reaction,
                         const ENDFtk::section::Type< 6 >::ReactionProduct& product,
                         bool normalise ) {

    id::ParticleID id = createProductIdentifier( product.productIdentifier(),
                                                 product.productModifierFlag() );
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    auto multiplicity = createMultiplicity( product.multiplicity() );

    return ReactionProduct( std::move( id ), std::move( multiplicity ) );
  }

  /**
   *  @brief Create a ReactionProduct from a parsed ENDF MF26 reaction product
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] product      the MF26 reaction product data
   *  @param[in] mt           the ENDF MT number
   *  @param[in] normalise    the flag to indicate whether or not the distributions
   *                          need to be normalised
   */
  ReactionProduct
  createReactionProduct( const id::ReactionID& reaction,
                         const ENDFtk::section::Type< 26 >::ReactionProduct& product,
                         int mt,
                         bool normalise ) {

    id::ParticleID id = createProductIdentifier( product.productIdentifier(), 0 );
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    auto multiplicity = createMultiplicity( product.multiplicity() );

    //! @todo what about the reference frames?

    switch ( product.LAW() ) {

      case 1 : {

        // ENDF/B-VIII.0 erroneously uses 11 for the gamma identifier in MF26 MT527
        // LAW = 1 is only used for the outgoing gamma, the electron uses LAW = 8
        if ( ( mt == 527 ) && ( id == id::ParticleID::electron() ) ) {

          id = id::ParticleID::photon();
          Log::warning( "Reaction product identifier changed from \'e-\' to \'g\'" );
        }

        // MF26 LAW = 1 : NA must be 0 and LANG must be 1
        decltype(auto) data = std::get< ENDFtk::section::Type< 26 >::ContinuumEnergyAngle >( product.distribution() );
        auto distribution = UncorrelatedDistributionData( ReferenceFrame::Laboratory,
                                                          IsotropicAngularDistributions(),
                                                          createTabulatedEnergyDistributions( data, normalise ) );
        return ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
      }
      case 2 : {

        // MF26 LAW = 2 : Legendre coefficients are not allowed
        decltype(auto) data = std::get< ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering >( product.distribution() );
        auto distribution = TwoBodyDistributionData( ReferenceFrame::CentreOfMass,
                                                     createTabulatedAngularDistributions( data, normalise ) );
        return ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
      }
      case 8 : {

        // MF26 LAW = 8 : energy transfer is given (converted to the average energy of the outgoing electron)
        decltype(auto) data = std::get< ENDFtk::section::Type< 26 >::EnergyTransfer >( product.distribution() );
        auto average = createTabulatedAverageEnergy( data );
        return ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( average ) );
      }
      default : {

        Log::error( "This should be unreachable" );
        throw std::exception();
      }
    }
  }

  /**
   *  @brief Create a ReactionProduct from parsed ENDF MF27 MT502, MT505 and MT506
   *         section (coherent scattering)
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] incoherent   the MF27 MT504 section
   *  @param[in] real         the optional MF27 MT505 section
   *  @param[in] imaginary    the optional MF27 MT506 section
   *  @param[in] mt           the ENDF MT number
   *  @param[in] normalise    the flag to indicate whether or not the distributions
   *                          need to be normalised
   */
  ReactionProduct
  createReactionProduct( const id::ReactionID& reaction,
                         const ENDFtk::section::Type< 27 >& coherent,
                         const std::optional< ENDFtk::section::Type< 27 > >& real,
                         const std::optional< ENDFtk::section::Type< 27 > >& imaginary,
                         int mt,
                         bool normalise ) {

    id::ParticleID id = id::ParticleID::photon();
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    int multiplicity = 1;

    //! @todo what about the reference frames?

    if ( real.has_value() || imaginary.has_value() ) {

      auto distribution = CoherentDistributionData( ReferenceFrame::Laboratory,
                                                    createTabulatedScatteringFunction( coherent ),
                                                    createTabulatedFormFactor( real.value() ),
                                                    createTabulatedFormFactor( imaginary.value() ) );
      return ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );

    }
    else {

      auto distribution = CoherentDistributionData( ReferenceFrame::Laboratory,
                                                    createTabulatedScatteringFunction( coherent ) );
      return ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
    }
  }

  /**
   *  @brief Create a ReactionProduct from a parsed ENDF MF27 MT504 section (incoherent scattering)
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] incoherent   the MF27 MT504 section
   *  @param[in] mt           the ENDF MT number
   *  @param[in] normalise    the flag to indicate whether or not the distributions
   *                          need to be normalised
   */
  ReactionProduct
  createReactionProduct( const id::ReactionID& reaction,
                         const ENDFtk::section::Type< 27 >& incoherent,
                         int mt,
                         bool normalise ) {

    id::ParticleID id = id::ParticleID::photon();
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    int multiplicity = 1;

    //! @todo what about the reference frames?

    auto distribution = IncoherentDistributionData( ReferenceFrame::Laboratory,
                                                    createTabulatedScatteringFunction( incoherent ) );
    return ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
