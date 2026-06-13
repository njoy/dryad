// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createInterpolant.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createInterpolant" ) {

  GIVEN( "ENDF interpolation types" ) {

    WHEN( "a single interpolation type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( InterpolationType::Histogram    == endf::read::createInterpolant( 1 ) );
        CHECK( InterpolationType::LinearLinear == endf::read::createInterpolant( 2 ) );
        CHECK( InterpolationType::LinearLog    == endf::read::createInterpolant( 3 ) );
        CHECK( InterpolationType::LogLinear    == endf::read::createInterpolant( 4 ) );
        CHECK( InterpolationType::LogLog       == endf::read::createInterpolant( 5 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported type" ) {

        CHECK_THROWS( endf::read::createInterpolant( 0 ) );
        CHECK_THROWS( endf::read::createInterpolant( 6 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
