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
#include "njoy/format/ace.hpp"
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
   *  @param[in] number          the extension number (above 0, less than 100)
   *  @param[in] date            the processing date
   *  @param[in] title           the ace file title
   *
   *  number, date and title are for the header and are temporary so we can
   *  produce the eprdata files
   */
  inline void
  processElectronPhotonRelaxation( const dryad::ProjectileTarget& photoatomic,
                                   const dryad::ProjectileTarget& electroatomic,
                                   const dryad::AtomicRelaxation& relaxation,
                                   const std::string& filename,
                                   int number,
                                   std::string date,
                                   std::string title ) {

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
    //! @todo verify if the number of Compton profiles is the same as the number of shells in
    //!       the relaxation data (relativistic only)
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

    unsigned int z = target.z();
    decltype(auto) particle = photoatomic.particleData()->particle( target );
    double mass = particle.mass().has_value() ? particle.mass().value() / constants::neutron_mass : 0.;
    ACEtk::Table::Header header( std::to_string( z * 1000 ) + '.' + std::to_string( number ) + 'p',
                                 mass, 0., std::move( date ), std::move( title ), "mat" + std::to_string( z * 100 ) );
    std::vector< unsigned int > za = {};
    std::vector< double > awr = {};

    auto eszg = format::ace::write::photoatomic::createPrincipalCrossSectionBlock( photoatomic );
    auto jinc = format::ace::write::photoatomic::createIncoherentScatteringFunctionBlock( photoatomic );
    auto jcoh = format::ace::write::photoatomic::createCoherentFormFactorBlock( photoatomic );
    auto lhnm = format::ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, relaxation );
    auto jflo = format::ace::write::photoatomic::createFluorescenceDataBlock( photoatomic, relaxation );
    auto eps = format::ace::write::atomic::createElectronShellBlock( relativistic, relaxation );
    auto swd = format::ace::write::photoatomic::createComptonProfileBlock( photoatomic );
    auto subsh = format::ace::write::atomic::createElectronSubshellBlock( relaxation );
    auto sphel = format::ace::write::photoatomic::createPhotoelectricCrossSectionBlock( photoatomic );
    auto xprob = format::ace::write::atomic::createSubshellTransitionDataBlock( relaxation );
    auto esze = format::ace::write::electroatomic::createPrincipalCrossSectionBlock( electroatomic );
    auto excit = format::ace::write::electroatomic::createExcitationBlock( electroatomic );
    auto elas = format::ace::write::electroatomic::createElasticAngularDistributionBlock( electroatomic );
    auto eion = format::ace::write::electroatomic::createIonisationDistributionBlocks( electroatomic );
    auto breme = format::ace::write::electroatomic::createBremsstrahlungDistributionBlock( electroatomic );
    auto breml = format::ace::write::electroatomic::createBremsstrahlungBlock( electroatomic );
    auto selas = format::ace::write::electroatomic::createElasticCrossSectionBlock( electroatomic );

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
