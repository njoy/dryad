// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/convertTemperatures.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertTemperatures" ) {

  GIVEN( "GNDS temperature ranges and units" ) {

    WHEN( "a single temperature range is given" ) {

      THEN( "it can be converted" ) {

        std::vector< double > temperatures = { 1., 1000. };
        format::gnds::convertTemperatures( temperatures, "K" );
        CHECK( 2 == temperatures.size() );
        CHECK(    1. == temperatures[0] );
        CHECK( 1000. == temperatures[1] );

        temperatures = { 1., 1000. };
        format::gnds::convertTemperatures( temperatures, "degrees C" );
        CHECK( 2 == temperatures.size() );
        CHECK(  274.15 == temperatures[0] );
        CHECK( 1273.15 == temperatures[1] );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        std::vector< double > temperatures = { 1., 1000. };
        CHECK_THROWS( format::gnds::convertTemperatures( temperatures, "unsupported" ) );
        CHECK( 2 == temperatures.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
