// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/convertCrossSections.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertCrossSections" ) {

  GIVEN( "GNDS cross section ranges and units" ) {

    WHEN( "a single cross section range is given" ) {

      THEN( "it can be converted" ) {

        std::vector< double > xs = { 1., 1000. };
        format::gnds::convertCrossSections( xs, "b" );
        CHECK( 2 == xs.size() );
        CHECK(    1. == xs[0] );
        CHECK( 1000. == xs[1] );

        xs = { 1., 1000. };
        format::gnds::convertCrossSections( xs, "Mb" );
        CHECK( 2 == xs.size() );
        CHECK(    1. == xs[0] );
        CHECK( 1000. == xs[1] );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        std::vector< double > xs = { 1., 1000. };
        CHECK_THROWS( format::gnds::convertCrossSections( xs, "unsupported" ) );
        CHECK( 2 == xs.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
