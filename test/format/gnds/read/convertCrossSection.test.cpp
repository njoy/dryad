// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/convertCrossSection.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "convertCrossSection" ) {

  GIVEN( "GNDS cross section values and units" ) {

    WHEN( "a single cross section value is given" ) {

      THEN( "it can be converted" ) {

        double xs = 1000.;
        gnds::read::convertCrossSection( xs, "b" );
        CHECK( 1000. == xs );

        xs = 1000.;
        gnds::read::convertCrossSection( xs, "Mb" );
        CHECK( 1000e+6 == xs );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        double xs = 1000.;
        CHECK_THROWS( gnds::read::convertCrossSection( xs, "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
