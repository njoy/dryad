// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/boundaries.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "boundaries" ) {

  GIVEN( "ENDF boudnary indeices" ) {

    WHEN( "a single boundary index type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( 0 == format::endf::boundary( 1 ) );
        CHECK( 1 == format::endf::boundary( 2 ) );
        CHECK( 2 == format::endf::boundary( 3 ) );
        CHECK( 3 == format::endf::boundary( 4 ) );
        CHECK( 4 == format::endf::boundary( 5 ) );
      } // THEN

      THEN( "an exception is thrown for an invalid boundary index" ) {

        CHECK_THROWS( format::endf::boundary( -1 ) );
        CHECK_THROWS( format::endf::boundary( 0 ) );
      } // THEN
    } // WHEN

    WHEN( "a range of boundary indices is given" ) {

      THEN( "it can be converted" ) {

        std::vector< int > boundaries = { 1, 2, 3, 4, 5 };
        auto converted = format::endf::boundaries( boundaries );

        CHECK( 0 == converted[0] );
        CHECK( 1 == converted[1] );
        CHECK( 2 == converted[2] );
        CHECK( 3 == converted[3] );
        CHECK( 4 == converted[4] );
      } // THEN

      THEN( "an exception is thrown for invalid boundary indeces" ) {

        std::vector< int > zero = { 0 };
        std::vector< int > negative = { -1 };
        CHECK_THROWS( format::endf::boundaries( zero ) );
        CHECK_THROWS( format::endf::boundaries( negative ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
