// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/adjustScatterLevel.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "adjustScatterLevel" ) {

  GIVEN( "projectiles, targets and mt numbers" ) {

    WHEN( "a target in the ground and excited state" ) {

      id::ParticleID neutron = id::ParticleID::neutron();
      id::ParticleID am242_e0( "Am242_e0" );
      id::ParticleID am242_e2( "Am242_e2" );

      THEN( "the elastic mt can be adjusted" ) {

        CHECK(  1 == adjustScatterLevel( neutron, am242_e0, 1 ) );
        CHECK(  2 == adjustScatterLevel( neutron, am242_e0, 2 ) );
        CHECK( 51 == adjustScatterLevel( neutron, am242_e0, 51 ) );
        CHECK( 52 == adjustScatterLevel( neutron, am242_e0, 52 ) );
        CHECK( 53 == adjustScatterLevel( neutron, am242_e0, 53 ) );
        CHECK( 54 == adjustScatterLevel( neutron, am242_e0, 54 ) );

        CHECK(  1 == adjustScatterLevel( neutron, am242_e2, 1 ) );
        CHECK( 50 == adjustScatterLevel( neutron, am242_e2, 51 ) );
        CHECK( 51 == adjustScatterLevel( neutron, am242_e2, 52 ) );
        CHECK(  2 == adjustScatterLevel( neutron, am242_e2, 2 ) );
        CHECK( 53 == adjustScatterLevel( neutron, am242_e2, 53 ) );
        CHECK( 54 == adjustScatterLevel( neutron, am242_e2, 54 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
