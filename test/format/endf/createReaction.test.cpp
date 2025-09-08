// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createReaction.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReaction" ) {

  GIVEN( "ENDF materials - incident neutrons - stable target" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material and MT number is given" ) {

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );

        Reaction total1 = format::endf::createReaction( projectile, target, material, 1, false );
        Reaction total2 = format::endf::createReaction( projectile, target, material, 1, true );
        neutron::h1::verifyTotalReaction( total1 );
        neutron::h1::verifyTotalReaction( total2 );

        Reaction elastic1 = format::endf::createReaction( projectile, target, material, 2, false );
        Reaction elastic2 = format::endf::createReaction( projectile, target, material, 2, true );
        neutron::h1::verifyElasticReaction( elastic1 );
        neutron::h1::verifyElasticReaction( elastic2 );

        Reaction capture1 = format::endf::createReaction( projectile, target, material, 102, false );
        Reaction capture2 = format::endf::createReaction( projectile, target, material, 102, true );
        neutron::h1::verifyCaptureReaction( capture1 );
        neutron::h1::verifyCaptureReaction( capture2 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - incident neutrons - metastable target" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-093_Np_236m1.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material and MT number is given" ) {

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Np236_e2" );

        Reaction total1 = format::endf::createReaction( projectile, target, material, 1, false );
        Reaction total2 = format::endf::createReaction( projectile, target, material, 1, true );
        neutron::np236m1::verifyTotalReaction( total1 );
        neutron::np236m1::verifyTotalReaction( total2 );

        Reaction elastic1 = format::endf::createReaction( projectile, target, material, 2, false );
        Reaction elastic2 = format::endf::createReaction( projectile, target, material, 2, true );
        neutron::np236m1::verifyElasticReaction( elastic1 );
        neutron::np236m1::verifyElasticReaction( elastic2 );

        Reaction inelastic1 = format::endf::createReaction( projectile, target, material, 4, false );
        Reaction inelastic2 = format::endf::createReaction( projectile, target, material, 4, true );
        neutron::np236m1::verifyInelasticReaction( inelastic1 );
        neutron::np236m1::verifyInelasticReaction( inelastic2 );

        Reaction capture1 = format::endf::createReaction( projectile, target, material, 102, false );
        Reaction capture2 = format::endf::createReaction( projectile, target, material, 102, true );
        neutron::np236m1::verifyCaptureReaction( capture1 );
        neutron::np236m1::verifyCaptureReaction( capture2 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - electro-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material and MT number is given" ) {

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H" );

        Reaction total1 = format::endf::createReaction( projectile, target, material, 501, false );
        Reaction total2 = format::endf::createReaction( projectile, target, material, 501, true );
        electron::h0::verifyTotalReaction( total1 );
        electron::h0::verifyTotalReaction( total2 );

        Reaction ionisation1 = format::endf::createReaction( projectile, target, material, 522, false );
        Reaction ionisation2 = format::endf::createReaction( projectile, target, material, 522, true );
        electron::h0::verifyTotalIonisationReaction( ionisation1 );
        electron::h0::verifyTotalIonisationReaction( ionisation2 );

        Reaction elastic1 = format::endf::createReaction( projectile, target, material, 525, false );
        Reaction elastic2 = format::endf::createReaction( projectile, target, material, 525, true );
        electron::h0::verifyElasticReaction( elastic1, false );
        electron::h0::verifyElasticReaction( elastic2, true );

        Reaction telastic1 = format::endf::createReaction( projectile, target, material, 526, false );
        Reaction telastic2 = format::endf::createReaction( projectile, target, material, 526, true );
        electron::h0::verifyTotalElasticReaction( telastic1 );
        electron::h0::verifyTotalElasticReaction( telastic2 );

        Reaction bremsstrahlung1 = format::endf::createReaction( projectile, target, material, 527, false );
        Reaction bremsstrahlung2 = format::endf::createReaction( projectile, target, material, 527, true );
        electron::h0::verifyBremsstrahlungReaction( bremsstrahlung1, false );
        electron::h0::verifyBremsstrahlungReaction( bremsstrahlung2, true );

        Reaction excitation1 = format::endf::createReaction( projectile, target, material, 528, false );
        Reaction excitation2 = format::endf::createReaction( projectile, target, material, 528, true );
        electron::h0::verifyExcitationReaction( excitation1 );
        electron::h0::verifyExcitationReaction( excitation2 );

        Reaction subionisation1 = format::endf::createReaction( projectile, target, material, 534, false );
        Reaction subionisation2 = format::endf::createReaction( projectile, target, material, 534, true );
        electron::h0::verifySubshellIonisationReaction( subionisation1, false );
        electron::h0::verifySubshellIonisationReaction( subionisation2, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - photo-atomic" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material and MT number is given" ) {

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "g" );
        id::ParticleID target( "H" );

        Reaction total1 = format::endf::createReaction( projectile, target, material, 501, false );
        Reaction total2 = format::endf::createReaction( projectile, target, material, 501, true );
        photoatomic::h0::verifyTotalReaction( total1 );
        photoatomic::h0::verifyTotalReaction( total2 );

        Reaction coherent1 = format::endf::createReaction( projectile, target, material, 502, false );
        Reaction coherent2 = format::endf::createReaction( projectile, target, material, 502, true );
        photoatomic::h0::verifyCoherentReaction( coherent1 );
        photoatomic::h0::verifyCoherentReaction( coherent2 );

        Reaction incoherent1 = format::endf::createReaction( projectile, target, material, 504, false );
        Reaction incoherent2 = format::endf::createReaction( projectile, target, material, 504, true );
        photoatomic::h0::verifyIncoherentReaction( incoherent1 );
        photoatomic::h0::verifyIncoherentReaction( incoherent2 );

        Reaction epairproduction1 = format::endf::createReaction( projectile, target, material, 515, false );
        Reaction epairproduction2 = format::endf::createReaction( projectile, target, material, 515, true );
        photoatomic::h0::verifyElectronFieldPairProductionReaction( epairproduction1 );
        photoatomic::h0::verifyElectronFieldPairProductionReaction( epairproduction2 );

        Reaction tpairproduction1 = format::endf::createReaction( projectile, target, material, 516, false );
        Reaction tpairproduction2 = format::endf::createReaction( projectile, target, material, 516, true );
        photoatomic::h0::verifyTotalPairProductionReaction( tpairproduction1 );
        photoatomic::h0::verifyTotalPairProductionReaction( tpairproduction2 );

        Reaction npairproduction1 = format::endf::createReaction( projectile, target, material, 517, true );
        Reaction npairproduction2 = format::endf::createReaction( projectile, target, material, 517, false );
        photoatomic::h0::verifyNuclearFieldPairProductionReaction( npairproduction1 );
        photoatomic::h0::verifyNuclearFieldPairProductionReaction( npairproduction2 );

        Reaction tionisation1 = format::endf::createReaction( projectile, target, material, 522, false );
        Reaction tionisation2 = format::endf::createReaction( projectile, target, material, 522, true );
        photoatomic::h0::verifyTotalIonisationReaction( tionisation1 );
        photoatomic::h0::verifyTotalIonisationReaction( tionisation2 );

        Reaction ionisation1 = format::endf::createReaction( projectile, target, material, 534, false );
        Reaction ionisation2 = format::endf::createReaction( projectile, target, material, 534, true );
        photoatomic::h0::verifyIonisationReaction( ionisation1 );
        photoatomic::h0::verifyIonisationReaction( ionisation2 );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
