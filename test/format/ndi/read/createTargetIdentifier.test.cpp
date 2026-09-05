// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ndi/read/createTargetIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createTargetIdentifier" ) {

  GIVEN( "NDI zaid values" ) {

    WHEN( "a zaid is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "H1" ) == ndi::read::createTargetIdentifier( "1001.853nm" ) );
        CHECK( id::ParticleID( "Al26_e1" ) == ndi::read::createTargetIdentifier( "1013026.853nm" ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported zaid type" ) {

        CHECK_THROWS( ndi::read::createTargetIdentifier( "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
