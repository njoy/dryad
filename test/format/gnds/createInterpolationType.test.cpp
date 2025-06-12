// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createInterpolationType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createInterpolationType" ) {

  GIVEN( "GNDS interpolation values" ) {

    WHEN( "an interpolation value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( InterpolationType::LinearLinear == format::gnds::createInterpolationType( "" ) );
        CHECK( InterpolationType::LinearLinear == format::gnds::createInterpolationType( "lin-lin" ) );
        CHECK( InterpolationType::LogLog == format::gnds::createInterpolationType( "log-log" ) );
        CHECK( InterpolationType::LogLinear == format::gnds::createInterpolationType( "log-lin" ) );
        CHECK( InterpolationType::LinearLog == format::gnds::createInterpolationType( "lin-log" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( format::gnds::createInterpolationType( "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
