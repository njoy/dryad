// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/createIndex.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "boundaries" ) {

  GIVEN( "ENDF boundary indices" ) {

    WHEN( "a single boundary index type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( 0 == format::createIndex( 1 ) );
        CHECK( 1 == format::createIndex( 2 ) );
        CHECK( 2 == format::createIndex( 3 ) );
        CHECK( 3 == format::createIndex( 4 ) );
        CHECK( 4 == format::createIndex( 5 ) );
      } // THEN

      THEN( "an exception is thrown for an invalid boundary index" ) {

        CHECK_THROWS( format::createIndex( -1 ) );
        CHECK_THROWS( format::createIndex( 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
