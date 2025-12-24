#ifndef NJOY_ACER_PROCESSELECTRONPHOTONRELAXATION
#define NJOY_ACER_PROCESSELECTRONPHOTONRELAXATION

// system includes
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "njoy/dryad/format/ace.hpp"

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
  inline void processElectronPhotonRelaxation( const dryad::ProjectileTarget& photoatomic,
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
    if ( photoatomic.targetIdentifier() != photoatomic.targetIdentifier() ||
         photoatomic.targetIdentifier().z() != relaxation.elementIdentifier().number() ) {

      throw std::runtime_error( "The targets and relaxation element are not consistent" );
    }

    //! @todo verify unionisation of the photoatomic and electroatomic data
    //! @todo verify if binding energies of shells appear in total ionisation as jumps
    //! @todo verify normalisation?

    bool relativistic = true;

    unsigned int z = photoatomic.targetIdentifier().z();
    ACEtk::Table::Header header;
    std::vector< unsigned int > za = {};
    std::vector< double > awr = {};

    auto eszg = dryad::format::ace::photoatomic::createAcePrincipalCrossSectionBlock( photoatomic );
    auto jinc = dryad::format::ace::photoatomic::createAceIncoherentScatteringFunctionBlock( photoatomic );
    auto jcoh = dryad::format::ace::photoatomic::createAceCoherentFormFactorBlock( photoatomic );
//    auto lhnm = ;
//    auto jflo = ;
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
  }

} // acer namespace
} // njoy namespace

#endif
