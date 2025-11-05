// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createEndfInterpolant.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createEndfInterpolant" ) {

  GIVEN( "dryad interpolation types" ) {

    WHEN( "a single interpolation type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( 1 == format::endf::createEndfInterpolant( InterpolationType::Histogram    ) );
        CHECK( 2 == format::endf::createEndfInterpolant( InterpolationType::LinearLinear ) );
        CHECK( 3 == format::endf::createEndfInterpolant( InterpolationType::LinearLog    ) );
        CHECK( 4 == format::endf::createEndfInterpolant( InterpolationType::LogLinear    ) );
        CHECK( 5 == format::endf::createEndfInterpolant( InterpolationType::LogLog       ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
