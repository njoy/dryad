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

  GIVEN( "GNDS data - coherent elastic and inelastic" ) {

    WHEN( "a GNDS XML document is given" ) {

      pugi::xml_document document;
      document.load_file( "tsl-Be-metal.endf.gnds.xml" );

      THEN( "it can be converted" ) {

        ThermalScattering chunk = format::gnds::createThermalScattering( document );

        tsl::bemetal::verifyBeMetal( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - incoherent elastic and inelastic" ) {

    WHEN( "a GNDS XML document is given" ) {

      pugi::xml_document document;
      document.load_file( "tsl-ZrinZrH.endf.gnds.xml" );

      THEN( "it can be converted" ) {

        ThermalScattering chunk = format::gnds::createThermalScattering( document );

        tsl::zrinzrh::verifyZrInZrH( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - mixed elastic and inelastic" ) {

    WHEN( "a GNDS XML document is given" ) {

      pugi::xml_document document;
      document.load_file( "tsl-7Liin7LiD-mixed.endf.gnds.xml" );

      THEN( "it can be converted" ) {

        ThermalScattering chunk = format::gnds::createThermalScattering( document );

        tsl::li7inli7d::verifyLi7InLi7D( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
