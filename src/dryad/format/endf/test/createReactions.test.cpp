// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createReactions.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReactions" ) {

  GIVEN( "ENDF materials - incident neutrons" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material is given" ) {

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        std::vector< Reaction > reactions = format::endf::createReactions( projectile, target, material );

        auto total = reactions[0];
        verifyNeutronTotalReaction( total );

        auto elastic = reactions[1];
        verifyNeutronElasticReaction( elastic );

        auto capture = reactions[2];
        verifyNeutronCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - electro-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material is given" ) {

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        std::vector< Reaction > reactions = format::endf::createReactions( projectile, target, material );

        auto total = reactions[0];
        verifyElectronTotalReaction( total );

        auto ionisation = reactions[1];
        verifyElectronTotalIonisationReaction( ionisation );

        auto elastic = reactions[2];
        verifyElectronElasticReaction( elastic );

        auto telastic = reactions[3];
        verifyElectronTotalElasticReaction( telastic );

        auto bremsstrahlung = reactions[4];
        verifyElectronBremsstrahlungReaction( bremsstrahlung );

        auto excitation = reactions[5];
        verifyElectronExcitationReaction( excitation );

        auto subionisation = reactions[6];
        verifyElectronSubshellIonisationReaction( subionisation );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
