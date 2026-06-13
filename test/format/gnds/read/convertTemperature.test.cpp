// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/convertTemperature.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertTemperature" ) {

  GIVEN( "GNDS temperature values and units" ) {

    WHEN( "a single temperature value is given" ) {

      THEN( "it can be converted" ) {

        double temperature = 1000.; format::gnds::convertTemperature( temperature, "K" );
        CHECK( 1000. == temperature );

        temperature = 1000.; format::gnds::convertTemperature( temperature, "degrees C" );
        CHECK( 1273.15 == temperature );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        double temperature = 1000.;
        CHECK_THROWS( format::gnds::convertTemperature( temperature, "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
