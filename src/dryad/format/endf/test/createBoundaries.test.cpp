// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createBoundaries.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createBoundaries" ) {

  GIVEN( "ENDF boundary indices" ) {

    WHEN( "a range of boundary indices is given" ) {

      THEN( "it can be converted" ) {

        std::vector< int > boundaries = { 1, 2, 3, 4, 5 };
        std::vector< std::size_t > converted = format::endf::createBoundaries( boundaries );

        CHECK( 0 == converted[0] );
        CHECK( 1 == converted[1] );
        CHECK( 2 == converted[2] );
        CHECK( 3 == converted[3] );
        CHECK( 4 == converted[4] );
      } // THEN

      THEN( "an exception is thrown for invalid boundary indeces" ) {

        std::vector< int > zero = { 0 };
        std::vector< int > negative = { -1 };
        CHECK_THROWS( format::endf::createBoundaries( zero ) );
        CHECK_THROWS( format::endf::createBoundaries( negative ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
