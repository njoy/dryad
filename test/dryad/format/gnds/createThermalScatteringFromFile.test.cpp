// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/createThermalScatteringFromFile.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createThermalScatteringFromFile" ) {

  GIVEN( "GNDS data - coherent elastic and inelastic" ) {

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ThermalScattering chunk = format::gnds::createThermalScatteringFromFile( "tsl-Be-metal.endf.gnds.xml" );

        tsl::bemetal::verifyBeMetal( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - incoherent elastic and inelastic" ) {

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ThermalScattering chunk = format::gnds::createThermalScatteringFromFile( "tsl-ZrinZrH.endf.gnds.xml" );

        tsl::zrinzrh::verifyZrInZrH( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
