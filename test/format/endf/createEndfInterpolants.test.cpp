// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createEndfInterpolants.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createEndfInterpolants" ) {

  GIVEN( "dryad interpolation types" ) {

    WHEN( "a range of interpolation types is given" ) {

      THEN( "it can be converted" ) {

        std::vector< InterpolationType > interpolants = { InterpolationType::Histogram,
                                                          InterpolationType::LinearLinear,
                                                          InterpolationType::LinearLog,
                                                          InterpolationType::LogLinear,
                                                          InterpolationType::LogLog };
        std::vector< std::size_t > converted = format::endf::createEndfInterpolants( interpolants );

        CHECK( 1 == converted[0] );
        CHECK( 2 == converted[1] );
        CHECK( 3 == converted[2] );
        CHECK( 4 == converted[3] );
        CHECK( 5 == converted[4] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
