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

        CHECK( id::ParticleID( "g" ) == format::endf::createProductIdentifier( 0, 0 ) );
        CHECK( id::ParticleID( "n" ) == format::endf::createProductIdentifier( 1, 0 ) );
        CHECK( id::ParticleID( "e-" ) == format::endf::createProductIdentifier( 11, 0 ) );
        CHECK( id::ParticleID( "p" ) == format::endf::createProductIdentifier( 1001, 0 ) );
        CHECK( id::ParticleID( "d" ) == format::endf::createProductIdentifier( 1002, 0 ) );
        CHECK( id::ParticleID( "t" ) == format::endf::createProductIdentifier( 1003, 0 ) );
        CHECK( id::ParticleID( "h" ) == format::endf::createProductIdentifier( 2003, 0 ) );
        CHECK( id::ParticleID( "a" ) == format::endf::createProductIdentifier( 2004, 0 ) );
        CHECK( id::ParticleID( "Al27_e1" ) == format::endf::createProductIdentifier( 13027, 1 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
