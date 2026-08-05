// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/createInterpolationType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createInterpolationType" ) {

  GIVEN( "dryad interpolation values" ) {

    WHEN( "an interpolation value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( "lin-lin" == gnds::write::createInterpolationType( InterpolationType::LinearLinear ) );
        CHECK( "log-log" == gnds::write::createInterpolationType( InterpolationType::LogLog ) );
        CHECK( "log-lin" == gnds::write::createInterpolationType( InterpolationType::LogLinear ) );
        CHECK( "lin-log" == gnds::write::createInterpolationType( InterpolationType::LinearLog ) );
        CHECK( "flat" == gnds::write::createInterpolationType( InterpolationType::Histogram ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
