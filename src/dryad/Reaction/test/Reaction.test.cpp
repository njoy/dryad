// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/Reaction.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const Reaction& );
void verifyLinearisedChunk( const Reaction& );

SCENARIO( "Reaction" ) {

  GIVEN( "valid data for a reaction" ) {

    WHEN( "the data is given explicitly" ) {

      ReactionID id( "n,Fe56->n,Fe56_e1" );
      double mass_q = 0;
      double reaction_q = -1;
      TabulatedCrossSection xs( { 1., 2., 2., 3., 4. },
                                { 4., 3., 4., 3., 2. },
                                { 1, 4 },
                                { InterpolationType::LinearLinear,
                                  InterpolationType::LinearLog } );

      Reaction chunk( std::move( id ), mass_q, reaction_q, std::move( xs ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "a Reaction can be linearised" ) {

        Reaction linear = chunk.linearise();

        verifyLinearisedChunk( linear );
      } // THEN

      THEN( "a Reaction can be linearised inplace" ) {

        Reaction copy = chunk; // we'll do this test on a copy
        verifyChunk( copy );
        copy.lineariseInplace();
        verifyLinearisedChunk( copy );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const Reaction& chunk ) {

  // reaction identifier
  CHECK( ReactionID( "n,Fe56->n,Fe56_e1" ) == chunk.identifier() );

  // q values
  CHECK_THAT( 0, WithinRel( chunk.massDifferenceQValue() ) );
  CHECK_THAT( -1, WithinRel( chunk.reactionQValue() ) );

  // cross section
  CHECK( 5 == chunk.crossSection().numberPoints() );
  CHECK( 2 == chunk.crossSection().numberRegions() );
  CHECK( 5 == chunk.crossSection().energies().size() );
  CHECK( 5 == chunk.crossSection().values().size() );
  CHECK( 2 == chunk.crossSection().boundaries().size() );
  CHECK( 2 == chunk.crossSection().interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.crossSection().energies()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().energies()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().energies()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().energies()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().energies()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().values()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().values()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().values()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().values()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().values()[4] ) );
  CHECK( 1 == chunk.crossSection().boundaries()[0] );
  CHECK( 4 == chunk.crossSection().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.crossSection().interpolants()[0] );
  CHECK( InterpolationType::LinearLog == chunk.crossSection().interpolants()[1] );
  CHECK( false == chunk.crossSection().isLinearised() );

  // metadata
  CHECK( false == chunk.isLinearised() );
}

void verifyLinearisedChunk( const Reaction& chunk ) {

  // reaction identifier
  CHECK( ReactionID( "n,Fe56->n,Fe56_e1" ) == chunk.identifier() );

  // cross section
  CHECK( 12 == chunk.crossSection().numberPoints() );
  CHECK( 2 == chunk.crossSection().numberRegions() );
  CHECK( 12 == chunk.crossSection().energies().size() );
  CHECK( 12 == chunk.crossSection().values().size() );
  CHECK( 2 == chunk.crossSection().boundaries().size() );
  CHECK( 2 == chunk.crossSection().interpolants().size() );
  CHECK_THAT( 1.   , WithinRel( chunk.crossSection().energies()[0] ) );
  CHECK_THAT( 2.   , WithinRel( chunk.crossSection().energies()[1] ) );
  CHECK_THAT( 2.   , WithinRel( chunk.crossSection().energies()[2] ) );
  CHECK_THAT( 2.125, WithinRel( chunk.crossSection().energies()[3] ) );
  CHECK_THAT( 2.25 , WithinRel( chunk.crossSection().energies()[4] ) );
  CHECK_THAT( 2.5  , WithinRel( chunk.crossSection().energies()[5] ) );
  CHECK_THAT( 2.75 , WithinRel( chunk.crossSection().energies()[6] ) );
  CHECK_THAT( 3.   , WithinRel( chunk.crossSection().energies()[7] ) );
  CHECK_THAT( 3.25 , WithinRel( chunk.crossSection().energies()[8] ) );
  CHECK_THAT( 3.5  , WithinRel( chunk.crossSection().energies()[9] ) );
  CHECK_THAT( 3.75 , WithinRel( chunk.crossSection().energies()[10] ) );
  CHECK_THAT( 4.   , WithinRel( chunk.crossSection().energies()[11] ) );
  CHECK_THAT( 4.              , WithinRel( chunk.crossSection().values()[0] ) );
  CHECK_THAT( 3.              , WithinRel( chunk.crossSection().values()[1] ) );
  CHECK_THAT( 4.              , WithinRel( chunk.crossSection().values()[2] ) );
  CHECK_THAT( 3.85048128530886, WithinRel( chunk.crossSection().values()[3] ) );
  CHECK_THAT( 3.70951129135145, WithinRel( chunk.crossSection().values()[4] ) );
  CHECK_THAT( 3.44966028678679, WithinRel( chunk.crossSection().values()[5] ) );
  CHECK_THAT( 3.21459646033567, WithinRel( chunk.crossSection().values()[6] ) );
  CHECK_THAT( 3.              , WithinRel( chunk.crossSection().values()[7] ) );
  CHECK_THAT( 2.72176678584324, WithinRel( chunk.crossSection().values()[8] ) );
  CHECK_THAT( 2.46416306545103, WithinRel( chunk.crossSection().values()[9] ) );
  CHECK_THAT( 2.22433973930853, WithinRel( chunk.crossSection().values()[10] ) );
  CHECK_THAT( 2.              , WithinRel( chunk.crossSection().values()[11] ) );
  CHECK( 1 == chunk.crossSection().boundaries()[0] );
  CHECK( 11 == chunk.crossSection().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.crossSection().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.crossSection().interpolants()[1] );
  CHECK( true == chunk.crossSection().isLinearised() );

  // metadata
  CHECK( true == chunk.isLinearised() );
}