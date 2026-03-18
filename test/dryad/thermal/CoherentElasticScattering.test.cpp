// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/thermal/CoherentElasticScattering.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const CoherentElasticScattering& );

SCENARIO( "CoherentElasticScattering" ) {

  GIVEN( "valid incoherent scattering data" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< BraggEdgeData > bragg_edges = {

        BraggEdgeData( 600.0, { 5.219736e-3, 5. }, { 1e-2, 1. } ),
        BraggEdgeData( 293.6, { 5.219736e-3, 5. }, { 8.703783e-3, 9.484639e-1 } )
      };

      CoherentElasticScattering chunk( std::move( bragg_edges ) );

      THEN( "CoherentElasticScattering can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of CoherentElasticScattering is given" ) {

      CoherentElasticScattering chunk(
          { BraggEdgeData( 600.0, { 5.219736e-3, 5. }, { 1e-2, 1. } ),
            BraggEdgeData( 293.6, { 5.219736e-3, 5. }, { 8.703783e-3, 9.484639e-1 } ) } );

      THEN( "the Bragg edge data can be changed" ) {

        std::vector< BraggEdgeData > newedges = {

          BraggEdgeData( 300.0, { 5.219736e-3, 5. }, { 1e-2, 1. } )
        };
        std::vector< BraggEdgeData > original = {

          BraggEdgeData( 600.0, { 5.219736e-3, 5. }, { 1e-2, 1. } ),
          BraggEdgeData( 293.6, { 5.219736e-3, 5. }, { 8.703783e-3, 9.484639e-1 } )
        };

        chunk.braggEdges( newedges );

        CHECK( newedges == chunk.braggEdges() );

        chunk.braggEdges( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of CoherentElasticScattering are given" ) {

      CoherentElasticScattering left(
          { BraggEdgeData( 600.0, { 5.219736e-3, 5. }, { 1e-2, 1. } ),
            BraggEdgeData( 293.6, { 5.219736e-3, 5. }, { 8.703783e-3, 9.484639e-1 } ) } );
      CoherentElasticScattering equal(
          { BraggEdgeData( 600.0, { 5.219736e-3, 5. }, { 1e-2, 1. } ),
            BraggEdgeData( 293.6, { 5.219736e-3, 5. }, { 8.703783e-3, 9.484639e-1 } ) } );
      CoherentElasticScattering different(
          { BraggEdgeData( 300.0, { 5.219736e-3, 5. }, { 1e-2, 1. } ) } );

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

void verifyChunk( const CoherentElasticScattering& chunk ) {

  CHECK( 2 == chunk.numberModeratorTemperatures() );
  CHECK( 2 == chunk.moderatorTemperatures().size() );
  CHECK( 2 == chunk.braggEdges().size() );

  // temperatures are sorted upon construction
  CHECK_THAT(  293.6, WithinRel( chunk.moderatorTemperatures()[0] ) );
  CHECK_THAT(  600. , WithinRel( chunk.moderatorTemperatures()[1] ) );

  auto edge0 = chunk.braggEdges()[0];
  CHECK( 2 == edge0.numberBraggEdges() );
  CHECK( 2 == edge0.energies().size() );
  CHECK( 2 == edge0.values().size() );
  CHECK_THAT(  293.6, WithinRel( edge0.temperature() ) );
  CHECK_THAT( 5.219736e-3, WithinRel( edge0.energies()[0] ) );
  CHECK_THAT( 5.         , WithinRel( edge0.energies()[1] ) );
  CHECK_THAT( 8.703783e-3, WithinRel( edge0.values()[0] ) );
  CHECK_THAT( 9.484639e-1, WithinRel( edge0.values()[1] ) );

  auto edge1 = chunk.braggEdges()[1];
  CHECK( 2 == edge1.numberBraggEdges() );
  CHECK( 2 == edge1.energies().size() );
  CHECK( 2 == edge1.values().size() );
  CHECK_THAT(  600, WithinRel( edge1.temperature() ) );
  CHECK_THAT( 5.219736e-3, WithinRel( edge1.energies()[0] ) );
  CHECK_THAT( 5.         , WithinRel( edge1.energies()[1] ) );
  CHECK_THAT( 1e-2       , WithinRel( edge1.values()[0] ) );
  CHECK_THAT( 1.         , WithinRel( edge1.values()[1] ) );

  edge0 = chunk.braggEdgeData( 293.6 );
  CHECK( 2 == edge0.numberBraggEdges() );
  CHECK( 2 == edge0.energies().size() );
  CHECK( 2 == edge0.values().size() );
  CHECK_THAT(  293.6, WithinRel( edge0.temperature() ) );
  CHECK_THAT( 5.219736e-3, WithinRel( edge0.energies()[0] ) );
  CHECK_THAT( 5.         , WithinRel( edge0.energies()[1] ) );
  CHECK_THAT( 8.703783e-3, WithinRel( edge0.values()[0] ) );
  CHECK_THAT( 9.484639e-1, WithinRel( edge0.values()[1] ) );

  edge1 = chunk.braggEdgeData( 600 );
  CHECK( 2 == edge1.numberBraggEdges() );
  CHECK( 2 == edge1.energies().size() );
  CHECK( 2 == edge1.values().size() );
  CHECK_THAT(  600, WithinRel( edge1.temperature() ) );
  CHECK_THAT( 5.219736e-3, WithinRel( edge1.energies()[0] ) );
  CHECK_THAT( 5.         , WithinRel( edge1.energies()[1] ) );
  CHECK_THAT( 1e-2       , WithinRel( edge1.values()[0] ) );
  CHECK_THAT( 1.         , WithinRel( edge1.values()[1] ) );
}
