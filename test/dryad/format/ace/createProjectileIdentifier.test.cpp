// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/createProjectileIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createProjectileIdentifier" ) {

  GIVEN( "ACE zaid values" ) {

    WHEN( "a zaid is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "g" ) == format::ace::createProjectileIdentifier( "1001.10u" ) );
        CHECK( id::ParticleID( "n" ) == format::ace::createProjectileIdentifier( "1001.10c" ) );
        CHECK( id::ParticleID( "p" ) == format::ace::createProjectileIdentifier( "1001.10h" ) );
        CHECK( id::ParticleID( "d" ) == format::ace::createProjectileIdentifier( "1001.10o" ) );
        CHECK( id::ParticleID( "t" ) == format::ace::createProjectileIdentifier( "1001.10r" ) );
        CHECK( id::ParticleID( "h" ) == format::ace::createProjectileIdentifier( "1001.10s" ) );
        CHECK( id::ParticleID( "a" ) == format::ace::createProjectileIdentifier( "1001.10a" ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported zaid type" ) {

        CHECK_THROWS( format::ace::createProjectileIdentifier( "1001.10e" ) );
        CHECK_THROWS( format::ace::createProjectileIdentifier( "1001.10t" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
