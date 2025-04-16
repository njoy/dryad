// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/LinearCombinationCovariance.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "LinearCombinationCovariance" ) {

  GIVEN( "valid covariance data for a diagonal LinearCombinationCovariance" ) {

    std::vector< id::ReactionID > reactions = { "2", "4", "16" };
    std::vector< double > coefficients = { .1, .2, .3 };

    LinearCombinationCovariance chunk( std::move( reactions ), std::move( coefficients ) );

    THEN( "a LinearCombinationCovariance can be constructed and members can be tested" ) {

      CHECK( 3 == chunk.numberReactions() );

      CHECK( 3 == chunk.reactions().size() );
      CHECK( id::ReactionID( "2" )  == chunk.reactions()[0] );
      CHECK( id::ReactionID( "4" )  == chunk.reactions()[1] );
      CHECK( id::ReactionID( "16" ) == chunk.reactions()[2] );

      CHECK( 3 == chunk.coefficients().size() );
      CHECK_THAT( 0.1, WithinRel( chunk.coefficients()[0] ) );
      CHECK_THAT( 0.2, WithinRel( chunk.coefficients()[1] ) );
      CHECK_THAT( 0.3, WithinRel( chunk.coefficients()[2] ) );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a LinearCombinationCovariance" ) {

    WHEN( "the number of reactions and coefficients is not consistent" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearCombinationCovariance( {}, { .1, .2, .3 } ) );
        CHECK_THROWS( LinearCombinationCovariance( { "2", "4", "16" }, {} ) );
        CHECK_THROWS( LinearCombinationCovariance( {}, {} ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO