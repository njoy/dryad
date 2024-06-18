// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/ReactionProduct.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const ReactionProduct& );
void verifyLinearisedChunk( const ReactionProduct& );

SCENARIO( "ReactionProduct" ) {

  GIVEN( "valid data for a ReactionProduct with an integer multiplicity" ) {

    WHEN( "the data is given explicitly" ) {

      ParticleID id( "n" );
      int multiplicity = 1;

      ReactionProduct chunk( std::move( id ), std::move( multiplicity ) );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "a ReactionProduct can be linearised" ) {

        ReactionProduct linear = chunk.linearise();

        verifyLinearisedChunk( linear );
      } // THEN

      THEN( "a ReactionProduct can be linearised inplace" ) {

        ReactionProduct copy = chunk; // we'll do this test on a copy
        verifyChunk( copy );
        copy.lineariseInplace();
        verifyLinearisedChunk( copy );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const ReactionProduct& chunk ) {

  // ReactionProduct identifier
  CHECK( ParticleID( "n" ) == chunk.identifier() );

  // multiplicity
  auto multiplicity = chunk.multiplicity();
  CHECK( true == std::holds_alternative< int >( multiplicity ) );
  CHECK( 1 == std::get< int >( multiplicity ) );

  // metadata
  CHECK( true == chunk.isLinearised() );
}

void verifyLinearisedChunk( const ReactionProduct& chunk ) {

  // ReactionProduct identifier
  CHECK( ParticleID( "n" ) == chunk.identifier() );

  // multiplicity
  auto multiplicity = chunk.multiplicity();
  CHECK( true == std::holds_alternative< int >( multiplicity ) );
  CHECK( 1 == std::get< int >( multiplicity ) );

  // metadata
  CHECK( true == chunk.isLinearised() );
}
