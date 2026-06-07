// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/createParticleDatabase.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createParticleDatabase" ) {

  GIVEN( "ENDF materials - incident neutrons - stable target" ) {

    WHEN( "a single ENDF material is given" ) {

      using Tape = njoy::ENDFtk::tree::Tape;
      auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-001_H_001.endf" );
      auto material = tape.materials().front();
      auto information = material.section( 1, 451 ).parse< 1, 451 >();

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        ParticleDatabase particles = format::endf::createParticleDatabase( projectile, target, information );
        neutron::h1::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given with lumped covariance reactions" ) {

      using Tape = njoy::ENDFtk::tree::Tape;
      auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-003_Li_007.endf" );
      auto material = tape.materials().front();
      auto information = material.section( 1, 451 ).parse< 1, 451 >();

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Li7" );
        ParticleDatabase particles = format::endf::createParticleDatabase( projectile, target, information );
        neutron::li7::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN

    WHEN( "a single ENDF material is given with angular covariances" ) {

      using Tape = njoy::ENDFtk::tree::Tape;
      auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-010_Ne_022.endf" );
      auto material = tape.materials().front();
      auto information = material.section( 1, 451 ).parse< 1, 451 >();

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Ne22" );
        ParticleDatabase particles = format::endf::createParticleDatabase( projectile, target, information );
        neutron::ne22::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - incident neutrons - metastable target" ) {

    WHEN( "a single ENDF material is given" ) {

      using Tape = njoy::ENDFtk::tree::Tape;
      auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-093_Np_236m1.endf" );
      auto material = tape.materials().front();
      auto information = material.section( 1, 451 ).parse< 1, 451 >();

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Np236_e2" );
        ParticleDatabase particles = format::endf::createParticleDatabase( projectile, target, information );
        neutron::np236m1::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - electro-atomic" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "e-001_H_000.endf" );
    auto material = tape.materials().front();
    auto information = material.section( 1, 451 ).parse< 1, 451 >();

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H" );
        ParticleDatabase particles = format::endf::createParticleDatabase( projectile, target, information );
        electron::h0::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - photo-atomic" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "photoat-001_H_000.endf" );
    auto material = tape.materials().front();
    auto information = material.section( 1, 451 ).parse< 1, 451 >();

    WHEN( "a single ENDF materials is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "g" );
        id::ParticleID target( "H" );
        ParticleDatabase particles = format::endf::createParticleDatabase( projectile, target, information );
        photoatomic::h0::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
