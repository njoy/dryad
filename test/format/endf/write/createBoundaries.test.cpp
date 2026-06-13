// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/createBoundaries.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "createBoundaries" ) {

  GIVEN( "ENDF boundary indices" ) {

    WHEN( "a range of boundary indices is given" ) {

      THEN( "it can be converted" ) {

        std::vector< int > boundaries = { 0, 1, 2, 3, 4, 5 };
        std::vector< long > converted = endf::write::createBoundaries( boundaries );

        CHECK( 1 == converted[0] );
        CHECK( 2 == converted[1] );
        CHECK( 3 == converted[2] );
        CHECK( 4 == converted[3] );
        CHECK( 5 == converted[4] );
        CHECK( 6 == converted[5] );
      } // THEN

      THEN( "an exception is thrown for invalid boundary indeces" ) {

        std::vector< int > negative = { -1 };
        CHECK_THROWS( endf::write::createBoundaries( negative ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
