// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createProjectileTargetFromFile.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "projectileTarget" ) {

  GIVEN( "ENDF materials - incident neutrons" ) {

    WHEN( "a single ENDF material is given for a ground state target" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTargetFromFile( "n-001_H_001.endf", false );
        ProjectileTarget second = format::endf::createProjectileTargetFromFile( "n-001_H_001.endf", true );

        neutron::h1::verifyH1( first, false );
        neutron::h1::verifyH1( second, true );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given for a metastable target" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTargetFromFile( "n-093_Np_236m1.endf", false );
        ProjectileTarget second = format::endf::createProjectileTargetFromFile( "n-093_Np_236m1.endf", true );

        neutron::np236m1::verifyNp236m1( first, false );
        neutron::np236m1::verifyNp236m1( second, true );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given with lumped covariance reactions" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTargetFromFile( "n-003_Li_007.endf", false );
        ProjectileTarget second = format::endf::createProjectileTargetFromFile( "n-003_Li_007.endf", true );

        neutron::li7::verifyLi7( first, false );
        neutron::li7::verifyLi7( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - electro-atomic" ) {

    // two test are used:
    // - ENDF/B-VIII.1 data (same as GNDS test files)
    // - ENDF/B-VIII.0 data which used an electron instead of photon particle id
    //   This test verifies that we can handle it. For ENDF/B-VIII.1 (see above)
    //   the ENDF file was corrected.

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTargetFromFile( "e-001_H_000.endf", false );
        ProjectileTarget second = format::endf::createProjectileTargetFromFile( "e-001_H_000.endf", true );

        electron::h0::endf81::verifyDocumentation( first.documentation() );
        electron::h0::endf81::verifyDocumentation( second.documentation() );

        electron::h0::verifyH0( first, false );
        electron::h0::verifyH0( second, true );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given - endf/B-VIII.0" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTargetFromFile( "e-001_H_000-endf80.endf", false );
        ProjectileTarget second = format::endf::createProjectileTargetFromFile( "e-001_H_000-endf80.endf", true );

        electron::h0::endf80::verifyDocumentation( first.documentation() );
        electron::h0::endf80::verifyDocumentation( second.documentation() );

        electron::h0::verifyH0( first, false );
        electron::h0::verifyH0( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - photo-atomic" ) {

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf", false );
        ProjectileTarget second = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );

        photoatomic::h0::verifyH0( first, false );
        photoatomic::h0::verifyH0( second, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
