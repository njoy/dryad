// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/convertLegendreMoments.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "convertLegendreMoments" ) {

  GIVEN( "Legendre moments" ) {

    std::vector< double > moments = { 1., 2., 3., 4. };

    convertLegendreMoments( moments );

    THEN( "the moments can be converted" ) {

      CHECK_THAT(  0.5, WithinRel( moments[0] ) );
      CHECK_THAT(  3.0, WithinRel( moments[1] ) );
      CHECK_THAT(  7.5, WithinRel( moments[2] ) );
      CHECK_THAT( 14.0, WithinRel( moments[3] ) );
    } // THEN
  } // GIVEN
} // SCENARIO
