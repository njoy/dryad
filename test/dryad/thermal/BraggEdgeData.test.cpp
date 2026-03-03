// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/thermal/BraggEdgeData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const BraggEdgeData& );

SCENARIO( "BraggEdgeData" ) {

  GIVEN( "valid Bragg edge data" ) {

    WHEN( "the data is given explicitly" ) {

      double temperature = 293.6;
      std::vector< double > energies = { 5.219736e-3, 5. };
      std::vector< double > values = { 8.703783e-3, 9.484639e-1 };

      BraggEdgeData chunk( temperature, std::move( energies ), std::move( values ) );

      THEN( "BraggEdgeData can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of BraggEdgeData are given" ) {

      BraggEdgeData left( 293.6,
                          { 5.219736e-3, 5. },
                          { 8.703783e-3, 9.484639e-1 } );
      BraggEdgeData equal( 293.6,
                          { 5.219736e-3, 5. },
                          { 8.703783e-3, 9.484639e-1 } );
      BraggEdgeData different( 300,
                               { 5.219736e-3 },
                               { 8.703783e-3 } );

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

void verifyChunk( const BraggEdgeData& chunk ) {

  CHECK_THAT( 293.6, WithinRel( chunk.temperature() ) );

  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.values().size() );
  CHECK_THAT( 5.219736e-3, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 5.         , WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 8.703783e-3, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 9.484639e-1, WithinRel( chunk.values()[1] ) );
}
