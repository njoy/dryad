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

        CHECK( id::ParticleID( "g" ) == format::endf::createProductIdentifier( 0, 0, false ) );
        CHECK( id::ParticleID( "n" ) == format::endf::createProductIdentifier( 1, 0, false ) );
        CHECK( id::ParticleID( "e-" ) == format::endf::createProductIdentifier( 11, 0, false ) );
        CHECK( id::ParticleID( "p" ) == format::endf::createProductIdentifier( 1001, 0, false ) );
        CHECK( id::ParticleID( "d" ) == format::endf::createProductIdentifier( 1002, 0, false ) );
        CHECK( id::ParticleID( "t" ) == format::endf::createProductIdentifier( 1003, 0, false ) );
        CHECK( id::ParticleID( "he3" ) == format::endf::createProductIdentifier( 2003, 0, false ) );
        CHECK( id::ParticleID( "a" ) == format::endf::createProductIdentifier( 2004, 0, false ) );
        CHECK( id::ParticleID( "g_0" ) == format::endf::createProductIdentifier( 0, 0, true ) );
        CHECK( id::ParticleID( "n_0" ) == format::endf::createProductIdentifier( 1, 0, true ) );
        CHECK( id::ParticleID( "e-_0" ) == format::endf::createProductIdentifier( 11, 0, true ) );
        CHECK( id::ParticleID( "p_0" ) == format::endf::createProductIdentifier( 1001, 0, true ) );
        CHECK( id::ParticleID( "d_0" ) == format::endf::createProductIdentifier( 1002, 0, true ) );
        CHECK( id::ParticleID( "t_0" ) == format::endf::createProductIdentifier( 1003, 0, true ) );
        CHECK( id::ParticleID( "he3_0" ) == format::endf::createProductIdentifier( 2003, 0, true ) );
        CHECK( id::ParticleID( "a_0" ) == format::endf::createProductIdentifier( 2004, 0, true ) );
        CHECK( id::ParticleID( "g_1" ) == format::endf::createProductIdentifier( 0, 1, true ) );
        CHECK( id::ParticleID( "n_1" ) == format::endf::createProductIdentifier( 1, 1, true ) );
        CHECK( id::ParticleID( "e-_1" ) == format::endf::createProductIdentifier( 11, 1, true ) );
        CHECK( id::ParticleID( "p_1" ) == format::endf::createProductIdentifier( 1001, 1, true ) );
        CHECK( id::ParticleID( "d_1" ) == format::endf::createProductIdentifier( 1002, 1, true ) );
        CHECK( id::ParticleID( "t_1" ) == format::endf::createProductIdentifier( 1003, 1, true ) );
        CHECK( id::ParticleID( "he3_1" ) == format::endf::createProductIdentifier( 2003, 1, true ) );
        CHECK( id::ParticleID( "a_1" ) == format::endf::createProductIdentifier( 2004, 1, true ) );
        CHECK( id::ParticleID( "13027_e1" ) == format::endf::createProductIdentifier( 13027, 1 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
