// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ndi/read/createProjectileIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createProjectileIdentifier" ) {

  GIVEN( "NDI zaid values" ) {

    WHEN( "a zaid is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID::neutron() == ndi::read::createProjectileIdentifier( "1001.853nm" ) );
        CHECK( id::ParticleID::neutron() == ndi::read::createProjectileIdentifier( "1001.853nd" ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported zaid type" ) {

        CHECK_THROWS( ndi::read::createProjectileIdentifier( "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
