// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createInterpolants.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "interpolants" ) {

  GIVEN( "ENDF interpolation types" ) {

    WHEN( "a range of interpolation types is given" ) {

      THEN( "it can be converted" ) {

        std::vector< std::size_t > interpolants = { 1, 2, 3, 4, 5 };
        auto converted = format::endf::createInterpolants( interpolants );

        CHECK( InterpolationType::Histogram    == converted[0] );
        CHECK( InterpolationType::LinearLinear == converted[1] );
        CHECK( InterpolationType::LinearLog    == converted[2] );
        CHECK( InterpolationType::LogLinear    == converted[3] );
        CHECK( InterpolationType::LogLog       == converted[4] );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported type" ) {

        std::vector< int > interpolants = { 0, 1, 2, 3, 4, 5, 6 };
        CHECK_THROWS( format::endf::createInterpolants( interpolants ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
