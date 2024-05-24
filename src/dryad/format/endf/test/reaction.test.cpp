// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/reaction.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyTotalReaction( const Reaction& );
void verifyElasticReaction( const Reaction& );
void verifyCaptureReaction( const Reaction& );

SCENARIO( "reaction" ) {

  GIVEN( "ENDF materials" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material and MT number is given" ) {

      THEN( "a Reaction can be created" ) {

        Reaction total = format::endf::createReaction( material, 1 );
        verifyTotalReaction( total );

        Reaction elastic = format::endf::createReaction( material, 2 );
        verifyElasticReaction( elastic );

        Reaction capture = format::endf::createReaction( material, 102 );
        verifyCaptureReaction( capture );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given" ) {

      THEN( "all reactions can be created" ) {

        std::vector< Reaction > reactions = format::endf::createReactions( material );

        auto total = reactions[0];
        verifyTotalReaction( total );

        auto elastic = reactions[1];
        verifyElasticReaction( elastic );

        auto capture = reactions[2];
        verifyCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyTotalReaction( const Reaction& total ) {

  CHECK( ReactionID( "1" ) == total.identifier() );
  CHECK( false == total.isLinearised() );
  CHECK_THAT( 0, WithinRel( total.massDifferenceQValue() ) );
  CHECK_THAT( 0, WithinRel( total.reactionQValue() ) );
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
  CHECK_THAT( 0, WithinRel( elastic.massDifferenceQValue() ) );
  CHECK_THAT( 0, WithinRel( elastic.reactionQValue() ) );
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
  CHECK_THAT( 2.224648e+6, WithinRel( capture.massDifferenceQValue() ) );
  CHECK_THAT( 2.224648e+6, WithinRel( capture.reactionQValue() ) );
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
