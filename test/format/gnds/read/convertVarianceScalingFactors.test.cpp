// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/convertVarianceScalingFactors.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "convertVarianceScalingFactors" ) {

  GIVEN( "GNDS variance scaling factors ranges and units" ) {

    WHEN( "a single range of variance scaling factors is given" ) {

      THEN( "it can be converted" ) {

        std::vector< double > x = { 1., 1000. };
        gnds::read::convertVarianceScalingFactors( x, "Mb**2" );
        CHECK( 2 == x.size() );
        CHECK(    1e+12 == x[0] );
        CHECK( 1000e+12 == x[1] );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        std::vector< double > x = { 1., 1000. };
        CHECK_THROWS( gnds::read::convertVarianceScalingFactors( x, "unsupported" ) );
        CHECK( 2 == x.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
