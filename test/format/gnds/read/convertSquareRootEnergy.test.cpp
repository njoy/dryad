// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/convertSquareRootEnergy.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "convertSquareRootEnergy" ) {

  GIVEN( "GNDS square root energy values and units" ) {

    WHEN( "a single square root energy value is given" ) {

      THEN( "it can be converted" ) {

        double sqrt_energy = 1000.;
        gnds::read::convertSquareRootEnergy( sqrt_energy, "eV**(1/2)" );
        CHECK( 1000. == sqrt_energy );

        sqrt_energy = 1000.;
        gnds::read::convertSquareRootEnergy( sqrt_energy, "MeV**(1/2)" );
        CHECK( 1. == sqrt_energy );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        double sqrt_energy = 1000.;
        CHECK_THROWS( gnds::read::convertSquareRootEnergy( sqrt_energy, "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
