// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createBoundary.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "boundaries" ) {

  GIVEN( "ENDF boudnary indeices" ) {

    WHEN( "a single boundary index type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( 0 == format::endf::createBoundary( 1 ) );
        CHECK( 1 == format::endf::createBoundary( 2 ) );
        CHECK( 2 == format::endf::createBoundary( 3 ) );
        CHECK( 3 == format::endf::createBoundary( 4 ) );
        CHECK( 4 == format::endf::createBoundary( 5 ) );
      } // THEN

      THEN( "an exception is thrown for an invalid boundary index" ) {

        CHECK_THROWS( format::endf::createBoundary( -1 ) );
        CHECK_THROWS( format::endf::createBoundary( 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
