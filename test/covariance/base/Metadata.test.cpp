// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/base/Metadata.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad::covariance;

SCENARIO( "Metadata" ) {

  GIVEN( "valid metadata for a 1D covariance matrix" ) {

    using Key = std::tuple< int, int >;
    using Metadata = base::Metadata< int, int >;

    WHEN( "using covariance data for an on-diagonal matrix" ) {

      Metadata chunk( { Key{ 0, 0 }, Key{ 1, 0 }, Key{ 2, 0 } } );

      THEN( "a Metadata can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.keys().size() );
        CHECK( std::tuple{ 0, 0 } == chunk.keys()[0] );
        CHECK( std::tuple{ 1, 0 } == chunk.keys()[1] );
        CHECK( std::tuple{ 2, 0 } == chunk.keys()[2] );
      } // THEN

      THEN( "a selection can be made and indices are returned" ) {

        auto selection = chunk.selection( std::nullopt, 0 );

        CHECK( 3 == selection.size() );
        CHECK( 0 == selection[0] );
        CHECK( 1 == selection[1] );
        CHECK( 2 == selection[2] );

        selection = chunk.selection( 2, std::nullopt );

        CHECK( 1 == selection.size() );
        CHECK( 2 == selection[0] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO