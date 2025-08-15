// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/photoatomic/createProjectileTarget.hpp"

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

        ProjectileTarget H0 = format::ace::photoatomic::createProjectileTarget( table );

        CHECK( std::nullopt == H0.documentation().awr() );
        CHECK( std::nullopt == H0.documentation().library() );
        CHECK( std::nullopt == H0.documentation().version() );
        CHECK( std::nullopt == H0.documentation().description() );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->total[atomic]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->g,H[coherent]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->g,H[incoherent]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->pair-production" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->e-,H" ) ) );
//        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 5 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        photoatomic::mcplib84::h::verifyTotalReaction( total );

        auto coherent = H0.reactions()[1];
        photoatomic::mcplib84::h::verifyCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        photoatomic::mcplib84::h::verifyIncoherentReaction( incoherent );

        auto pair = H0.reactions()[3];
        photoatomic::mcplib84::h::verifyPairProductionReaction( pair );

        auto photoelectric = H0.reactions()[4];
        photoatomic::mcplib84::h::verifyTotalPhotoElectricReaction( photoelectric );

        total = H0.reaction( id::ReactionID( "g,H->total[atomic]" ) );
        photoatomic::mcplib84::h::verifyTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "g,H->g,H[coherent]" ) );
        photoatomic::mcplib84::h::verifyCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "g,H->g,H[incoherent]" ) );
        photoatomic::mcplib84::h::verifyIncoherentReaction( incoherent );

        pair = H0.reaction( id::ReactionID( "g,H->pair-production" ) );
        photoatomic::mcplib84::h::verifyPairProductionReaction( pair );

        photoelectric = H0.reaction( id::ReactionID( "g,H->e-,H" ) );
        photoatomic::mcplib84::h::verifyTotalPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::photoatomic::createProjectileTarget( table );

        CHECK( std::nullopt == H0.documentation().awr() );
        CHECK( std::nullopt == H0.documentation().library() );
        CHECK( std::nullopt == H0.documentation().version() );
        CHECK( std::nullopt == H0.documentation().description() );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->total[atomic]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->g,H[coherent]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->g,H[incoherent]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->pair-production" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->e-,H" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->e-,H{1s1/2}" ) ) );
//        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        photoatomic::eprdata12::h::verifyTotalReaction( total );

        auto coherent = H0.reactions()[1];
        photoatomic::eprdata12::h::verifyCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        photoatomic::eprdata12::h::verifyIncoherentReaction( incoherent );

        auto pair = H0.reactions()[3];
        photoatomic::eprdata12::h::verifyPairProductionReaction( pair );

        auto tphotoelectric = H0.reactions()[4];
        photoatomic::eprdata12::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = H0.reactions()[5];
        photoatomic::eprdata12::h::verifyPhotoElectricReaction( photoelectric );

        total = H0.reaction( id::ReactionID( "g,H->total[atomic]" ) );
        photoatomic::eprdata12::h::verifyTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "g,H->g,H[coherent]" ) );
        photoatomic::eprdata12::h::verifyCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "g,H->g,H[incoherent]" ) );
        photoatomic::eprdata12::h::verifyIncoherentReaction( incoherent );

        pair = H0.reaction( id::ReactionID( "g,H->pair-production" ) );
        photoatomic::eprdata12::h::verifyPairProductionReaction( pair );

        tphotoelectric = H0.reaction( id::ReactionID( "g,H->e-,H" ) );
        photoatomic::eprdata12::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        photoelectric = H0.reaction( id::ReactionID( "g,H->e-,H{1s1/2}" ) );
        photoatomic::eprdata12::h::verifyPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::photoatomic::createProjectileTarget( table );

        CHECK( std::nullopt == H0.documentation().awr() );
        CHECK( std::nullopt == H0.documentation().library() );
        CHECK( std::nullopt == H0.documentation().version() );
        CHECK( std::nullopt == H0.documentation().description() );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( 1000 ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->total[atomic]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->g,H[coherent]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->g,H[incoherent]" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->pair-production" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->e-,H" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "g,H->e-,H{1s1/2}" ) ) );
//        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        photoatomic::eprdata14::h::verifyTotalReaction( total );

        auto coherent = H0.reactions()[1];
        photoatomic::eprdata14::h::verifyCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        photoatomic::eprdata14::h::verifyIncoherentReaction( incoherent );

        auto pair = H0.reactions()[3];
        photoatomic::eprdata14::h::verifyPairProductionReaction( pair );

        auto tphotoelectric = H0.reactions()[4];
        photoatomic::eprdata14::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = H0.reactions()[5];
        photoatomic::eprdata14::h::verifyPhotoElectricReaction( photoelectric );

        total = H0.reaction( id::ReactionID( "g,H->total[atomic]" ) );
        photoatomic::eprdata14::h::verifyTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "g,H->g,H[coherent]" ) );
        photoatomic::eprdata14::h::verifyCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "g,H->g,H[incoherent]" ) );
        photoatomic::eprdata14::h::verifyIncoherentReaction( incoherent );

        pair = H0.reaction( id::ReactionID( "g,H->pair-production" ) );
        photoatomic::eprdata14::h::verifyPairProductionReaction( pair );

        tphotoelectric = H0.reaction( id::ReactionID( "g,H->e-,H" ) );
        photoatomic::eprdata14::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        photoelectric = H0.reaction( id::ReactionID( "g,H->e-,H{1s1/2}" ) );
        photoatomic::eprdata14::h::verifyPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
