// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/photonuclear/createProjectileTarget.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createProjectileTarget" ) {

  GIVEN( "instances of PhotonuclearTable" ) {

    WHEN( "an la150u formatted table is given" ) {

      njoy::ACEtk::PhotonuclearTable table( njoy::ACEtk::fromFile( "6012.24u" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget C12 = format::ace::photonuclear::createProjectileTarget( table, false );

        CHECK( std::nullopt == C12.documentation().library() );
        CHECK( std::nullopt == C12.documentation().version() );
        CHECK( std::nullopt == C12.documentation().description() );

        CHECK( id::ParticleID( "g" ) == C12.projectileIdentifier() );
        CHECK( id::ParticleID( "C12" ) == C12.targetIdentifier() );

        CHECK( InteractionType::Nuclear == C12.interactionType() );

        CHECK( std::nullopt != C12.particleData() );
        photonuclear::la150u::c12::verifyParticleDatabase( C12.particleData().value() );

        CHECK( std::nullopt == C12.resonances() );

        CHECK( true == C12.hasReaction( id::ReactionID( "g,C12->total" ) ) );
        CHECK( true == C12.hasReaction( id::ReactionID( "g,C12->anything" ) ) );
        CHECK( true == C12.hasReaction( id::ReactionID( "g,C12->n,C11" ) ) );
        CHECK( true == C12.hasReaction( id::ReactionID( "g,C12->p,B11" ) ) );

        CHECK( 4 == C12.reactions().size() );

        auto total = C12.reactions()[0];
        photonuclear::la150u::c12::verifyTotalReaction( total );

        auto anything = C12.reactions()[1];
        photonuclear::la150u::c12::verifyAnythingReaction( anything );

        auto neutron = C12.reactions()[2];
        photonuclear::la150u::c12::verifyNeutronReaction( neutron );

        auto proton = C12.reactions()[3];
        photonuclear::la150u::c12::verifyProtonReaction( proton );

        total = C12.reaction( id::ReactionID( "g,C12->total" ) );
        photonuclear::la150u::c12::verifyTotalReaction( total );

        anything = C12.reaction( id::ReactionID( "g,C12->anything" ) );
        photonuclear::la150u::c12::verifyAnythingReaction( anything );

        neutron = C12.reaction( id::ReactionID( "g,C12->n,C11" ) );
        photonuclear::la150u::c12::verifyNeutronReaction( neutron );

        proton = C12.reaction( id::ReactionID( "g,C12->p,B11" ) );
        photonuclear::la150u::c12::verifyProtonReaction( proton );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
