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

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node suite = document.child( "reactionSuite" );

    WHEN( "a GNDS reaction suite is given" ) {

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        std::vector< Reaction > reactions = format::gnds::createReactions( projectile, target, suite );

        CHECK( 3 == reactions.size() );

        auto total = reactions[0];
        verifyNeutronTotalReaction( total );

        auto elastic = reactions[1];
        verifyNeutronElasticReaction( elastic );

        auto capture = reactions[2];
        verifyNeutronCaptureReaction( capture );
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

        auto deficit = reactions[7];
        verifyElectronElasticDeficitReaction( deficit );
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
        verifyPhotonTotalReaction( total );

        auto coherent = reactions[1];
        verifyPhotonCoherentReaction( coherent );

        auto incoherent = reactions[2];
        verifyPhotonIncoherentReaction( incoherent );

        auto epairproduction = reactions[3];
        verifyPhotonElectronFieldPairProductionReaction( epairproduction );

        auto tpairproduction = reactions[4];
        verifyPhotonTotalPairProductionReaction( tpairproduction );

        auto npairproduction = reactions[5];
        verifyPhotonNuclearFieldPairProductionReaction( npairproduction );

        auto tionisation = reactions[6];
        verifyPhotonTotalIonisationReaction( tionisation );

        auto ionisation = reactions[7];
        verifyPhotonIonisationReaction( ionisation );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
