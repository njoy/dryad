// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/createProjectileTargetFromFile.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "electroatomic/test_verification_functions.hpp"
#include "photoatomic/test_verification_functions.hpp"

SCENARIO( "createProjectileTargetFromFile" ) {

  GIVEN( "photoatomic and electroatomic ace file names" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      THEN( "a ProjectileTarget can be derived" ) {

        auto targets = format::ace::createProjectileTargetFromFile( "1000.84p" );

        CHECK( true == std::holds_alternative< ProjectileTarget >( targets ) );
        auto H0_pa = std::get< ProjectileTarget >( targets );

        CHECK( std::nullopt == H0_pa.documentation().awr() );
        CHECK( std::nullopt == H0_pa.documentation().library() );
        CHECK( std::nullopt == H0_pa.documentation().version() );
        CHECK( std::nullopt == H0_pa.documentation().description() );

        CHECK( id::ParticleID( "g" ) == H0_pa.projectileIdentifier() );
        CHECK( id::ParticleID( "H" ) == H0_pa.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0_pa.interactionType() );

        CHECK( true == H0_pa.isLinearised() );

        CHECK( std::nullopt == H0_pa.resonances() );

        CHECK( true == H0_pa.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "502" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "504" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "516" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( false == H0_pa.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 5 == H0_pa.reactions().size() );

        auto total = H0_pa.reactions()[0];
        photoatomic::mcplib84::h::verifyTotalReaction( total );

        auto coherent = H0_pa.reactions()[1];
        photoatomic::mcplib84::h::verifyCoherentReaction( coherent );

        auto incoherent = H0_pa.reactions()[2];
        photoatomic::mcplib84::h::verifyIncoherentReaction( incoherent );

        auto pair = H0_pa.reactions()[3];
        photoatomic::mcplib84::h::verifyPairProductionReaction( pair );

        auto photoelectric = H0_pa.reactions()[4];
        photoatomic::mcplib84::h::verifyTotalPhotoElectricReaction( photoelectric );

        total = H0_pa.reaction( id::ReactionID( "501" ) );
        photoatomic::mcplib84::h::verifyTotalReaction( total );

        coherent = H0_pa.reaction( id::ReactionID( "502" ) );
        photoatomic::mcplib84::h::verifyCoherentReaction( coherent );

        incoherent = H0_pa.reaction( id::ReactionID( "504" ) );
        photoatomic::mcplib84::h::verifyIncoherentReaction( incoherent );

        pair = H0_pa.reaction( id::ReactionID( "516" ) );
        photoatomic::mcplib84::h::verifyPairProductionReaction( pair );

        photoelectric = H0_pa.reaction( id::ReactionID( "522" ) );
        photoatomic::mcplib84::h::verifyTotalPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        auto targets = format::ace::createProjectileTargetFromFile( "1000.12p" );

        CHECK( true == std::holds_alternative< std::pair< ProjectileTarget, ProjectileTarget > >( targets ) );
        auto H0_pa = std::get< std::pair< ProjectileTarget, ProjectileTarget > >( targets ).first;
        auto H0_ea = std::get< std::pair< ProjectileTarget, ProjectileTarget > >( targets ).second;

        // photoatomic data
        CHECK( std::nullopt == H0_pa.documentation().awr() );
        CHECK( std::nullopt == H0_pa.documentation().library() );
        CHECK( std::nullopt == H0_pa.documentation().version() );
        CHECK( std::nullopt == H0_pa.documentation().description() );

        CHECK( id::ParticleID( "g" ) == H0_pa.projectileIdentifier() );
        CHECK( id::ParticleID( "H" ) == H0_pa.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0_pa.interactionType() );

        CHECK( true == H0_pa.isLinearised() );

        CHECK( std::nullopt == H0_pa.resonances() );

        CHECK( true == H0_pa.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "502" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "504" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "516" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( false == H0_pa.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0_pa.reactions().size() );

        auto total = H0_pa.reactions()[0];
        photoatomic::eprdata12::h::verifyTotalReaction( total );

        auto coherent = H0_pa.reactions()[1];
        photoatomic::eprdata12::h::verifyCoherentReaction( coherent );

        auto incoherent = H0_pa.reactions()[2];
        photoatomic::eprdata12::h::verifyIncoherentReaction( incoherent );

        auto pair = H0_pa.reactions()[3];
        photoatomic::eprdata12::h::verifyPairProductionReaction( pair );

        auto tphotoelectric = H0_pa.reactions()[4];
        photoatomic::eprdata12::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = H0_pa.reactions()[5];
        photoatomic::eprdata12::h::verifyPhotoElectricReaction( photoelectric );

        total = H0_pa.reaction( id::ReactionID( "501" ) );
        photoatomic::eprdata12::h::verifyTotalReaction( total );

        coherent = H0_pa.reaction( id::ReactionID( "502" ) );
        photoatomic::eprdata12::h::verifyCoherentReaction( coherent );

        incoherent = H0_pa.reaction( id::ReactionID( "504" ) );
        photoatomic::eprdata12::h::verifyIncoherentReaction( incoherent );

        pair = H0_pa.reaction( id::ReactionID( "516" ) );
        photoatomic::eprdata12::h::verifyPairProductionReaction( pair );

        tphotoelectric = H0_pa.reaction( id::ReactionID( "522" ) );
        photoatomic::eprdata12::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        photoelectric = H0_pa.reaction( id::ReactionID( "534" ) );
        photoatomic::eprdata12::h::verifyPhotoElectricReaction( photoelectric );

        // electroatomic data
        CHECK( std::nullopt == H0_ea.documentation().awr() );
        CHECK( std::nullopt == H0_ea.documentation().library() );
        CHECK( std::nullopt == H0_ea.documentation().version() );
        CHECK( std::nullopt == H0_ea.documentation().description() );

        CHECK( id::ParticleID( "e-" ) == H0_ea.projectileIdentifier() );
        CHECK( id::ParticleID( "H" ) == H0_ea.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0_ea.interactionType() );

        CHECK( true == H0_ea.isLinearised() );

        CHECK( std::nullopt == H0_ea.resonances() );

        CHECK( true == H0_ea.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "526" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "527" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "528" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( false == H0_ea.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0_ea.reactions().size() );

        total = H0_ea.reactions()[0];
        electroatomic::eprdata12::h::verifyTotalReaction( total );

        auto tionisation = H0_ea.reactions()[1];
        electroatomic::eprdata12::h::verifyTotalIonisationReaction( tionisation );

        auto telastic = H0_ea.reactions()[2];
        electroatomic::eprdata12::h::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = H0_ea.reactions()[3];
        electroatomic::eprdata12::h::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0_ea.reactions()[4];
        electroatomic::eprdata12::h::verifyExcitationReaction( excitation );

        auto ionisation = H0_ea.reactions()[5];
        electroatomic::eprdata12::h::verifyIonisationReaction( ionisation );

        total = H0_ea.reaction( id::ReactionID( "501" ) );
        electroatomic::eprdata12::h::verifyTotalReaction( total );

        tionisation = H0_ea.reaction( id::ReactionID( "522" ) );
        electroatomic::eprdata12::h::verifyTotalIonisationReaction( tionisation );

        telastic = H0_ea.reaction( id::ReactionID( "526" ) );
        electroatomic::eprdata12::h::verifyTotalElasticReaction( telastic );

        bremsstrahlung = H0_ea.reaction( id::ReactionID( "527" ) );
        electroatomic::eprdata12::h::verifyBremsstrahlungReaction( bremsstrahlung );

        excitation = H0_ea.reaction( id::ReactionID( "528" ) );
        electroatomic::eprdata12::h::verifyExcitationReaction( excitation );

        ionisation = H0_ea.reaction( id::ReactionID( "534" ) );
        electroatomic::eprdata12::h::verifyIonisationReaction( ionisation );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      THEN( "a ProjectileTarget can be derived" ) {

        auto targets = format::ace::createProjectileTargetFromFile( "1000.14p" );

        CHECK( true == std::holds_alternative< std::pair< ProjectileTarget, ProjectileTarget > >( targets ) );
        auto H0_pa = std::get< std::pair< ProjectileTarget, ProjectileTarget > >( targets ).first;
        auto H0_ea = std::get< std::pair< ProjectileTarget, ProjectileTarget > >( targets ).second;

        // photoatomic data
        CHECK( std::nullopt == H0_pa.documentation().awr() );
        CHECK( std::nullopt == H0_pa.documentation().library() );
        CHECK( std::nullopt == H0_pa.documentation().version() );
        CHECK( std::nullopt == H0_pa.documentation().description() );

        CHECK( id::ParticleID( "g" ) == H0_pa.projectileIdentifier() );
        CHECK( id::ParticleID( "H" ) == H0_pa.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0_pa.interactionType() );

        CHECK( true == H0_pa.isLinearised() );

        CHECK( std::nullopt == H0_pa.resonances() );

        CHECK( true == H0_pa.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "502" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "504" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "516" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0_pa.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( false == H0_pa.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0_pa.reactions().size() );

        auto total = H0_pa.reactions()[0];
        photoatomic::eprdata14::h::verifyTotalReaction( total );

        auto coherent = H0_pa.reactions()[1];
        photoatomic::eprdata14::h::verifyCoherentReaction( coherent );

        auto incoherent = H0_pa.reactions()[2];
        photoatomic::eprdata14::h::verifyIncoherentReaction( incoherent );

        auto pair = H0_pa.reactions()[3];
        photoatomic::eprdata14::h::verifyPairProductionReaction( pair );

        auto tphotoelectric = H0_pa.reactions()[4];
        photoatomic::eprdata14::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = H0_pa.reactions()[5];
        photoatomic::eprdata14::h::verifyPhotoElectricReaction( photoelectric );

        total = H0_pa.reaction( id::ReactionID( "501" ) );
        photoatomic::eprdata14::h::verifyTotalReaction( total );

        coherent = H0_pa.reaction( id::ReactionID( "502" ) );
        photoatomic::eprdata14::h::verifyCoherentReaction( coherent );

        incoherent = H0_pa.reaction( id::ReactionID( "504" ) );
        photoatomic::eprdata14::h::verifyIncoherentReaction( incoherent );

        pair = H0_pa.reaction( id::ReactionID( "516" ) );
        photoatomic::eprdata14::h::verifyPairProductionReaction( pair );

        tphotoelectric = H0_pa.reaction( id::ReactionID( "522" ) );
        photoatomic::eprdata14::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        photoelectric = H0_pa.reaction( id::ReactionID( "534" ) );
        photoatomic::eprdata14::h::verifyPhotoElectricReaction( photoelectric );

        // electroatomic data
        CHECK( std::nullopt == H0_ea.documentation().awr() );
        CHECK( std::nullopt == H0_ea.documentation().library() );
        CHECK( std::nullopt == H0_ea.documentation().version() );
        CHECK( std::nullopt == H0_ea.documentation().description() );

        CHECK( id::ParticleID( "e-" ) == H0_ea.projectileIdentifier() );
        CHECK( id::ParticleID( "H" ) == H0_ea.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0_ea.interactionType() );

        CHECK( true == H0_ea.isLinearised() );

        CHECK( std::nullopt == H0_ea.resonances() );

        CHECK( true == H0_ea.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "525" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "526" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "527" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "528" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( true == H0_ea.hasReaction( id::ReactionID( "-526" ) ) );
        CHECK( false == H0_ea.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0_ea.reactions().size() );

        total = H0_ea.reactions()[0];
        electroatomic::eprdata14::h::verifyTotalReaction( total );

        auto tionisation = H0_ea.reactions()[1];
        electroatomic::eprdata14::h::verifyTotalIonisationReaction( tionisation );

        auto elastic = H0_ea.reactions()[2];
        electroatomic::eprdata14::h::verifyLargeAngleElasticReaction( elastic );

        auto telastic = H0_ea.reactions()[3];
        electroatomic::eprdata14::h::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = H0_ea.reactions()[4];
        electroatomic::eprdata14::h::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0_ea.reactions()[5];
        electroatomic::eprdata14::h::verifyExcitationReaction( excitation );

        auto ionisation = H0_ea.reactions()[6];
        electroatomic::eprdata14::h::verifyIonisationReaction( ionisation );

        auto deficit = H0_ea.reactions()[7];
        electroatomic::eprdata14::h::verifyElasticReactionDeficit( deficit );

        total = H0_ea.reaction( id::ReactionID( "501" ) );
        electroatomic::eprdata14::h::verifyTotalReaction( total );

        tionisation = H0_ea.reaction( id::ReactionID( "522" ) );
        electroatomic::eprdata14::h::verifyTotalIonisationReaction( tionisation );

        elastic = H0_ea.reaction( id::ReactionID( "525" ) );
        electroatomic::eprdata14::h::verifyLargeAngleElasticReaction( elastic );

        telastic = H0_ea.reaction( id::ReactionID( "526" ) );
        electroatomic::eprdata14::h::verifyTotalElasticReaction( telastic );

        bremsstrahlung = H0_ea.reaction( id::ReactionID( "527" ) );
        electroatomic::eprdata14::h::verifyBremsstrahlungReaction( bremsstrahlung );

        excitation = H0_ea.reaction( id::ReactionID( "528" ) );
        electroatomic::eprdata14::h::verifyExcitationReaction( excitation );

        ionisation = H0_ea.reaction( id::ReactionID( "534" ) );
        electroatomic::eprdata14::h::verifyIonisationReaction( ionisation );

        deficit = H0_ea.reaction( id::ReactionID( "-526" ) );
        electroatomic::eprdata14::h::verifyElasticReactionDeficit( deficit );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
