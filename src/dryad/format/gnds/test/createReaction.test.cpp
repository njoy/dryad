// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createReaction.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReaction" ) {

  GIVEN( "GNDS data - incident neutrons" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node suite = document.child( "reactionSuite" );
    pugi::xml_node reactions = suite.child( "reactions" );
    pugi::xml_node sums = document.child( "reactionSuite" ).child( "sums" ).child( "crossSectionSums" );

    WHEN( "a single GNDS reaction data node is given" ) {

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );

        auto node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "1" );
        Reaction total = format::gnds::createReaction( projectile, target, suite, node );
        verifyNeutronTotalReaction( total );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "2" );
        Reaction elastic = format::gnds::createReaction( projectile, target, suite, node );
        verifyNeutronElasticReaction( elastic );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "102" );
        Reaction capture = format::gnds::createReaction( projectile, target, suite, node );
        verifyNeutronCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - electro-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node suite = document.child( "reactionSuite" );
    pugi::xml_node reactions = suite.child( "reactions" );
    pugi::xml_node sums = suite.child( "sums" ).child( "crossSectionSums" );
    pugi::xml_node incomplete = suite.child( "incompleteReactions" );

    WHEN( "a single GNDS reaction data node is given" ) {

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H" );

        auto node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "501" );
        Reaction total = format::gnds::createReaction( projectile, target, suite, node );
        verifyElectronTotalReaction( total );

        node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "522" );
        Reaction ionisation = format::gnds::createReaction( projectile, target, suite, node );
        verifyElectronTotalIonisationReaction( ionisation );

        node = incomplete.find_child_by_attribute( "reaction", "ENDF_MT", "525" );
        Reaction elastic = format::gnds::createReaction( projectile, target, suite, node );
        verifyElectronElasticReaction( elastic );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "526" );
        Reaction telastic = format::gnds::createReaction( projectile, target, suite, node );
        verifyElectronTotalElasticReaction( telastic );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "527" );
        Reaction bremsstrahlung = format::gnds::createReaction( projectile, target, suite, node );
        verifyElectronBremsstrahlungReaction( bremsstrahlung );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "528" );
        Reaction excitation = format::gnds::createReaction( projectile, target, suite, node );
        verifyElectronExcitationReaction( excitation );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "534" );
        Reaction subionisation = format::gnds::createReaction( projectile, target, suite, node );
        verifyElectronSubshellIonisationReaction( subionisation );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - photo-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );
    pugi::xml_node suite = document.child( "reactionSuite" );
    pugi::xml_node reactions = suite.child( "reactions" );
    pugi::xml_node sums = document.child( "reactionSuite" ).child( "sums" ).child( "crossSectionSums" );

    WHEN( "a single GNDS reaction data node is given" ) {

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "g" );
        id::ParticleID target( "H" );

        auto node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "501" );
        Reaction total = format::gnds::createReaction( projectile, target, suite, node );
        verifyPhotonTotalReaction( total );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "502" );
        Reaction coherent = format::gnds::createReaction( projectile, target, suite, node );
        verifyPhotonCoherentReaction( coherent );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "504" );
        Reaction incoherent = format::gnds::createReaction( projectile, target, suite, node );
        verifyPhotonIncoherentReaction( incoherent );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "515" );
        Reaction epairproduction = format::gnds::createReaction( projectile, target, suite, node );
        verifyPhotonElectronFieldPairProductionReaction( epairproduction );

        node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "516" );
        Reaction tpairproduction = format::gnds::createReaction( projectile, target, suite, node );
        verifyPhotonTotalPairProductionReaction( tpairproduction );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "517" );
        Reaction npairproduction = format::gnds::createReaction( projectile, target, suite, node );
        verifyPhotonNuclearFieldPairProductionReaction( npairproduction );

        node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "522" );
        Reaction tionisation = format::gnds::createReaction( projectile, target, suite, node );
        verifyPhotonTotalIonisationReaction( tionisation );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "534" );
        Reaction ionisation = format::gnds::createReaction( projectile, target, suite, node );
        verifyPhotonIonisationReaction( ionisation );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
