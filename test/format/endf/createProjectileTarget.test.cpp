// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createProjectileTarget.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createProjectileTarget" ) {

  GIVEN( "ENDF materials - incident neutrons" ) {

    WHEN( "a single ENDF material is given without lumped covariance reactions" ) {

      auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
      auto material = tape.materials().front();

      THEN( "it can be converted" ) {

        ProjectileTarget H1 = format::endf::createProjectileTarget( material );

        CHECK( std::nullopt == H1.documentation().awr() );
        CHECK( std::nullopt == H1.documentation().library() );
        CHECK( std::nullopt == H1.documentation().version() );
        CHECK( std::nullopt == H1.documentation().description() );

        CHECK( id::ParticleID( "n" ) == H1.projectileIdentifier() );
        CHECK( id::ParticleID( "H1" ) == H1.targetIdentifier() );

        CHECK( InteractionType::Nuclear == H1.interactionType() );

        CHECK( false == H1.isLinearised() );

        CHECK( std::nullopt == H1.resonances() );

        CHECK( true == H1.hasReaction( id::ReactionID( "1" ) ) );
        CHECK( true == H1.hasReaction( id::ReactionID( "2" ) ) );
        CHECK( true == H1.hasReaction( id::ReactionID( "102" ) ) );
        CHECK( false == H1.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 3 == H1.reactions().size() );

        auto total = H1.reactions()[0];
        neutron::h1::verifyTotalReaction( total );

        auto elastic = H1.reactions()[1];
        neutron::h1::verifyElasticReaction( elastic );

        auto capture = H1.reactions()[2];
        neutron::h1::verifyCaptureReaction( capture );

        total = H1.reaction( id::ReactionID( "1" ) );
        neutron::h1::verifyTotalReaction( total );

        elastic = H1.reaction( id::ReactionID( "2" ) );
        neutron::h1::verifyElasticReaction( elastic );

        capture = H1.reaction( id::ReactionID( "102" ) );
        neutron::h1::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given with lumped covariance reactions" ) {

      auto tape = njoy::ENDFtk::tree::fromFile( "n-003_Li_007.endf" );
      auto material = tape.materials().front();

      THEN( "it can be converted" ) {

        ProjectileTarget Li7 = format::endf::createProjectileTarget( material );

        CHECK( std::nullopt == Li7.documentation().awr() );
        CHECK( std::nullopt == Li7.documentation().library() );
        CHECK( std::nullopt == Li7.documentation().version() );
        CHECK( std::nullopt == Li7.documentation().description() );

        CHECK( id::ParticleID( "n" ) == Li7.projectileIdentifier() );
        CHECK( id::ParticleID( "Li7" ) == Li7.targetIdentifier() );

        CHECK( InteractionType::Nuclear == Li7.interactionType() );

        CHECK( true == Li7.isLinearised() );

        CHECK( std::nullopt == Li7.resonances() );

        CHECK( true == Li7.hasReaction( id::ReactionID( "1" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "2" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "4" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "16" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "24" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "25" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "51" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "52" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "53" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "54" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "55" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "56" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "57" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "58" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "59" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "60" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "61" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "62" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "63" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "64" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "65" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "66" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "67" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "68" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "69" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "70" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "71" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "72" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "73" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "74" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "75" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "76" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "77" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "78" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "79" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "80" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "81" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "82" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "102" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "104" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "851" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "852" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "853" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "854" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "855" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "856" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "857" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "858" ) ) );
        CHECK( true == Li7.hasReaction( id::ReactionID( "859" ) ) );
        CHECK( false == Li7.hasReaction( id::ReactionID( "some unknown reaction" ) ) );
        CHECK( false == Li7.hasReaction( id::ReactionID( "203" ) ) );
        CHECK( false == Li7.hasReaction( id::ReactionID( "204" ) ) );
        CHECK( false == Li7.hasReaction( id::ReactionID( "205" ) ) );
        CHECK( false == Li7.hasReaction( id::ReactionID( "206" ) ) );

        CHECK( 49 == Li7.reactions().size() );

        auto total = Li7.reactions()[0];
        neutron::li7::verifyTotalReaction( total );

        auto elastic = Li7.reactions()[1];
        neutron::li7::verifyElasticReaction( elastic );

        auto capture = Li7.reactions()[38];
        neutron::li7::verifyCaptureReaction( capture );

        auto lumped = Li7.reactions()[40];
        neutron::li7::verifyLumpedReaction851( lumped );

        lumped = Li7.reactions()[41];
        neutron::li7::verifyLumpedReaction852( lumped );

        lumped = Li7.reactions()[42];
        neutron::li7::verifyLumpedReaction853( lumped );

        lumped = Li7.reactions()[43];
        neutron::li7::verifyLumpedReaction854( lumped );

        lumped = Li7.reactions()[44];
        neutron::li7::verifyLumpedReaction855( lumped );

        lumped = Li7.reactions()[45];
        neutron::li7::verifyLumpedReaction856( lumped );

        lumped = Li7.reactions()[46];
        neutron::li7::verifyLumpedReaction857( lumped );

        lumped = Li7.reactions()[47];
        neutron::li7::verifyLumpedReaction858( lumped );

        lumped = Li7.reactions()[48];
        neutron::li7::verifyLumpedReaction859( lumped );

        total = Li7.reaction( id::ReactionID( "1" ) );
        neutron::li7::verifyTotalReaction( total );

        elastic = Li7.reaction( id::ReactionID( "2" ) );
        neutron::li7::verifyElasticReaction( elastic );

        capture = Li7.reaction( id::ReactionID( "102" ) );
        neutron::li7::verifyCaptureReaction( capture );

        lumped = Li7.reaction( id::ReactionID( "851" ) );
        neutron::li7::verifyLumpedReaction851( lumped );

        lumped = Li7.reaction( id::ReactionID( "852" ) );
        neutron::li7::verifyLumpedReaction852( lumped );

        lumped = Li7.reaction( id::ReactionID( "853" ) );
        neutron::li7::verifyLumpedReaction853( lumped );

        lumped = Li7.reaction( id::ReactionID( "854" ) );
        neutron::li7::verifyLumpedReaction854( lumped );

        lumped = Li7.reaction( id::ReactionID( "855" ) );
        neutron::li7::verifyLumpedReaction855( lumped );

        lumped = Li7.reaction( id::ReactionID( "856" ) );
        neutron::li7::verifyLumpedReaction856( lumped );

        lumped = Li7.reaction( id::ReactionID( "857" ) );
        neutron::li7::verifyLumpedReaction857( lumped );

        lumped = Li7.reaction( id::ReactionID( "858" ) );
        neutron::li7::verifyLumpedReaction858( lumped );

        lumped = Li7.reaction( id::ReactionID( "859" ) );
        neutron::li7::verifyLumpedReaction859( lumped );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - electro-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H0 = format::endf::createProjectileTarget( material );

        CHECK( std::nullopt == H0.documentation().awr() );
        CHECK( std::nullopt == H0.documentation().library() );
        CHECK( std::nullopt == H0.documentation().version() );
        CHECK( std::nullopt == H0.documentation().description() );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "Hydrogen" ) == H0.targetIdentifier() );

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
        electron::h1::verifyTotalReaction( total );

        auto ionisation = H0.reactions()[1];
        electron::h1::verifyTotalIonisationReaction( ionisation );

        auto elastic = H0.reactions()[2];
        electron::h1::verifyElasticReaction( elastic );

        auto telastic = H0.reactions()[3];
        electron::h1::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = H0.reactions()[4];
        electron::h1::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0.reactions()[5];
        electron::h1::verifyExcitationReaction( excitation );

        auto subionisation = H0.reactions()[6];
        electron::h1::verifySubshellIonisationReaction( subionisation );

        auto deficit = H0.reactions()[7];
        electron::h1::verifyElasticDeficitReaction( deficit );

        total = H0.reaction( id::ReactionID( "501" ) );
        electron::h1::verifyTotalReaction( total );

        ionisation = H0.reaction( id::ReactionID( "522" ) );
        electron::h1::verifyTotalIonisationReaction( ionisation );

        elastic = H0.reaction( id::ReactionID( "525" ) );
        electron::h1::verifyElasticReaction( elastic );

        telastic = H0.reaction( id::ReactionID( "526" ) );
        electron::h1::verifyTotalElasticReaction( telastic );

        bremsstrahlung = H0.reaction( id::ReactionID( "527" ) );
        electron::h1::verifyBremsstrahlungReaction( bremsstrahlung );

        excitation = H0.reaction( id::ReactionID( "528" ) );
        electron::h1::verifyExcitationReaction( excitation );

        subionisation = H0.reaction( id::ReactionID( "534" ) );
        electron::h1::verifySubshellIonisationReaction( subionisation );

        deficit = H0.reaction( id::ReactionID( "-526" ) );
        electron::h1::verifyElasticDeficitReaction( deficit );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - photo-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H0 = format::endf::createProjectileTarget( material );

        CHECK( std::nullopt == H0.documentation().awr() );
        CHECK( std::nullopt == H0.documentation().library() );
        CHECK( std::nullopt == H0.documentation().version() );
        CHECK( std::nullopt == H0.documentation().description() );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "Hydrogen" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID(  "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "502" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "504" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "515" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "516" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "517" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "534" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        photoatomic::h1::verifyTotalReaction( total );

        auto coherent = H0.reactions()[1];
        photoatomic::h1::verifyCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        photoatomic::h1::verifyIncoherentReaction( incoherent );

        auto epairproduction = H0.reactions()[3];
        photoatomic::h1::verifyElectronFieldPairProductionReaction( epairproduction );

        auto tpairproduction = H0.reactions()[4];
        photoatomic::h1::verifyTotalPairProductionReaction( tpairproduction );

        auto npairproduction = H0.reactions()[5];
        photoatomic::h1::verifyNuclearFieldPairProductionReaction( npairproduction );

        auto tionisation = H0.reactions()[6];
        photoatomic::h1::verifyTotalIonisationReaction( tionisation );

        auto ionisation = H0.reactions()[7];
        photoatomic::h1::verifyIonisationReaction( ionisation );

        total = H0.reaction( id::ReactionID( "501" ) );
        photoatomic::h1::verifyTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "502" ) );
        photoatomic::h1::verifyCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "504" ) );
        photoatomic::h1::verifyIncoherentReaction( incoherent );

        epairproduction = H0.reaction( id::ReactionID( "515" ) );
        photoatomic::h1::verifyElectronFieldPairProductionReaction( epairproduction );

        tpairproduction = H0.reaction( id::ReactionID( "516" ) );
        photoatomic::h1::verifyTotalPairProductionReaction( tpairproduction );

        npairproduction = H0.reaction( id::ReactionID( "517" ) );
        photoatomic::h1::verifyNuclearFieldPairProductionReaction( npairproduction );

        tionisation = H0.reaction( id::ReactionID( "522" ) );
        photoatomic::h1::verifyTotalIonisationReaction( tionisation );

        ionisation = H0.reaction( id::ReactionID( "534" ) );
        photoatomic::h1::verifyIonisationReaction( ionisation );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
