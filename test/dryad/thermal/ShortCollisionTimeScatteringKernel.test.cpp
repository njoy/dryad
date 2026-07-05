// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/thermal/ShortCollisionTimeScatteringKernel.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const ShortCollisionTimeScatteringKernel& );

SCENARIO( "ShortCollisionTimeScatteringKernel" ) {

  GIVEN( "valid Bragg edge data" ) {

    WHEN( "the data is given explicitly" ) {

      double moderatorTemperature = 293.6;
      double effectiveTemperature = 300.;

      ShortCollisionTimeScatteringKernel chunk( moderatorTemperature, effectiveTemperature );

      THEN( "ShortCollisionTimeScatteringKernel can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ShortCollisionTimeScatteringKernel are given" ) {

      ShortCollisionTimeScatteringKernel left( 293.6, 300. );
      ShortCollisionTimeScatteringKernel equal( 293.6, 300. );
      ShortCollisionTimeScatteringKernel different( 300, 305. );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const ShortCollisionTimeScatteringKernel& chunk ) {

  CHECK_THAT( 293.6, WithinRel( chunk.moderatorTemperature() ) );
  CHECK_THAT( 300. , WithinRel( chunk.effectiveTemperature() ) );

  CHECK_THAT( 0.169264243790294, WithinRel( chunk( 1., 1. ) ) );
  CHECK_THAT( 0.169264243790294, WithinRel( chunk( 1., -1. ) ) );
  CHECK_THAT( 0.080382331926097, WithinRel( chunk( 1., 2. ) ) );
  CHECK_THAT( 0.080382331926097, WithinRel( chunk( 1., -2. ) ) );
  CHECK_THAT( 0.072594377669250, WithinRel( chunk( 2., 2. ) ) );
  CHECK_THAT( 0.072594377669250, WithinRel( chunk( 2., -2. ) ) );
}
