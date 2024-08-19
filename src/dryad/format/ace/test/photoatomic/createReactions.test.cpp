// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/photoatomic/createReactions.hpp"

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

        auto reactions = format::ace::photoatomic::createReactions( table );

        CHECK( 5 == reactions.size() );

        auto total = reactions[0];
        verifyMcplib84PhotonTotalReaction( total );

        auto coherent = reactions[1];
        verifyMcplib84PhotonCoherentReaction( coherent );

        auto incoherent = reactions[2];
        verifyMcplib84PhotonIncoherentReaction( incoherent );

        auto pair = reactions[3];
        verifyMcplib84PhotonPairProductionReaction( pair );

        auto photoelectric = reactions[4];
        verifyMcplib84PhotonTotalPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::photoatomic::createReactions( table );

        CHECK( 6 == reactions.size() );

        auto total = reactions[0];
        verifyEprdata12PhotonTotalReaction( total );

        auto coherent = reactions[1];
        verifyEprdata12PhotonCoherentReaction( coherent );

        auto incoherent = reactions[2];
        verifyEprdata12PhotonIncoherentReaction( incoherent );

        auto pair = reactions[3];
        verifyEprdata12PhotonPairProductionReaction( pair );

        auto tphotoelectric = reactions[4];
        verifyEprdata12PhotonTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = reactions[5];
        verifyEprdata12PhotonPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::photoatomic::createReactions( table );

        CHECK( 6 == reactions.size() );

        auto total = reactions[0];
        verifyEprdata14PhotonTotalReaction( total );

        auto coherent = reactions[1];
        verifyEprdata14PhotonCoherentReaction( coherent );

        auto incoherent = reactions[2];
        verifyEprdata14PhotonIncoherentReaction( incoherent );

        auto pair = reactions[3];
        verifyEprdata14PhotonPairProductionReaction( pair );

        auto tphotoelectric = reactions[4];
        verifyEprdata14PhotonTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = reactions[5];
        verifyEprdata14PhotonPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
