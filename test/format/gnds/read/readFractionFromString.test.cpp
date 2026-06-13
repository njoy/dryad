// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readFractionFromString.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

SCENARIO( "readFractionFromString" ) {

  GIVEN( "fraction strings" ) {

    THEN( "they can be converted" ) {

      CHECK_THAT( 0.5, WithinRel( gnds::read::readFractionFromString( "1/2" ) ) );
      CHECK_THAT( 0.5, WithinRel( gnds::read::readFractionFromString( " 1 / 2 " ) ) );
      CHECK_THAT( 0.5, WithinRel( gnds::read::readFractionFromString( "1 / 2" ) ) );
      CHECK_THAT( 2.0, WithinRel( gnds::read::readFractionFromString( "2" ) ) );

      CHECK_THROWS( gnds::read::readFractionFromString( "1/2/3" ) );
    } // THEN
  } // GIVEN
} // SCENARIO
