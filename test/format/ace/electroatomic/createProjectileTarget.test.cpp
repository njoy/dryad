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

        CHECK( std::nullopt == H0.documentation().awr() );
        CHECK( std::nullopt == H0.documentation().library() );
        CHECK( std::nullopt == H0.documentation().version() );
        CHECK( std::nullopt == H0.documentation().description() );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::electroatomic::createProjectileTarget( table );

        CHECK( std::nullopt == H0.documentation().awr() );
        CHECK( std::nullopt == H0.documentation().library() );
        CHECK( std::nullopt == H0.documentation().version() );
        CHECK( std::nullopt == H0.documentation().description() );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->total[atomic]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->2e-,H" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->e-,H[total-scattering]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->e-,H[excitation]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->e-,H[bremsstrahlung]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->2e-,H{1s1/2}" ) ) );
//        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        electroatomic::eprdata12::h::verifyTotalReaction( total );

        auto tionisation = H0.reactions()[1];
        electroatomic::eprdata12::h::verifyTotalIonisationReaction( tionisation );

        auto telastic = H0.reactions()[2];
        electroatomic::eprdata12::h::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = H0.reactions()[3];
        electroatomic::eprdata12::h::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0.reactions()[4];
        electroatomic::eprdata12::h::verifyExcitationReaction( excitation );

        auto ionisation = H0.reactions()[5];
        electroatomic::eprdata12::h::verifyIonisationReaction( ionisation );

        total = H0.reaction( id::ReactionID( "e-,H->total[atomic]" ) );
        electroatomic::eprdata12::h::verifyTotalReaction( total );

        tionisation = H0.reaction( id::ReactionID( "e-,H->2e-,H" ) );
        electroatomic::eprdata12::h::verifyTotalIonisationReaction( tionisation );

        telastic = H0.reaction( id::ReactionID( "e-,H->e-,H[total-scattering]" ) );
        electroatomic::eprdata12::h::verifyTotalElasticReaction( telastic );

        bremsstrahlung = H0.reaction( id::ReactionID( "e-,H->e-,H[bremsstrahlung]" ) );
        electroatomic::eprdata12::h::verifyBremsstrahlungReaction( bremsstrahlung );

        excitation = H0.reaction( id::ReactionID( "e-,H->e-,H[excitation]" ) );
        electroatomic::eprdata12::h::verifyExcitationReaction( excitation );

        ionisation = H0.reaction( id::ReactionID( "e-,H->2e-,H{1s1/2}" ) );
        electroatomic::eprdata12::h::verifyIonisationReaction( ionisation );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::electroatomic::createProjectileTarget( table );

        CHECK( std::nullopt == H0.documentation().awr() );
        CHECK( std::nullopt == H0.documentation().library() );
        CHECK( std::nullopt == H0.documentation().version() );
        CHECK( std::nullopt == H0.documentation().description() );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->total[atomic]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->2e-,H" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->e-,H[large-angle-scattering]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->e-,H[total-scattering]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->e-,H[excitation]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->e-,H[bremsstrahlung]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->2e-,H{1s1/2}" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "e-,H->e-,H[deficit-scattering]" ) ) );
//        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        electroatomic::eprdata14::h::verifyTotalReaction( total );

        auto tionisation = H0.reactions()[1];
        electroatomic::eprdata14::h::verifyTotalIonisationReaction( tionisation );

        auto elastic = H0.reactions()[2];
        electroatomic::eprdata14::h::verifyLargeAngleElasticReaction( elastic );

        auto telastic = H0.reactions()[3];
        electroatomic::eprdata14::h::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = H0.reactions()[4];
        electroatomic::eprdata14::h::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0.reactions()[5];
        electroatomic::eprdata14::h::verifyExcitationReaction( excitation );

        auto ionisation = H0.reactions()[6];
        electroatomic::eprdata14::h::verifyIonisationReaction( ionisation );

        auto deficit = H0.reactions()[7];
        electroatomic::eprdata14::h::verifyElasticReactionDeficit( deficit );

        total = H0.reaction( id::ReactionID( "e-,H->total[atomic]" ) );
        electroatomic::eprdata14::h::verifyTotalReaction( total );

        tionisation = H0.reaction( id::ReactionID( "e-,H->2e-,H" ) );
        electroatomic::eprdata14::h::verifyTotalIonisationReaction( tionisation );

        elastic = H0.reaction( id::ReactionID( "e-,H->e-,H[large-angle-scattering]" ) );
        electroatomic::eprdata14::h::verifyLargeAngleElasticReaction( elastic );

        telastic = H0.reaction( id::ReactionID( "e-,H->e-,H[total-scattering]" ) );
        electroatomic::eprdata14::h::verifyTotalElasticReaction( telastic );

        bremsstrahlung = H0.reaction( id::ReactionID( "e-,H->e-,H[bremsstrahlung]" ) );
        electroatomic::eprdata14::h::verifyBremsstrahlungReaction( bremsstrahlung );

        excitation = H0.reaction( id::ReactionID( "e-,H->e-,H[excitation]" ) );
        electroatomic::eprdata14::h::verifyExcitationReaction( excitation );

        ionisation = H0.reaction( id::ReactionID( "e-,H->2e-,H{1s1/2}" ) );
        electroatomic::eprdata14::h::verifyIonisationReaction( ionisation );

        deficit = H0.reaction( id::ReactionID( "e-,H->e-,H[deficit-scattering]" ) );
        electroatomic::eprdata14::h::verifyElasticReactionDeficit( deficit );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
