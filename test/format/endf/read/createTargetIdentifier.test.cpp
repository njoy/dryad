// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createTargetIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createTargetIdentifier" ) {

  GIVEN( "ENDF sublibrary values" ) {

    WHEN( "a single sublibrary value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "H1_e1" ) == endf::read::createTargetIdentifier( 1001, 1 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
