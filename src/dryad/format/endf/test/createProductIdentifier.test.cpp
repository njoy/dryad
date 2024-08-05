// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createProductIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createProductIdentifier" ) {

  GIVEN( "ENDF zap values" ) {

    WHEN( "a single zap value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "g" ) == format::endf::createProductIdentifier( 0 ) );
        CHECK( id::ParticleID( "n" ) == format::endf::createProductIdentifier( 1 ) );
        CHECK( id::ParticleID( "e-" ) == format::endf::createProductIdentifier( 11 ) );
        CHECK( id::ParticleID( "p" ) == format::endf::createProductIdentifier( 1001 ) );
        CHECK( id::ParticleID( "d" ) == format::endf::createProductIdentifier( 1002 ) );
        CHECK( id::ParticleID( "t" ) == format::endf::createProductIdentifier( 1003 ) );
        CHECK( id::ParticleID( "he3" ) == format::endf::createProductIdentifier( 2003 ) );
        CHECK( id::ParticleID( "a" ) == format::endf::createProductIdentifier( 2004 ) );
        CHECK( id::ParticleID( "13027" ) == format::endf::createProductIdentifier( 13027 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
