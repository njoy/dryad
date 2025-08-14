// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createProjectileTargetFromFile.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "projectileTargetFromFile" ) {

  GIVEN( "GNDS data - incident neutrons" ) {

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::gnds::createProjectileTargetFromFile( "n-001_H_001.endf.gnds.xml", false );
        ProjectileTarget second = format::gnds::createProjectileTargetFromFile( "n-001_H_001.endf.gnds.xml", true );

        neutron::h1::verifyH1( first, false );
        neutron::h1::verifyH1( second, true );
      } // THEN
    } // WHEN

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::gnds::createProjectileTargetFromFile( "n-003_Li_007.endf.gnds.xml", false );
        ProjectileTarget second = format::gnds::createProjectileTargetFromFile( "n-003_Li_007.endf.gnds.xml", true );

        neutron::li7::verifyLi7( first, false );
        neutron::li7::verifyLi7( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - electro-atomic" ) {

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::gnds::createProjectileTargetFromFile( "e-001_H_000.endf.gnds.xml", false );
        ProjectileTarget second = format::gnds::createProjectileTargetFromFile( "e-001_H_000.endf.gnds.xml", true );

        electron::h0::endf81::verifyDocumentation( first.documentation() );
        electron::h0::endf81::verifyDocumentation( second.documentation() );

        electron::h0::verifyH0( first, false );
        electron::h0::verifyH0( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - photo-atomic" ) {

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::gnds::createProjectileTargetFromFile( "photoat-001_H_000.endf.gnds.xml", false );
        ProjectileTarget second = format::gnds::createProjectileTargetFromFile( "photoat-001_H_000.endf.gnds.xml", true );

        photoatomic::h0::verifyH0( first, false );
        photoatomic::h0::verifyH0( second, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
