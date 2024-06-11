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

void verifyTotalReaction( const Reaction& );
void verifyElasticReaction( const Reaction& );
void verifyCaptureReaction( const Reaction& );

SCENARIO( "projectileTarget" ) {

  GIVEN( "ENDF materials" ) {

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H1 = format::endf::createProjectileTargetFromFile( "n-001_H_001.endf" );

        CHECK( ParticleID( "n" ) == H1.projectileIdentifier() );
        CHECK( ParticleID( "1001_e0" ) == H1.targetIdentifier() );

        CHECK( InteractionType::Nuclear == H1.interactionType() );

        CHECK( false == H1.isLinearised() );

        CHECK( std::nullopt == H1.resonances() );

        CHECK( true == H1.hasReaction( ReactionID( "1" ) ) );
        CHECK( true == H1.hasReaction( ReactionID( "2" ) ) );
        CHECK( true == H1.hasReaction( ReactionID( "102" ) ) );
        CHECK( false == H1.hasReaction( ReactionID( "some unknown reaction" ) ) );

        auto total = H1.reactions()[0];
        verifyTotalReaction( total );

        auto elastic = H1.reactions()[1];
        verifyElasticReaction( elastic );

        auto capture = H1.reactions()[2];
        verifyCaptureReaction( capture );

        total = H1.reaction( ReactionID( "1" ) );
        verifyTotalReaction( total );

        elastic = H1.reaction( ReactionID( "2" ) );
        verifyElasticReaction( elastic );

        capture = H1.reaction( ReactionID( "102" ) );
        verifyCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyTotalReaction( const Reaction& total ) {

  CHECK( ReactionID( "1" ) == total.identifier() );
  CHECK( false == total.isLinearised() );
  CHECK_THAT( 0, WithinRel( total.massDifferenceQValue().value() ) );
  CHECK_THAT( 0, WithinRel( total.reactionQValue().value() ) );
  CHECK( false == total.crossSection().isLinearised() );
  CHECK( 153 == total.crossSection().numberPoints() );
  CHECK( 2 == total.crossSection().numberRegions() );
  CHECK( 153 == total.crossSection().energies().size() );
  CHECK( 153 == total.crossSection().values().size() );
  CHECK( 2 == total.crossSection().boundaries().size() );
  CHECK( 2 == total.crossSection().interpolants().size() );
  CHECK( 8 == total.crossSection().boundaries()[0] );
  CHECK( 152 == total.crossSection().boundaries()[1] );
  CHECK( InterpolationType::LogLog == total.crossSection().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == total.crossSection().interpolants()[1] );
  CHECK_THAT( 1e-5, WithinRel( total.crossSection().energies()[0] ) );
  CHECK_THAT( 5e-3, WithinRel( total.crossSection().energies()[8] ) );
  CHECK_THAT( 2e+7, WithinRel( total.crossSection().energies()[152] ) );
  CHECK_THAT( 3.716477e+1, WithinRel( total.crossSection().values()[0] ) );
  CHECK_THAT( 2.118421e+1, WithinRel( total.crossSection().values()[8] ) );
  CHECK_THAT( 4.818679e-1, WithinRel( total.crossSection().values()[152] ) );
}

void verifyElasticReaction( const Reaction& elastic ) {

  CHECK( ReactionID( "2" ) == elastic.identifier() );
  CHECK( true == elastic.isLinearised() );
  CHECK_THAT( 0, WithinRel( elastic.massDifferenceQValue().value() ) );
  CHECK_THAT( 0, WithinRel( elastic.reactionQValue().value() ) );
  CHECK( true == elastic.crossSection().isLinearised() );
  CHECK( 153 == elastic.crossSection().numberPoints() );
  CHECK( 1 == elastic.crossSection().numberRegions() );
  CHECK( 153 == elastic.crossSection().energies().size() );
  CHECK( 153 == elastic.crossSection().values().size() );
  CHECK( 1 == elastic.crossSection().boundaries().size() );
  CHECK( 1 == elastic.crossSection().interpolants().size() );
  CHECK( 152 == elastic.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == elastic.crossSection().interpolants()[0] );
  CHECK_THAT( 1e-5, WithinRel( elastic.crossSection().energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( elastic.crossSection().energies()[152] ) );
  CHECK_THAT( 2.043608e+1, WithinRel( elastic.crossSection().values()[0] ) );
  CHECK_THAT( 4.818408e-1, WithinRel( elastic.crossSection().values()[152] ) );
}

void verifyCaptureReaction( const Reaction& capture ) {

  CHECK( ReactionID( "102" ) == capture.identifier() );
  CHECK( false == capture.isLinearised() );
  CHECK_THAT( 2.224648e+6, WithinRel( capture.massDifferenceQValue().value() ) );
  CHECK_THAT( 2.224648e+6, WithinRel( capture.reactionQValue().value() ) );
  CHECK( false == capture.crossSection().isLinearised() );
  CHECK( 153 == capture.crossSection().numberPoints() );
  CHECK( 2 == capture.crossSection().numberRegions() );
  CHECK( 153 == capture.crossSection().energies().size() );
  CHECK( 153 == capture.crossSection().values().size() );
  CHECK( 2 == capture.crossSection().boundaries().size() );
  CHECK( 2 == capture.crossSection().interpolants().size() );
  CHECK( 32 == capture.crossSection().boundaries()[0] );
  CHECK( 152 == capture.crossSection().boundaries()[1] );
  CHECK( InterpolationType::LogLog == capture.crossSection().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == capture.crossSection().interpolants()[1] );
  CHECK_THAT( 1e-5, WithinRel( capture.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+4, WithinRel( capture.crossSection().energies()[32] ) );
  CHECK_THAT( 2e+7, WithinRel( capture.crossSection().energies()[152] ) );
  CHECK_THAT( 1.672869e+1, WithinRel( capture.crossSection().values()[0] ) );
  CHECK_THAT( 4.950573e-4, WithinRel( capture.crossSection().values()[32] ) );
  CHECK_THAT( 2.710792e-5, WithinRel( capture.crossSection().values()[152] ) );
}
