// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createParticleID.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createParticleID" ) {

  GIVEN( "ENDF sublibrary values" ) {

    WHEN( "a single sublibrary value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( ParticleID( "g" ) == format::endf::createParticleID( 0 ) );
        CHECK( ParticleID( "g" ) == format::endf::createParticleID( 3 ) );
        CHECK( ParticleID( "n" ) == format::endf::createParticleID( 10 ) );
        CHECK( ParticleID( "e-" ) == format::endf::createParticleID( 113 ) );
        CHECK( ParticleID( "p" ) == format::endf::createParticleID( 10010 ) );
        CHECK( ParticleID( "d" ) == format::endf::createParticleID( 10020 ) );
        CHECK( ParticleID( "t" ) == format::endf::createParticleID( 10030 ) );
        CHECK( ParticleID( "he3" ) == format::endf::createParticleID( 20030 ) );
        CHECK( ParticleID( "a" ) == format::endf::createParticleID( 20040 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported sublibrary type" ) {

        CHECK_THROWS( format::endf::createParticleID( 1 ) );
        CHECK_THROWS( format::endf::createParticleID( 40090 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
