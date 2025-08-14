// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createEndfIndex.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "boundaries" ) {

  GIVEN( "dryad boundary indices" ) {

    WHEN( "a single boundary index type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( 1 == format::createEndfIndex( 0 ) );
        CHECK( 2 == format::createEndfIndex( 1 ) );
        CHECK( 3 == format::createEndfIndex( 2 ) );
        CHECK( 4 == format::createEndfIndex( 3 ) );
        CHECK( 5 == format::createEndfIndex( 4 ) );
        CHECK( 6 == format::createEndfIndex( 5 ) );
      } // THEN

      THEN( "an exception is thrown for an invalid boundary index" ) {

        CHECK_THROWS( format::createEndfIndex( -1 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
