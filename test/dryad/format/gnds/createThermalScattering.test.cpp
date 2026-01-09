// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/createThermalScattering.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createThermalScattering" ) {

  GIVEN( "GNDS data - incoherent elastic and inelastic" ) {

    WHEN( "a GNDS XML document is given" ) {

      pugi::xml_document document;
      pugi::xml_parse_result result = document.load_file( "tsl-ZrinZrH.endf.gnds.xml" );

      THEN( "it can be converted" ) {

        ThermalScattering chunk = format::gnds::createThermalScattering( document );

        tsl::zrinzrh::verifyZrInZrH( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
