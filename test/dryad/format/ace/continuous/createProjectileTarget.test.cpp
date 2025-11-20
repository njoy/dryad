// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/continuous/createProjectileTarget.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createProjectileTarget" ) {

  GIVEN( "instances of ContinuousEnergyTable" ) {

    WHEN( "a Lib81 formatted table is given" ) {

      njoy::ACEtk::ContinuousEnergyTable table( njoy::ACEtk::fromFile( "1001.10c" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H1 = format::ace::continuous::createProjectileTarget( table, false );

        CHECK( std::nullopt == H1.documentation().awr() );
        CHECK( std::nullopt == H1.documentation().library() );
        CHECK( std::nullopt == H1.documentation().version() );
        CHECK( std::nullopt == H1.documentation().description() );

        CHECK( id::ParticleID( "n" ) == H1.projectileIdentifier() );
        CHECK( id::ParticleID( "H1" ) == H1.targetIdentifier() );

        CHECK( InteractionType::Nuclear == H1.interactionType() );

        CHECK( std::nullopt == H1.resonances() );

        CHECK( false == H1.hasReaction( id::ReactionID( "n,H1->total" ) ) );
        CHECK( true == H1.hasReaction( id::ReactionID( "n,H1->n,H1" ) ) );
        CHECK( true == H1.hasReaction( id::ReactionID( "n,H1->g,H2[all]" ) ) );

        CHECK( 2 == H1.reactions().size() );

        auto elastic = H1.reactions()[0];
        continuous::lib81::h1::verifyElasticReaction( elastic );

        auto capture = H1.reactions()[1];
        continuous::lib81::h1::verifyCaptureReaction( capture );

        elastic = H1.reaction( id::ReactionID( "n,H1->n,H1" ) );
        continuous::lib81::h1::verifyElasticReaction( elastic );

        capture = H1.reaction( id::ReactionID( "n,H1->g,H2[all]" ) );
        continuous::lib81::h1::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
