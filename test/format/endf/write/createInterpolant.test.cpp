// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/createInterpolant.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createInterpolant" ) {

  GIVEN( "dryad interpolation types" ) {

    WHEN( "a single interpolation type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( 1 == endf::write::createInterpolant( InterpolationType::Histogram    ) );
        CHECK( 2 == endf::write::createInterpolant( InterpolationType::LinearLinear ) );
        CHECK( 3 == endf::write::createInterpolant( InterpolationType::LinearLog    ) );
        CHECK( 4 == endf::write::createInterpolant( InterpolationType::LogLinear    ) );
        CHECK( 5 == endf::write::createInterpolant( InterpolationType::LogLog       ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
