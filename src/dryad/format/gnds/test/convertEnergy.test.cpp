// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createEnergy.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createEnergy" ) {

  GIVEN( "GNDS energy values and units" ) {

    WHEN( "a range of boundary indices is given" ) {

      THEN( "it can be converted" ) {


        CHECK( 1000. == format::gnds::createEnergy( 1000., "eV" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        CHECK_THROWS( format::gnds::createEnergy( 1000., "MeV" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
