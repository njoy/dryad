// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createReactions.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReactions" ) {

  GIVEN( "GNDS data - incident neutrons" ) {

    WHEN( "a GNDS reaction suite is given" ) {

      pugi::xml_document document;
      pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
      pugi::xml_node suite = document.child( "reactionSuite" );

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        std::vector< Reaction > reactions1 = format::gnds::createReactions( projectile, target, suite, false );
        std::vector< Reaction > reactions2 = format::gnds::createReactions( projectile, target, suite, true );

        CHECK( 3 == reactions1.size() );
        auto total = reactions1[0];
        neutron::h1::verifyTotalReaction( total );
        auto elastic = reactions1[1];
        neutron::h1::verifyElasticReaction( elastic );
        auto capture = reactions1[2];
        neutron::h1::verifyCaptureReaction( capture );

        CHECK( 3 == reactions2.size() );
        total = reactions2[0];
        neutron::h1::verifyTotalReaction( total );
        elastic = reactions2[1];
        neutron::h1::verifyElasticReaction( elastic );
        capture = reactions2[2];
        neutron::h1::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN

    WHEN( "a GNDS reaction suite is given" ) {

      pugi::xml_document document;
      pugi::xml_parse_result result = document.load_file( "n-003_Li_007.endf.gnds.xml" );
      pugi::xml_node suite = document.child( "reactionSuite" );

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Li7" );
        std::vector< Reaction > reactions1 = format::gnds::createReactions( projectile, target, suite, false );
        std::vector< Reaction > reactions2 = format::gnds::createReactions( projectile, target, suite, true );

        CHECK( 49 == reactions1.size() );
        auto total = reactions1[0];
        neutron::li7::verifyTotalReaction( total );
        auto elastic = reactions1[5];
        neutron::li7::verifyElasticReaction( elastic );
        auto capture = reactions1[38];
        neutron::li7::verifyCaptureReaction( capture );
        auto lumped = reactions1[40];
        neutron::li7::verifyLumpedReaction851( lumped );
        lumped = reactions1[41];
        neutron::li7::verifyLumpedReaction852( lumped );
        lumped = reactions1[42];
        neutron::li7::verifyLumpedReaction853( lumped );
        lumped = reactions1[43];
        neutron::li7::verifyLumpedReaction854( lumped );
        lumped = reactions1[44];
        neutron::li7::verifyLumpedReaction855( lumped );
        lumped = reactions1[45];
        neutron::li7::verifyLumpedReaction856( lumped );
        lumped = reactions1[46];
        neutron::li7::verifyLumpedReaction857( lumped );
        lumped = reactions1[47];
        neutron::li7::verifyLumpedReaction858( lumped );
        lumped = reactions1[48];
        neutron::li7::verifyLumpedReaction859( lumped );

        CHECK( 49 == reactions2.size() );
        total = reactions2[0];
        neutron::li7::verifyTotalReaction( total );
        elastic = reactions2[5];
        neutron::li7::verifyElasticReaction( elastic );
        capture = reactions2[38];
        neutron::li7::verifyCaptureReaction( capture );
        lumped = reactions2[40];
        neutron::li7::verifyLumpedReaction851( lumped );
        lumped = reactions2[41];
        neutron::li7::verifyLumpedReaction852( lumped );
        lumped = reactions2[42];
        neutron::li7::verifyLumpedReaction853( lumped );
        lumped = reactions2[43];
        neutron::li7::verifyLumpedReaction854( lumped );
        lumped = reactions2[44];
        neutron::li7::verifyLumpedReaction855( lumped );
        lumped = reactions2[45];
        neutron::li7::verifyLumpedReaction856( lumped );
        lumped = reactions2[46];
        neutron::li7::verifyLumpedReaction857( lumped );
        lumped = reactions2[47];
        neutron::li7::verifyLumpedReaction858( lumped );
        lumped = reactions2[48];
        neutron::li7::verifyLumpedReaction859( lumped );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - electro-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node suite = document.child( "reactionSuite" );

    WHEN( "a GNDS reaction suite is given" ) {

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H" );
        std::vector< Reaction > reactions1 = format::gnds::createReactions( projectile, target, suite, false );
        std::vector< Reaction > reactions2 = format::gnds::createReactions( projectile, target, suite, true );

        CHECK( 8 == reactions1.size() );
        auto total = reactions1[0];
        electron::h0::verifyTotalReaction( total );
        auto ionisation = reactions1[1];
        electron::h0::verifyTotalIonisationReaction( ionisation );
        auto elastic = reactions1[2];
        electron::h0::verifyElasticReaction( elastic, false );
        auto telastic = reactions1[3];
        electron::h0::verifyTotalElasticReaction( telastic );
        auto bremsstrahlung = reactions1[4];
        electron::h0::verifyBremsstrahlungReaction( bremsstrahlung, false );
        auto excitation = reactions1[5];
        electron::h0::verifyExcitationReaction( excitation );
        auto subionisation = reactions1[6];
        electron::h0::verifySubshellIonisationReaction( subionisation, false );
        auto deficit = reactions1[7];
        electron::h0::verifyElasticDeficitReaction( deficit );

        CHECK( 8 == reactions2.size() );
        total = reactions2[0];
        electron::h0::verifyTotalReaction( total );
        ionisation = reactions2[1];
        electron::h0::verifyTotalIonisationReaction( ionisation );
        elastic = reactions2[2];
        electron::h0::verifyElasticReaction( elastic, true );
        telastic = reactions2[3];
        electron::h0::verifyTotalElasticReaction( telastic );
        bremsstrahlung = reactions2[4];
        electron::h0::verifyBremsstrahlungReaction( bremsstrahlung, true );
        excitation = reactions2[5];
        electron::h0::verifyExcitationReaction( excitation );
        subionisation = reactions2[6];
        electron::h0::verifySubshellIonisationReaction( subionisation, true );
        deficit = reactions2[7];
        electron::h0::verifyElasticDeficitReaction( deficit );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - photo-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );
    pugi::xml_node suite = document.child( "reactionSuite" );

    WHEN( "a GNDS reaction suite is given" ) {

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "g" );
        id::ParticleID target( "H" );
        std::vector< Reaction > reactions1 = format::gnds::createReactions( projectile, target, suite, false );
        std::vector< Reaction > reactions2 = format::gnds::createReactions( projectile, target, suite, true );

        CHECK( 8 == reactions1.size() );
        auto total = reactions1[0];
        photoatomic::h0::verifyTotalReaction( total );
        auto coherent = reactions1[1];
        photoatomic::h0::verifyCoherentReaction( coherent );
        auto incoherent = reactions1[2];
        photoatomic::h0::verifyIncoherentReaction( incoherent );
        auto epairproduction = reactions1[3];
        photoatomic::h0::verifyElectronFieldPairProductionReaction( epairproduction );
        auto tpairproduction = reactions1[4];
        photoatomic::h0::verifyTotalPairProductionReaction( tpairproduction );
        auto npairproduction = reactions1[5];
        photoatomic::h0::verifyNuclearFieldPairProductionReaction( npairproduction );
        auto tionisation = reactions1[6];
        photoatomic::h0::verifyTotalIonisationReaction( tionisation );
        auto ionisation = reactions1[7];
        photoatomic::h0::verifyIonisationReaction( ionisation );

        CHECK( 8 == reactions2.size() );
        total = reactions2[0];
        photoatomic::h0::verifyTotalReaction( total );
        coherent = reactions2[1];
        photoatomic::h0::verifyCoherentReaction( coherent );
        incoherent = reactions2[2];
        photoatomic::h0::verifyIncoherentReaction( incoherent );
        epairproduction = reactions2[3];
        photoatomic::h0::verifyElectronFieldPairProductionReaction( epairproduction );
        tpairproduction = reactions2[4];
        photoatomic::h0::verifyTotalPairProductionReaction( tpairproduction );
        npairproduction = reactions2[5];
        photoatomic::h0::verifyNuclearFieldPairProductionReaction( npairproduction );
        tionisation = reactions2[6];
        photoatomic::h0::verifyTotalIonisationReaction( tionisation );
        ionisation = reactions2[7];
        photoatomic::h0::verifyIonisationReaction( ionisation );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
