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

SCENARIO( "reaction" ) {

  GIVEN( "ENDF materials" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        Reaction capture = format::endf::reaction( material, 102 );

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
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
