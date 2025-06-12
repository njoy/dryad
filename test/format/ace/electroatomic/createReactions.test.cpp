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
        electroatomic::eprdata12::h::verifyTotalReaction( total );

        auto tionisation = reactions[1];
        electroatomic::eprdata12::h::verifyTotalIonisationReaction( tionisation );

        auto telastic = reactions[2];
        electroatomic::eprdata12::h::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = reactions[3];
        electroatomic::eprdata12::h::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = reactions[4];
        electroatomic::eprdata12::h::verifyExcitationReaction( excitation );

        auto ionisation = reactions[5];
        electroatomic::eprdata12::h::verifyIonisationReaction( ionisation );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::electroatomic::createReactions( table );

        CHECK( 8 == reactions.size() );

        auto total = reactions[0];
        electroatomic::eprdata14::h::verifyTotalReaction( total );

        auto tionisation = reactions[1];
        electroatomic::eprdata14::h::verifyTotalIonisationReaction( tionisation );

        auto elastic = reactions[2];
        electroatomic::eprdata14::h::verifyLargeAngleElasticReaction( elastic );

        auto telastic = reactions[3];
        electroatomic::eprdata14::h::verifyTotalElasticReaction( telastic );

        auto bremsstrahlung = reactions[4];
        electroatomic::eprdata14::h::verifyBremsstrahlungReaction( bremsstrahlung );

        auto excitation = reactions[5];
        electroatomic::eprdata14::h::verifyExcitationReaction( excitation );

        auto ionisation = reactions[6];
        electroatomic::eprdata14::h::verifyIonisationReaction( ionisation );

        auto deficit = reactions[7];
        electroatomic::eprdata14::h::verifyElasticReactionDeficit( deficit );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
