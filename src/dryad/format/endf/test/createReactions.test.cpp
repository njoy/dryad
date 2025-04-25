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

        CHECK( 3 == reactions.size() );

        auto total = reactions[0];
        neutron::h1::verifyTotalReaction( total );

        auto elastic = reactions[1];
        neutron::h1::verifyElasticReaction( elastic );

        auto capture = reactions[2];
        neutron::h1::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - electro-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material is given" ) {

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H0" );
        std::vector< Reaction > reactions = format::endf::createReactions( projectile, target, material );

        CHECK( 8 == reactions.size() );

        auto total = reactions[0];
        electron::h1::verifyTotalReaction( total );

        auto ionisation = reactions[1];
        electron::h1::verifyTotalIonisationReaction( ionisation );

        auto elastic = reactions[2];
        electron::h1::verifyElasticReaction( elastic );

        auto telastic = reactions[3];
        electron::h1::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = reactions[4];
        electron::h1::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = reactions[5];
        electron::h1::verifyExcitationReaction( excitation );

        auto subionisation = reactions[6];
        electron::h1::verifySubshellIonisationReaction( subionisation );

        auto deficit = reactions[7];
        electron::h1::verifyElasticDeficitReaction( deficit );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - photo-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material is given" ) {

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "G" );
        id::ParticleID target( "H0" );
        std::vector< Reaction > reactions = format::endf::createReactions( projectile, target, material );

        CHECK( 8 == reactions.size() );

        auto total = reactions[0];
        photoatomic::h1::verifyTotalReaction( total );

        auto coherent = reactions[1];
        photoatomic::h1::verifyCoherentReaction( coherent );

        auto incoherent = reactions[2];
        photoatomic::h1::verifyIncoherentReaction( incoherent );

        auto epairproduction = reactions[3];
        photoatomic::h1::verifyElectronFieldPairProductionReaction( epairproduction );

        auto tpairproduction = reactions[4];
        photoatomic::h1::verifyTotalPairProductionReaction( tpairproduction );

        auto npairproduction = reactions[5];
        photoatomic::h1::verifyNuclearFieldPairProductionReaction( npairproduction );

        auto tionisation = reactions[6];
        photoatomic::h1::verifyTotalIonisationReaction( tionisation );

        auto ionisation = reactions[7];
        photoatomic::h1::verifyIonisationReaction( ionisation );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
