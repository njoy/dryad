// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/electroatomic/createProjectileTarget.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createProjectileTarget" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::electroatomic::createProjectileTarget( table );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::electroatomic::createProjectileTarget( table );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "526" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "527" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "528" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        verifyEprdata12ElectronTotalReaction( total );

        auto tionisation = H0.reactions()[1];
        verifyEprdata12ElectronTotalIonisationReaction( tionisation );

        auto telastic = H0.reactions()[2];
        verifyEprdata12ElectronTotalElasticReaction( telastic );

        auto bremsstrahlung = H0.reactions()[3];
        verifyEprdata12ElectronBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0.reactions()[4];
        verifyEprdata12ElectronExcitationReaction( excitation );

        auto ionisation = H0.reactions()[5];
        verifyEprdata12ElectronIonisationReaction( ionisation );

        total = H0.reaction( id::ReactionID( "501" ) );
        verifyEprdata12ElectronTotalReaction( total );

        tionisation = H0.reaction( id::ReactionID( "522" ) );
        verifyEprdata12ElectronTotalIonisationReaction( tionisation );

        telastic = H0.reaction( id::ReactionID( "526" ) );
        verifyEprdata12ElectronTotalElasticReaction( telastic );

        bremsstrahlung = H0.reaction( id::ReactionID( "527" ) );
        verifyEprdata12ElectronBremsstrahlungReaction( bremsstrahlung );

        excitation = H0.reaction( id::ReactionID( "528" ) );
        verifyEprdata12ElectronExcitationReaction( excitation );

        ionisation = H0.reaction( id::ReactionID( "534" ) );
        verifyEprdata12ElectronIonisationReaction( ionisation );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::electroatomic::createProjectileTarget( table );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "525" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "526" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "527" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "528" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "-526" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        verifyEprdata14ElectronTotalReaction( total );

        auto tionisation = H0.reactions()[1];
        verifyEprdata14ElectronTotalIonisationReaction( tionisation );

        auto elastic = H0.reactions()[2];
        verifyEprdata14ElectronLargeAngleElasticReaction( elastic );

        auto telastic = H0.reactions()[3];
        verifyEprdata14ElectronTotalElasticReaction( telastic );

        auto bremsstrahlung = H0.reactions()[4];
        verifyEprdata14ElectronBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0.reactions()[5];
        verifyEprdata14ElectronExcitationReaction( excitation );

        auto ionisation = H0.reactions()[6];
        verifyEprdata14ElectronIonisationReaction( ionisation );

        auto deficit = H0.reactions()[7];
        verifyEprdata14ElectronElasticReactionDeficit( deficit );

        total = H0.reaction( id::ReactionID( "501" ) );
        verifyEprdata14ElectronTotalReaction( total );

        tionisation = H0.reaction( id::ReactionID( "522" ) );
        verifyEprdata14ElectronTotalIonisationReaction( tionisation );

        elastic = H0.reaction( id::ReactionID( "525" ) );
        verifyEprdata14ElectronLargeAngleElasticReaction( elastic );

        telastic = H0.reaction( id::ReactionID( "526" ) );
        verifyEprdata14ElectronTotalElasticReaction( telastic );

        bremsstrahlung = H0.reaction( id::ReactionID( "527" ) );
        verifyEprdata14ElectronBremsstrahlungReaction( bremsstrahlung );

        excitation = H0.reaction( id::ReactionID( "528" ) );
        verifyEprdata14ElectronExcitationReaction( excitation );

        ionisation = H0.reaction( id::ReactionID( "534" ) );
        verifyEprdata14ElectronIonisationReaction( ionisation );

        deficit = H0.reaction( id::ReactionID( "-526" ) );
        verifyEprdata14ElectronElasticReactionDeficit( deficit );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
