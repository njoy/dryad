// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/Reaction.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "Reaction" ) {

  GIVEN( "valid data for a reaction" ) {

    WHEN( "the data is given explicitly" ) {

      ReactionID id( "n,Fe56->n,Fe56" );
      CrossSection xs( { 1e-5, 2., 2., 3., 20. },
                       { 4., 3., 4., 3., 2. },
                       { 1, 4 },
                       { InterpolationType::LinearLinear,
                         InterpolationType::LinearLog } );

      Reaction chunk( std::move( id ), std::move( xs ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        // reaction identifier
        CHECK( ReactionID( "n,Fe56->n,Fe56" ) == chunk.identifier() );

        // cross section
        CHECK( 5 == chunk.crossSection().energies().size() );
        CHECK( 5 == chunk.crossSection().values().size() );
        CHECK( 2 == chunk.crossSection().boundaries().size() );
        CHECK( 2 == chunk.crossSection().interpolants().size() );
        CHECK_THAT( 1e-5, WithinRel( chunk.crossSection().energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.crossSection().energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.crossSection().energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.crossSection().energies()[3] ) );
        CHECK_THAT( 20., WithinRel( chunk.crossSection().energies()[4] ) );
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
      } // THEN

      THEN( "a Reaction can be linearised" ) {

      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
