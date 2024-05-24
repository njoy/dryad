// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/interpolants.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "interpolants" ) {

  GIVEN( "ENDF interpolation types" ) {

    WHEN( "a single interpolation type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( InterpolationType::Histogram    == format::endf::interpolant( 1 ) );
        CHECK( InterpolationType::LinearLinear == format::endf::interpolant( 2 ) );
        CHECK( InterpolationType::LinearLog    == format::endf::interpolant( 3 ) );
        CHECK( InterpolationType::LogLinear    == format::endf::interpolant( 4 ) );
        CHECK( InterpolationType::LogLog       == format::endf::interpolant( 5 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported type" ) {

        CHECK_THROWS( format::endf::interpolant( 0 ) );
        CHECK_THROWS( format::endf::interpolant( 6 ) );
      } // THEN
    } // WHEN

    WHEN( "a range of interpolation types is given" ) {

      THEN( "it can be converted" ) {

        std::vector< std::size_t > interpolants = { 1, 2, 3, 4, 5 };
        auto converted = format::endf::interpolants( interpolants );

        CHECK( InterpolationType::Histogram    == converted[0] );
        CHECK( InterpolationType::LinearLinear == converted[1] );
        CHECK( InterpolationType::LinearLog    == converted[2] );
        CHECK( InterpolationType::LogLinear    == converted[3] );
        CHECK( InterpolationType::LogLog       == converted[4] );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported type" ) {

        std::vector< int > interpolants = { 0, 1, 2, 3, 4, 5, 6 };
        CHECK_THROWS( format::endf::interpolants( interpolants ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
