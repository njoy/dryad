// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/createIndex.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "boundaries" ) {

  GIVEN( "dryad boundary indices" ) {

    WHEN( "a single boundary index type is given" ) {

      THEN( "it can be converted" ) {

        CHECK( 1 == endf::write::createIndex( 0 ) );
        CHECK( 2 == endf::write::createIndex( 1 ) );
        CHECK( 3 == endf::write::createIndex( 2 ) );
        CHECK( 4 == endf::write::createIndex( 3 ) );
        CHECK( 5 == endf::write::createIndex( 4 ) );
        CHECK( 6 == endf::write::createIndex( 5 ) );
      } // THEN

      THEN( "an exception is thrown for an invalid boundary index" ) {

        CHECK_THROWS( endf::write::createIndex( -1 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
