// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/convertMass.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "convertMass" ) {

  GIVEN( "GNDS cross section values and units" ) {

    WHEN( "a single cross section value is given" ) {

      THEN( "it can be converted" ) {

        double mass = 1000.; format::gnds::convertMass( mass, "amu" );
        CHECK( 1000. == mass );

        mass = njoy::constants::amu * 1000.; format::gnds::convertMass( mass, "kg" );
        CHECK_THAT( 1000, WithinRel( mass ) );

        mass = njoy::constants::amu * 1000.; format::gnds::convertMass( mass, "nmu" );
        CHECK_THAT( 1000 * njoy::constants::neutron_mass, WithinRel( mass ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported unit" ) {

        double mass = 1000.;
        CHECK_THROWS( format::gnds::convertMass( mass, "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
