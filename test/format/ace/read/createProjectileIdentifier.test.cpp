// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/read/createProjectileIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createProjectileIdentifier" ) {

  GIVEN( "ACE zaid values" ) {

    WHEN( "a zaid is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "g" ) == ace::read::createProjectileIdentifier( "1001.10u" ) );
        CHECK( id::ParticleID( "n" ) == ace::read::createProjectileIdentifier( "1001.10c" ) );
        CHECK( id::ParticleID( "p" ) == ace::read::createProjectileIdentifier( "1001.10h" ) );
        CHECK( id::ParticleID( "d" ) == ace::read::createProjectileIdentifier( "1001.10o" ) );
        CHECK( id::ParticleID( "t" ) == ace::read::createProjectileIdentifier( "1001.10r" ) );
        CHECK( id::ParticleID( "h" ) == ace::read::createProjectileIdentifier( "1001.10s" ) );
        CHECK( id::ParticleID( "a" ) == ace::read::createProjectileIdentifier( "1001.10a" ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported zaid type" ) {

        CHECK_THROWS( ace::read::createProjectileIdentifier( "1001.10e" ) );
        CHECK_THROWS( ace::read::createProjectileIdentifier( "1001.10t" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
