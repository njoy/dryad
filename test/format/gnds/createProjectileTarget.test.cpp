// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createProjectileTarget.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createProjectileTarget" ) {

  GIVEN( "GNDS data - incident neutrons" ) {

    WHEN( "a GNDS XML document is given" ) {

      pugi::xml_document document;
      pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::gnds::createProjectileTarget( document, false );
        ProjectileTarget second = format::gnds::createProjectileTarget( document, true );

        neutron::h1::verifyH1( first, false );
        neutron::h1::verifyH1( second, true );
      } // THEN
    } // WHEN

    WHEN( "a GNDS XML document is given" ) {

      pugi::xml_document document;
      pugi::xml_parse_result result = document.load_file( "n-003_Li_007.endf.gnds.xml" );

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::gnds::createProjectileTarget( document, false );
        ProjectileTarget second = format::gnds::createProjectileTarget( document, true );

        neutron::li7::verifyLi7( first, false );
        neutron::li7::verifyLi7( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - electro-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::gnds::createProjectileTarget( document, false );
        ProjectileTarget second = format::gnds::createProjectileTarget( document, true );

        electron::h0::endf81::verifyDocumentation( first.documentation() );
        electron::h0::endf81::verifyDocumentation( second.documentation() );

        electron::h0::verifyH0( first, false );
        electron::h0::verifyH0( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - photo-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::gnds::createProjectileTarget( document, false );
        ProjectileTarget second = format::gnds::createProjectileTarget( document, true );

        photoatomic::h0::verifyH0( first, false );
        photoatomic::h0::verifyH0( second, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
