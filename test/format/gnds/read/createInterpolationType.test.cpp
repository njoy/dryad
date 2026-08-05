// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createInterpolationType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createInterpolationType" ) {

  GIVEN( "GNDS interpolation values" ) {

    WHEN( "an interpolation value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( InterpolationType::LinearLinear == gnds::read::createInterpolationType( "" ) );
        CHECK( InterpolationType::LinearLinear == gnds::read::createInterpolationType( "lin-lin" ) );
        CHECK( InterpolationType::LogLog == gnds::read::createInterpolationType( "log-log" ) );
        CHECK( InterpolationType::LogLinear == gnds::read::createInterpolationType( "log-lin" ) );
        CHECK( InterpolationType::LinearLog == gnds::read::createInterpolationType( "lin-log" ) );
        CHECK( InterpolationType::Histogram == gnds::read::createInterpolationType( "flat" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( gnds::read::createInterpolationType( "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
