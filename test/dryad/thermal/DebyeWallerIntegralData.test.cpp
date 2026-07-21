// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/thermal/DebyeWallerIntegralData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const DebyeWallerIntegralData& );

SCENARIO( "DebyeWallerIntegralData" ) {

  GIVEN( "valid Debye-Waller integral data" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > temperatures = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 2., 1. };

      DebyeWallerIntegralData chunk( std::move( temperatures ), std::move( values ) );

      THEN( "DebyeWallerIntegralData can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of DebyeWallerIntegralData are given" ) {

      DebyeWallerIntegralData left( { 1., 2., 3., 4. },
                                    { 4., 3., 2., 1. } );
      DebyeWallerIntegralData equal( { 1., 2., 3., 4. },
                                     { 4., 3., 2., 1. } );
      DebyeWallerIntegralData different( { 1., 2. },
                                         { 4., 3. } );

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

void verifyChunk( const DebyeWallerIntegralData& chunk ) {

  CHECK( 4 == chunk.temperatures().size() );
  CHECK( 4 == chunk.values().size() );
  CHECK_THAT( 1., WithinRel( chunk.temperatures()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.temperatures()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.temperatures()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.temperatures()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );

  CHECK( true == chunk.hasValue( 1. ) );
  CHECK( true == chunk.hasValue( 2. ) );
  CHECK( true == chunk.hasValue( 3. ) );
  CHECK( true == chunk.hasValue( 4. ) );
  CHECK( false == chunk.hasValue( 3.5 ) );
  CHECK_THAT( 4., WithinRel( chunk.value( 1. ) ) );
  CHECK_THAT( 3., WithinRel( chunk.value( 2. ) ) );
  CHECK_THAT( 2., WithinRel( chunk.value( 3. ) ) );
  CHECK_THAT( 1., WithinRel( chunk.value( 4. ) ) );

  CHECK_THROWS( chunk.value( 3.5 ) );

  // temperature within 1e-6 does not throw
  CHECK_NOTHROW( chunk.value( 2. * 0.9999999 ) );
  CHECK_NOTHROW( chunk.value( 2. * 1.0000001 ) );

  // check throw on temperature that are too far from the stored ones
  CHECK_THROWS( chunk.value( 2. * 0.99999 ) );
  CHECK_THROWS( chunk.value( 2. * 1.00001 ) );
  CHECK_THROWS( chunk.value( 3.5 ) );
}
