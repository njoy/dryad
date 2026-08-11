// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/convertSquareRootEnergies.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "convertSquareRootEnergies" ) {

  GIVEN( "GNDS square root energy ranges and units" ) {

    WHEN( "a single square root energy range is given" ) {

      THEN( "it can be converted" ) {

        std::vector< double > values = { 1., 1000. };
        gnds::read::convertSquareRootEnergies( values, "eV**(1/2)" );
        CHECK( 2 == values.size() );
        CHECK(    1. == values[0] );
        CHECK( 1000. == values[1] );

        values = { 1., 1000. };
        gnds::read::convertSquareRootEnergies( values, "MeV**(1/2)" );
        CHECK( 2 == values.size() );
        CHECK( 1e+3 == values[0] );
        CHECK( 1e+6 == values[1] );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        std::vector< double > values = { 1., 1000. };
        CHECK_THROWS( gnds::read::convertSquareRootEnergies( values, "unsupported" ) );
        CHECK( 2 == values.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
