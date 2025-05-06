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
        std::vector< Reaction > reactions = format::gnds::createReactions( projectile, target, suite );

        CHECK( 3 == reactions.size() );

        auto total = reactions[0];
        neutron::h1::verifyTotalReaction( total );

        auto elastic = reactions[1];
        neutron::h1::verifyElasticReaction( elastic );

        auto capture = reactions[2];
        neutron::h1::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN

    WHEN( "a GNDS reaction suite is given" ) {

      pugi::xml_document document;
      pugi::xml_parse_result result = document.load_file( "n-003_Li_007.endf.gnds.xml" );
      pugi::xml_node suite = document.child( "reactionSuite" );

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Li" );
        std::vector< Reaction > reactions = format::gnds::createReactions( projectile, target, suite );

        CHECK( 53 == reactions.size() );

        auto total = reactions[0];
        neutron::li7::verifyTotalReaction( total );

        auto elastic = reactions[1];
        neutron::li7::verifyElasticReaction( elastic );

        auto capture = reactions[38];
        neutron::li7::verifyCaptureReaction( capture );

        auto lumped = reactions[44];
        neutron::li7::verifyLumpedReaction851( lumped );

        lumped = reactions[45];
        neutron::li7::verifyLumpedReaction852( lumped );

        lumped = reactions[46];
        neutron::li7::verifyLumpedReaction853( lumped );

        lumped = reactions[47];
        neutron::li7::verifyLumpedReaction854( lumped );

        lumped = reactions[48];
        neutron::li7::verifyLumpedReaction855( lumped );

        lumped = reactions[49];
        neutron::li7::verifyLumpedReaction856( lumped );

        lumped = reactions[50];
        neutron::li7::verifyLumpedReaction857( lumped );

        lumped = reactions[51];
        neutron::li7::verifyLumpedReaction858( lumped );

        lumped = reactions[52];
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
        id::ParticleID target( "H0" );
        std::vector< Reaction > reactions = format::gnds::createReactions( projectile, target, suite );

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

  GIVEN( "GNDS data - photo-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );
    pugi::xml_node suite = document.child( "reactionSuite" );

    WHEN( "a GNDS reaction suite is given" ) {

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "G" );
        id::ParticleID target( "H0" );
        std::vector< Reaction > reactions = format::gnds::createReactions( projectile, target, suite );

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
