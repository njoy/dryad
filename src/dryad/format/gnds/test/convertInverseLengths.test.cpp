// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/convertInverseLengths.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertCrossSections" ) {

  GIVEN( "GNDS cross section ranges and units" ) {

    WHEN( "a single cross section range is given" ) {

      THEN( "it can be converted" ) {

        std::vector< double > x = { 1., 1000. };
        format::gnds::convertInverseLengths( x, "1/Ang" );
        CHECK( 2 == x.size() );
        CHECK(    1. == x[0] );
        CHECK( 1000. == x[1] );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        std::vector< double > x = { 1., 1000. };
        CHECK_THROWS( format::gnds::convertInverseLengths( x, "unsupported" ) );
        CHECK( 2 == x.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
