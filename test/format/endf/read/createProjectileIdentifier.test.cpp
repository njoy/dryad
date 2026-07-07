// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createProjectileIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createProjectileIdentifier" ) {

  GIVEN( "ENDF sublibrary values" ) {

    WHEN( "a single sublibrary value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "g" ) == endf::read::createProjectileIdentifier( 0 ) );
        CHECK( id::ParticleID( "g" ) == endf::read::createProjectileIdentifier( 3 ) );
        CHECK( id::ParticleID( "n" ) == endf::read::createProjectileIdentifier( 10 ) );
        CHECK( id::ParticleID( "e-" ) == endf::read::createProjectileIdentifier( 113 ) );
        CHECK( id::ParticleID( "p" ) == endf::read::createProjectileIdentifier( 10010 ) );
        CHECK( id::ParticleID( "d" ) == endf::read::createProjectileIdentifier( 10020 ) );
        CHECK( id::ParticleID( "t" ) == endf::read::createProjectileIdentifier( 10030 ) );
        CHECK( id::ParticleID( "h" ) == endf::read::createProjectileIdentifier( 20030 ) );
        CHECK( id::ParticleID( "a" ) == endf::read::createProjectileIdentifier( 20040 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported sublibrary type" ) {

        CHECK_THROWS( endf::read::createProjectileIdentifier( 1 ) );
        CHECK_THROWS( endf::read::createProjectileIdentifier( 40090 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
