// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createProjectileTargetFromFile.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "projectileTarget" ) {

  GIVEN( "ENDF materials - incident neutrons" ) {

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H1 = format::endf::createProjectileTargetFromFile( "n-001_H_001.endf" );

        CHECK( id::ParticleID( "n" ) == H1.projectileIdentifier() );
        CHECK( id::ParticleID( "1001_e0" ) == H1.targetIdentifier() );

        CHECK( InteractionType::Nuclear == H1.interactionType() );

        CHECK( false == H1.isLinearised() );

        CHECK( std::nullopt == H1.resonances() );

        CHECK( true == H1.hasReaction( id::ReactionID( "1" ) ) );
        CHECK( true == H1.hasReaction( id::ReactionID( "2" ) ) );
        CHECK( true == H1.hasReaction( id::ReactionID( "102" ) ) );
        CHECK( false == H1.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 3 == H1.reactions().size() );

        auto total = H1.reactions()[0];
        verifyNeutronTotalReaction( total );

        auto elastic = H1.reactions()[1];
        verifyNeutronElasticReaction( elastic );

        auto capture = H1.reactions()[2];
        verifyNeutronCaptureReaction( capture );

        total = H1.reaction( id::ReactionID( "1" ) );
        verifyNeutronTotalReaction( total );

        elastic = H1.reaction( id::ReactionID( "2" ) );
        verifyNeutronElasticReaction( elastic );

        capture = H1.reaction( id::ReactionID( "102" ) );
        verifyNeutronCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - electro-atomic" ) {

    // two test are used:
    // - ENDF/B-VIII.1 data (same as GNDS test files)
    // - ENDF/B-VIII.0 data which used an electron instead of photon particle id
    //   This test verifies that we can handle it. For ENDF/B-VIII.1 (see above)
    //   the ENDF file was corrected.

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H0 = format::endf::createProjectileTargetFromFile( "e-001_H_000.endf" );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000_e0" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID(  "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "525" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "526" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "527" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "528" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "534" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "-526" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        verifyElectronTotalReaction( total );

        auto ionisation = H0.reactions()[1];
        verifyElectronTotalIonisationReaction( ionisation );

        auto elastic = H0.reactions()[2];
        verifyElectronElasticReaction( elastic );

        auto telastic = H0.reactions()[3];
        verifyElectronTotalElasticReaction( telastic );

        auto bremsstrahlung = H0.reactions()[4];
        verifyElectronBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0.reactions()[5];
        verifyElectronExcitationReaction( excitation );

        auto subionisation = H0.reactions()[6];
        verifyElectronSubshellIonisationReaction( subionisation );

        auto deficit = H0.reactions()[7];
        verifyElectronElasticDeficitReaction( deficit );

        total = H0.reaction( id::ReactionID( "501" ) );
        verifyElectronTotalReaction( total );

        ionisation = H0.reaction( id::ReactionID( "522" ) );
        verifyElectronTotalIonisationReaction( ionisation );

        elastic = H0.reaction( id::ReactionID( "525" ) );
        verifyElectronElasticReaction( elastic );

        telastic = H0.reaction( id::ReactionID( "526" ) );
        verifyElectronTotalElasticReaction( telastic );

        bremsstrahlung = H0.reaction( id::ReactionID( "527" ) );
        verifyElectronBremsstrahlungReaction( bremsstrahlung );

        excitation = H0.reaction( id::ReactionID( "528" ) );
        verifyElectronExcitationReaction( excitation );

        subionisation = H0.reaction( id::ReactionID( "534" ) );
        verifyElectronSubshellIonisationReaction( subionisation );

        deficit = H0.reaction( id::ReactionID( "-526" ) );
        verifyElectronElasticDeficitReaction( deficit );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given - endf/B-VIII.0" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H0 = format::endf::createProjectileTargetFromFile( "e-001_H_000-endf80.endf" );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000_e0" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID(  "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "525" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "526" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "527" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "528" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "534" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "-526" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        verifyElectronTotalReaction( total );

        auto ionisation = H0.reactions()[1];
        verifyElectronTotalIonisationReaction( ionisation );

        auto elastic = H0.reactions()[2];
        verifyElectronElasticReaction( elastic );

        auto telastic = H0.reactions()[3];
        verifyElectronTotalElasticReaction( telastic );

        auto bremsstrahlung = H0.reactions()[4];
        verifyElectronBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0.reactions()[5];
        verifyElectronExcitationReaction( excitation );

        auto subionisation = H0.reactions()[6];
        verifyElectronSubshellIonisationReaction( subionisation );

        auto deficit = H0.reactions()[7];
        verifyElectronElasticDeficitReaction( deficit );

        total = H0.reaction( id::ReactionID( "501" ) );
        verifyElectronTotalReaction( total );

        ionisation = H0.reaction( id::ReactionID( "522" ) );
        verifyElectronTotalIonisationReaction( ionisation );

        elastic = H0.reaction( id::ReactionID( "525" ) );
        verifyElectronElasticReaction( elastic );

        telastic = H0.reaction( id::ReactionID( "526" ) );
        verifyElectronTotalElasticReaction( telastic );

        bremsstrahlung = H0.reaction( id::ReactionID( "527" ) );
        verifyElectronBremsstrahlungReaction( bremsstrahlung );

        excitation = H0.reaction( id::ReactionID( "528" ) );
        verifyElectronExcitationReaction( excitation );

        subionisation = H0.reaction( id::ReactionID( "534" ) );
        verifyElectronSubshellIonisationReaction( subionisation );

        deficit = H0.reaction( id::ReactionID( "-526" ) );
        verifyElectronElasticDeficitReaction( deficit );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - photo-atomic" ) {

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H0 = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf" );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000_e0" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "502" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "504" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "515" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "516" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "517" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        verifyPhotonTotalReaction( total );

        auto coherent = H0.reactions()[1];
        verifyPhotonCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        verifyPhotonIncoherentReaction( incoherent );

        auto epairproduction = H0.reactions()[3];
        verifyPhotonElectronFieldPairProductionReaction( epairproduction );

        auto tpairproduction = H0.reactions()[4];
        verifyPhotonTotalPairProductionReaction( tpairproduction );

        auto npairproduction = H0.reactions()[5];
        verifyPhotonNuclearFieldPairProductionReaction( npairproduction );

        auto tionisation = H0.reactions()[6];
        verifyPhotonTotalIonisationReaction( tionisation );

        auto ionisation = H0.reactions()[7];
        verifyPhotonIonisationReaction( ionisation );

        total = H0.reaction( id::ReactionID( "501" ) );
        verifyPhotonTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "502" ) );
        verifyPhotonCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "504" ) );
        verifyPhotonIncoherentReaction( incoherent );

        epairproduction = H0.reaction( id::ReactionID( "515" ) );
        verifyPhotonElectronFieldPairProductionReaction( epairproduction );

        tpairproduction = H0.reaction( id::ReactionID( "516" ) );
        verifyPhotonTotalPairProductionReaction( tpairproduction );

        npairproduction = H0.reaction( id::ReactionID( "517" ) );
        verifyPhotonNuclearFieldPairProductionReaction( npairproduction );

        tionisation = H0.reaction( id::ReactionID( "522" ) );
        verifyPhotonTotalIonisationReaction( tionisation );

        ionisation = H0.reaction( id::ReactionID( "534" ) );
        verifyPhotonIonisationReaction( ionisation );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
