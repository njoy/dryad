// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/convertEnergies.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertEnergies" ) {

  GIVEN( "GNDS energy ranges and units" ) {

    WHEN( "a single energy range is given" ) {

      THEN( "it can be converted" ) {

        std::vector< double > energies = { 1., 1000. };
        format::gnds::convertEnergies( energies, "eV" );
        CHECK( 2 == energies.size() );
        CHECK(    1. == energies[0] );
        CHECK( 1000. == energies[1] );

        energies = { 1., 1000. };
        format::gnds::convertEnergies( energies, "eV" );
        CHECK( 2 == energies.size() );
        CHECK(    1. == energies[0] );
        CHECK( 1000. == energies[1] );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        std::vector< double > energies = { 1., 1000. };
        CHECK_THROWS( format::gnds::convertEnergies( energies, "unsupported" ) );
        CHECK( 2 == energies.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
