// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/convertRadii.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertRadii" ) {

  GIVEN( "GNDS radius ranges and units" ) {

    WHEN( "a single radius range is given" ) {

      THEN( "it can be converted" ) {

        std::vector< double > radii = { 1., 1000. };
        format::gnds::convertRadii( radii, "fm" );
        CHECK( 2 == radii.size() );
        CHECK(    1. == radii[0] );
        CHECK( 1000. == radii[1] );

        radii = { 1., 1000. };
        format::gnds::convertRadii( radii, "nm" );
        CHECK( 2 == radii.size() );
        CHECK( 1e+6 == radii[0] );
        CHECK( 1e+9 == radii[1] );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        std::vector< double > radii = { 1., 1000. };
        CHECK_THROWS( format::gnds::convertRadii( radii, "unsupported" ) );
        CHECK( 2 == radii.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
