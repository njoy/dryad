// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/electroatomic/createReactions.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReactions" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::electroatomic::createReactions( table );

        CHECK( 0 == reactions.size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::electroatomic::createReactions( table );

        CHECK( 6 == reactions.size() );

        auto total = reactions[0];
        verifyEprdata12ElectronTotalReaction( total );

        auto tionisation = reactions[1];
        verifyEprdata12ElectronTotalIonisationReaction( tionisation );

        auto telastic = reactions[2];
        verifyEprdata12ElectronTotalElasticReaction( telastic );

        auto bremsstrahlung = reactions[3];
        verifyEprdata12ElectronBremsstrahlungReaction( bremsstrahlung );

        auto excitation = reactions[4];
        verifyEprdata12ElectronExcitationReaction( excitation );

        auto ionisation = reactions[5];
        verifyEprdata12ElectronIonisationReaction( ionisation );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::electroatomic::createReactions( table );

        CHECK( 8 == reactions.size() );

        auto total = reactions[0];
        verifyEprdata14ElectronTotalReaction( total );

        auto tionisation = reactions[1];
        verifyEprdata14ElectronTotalIonisationReaction( tionisation );

        auto elastic = reactions[2];
        verifyEprdata14ElectronLargeAngleElasticReaction( elastic );

        auto telastic = reactions[3];
        verifyEprdata14ElectronTotalElasticReaction( telastic );

        auto bremsstrahlung = reactions[4];
        verifyEprdata12ElectronBremsstrahlungReaction( bremsstrahlung );

        auto excitation = reactions[5];
        verifyEprdata12ElectronExcitationReaction( excitation );

        auto ionisation = reactions[6];
        verifyEprdata12ElectronIonisationReaction( ionisation );

        auto deficit = reactions[7];
        verifyEprdata14ElectronElasticReactionDeficit( deficit );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
