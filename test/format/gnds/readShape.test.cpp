// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/format/gnds/readShape.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "readShape" ) {

  GIVEN( "various comma separated strings" ) {

    WHEN( "a single comma separated string is used" ) {

      THEN( "it can be converted" ) {

        std::vector<  std::size_t > shape = format::gnds::readShape( "2,3,4" );

        CHECK( 3 == shape.size() );
        CHECK( 2 == shape[0] );
        CHECK( 3 == shape[1] );
        CHECK( 4 == shape[2] );
      } // THEN
    } // WHEN

    WHEN( "incorrect lists are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readShape( "2,a,4" ) ); // cannot be converted to int
        CHECK_THROWS( format::gnds::readShape( "2,-3,4" ) ); // negative int
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
