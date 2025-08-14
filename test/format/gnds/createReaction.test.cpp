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
        Reaction total1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction total2 = format::gnds::createReaction( projectile, target, suite, node, true );
        neutron::h1::verifyTotalReaction( total1 );
        neutron::h1::verifyTotalReaction( total2 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "2" );
        Reaction elastic1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction elastic2 = format::gnds::createReaction( projectile, target, suite, node, true );
        neutron::h1::verifyElasticReaction( elastic1 );
        neutron::h1::verifyElasticReaction( elastic2 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "102" );
        Reaction capture1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction capture2 = format::gnds::createReaction( projectile, target, suite, node, true );
        neutron::h1::verifyCaptureReaction( capture1 );
        neutron::h1::verifyCaptureReaction( capture2 );
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
        Reaction total1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction total2 = format::gnds::createReaction( projectile, target, suite, node, true );
        electron::h0::verifyTotalReaction( total1 );
        electron::h0::verifyTotalReaction( total2 );

        node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "522" );
        Reaction ionisation1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction ionisation2 = format::gnds::createReaction( projectile, target, suite, node, true );
        electron::h0::verifyTotalIonisationReaction( ionisation1 );
        electron::h0::verifyTotalIonisationReaction( ionisation2 );

        node = incomplete.find_child_by_attribute( "reaction", "ENDF_MT", "525" );
        Reaction elastic1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction elastic2 = format::gnds::createReaction( projectile, target, suite, node, true );
        electron::h0::verifyElasticReaction( elastic1, false );
        electron::h0::verifyElasticReaction( elastic2, true );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "526" );
        Reaction telastic1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction telastic2 = format::gnds::createReaction( projectile, target, suite, node, true );
        electron::h0::verifyTotalElasticReaction( telastic1 );
        electron::h0::verifyTotalElasticReaction( telastic1 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "527" );
        Reaction bremsstrahlung1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction bremsstrahlung2 = format::gnds::createReaction( projectile, target, suite, node, true );
        electron::h0::verifyBremsstrahlungReaction( bremsstrahlung1, false );
        electron::h0::verifyBremsstrahlungReaction( bremsstrahlung2, true );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "528" );
        Reaction excitation1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction excitation2 = format::gnds::createReaction( projectile, target, suite, node, true );
        electron::h0::verifyExcitationReaction( excitation1 );
        electron::h0::verifyExcitationReaction( excitation2 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "534" );
        Reaction subionisation1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction subionisation2 = format::gnds::createReaction( projectile, target, suite, node, true );
        electron::h0::verifySubshellIonisationReaction( subionisation1, false );
        electron::h0::verifySubshellIonisationReaction( subionisation2, true );
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
        Reaction total1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction total2 = format::gnds::createReaction( projectile, target, suite, node, true );
        photoatomic::h0::verifyTotalReaction( total1 );
        photoatomic::h0::verifyTotalReaction( total2 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "502" );
        Reaction coherent1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction coherent2 = format::gnds::createReaction( projectile, target, suite, node, true );
        photoatomic::h0::verifyCoherentReaction( coherent1 );
        photoatomic::h0::verifyCoherentReaction( coherent2 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "504" );
        Reaction incoherent1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction incoherent2 = format::gnds::createReaction( projectile, target, suite, node, true );
        photoatomic::h0::verifyIncoherentReaction( incoherent1 );
        photoatomic::h0::verifyIncoherentReaction( incoherent2 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "515" );
        Reaction epairproduction1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction epairproduction2 = format::gnds::createReaction( projectile, target, suite, node, true );
        photoatomic::h0::verifyElectronFieldPairProductionReaction( epairproduction1 );
        photoatomic::h0::verifyElectronFieldPairProductionReaction( epairproduction2 );

        node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "516" );
        Reaction tpairproduction1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction tpairproduction2 = format::gnds::createReaction( projectile, target, suite, node, true );
        photoatomic::h0::verifyTotalPairProductionReaction( tpairproduction1 );
        photoatomic::h0::verifyTotalPairProductionReaction( tpairproduction2 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "517" );
        Reaction npairproduction1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction npairproduction2 = format::gnds::createReaction( projectile, target, suite, node, true );
        photoatomic::h0::verifyNuclearFieldPairProductionReaction( npairproduction1 );
        photoatomic::h0::verifyNuclearFieldPairProductionReaction( npairproduction2 );

        node = sums.find_child_by_attribute( "crossSectionSum", "ENDF_MT", "522" );
        Reaction tionisation1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction tionisation2 = format::gnds::createReaction( projectile, target, suite, node, true );
        photoatomic::h0::verifyTotalIonisationReaction( tionisation1 );
        photoatomic::h0::verifyTotalIonisationReaction( tionisation2 );

        node = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "534" );
        Reaction ionisation1 = format::gnds::createReaction( projectile, target, suite, node, false );
        Reaction ionisation2 = format::gnds::createReaction( projectile, target, suite, node, true );
        photoatomic::h0::verifyIonisationReaction( ionisation1 );
        photoatomic::h0::verifyIonisationReaction( ionisation2 );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
