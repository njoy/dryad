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

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000.84p" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "502" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "504" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "516" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 5 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        verifyMcplib84PhotonTotalReaction( total );

        auto coherent = H0.reactions()[1];
        verifyMcplib84PhotonCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        verifyMcplib84PhotonIncoherentReaction( incoherent );

        auto pair = H0.reactions()[3];
        verifyMcplib84PhotonPairProductionReaction( pair );

        auto photoelectric = H0.reactions()[4];
        verifyMcplib84PhotonTotalPhotoElectricReaction( photoelectric );

        total = H0.reaction( id::ReactionID( "501" ) );
        verifyMcplib84PhotonTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "502" ) );
        verifyMcplib84PhotonCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "504" ) );
        verifyMcplib84PhotonIncoherentReaction( incoherent );

        pair = H0.reaction( id::ReactionID( "516" ) );
        verifyMcplib84PhotonPairProductionReaction( pair );

        photoelectric = H0.reaction( id::ReactionID( "522" ) );
        verifyMcplib84PhotonTotalPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::photoatomic::createProjectileTarget( table );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000.12p" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "502" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "504" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "516" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        verifyEprdata12PhotonTotalReaction( total );

        auto coherent = H0.reactions()[1];
        verifyEprdata12PhotonCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        verifyEprdata12PhotonIncoherentReaction( incoherent );

        auto pair = H0.reactions()[3];
        verifyEprdata12PhotonPairProductionReaction( pair );

        auto tphotoelectric = H0.reactions()[4];
        verifyEprdata12PhotonTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = H0.reactions()[5];
        verifyEprdata12PhotonPhotoElectricReaction( photoelectric );

        total = H0.reaction( id::ReactionID( "501" ) );
        verifyEprdata12PhotonTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "502" ) );
        verifyEprdata12PhotonCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "504" ) );
        verifyEprdata12PhotonIncoherentReaction( incoherent );

        pair = H0.reaction( id::ReactionID( "516" ) );
        verifyEprdata12PhotonPairProductionReaction( pair );

        tphotoelectric = H0.reaction( id::ReactionID( "522" ) );
        verifyEprdata12PhotonTotalPhotoElectricReaction( tphotoelectric );

        photoelectric = H0.reaction( id::ReactionID( "534" ) );
        verifyEprdata12PhotonPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::photoatomic::createProjectileTarget( table );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000.14p" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID( "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "502" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "504" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "516" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "534" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 6 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        verifyEprdata14PhotonTotalReaction( total );

        auto coherent = H0.reactions()[1];
        verifyEprdata14PhotonCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        verifyEprdata14PhotonIncoherentReaction( incoherent );

        auto pair = H0.reactions()[3];
        verifyEprdata14PhotonPairProductionReaction( pair );

        auto tphotoelectric = H0.reactions()[4];
        verifyEprdata14PhotonTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = H0.reactions()[5];
        verifyEprdata14PhotonPhotoElectricReaction( photoelectric );

        total = H0.reaction( id::ReactionID( "501" ) );
        verifyEprdata14PhotonTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "502" ) );
        verifyEprdata14PhotonCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "504" ) );
        verifyEprdata14PhotonIncoherentReaction( incoherent );

        pair = H0.reaction( id::ReactionID( "516" ) );
        verifyEprdata14PhotonPairProductionReaction( pair );

        tphotoelectric = H0.reaction( id::ReactionID( "522" ) );
        verifyEprdata14PhotonTotalPhotoElectricReaction( tphotoelectric );

        photoelectric = H0.reaction( id::ReactionID( "534" ) );
        verifyEprdata14PhotonPhotoElectricReaction( photoelectric );      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
