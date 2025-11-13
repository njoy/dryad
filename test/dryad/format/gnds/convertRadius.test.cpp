// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/convertRadius.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertRadius" ) {

  GIVEN( "GNDS radius values and units" ) {

    WHEN( "a single radius value is given" ) {

      THEN( "it can be converted" ) {

        double radius = 1000.; format::gnds::convertRadius( radius, "fm" );
        CHECK( 1000. == radius );

        radius = 1000.; format::gnds::convertRadius( radius, "nm" );
        CHECK( 1e+9 == radius );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        double radius = 1000.;
        CHECK_THROWS( format::gnds::convertRadius( radius, "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
