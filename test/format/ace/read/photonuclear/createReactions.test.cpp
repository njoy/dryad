// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/read/photonuclear/createReactions.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReactions" ) {

  GIVEN( "instances of PhotonuclearTable" ) {

    WHEN( "a Lib81 formatted table is given" ) {

      auto g = id::ParticleID::photon();
      auto C12 = id::ParticleID( "C12" );
      njoy::ACEtk::PhotonuclearTable table( njoy::ACEtk::fromFile( "6012.24u" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = ace::read::photonuclear::createReactions( g, C12, table, false );

        CHECK( 4 == reactions.size() );

        auto total = reactions[0];
        photonuclear::la150u::c12::verifyTotalReaction( total );

        auto anything = reactions[1];
        photonuclear::la150u::c12::verifyAnythingReaction( anything );

        auto neutron = reactions[2];
        photonuclear::la150u::c12::verifyNeutronReaction( neutron );

        auto proton = reactions[3];
        photonuclear::la150u::c12::verifyProtonReaction( proton );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
