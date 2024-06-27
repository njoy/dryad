// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createProjectileIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createProjectileIdentifier" ) {

  GIVEN( "ENDF sublibrary values" ) {

    WHEN( "a single sublibrary value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "g" ) == format::endf::createProjectileIdentifier( 0 ) );
        CHECK( id::ParticleID( "g" ) == format::endf::createProjectileIdentifier( 3 ) );
        CHECK( id::ParticleID( "n" ) == format::endf::createProjectileIdentifier( 10 ) );
        CHECK( id::ParticleID( "e-" ) == format::endf::createProjectileIdentifier( 113 ) );
        CHECK( id::ParticleID( "p" ) == format::endf::createProjectileIdentifier( 10010 ) );
        CHECK( id::ParticleID( "d" ) == format::endf::createProjectileIdentifier( 10020 ) );
        CHECK( id::ParticleID( "t" ) == format::endf::createProjectileIdentifier( 10030 ) );
        CHECK( id::ParticleID( "he3" ) == format::endf::createProjectileIdentifier( 20030 ) );
        CHECK( id::ParticleID( "a" ) == format::endf::createProjectileIdentifier( 20040 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported sublibrary type" ) {

        CHECK_THROWS( format::endf::createProjectileIdentifier( 1 ) );
        CHECK_THROWS( format::endf::createProjectileIdentifier( 40090 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
