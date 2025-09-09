// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createProjectileTarget.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createProjectileTarget" ) {

  GIVEN( "ENDF materials - incident neutrons - stable target" ) {

    WHEN( "a single ENDF material is given" ) {

      auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
      auto material = tape.materials().front();

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTarget( material, false );
        ProjectileTarget second = format::endf::createProjectileTarget( material, true );

        neutron::h1::verifyH1( first, false );
        neutron::h1::verifyH1( second, true );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given with lumped covariance reactions" ) {

      auto tape = njoy::ENDFtk::tree::fromFile( "n-003_Li_007.endf" );
      auto material = tape.materials().front();

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTarget( material, false );
        ProjectileTarget second = format::endf::createProjectileTarget( material, true );

        neutron::li7::verifyLi7( first, false );
        neutron::li7::verifyLi7( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - incident neutrons - metastable target" ) {

    WHEN( "a single ENDF material is given" ) {

      auto tape = njoy::ENDFtk::tree::fromFile( "n-093_Np_236m1.endf" );
      auto material = tape.materials().front();

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTarget( material, false );
        ProjectileTarget second = format::endf::createProjectileTarget( material, true );

        neutron::np236m1::verifyNp236m1( first, false );
        neutron::np236m1::verifyNp236m1( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - electro-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTarget( material, false );
        ProjectileTarget second = format::endf::createProjectileTarget( material, true );

        electron::h0::verifyH0( first, false );
        electron::h0::verifyH0( second, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - photo-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget first = format::endf::createProjectileTarget( material, false );
        ProjectileTarget second = format::endf::createProjectileTarget( material, true );

        photoatomic::h0::verifyH0( first, false );
        photoatomic::h0::verifyH0( second, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
