// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/createVector.hpp"

// other includes
#include "tools/std20/views.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::tools;

SCENARIO( "createVector" ) {

  GIVEN( "a range/view of data" ) {

    std::vector< double > data = { 0., 1., 2, 3. };
    auto view = data | std20::views::transform(
                           [] ( auto&& value )
                              { return static_cast< int >( std::round( value ) ); } );

    WHEN( "a range is used" ) {

      THEN( "it can be converted to a vector" ) {

        std::vector< double > doubles = format::createVector( data );
        CHECK( 0 == doubles[0] );
        CHECK( 1 == doubles[1] );
        CHECK( 2 == doubles[2] );
        CHECK( 3 == doubles[3] );

        std::vector< int > ints = format::createVector( view );
        CHECK( 0 == ints[0] );
        CHECK( 1 == ints[1] );
        CHECK( 2 == ints[2] );
        CHECK( 3 == ints[3] );

        // this will not compile: unsigned int is not the value type
        // std::vector< unsigned int > others = format::createVector( view );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
