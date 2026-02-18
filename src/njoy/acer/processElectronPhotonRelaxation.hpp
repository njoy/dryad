#ifndef NJOY_ACER_PROCESSELECTRONPHOTONRELAXATION
#define NJOY_ACER_PROCESSELECTRONPHOTONRELAXATION

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/overload.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "njoy/dryad/external/ComptonProfiles.hpp"
#include "njoy/dryad/format/ace.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace acer {

  /**
   *  @brief Process data into an epr ace file
   *
   *  @param[in] photoatomic     the photoatomic projectile-target data
   *  @param[in] electroatomic   the electroatomic projectile-target data
   *  @param[in] relaxation      the atomic relaxation data
   *  @param[in] filename        the filename for the ace file
   */
  inline void
  processElectronPhotonRelaxation( const dryad::ProjectileTarget& photoatomic,
                                   const dryad::ProjectileTarget& electroatomic,
                                   const dryad::AtomicRelaxation& relaxation,
                                   const std::string& filename ) {

    if ( photoatomic.interactionType() != dryad::InteractionType::Atomic ||
         photoatomic.projectileIdentifier() != dryad::id::ParticleID::photon() ) {

      throw std::runtime_error( "The projectile-target is not photoatomic" );
    }
    if ( electroatomic.interactionType() != dryad::InteractionType::Atomic ||
         electroatomic.projectileIdentifier() != dryad::id::ParticleID::electron() ) {

      throw std::runtime_error( "The projectile-target is not electroatomic" );
    }
    if ( photoatomic.targetIdentifier() != electroatomic.targetIdentifier() ||
         photoatomic.targetIdentifier().z() != relaxation.elementIdentifier().number() ) {

      throw std::runtime_error( "The targets and relaxation element are not consistent" );
    }

    //! @todo verify if Compton profiles are present
    //! @todo verify unionisation of the photoatomic and electroatomic data
    //! @todo verify if binding energies of shells appear in total ionisation as jumps
    //! @todo verify that average energies have been calculated
    //! @todo verify normalisation?

    // a useful lambda
    auto hasRelativisticSubshells = tools::overload{

      [] ( const dryad::IncoherentDistributionData& incoherent ) -> bool {

        return std::all_of( incoherent.comptonProfiles()->begin(),
                            incoherent.comptonProfiles()->end(),
                            [] ( auto&& profile ) { return profile.subshellIdentifier().isRelativistic(); } );
      },
      [] ( auto&& ) -> bool {

        throw std::runtime_error( "Expected incoherent scattering data, found something else" );
      }
    };

    // determine the type of Compton profile
    decltype(auto) projectile = photoatomic.projectileIdentifier();
    decltype(auto) target = photoatomic.targetIdentifier();
    dryad::id::ReactionID incoherent_id( projectile, target, dryad::id::ReactionType( projectile, 504 ) );
    decltype(auto) photon = photoatomic.reaction( incoherent_id ).product( projectile ).distributionData().value();
    bool relativistic = std::visit( hasRelativisticSubshells, photon );

    unsigned int z = photoatomic.targetIdentifier().z();
    ACEtk::Table::Header header( std::to_string( z * 1000 ) + ".25p", 0., 0., "", "", std::to_string( z * 100 ) );
    std::vector< unsigned int > za = {};
    std::vector< double > awr = {};

    auto eszg = dryad::format::ace::photoatomic::createAcePrincipalCrossSectionBlock( photoatomic );
    auto jinc = dryad::format::ace::photoatomic::createAceIncoherentScatteringFunctionBlock( photoatomic );
    auto jcoh = dryad::format::ace::photoatomic::createAceCoherentFormFactorBlock( photoatomic );
    auto lhnm = dryad::format::ace::photoatomic::createAceHeatingNumbersBlock( photoatomic, relaxation );
    auto jflo = dryad::format::ace::photoatomic::createAceFluorescenceDataBlock( photoatomic, relaxation );
    auto eps = dryad::format::ace::atomic::createAceElectronShellBlock( relativistic, relaxation );
    auto swd = dryad::format::ace::photoatomic::createAceComptonProfileBlock( photoatomic );
    auto subsh = dryad::format::ace::atomic::createAceElectronSubshellBlock( relaxation );
    auto sphel = dryad::format::ace::photoatomic::createAcePhotoelectricCrossSectionBlock( photoatomic );
    auto xprob = dryad::format::ace::atomic::createAceSubshellTransitionDataBlock( relaxation );
    auto esze = dryad::format::ace::electroatomic::createAcePrincipalCrossSectionBlock( electroatomic );
    auto excit = dryad::format::ace::electroatomic::createAceExcitationBlock( electroatomic );
    auto elas = dryad::format::ace::electroatomic::createAceElasticAngularDistributionBlock( electroatomic );
    auto eion = dryad::format::ace::electroatomic::createAceIonisationDistributionBlocks( electroatomic );
    auto breme = dryad::format::ace::electroatomic::createAceBremsstrahlungDistributionBlock( electroatomic );
    auto breml = dryad::format::ace::electroatomic::createAceBremsstrahlungBlock( electroatomic );
    auto selas = dryad::format::ace::electroatomic::createAceElasticCrossSectionBlock( electroatomic );

    ACEtk::PhotoatomicTable table( z, std::move( header ), std::move( za ), std::move( awr ),
                                   std::move( eszg ), std::move( jinc ), std::move( jcoh ), std::move( lhnm ),
                                   std::move( jflo ), std::move( eps ), std::move( swd ), std::move( subsh ),
                                   std::move( sphel ), std::move( xprob ), std::move( esze ), std::move( excit ),
                                   std::move( elas ), std::move( eion ), std::move( breme ), std::move( breml ),
                                   std::move( selas ) );

    // open a file and print the ACE file to the file
    std::ofstream out( filename );
    table.print( out );
    out.close();
  }

} // acer namespace
} // njoy namespace

#endif
