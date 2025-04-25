// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createProjectileTarget.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createProjectileTarget" ) {

  GIVEN( "GNDS data - incident neutrons" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H1 = format::gnds::createProjectileTarget( document );

        CHECK( id::ParticleID( "n" ) == H1.projectileIdentifier() );
        CHECK( id::ParticleID( "H1" ) == H1.targetIdentifier() );

        CHECK( InteractionType::Nuclear == H1.interactionType() );

        CHECK( false == H1.isLinearised() );

        CHECK( std::nullopt == H1.resonances() );

        CHECK( true == H1.hasReaction( id::ReactionID( "1" ) ) );
        CHECK( true == H1.hasReaction( id::ReactionID( "2" ) ) );
        CHECK( true == H1.hasReaction( id::ReactionID( "102" ) ) );
        CHECK( false == H1.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 3 == H1.reactions().size() );

        auto total = H1.reactions()[0];
        neutron::h1::verifyTotalReaction( total );

        auto elastic = H1.reactions()[1];
        neutron::h1::verifyElasticReaction( elastic );

        auto capture = H1.reactions()[2];
        neutron::h1::verifyCaptureReaction( capture );

        total = H1.reaction( id::ReactionID( "1" ) );
        neutron::h1::verifyTotalReaction( total );

        elastic = H1.reaction( id::ReactionID( "2" ) );
        neutron::h1::verifyElasticReaction( elastic );

        capture = H1.reaction( id::ReactionID( "102" ) );
        neutron::h1::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - electro-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H0 = format::gnds::createProjectileTarget( document );

        CHECK( id::ParticleID( "e-" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "H" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID(  "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "525" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "526" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "527" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "528" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "534" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID( "-526" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        electron::h1::verifyTotalReaction( total );

        auto ionisation = H0.reactions()[1];
        electron::h1::verifyTotalIonisationReaction( ionisation );

        auto elastic = H0.reactions()[2];
        electron::h1::verifyElasticReaction( elastic );

        auto telastic = H0.reactions()[3];
        electron::h1::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = H0.reactions()[4];
        electron::h1::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = H0.reactions()[5];
        electron::h1::verifyExcitationReaction( excitation );

        auto subionisation = H0.reactions()[6];
        electron::h1::verifySubshellIonisationReaction( subionisation );

        auto deficit = H0.reactions()[7];
        electron::h1::verifyElasticDeficitReaction( deficit );

        total = H0.reaction( id::ReactionID( "501" ) );
        electron::h1::verifyTotalReaction( total );

        ionisation = H0.reaction( id::ReactionID( "522" ) );
        electron::h1::verifyTotalIonisationReaction( ionisation );

        elastic = H0.reaction( id::ReactionID( "525" ) );
        electron::h1::verifyElasticReaction( elastic );

        telastic = H0.reaction( id::ReactionID( "526" ) );
        electron::h1::verifyTotalElasticReaction( telastic );

        bremsstrahlung = H0.reaction( id::ReactionID( "527" ) );
        electron::h1::verifyBremsstrahlungReaction( bremsstrahlung );

        excitation = H0.reaction( id::ReactionID( "528" ) );
        electron::h1::verifyExcitationReaction( excitation );

        subionisation = H0.reaction( id::ReactionID( "534" ) );
        electron::h1::verifySubshellIonisationReaction( subionisation );

        deficit = H0.reaction( id::ReactionID( "-526" ) );
        electron::h1::verifyElasticDeficitReaction( deficit );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS data - photo-atomic" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );

    WHEN( "a GNDS XML document is given" ) {

      THEN( "it can be converted" ) {

        ProjectileTarget H0 = format::gnds::createProjectileTarget( document );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "H" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );

        CHECK( true == H0.isLinearised() );

        CHECK( std::nullopt == H0.resonances() );

        CHECK( true == H0.hasReaction( id::ReactionID(  "501" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "502" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "504" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "515" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "516" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "517" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "522" ) ) );
        CHECK( true == H0.hasReaction( id::ReactionID(  "534" ) ) );
        CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

        CHECK( 8 == H0.reactions().size() );

        auto total = H0.reactions()[0];
        photoatomic::h1::verifyTotalReaction( total );

        auto coherent = H0.reactions()[1];
        photoatomic::h1::verifyCoherentReaction( coherent );

        auto incoherent = H0.reactions()[2];
        photoatomic::h1::verifyIncoherentReaction( incoherent );

        auto epairproduction = H0.reactions()[3];
        photoatomic::h1::verifyElectronFieldPairProductionReaction( epairproduction );

        auto tpairproduction = H0.reactions()[4];
        photoatomic::h1::verifyTotalPairProductionReaction( tpairproduction );

        auto npairproduction = H0.reactions()[5];
        photoatomic::h1::verifyNuclearFieldPairProductionReaction( npairproduction );

        auto tionisation = H0.reactions()[6];
        photoatomic::h1::verifyTotalIonisationReaction( tionisation );

        auto ionisation = H0.reactions()[7];
        photoatomic::h1::verifyIonisationReaction( ionisation );

        total = H0.reaction( id::ReactionID( "501" ) );
        photoatomic::h1::verifyTotalReaction( total );

        coherent = H0.reaction( id::ReactionID( "502" ) );
        photoatomic::h1::verifyCoherentReaction( coherent );

        incoherent = H0.reaction( id::ReactionID( "504" ) );
        photoatomic::h1::verifyIncoherentReaction( incoherent );

        epairproduction = H0.reaction( id::ReactionID( "515" ) );
        photoatomic::h1::verifyElectronFieldPairProductionReaction( epairproduction );

        tpairproduction = H0.reaction( id::ReactionID( "516" ) );
        photoatomic::h1::verifyTotalPairProductionReaction( tpairproduction );

        npairproduction = H0.reaction( id::ReactionID( "517" ) );
        photoatomic::h1::verifyNuclearFieldPairProductionReaction( npairproduction );

        tionisation = H0.reaction( id::ReactionID( "522" ) );
        photoatomic::h1::verifyTotalIonisationReaction( tionisation );

        ionisation = H0.reaction( id::ReactionID( "534" ) );
        photoatomic::h1::verifyIonisationReaction( ionisation );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
