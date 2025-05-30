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
        photoatomic::mcplib84::h::verifyTotalReaction( total );

        auto coherent = reactions[1];
        photoatomic::mcplib84::h::verifyCoherentReaction( coherent );

        auto incoherent = reactions[2];
        photoatomic::mcplib84::h::verifyIncoherentReaction( incoherent );

        auto pair = reactions[3];
        photoatomic::mcplib84::h::verifyPairProductionReaction( pair );

        auto photoelectric = reactions[4];
        photoatomic::mcplib84::h::verifyTotalPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::photoatomic::createReactions( table );

        CHECK( 6 == reactions.size() );

        auto total = reactions[0];
        photoatomic::eprdata12::h::verifyTotalReaction( total );

        auto coherent = reactions[1];
        photoatomic::eprdata12::h::verifyCoherentReaction( coherent );

        auto incoherent = reactions[2];
        photoatomic::eprdata12::h::verifyIncoherentReaction( incoherent );

        auto pair = reactions[3];
        photoatomic::eprdata12::h::verifyPairProductionReaction( pair );

        auto tphotoelectric = reactions[4];
        photoatomic::eprdata12::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = reactions[5];
        photoatomic::eprdata12::h::verifyPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::photoatomic::createReactions( table );

        CHECK( 6 == reactions.size() );

        auto total = reactions[0];
        photoatomic::eprdata14::h::verifyTotalReaction( total );

        auto coherent = reactions[1];
        photoatomic::eprdata14::h::verifyCoherentReaction( coherent );

        auto incoherent = reactions[2];
        photoatomic::eprdata14::h::verifyIncoherentReaction( incoherent );

        auto pair = reactions[3];
        photoatomic::eprdata14::h::verifyPairProductionReaction( pair );

        auto tphotoelectric = reactions[4];
        photoatomic::eprdata14::h::verifyTotalPhotoElectricReaction( tphotoelectric );

        auto photoelectric = reactions[5];
        photoatomic::eprdata14::h::verifyPhotoElectricReaction( photoelectric );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
