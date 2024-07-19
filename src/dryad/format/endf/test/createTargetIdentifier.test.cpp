// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTargetIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createTargetIdentifier" ) {

  GIVEN( "ENDF sublibrary values" ) {

    WHEN( "a single sublibrary value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "1001_e1" ) == format::endf::createTargetIdentifier( 1001, 1 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
