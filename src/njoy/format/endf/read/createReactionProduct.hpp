#ifndef NJOY_FORMAT_ENDF_READ_CREATEREACTIONPRODUCT
#define NJOY_FORMAT_ENDF_READ_CREATEREACTIONPRODUCT

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReactionProduct.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/format/endf/read/createProductIdentifier.hpp"
#include "njoy/format/endf/read/createReferenceFrame.hpp"
#include "njoy/format/endf/read/createMultiplicity.hpp"
#include "njoy/format/endf/read/createLegendreAngularDistributions.hpp"
#include "njoy/format/endf/read/createTabulatedAngularDistributions.hpp"
#include "njoy/format/endf/read/createMixedAngularDistributions.hpp"
#include "njoy/format/endf/read/createTabulatedEnergyDistributions.hpp"
#include "njoy/format/endf/read/createTabulatedAverageEnergy.hpp"
#include "njoy/format/endf/read/createTabulatedFormFactor.hpp"
#include "njoy/format/endf/read/createTabulatedScatteringFunction.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "tools/overload.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

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
  inline dryad::ReactionProduct
  createReactionProduct( const dryad::id::ReactionID& reaction,
                         const ENDFtk::section::Type< 4 >& section,
                         bool normalise ) {

    using Isotropic = ENDFtk::section::Type< 4 >::Isotropic;
    using LegendreDistributions = ENDFtk::section::Type< 4 >::LegendreDistributions;
    using TabulatedDistributions = ENDFtk::section::Type< 4 >::TabulatedDistributions;
    using MixedDistributions = ENDFtk::section::Type< 4 >::MixedDistributions;

    auto createDistributions = tools::overload{

      [&] ( const Isotropic& ) -> dryad::TwoBodyDistributionData::AngularDistributions {

        return dryad::IsotropicAngularDistributions();
      },
      [&] ( const LegendreDistributions& distributions ) -> dryad::TwoBodyDistributionData::AngularDistributions {

        return createLegendreAngularDistributions( distributions, normalise );
      },
      [&] ( const TabulatedDistributions& distributions ) -> dryad::TwoBodyDistributionData::AngularDistributions {

        return createTabulatedAngularDistributions( distributions, normalise );
      },
      [&] ( const MixedDistributions& distributions ) -> dryad::TwoBodyDistributionData::AngularDistributions {

        return createMixedAngularDistributions( distributions, normalise );
      }
    };

    // should only be used for neutrons
    if ( reaction.particles()->size() > 1 ) {

      Log::error( "An MF4 section cannot be used for a reaction that emits more than one particle type" );
      throw std::exception();
    }

    // get the particle id and check for neutrons
    dryad::id::ParticleID id = reaction.particles()->begin()->first;
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    if ( id != dryad::id::ParticleID::neutron() ) {

      Log::warning( "An MF4 section should only be used for neutrons, but in this case we'll allow it." );
    }

    auto frame = createReferenceFrame( section.referenceFrame() );
    int multiplicity = reaction.particles()->at( id );

    auto distribution = dryad::TwoBodyDistributionData(
                          frame,
                          std::visit( createDistributions, section.distributions() ) );
    return dryad::ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
  }

  /**
   *  @brief Create a ReactionProduct from a parsed ENDF MF6 reaction product
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] product      the MF6 reaction product data
   *  @param[in] normalise    the flag to indicate whether or not the distributions
   *                          need to be normalised
   */
  inline dryad::ReactionProduct
  createReactionProduct( const dryad::id::ReactionID& reaction,
                         const ENDFtk::section::Type< 6 >::ReactionProduct& product,
                         bool /* normalise */ ) {

    // get the reaction product id and look for the residual - if it is defined
    dryad::id::ParticleID id = createProductIdentifier( product.productIdentifier(),
                                                 product.productModifierFlag() );
    if ( reaction.residual().has_value() ) {

      auto residual = reaction.residual().value();
      if ( id.groundState() == residual.groundState() ) {

        if ( id.e() == residual.e() || ( id.e() == 0 && residual.e() > 0 ) ) {

          id = residual;
        }
      }
    }

    // change the product identifier to a fundamental particle if need be
    if ( reaction.residual() != id ) {

      if ( id == dryad::id::ParticleID( "H1" ) ) {

        id = dryad::id::ParticleID::proton();
      }
      else if ( id == dryad::id::ParticleID( "H2" ) ) {

        id = dryad::id::ParticleID::deuteron();
      }
      else if ( id == dryad::id::ParticleID( "H3" ) ) {

        id = dryad::id::ParticleID::triton();
      }
      else if ( id == dryad::id::ParticleID( "He3" ) ) {

        id = dryad::id::ParticleID::helion();
      }
      else if ( id == dryad::id::ParticleID( "He4" ) ) {

        id = dryad::id::ParticleID::alpha();
      }
    }

    // read data and add the product
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    auto multiplicity = createMultiplicity( product.multiplicity() );

    return dryad::ReactionProduct( std::move( id ), std::move( multiplicity ) );
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
  inline dryad::ReactionProduct
  createReactionProduct( const dryad::id::ReactionID& /* reaction */,
                         const ENDFtk::section::Type< 26 >::ReactionProduct& product,
                         int mt,
                         bool normalise ) {

    dryad::id::ParticleID id = createProductIdentifier( product.productIdentifier(), 0 );
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    auto multiplicity = createMultiplicity( product.multiplicity() );

    //! @todo what about the reference frames?

    switch ( product.LAW() ) {

      case 1 : {

        // ENDF/B-VIII.0 erroneously uses 11 for the gamma identifier in MF26 MT527
        // LAW = 1 is only used for the outgoing gamma, the electron uses LAW = 8
        if ( ( mt == 527 ) && ( id == dryad::id::ParticleID::electron() ) ) {

          id = dryad::id::ParticleID::photon();
          Log::warning( "Reaction product identifier changed from \'e-\' to \'g\'" );
        }

        // MF26 LAW = 1 : NA must be 0 and LANG must be 1
        decltype(auto) data = std::get< ENDFtk::section::Type< 26 >::ContinuumEnergyAngle >( product.distribution() );
        auto distribution = dryad::UncorrelatedDistributionData( dryad::ReferenceFrame::Laboratory,
                                                                 dryad::IsotropicAngularDistributions(),
                                                                 createTabulatedEnergyDistributions( data, normalise ) );
        return dryad::ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
      }
      case 2 : {

        // MF26 LAW = 2 : Legendre coefficients are not allowed
        decltype(auto) data = std::get< ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering >( product.distribution() );
        auto distribution = dryad::TwoBodyDistributionData( dryad::ReferenceFrame::CentreOfMass,
                                                            createTabulatedAngularDistributions( data, normalise ) );
        return dryad::ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
      }
      case 8 : {

        // MF26 LAW = 8 : energy transfer is given (converted to the average energy of the outgoing electron)
        decltype(auto) data = std::get< ENDFtk::section::Type< 26 >::EnergyTransfer >( product.distribution() );
        auto average = createTabulatedAverageEnergy( data );
        return dryad::ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( average ) );
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
  inline dryad::ReactionProduct
  createReactionProduct( const dryad::id::ReactionID& /* reaction */,
                         const ENDFtk::section::Type< 27 >& coherent,
                         const std::optional< ENDFtk::section::Type< 27 > >& real,
                         const std::optional< ENDFtk::section::Type< 27 > >& imaginary,
                         int /* mt */,
                         bool /* normalise */ ) {

    dryad::id::ParticleID id = dryad::id::ParticleID::photon();
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    int multiplicity = 1;

    //! @todo what about the reference frames?

    if ( real.has_value() || imaginary.has_value() ) {

      auto distribution = dryad::CoherentDistributionData( dryad::ReferenceFrame::Laboratory,
                                                           createTabulatedScatteringFunction( coherent ),
                                                           createTabulatedFormFactor( real.value() ),
                                                           createTabulatedFormFactor( imaginary.value() ) );
      return dryad::ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );

    }
    else {

      auto distribution = dryad::CoherentDistributionData( dryad::ReferenceFrame::Laboratory,
                                                           createTabulatedScatteringFunction( coherent ) );
      return dryad::ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
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
  inline dryad::ReactionProduct
  createReactionProduct( const dryad::id::ReactionID& /* reaction */,
                         const ENDFtk::section::Type< 27 >& incoherent,
                         int /* mt */,
                         bool /* normalise */ ) {

    dryad::id::ParticleID id = dryad::id::ParticleID::photon();
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );
    int multiplicity = 1;

    //! @todo what about the reference frames?

    auto distribution = dryad::IncoherentDistributionData( dryad::ReferenceFrame::Laboratory,
                                                           createTabulatedScatteringFunction( incoherent ) );
    return dryad::ReactionProduct( std::move( id ), std::move( multiplicity ), std::move( distribution ) );
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
