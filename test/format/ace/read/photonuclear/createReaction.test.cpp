// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/read/photonuclear/createReaction.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReaction" ) {

  GIVEN( "instances of PhotonuclearTable" ) {

    WHEN( "a Lib81 formatted table is given" ) {

      njoy::ACEtk::PhotonuclearTable table( njoy::ACEtk::fromFile( "6012.24u" ) );

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "g" );
        id::ParticleID target( "C12" );

        auto anything = ace::read::photonuclear::createReaction( projectile, target, table, 1, false );
        photonuclear::la150u::c12::verifyAnythingReaction( anything );

        auto neutron = ace::read::photonuclear::createReaction( projectile, target, table, 2, false );
        photonuclear::la150u::c12::verifyNeutronReaction( neutron );

        auto proton = ace::read::photonuclear::createReaction( projectile, target, table, 3, false );
        photonuclear::la150u::c12::verifyProtonReaction( proton );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
