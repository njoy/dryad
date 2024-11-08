// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/convertEnergy.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertEnergy" ) {

  GIVEN( "GNDS energy values and units" ) {

    WHEN( "a single energy value is given" ) {

      THEN( "it can be converted" ) {

        double energy = 1000.; format::gnds::convertEnergy( energy, "eV" );
        CHECK( 1000. == energy );

        energy = 1000.; format::gnds::convertEnergy( energy, "MeV" );
        CHECK( 1000e+6 == energy );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        double energy = 1000.;
        CHECK_THROWS( format::gnds::convertEnergy( energy, "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
