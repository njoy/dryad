// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createProductIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createProductIdentifier" ) {

  GIVEN( "ENDF zap values" ) {

    WHEN( "a single zap value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "g" ) == endf::read::createProductIdentifier( 0, 0 ) );
        CHECK( id::ParticleID( "n" ) == endf::read::createProductIdentifier( 1, 0 ) );
        CHECK( id::ParticleID( "e-" ) == endf::read::createProductIdentifier( 11, 0 ) );
        CHECK( id::ParticleID( "H1" ) == endf::read::createProductIdentifier( 1001, 0 ) );
        CHECK( id::ParticleID( "H2" ) == endf::read::createProductIdentifier( 1002, 0 ) );
        CHECK( id::ParticleID( "H3" ) == endf::read::createProductIdentifier( 1003, 0 ) );
        CHECK( id::ParticleID( "He3" ) == endf::read::createProductIdentifier( 2003, 0 ) );
        CHECK( id::ParticleID( "He4" ) == endf::read::createProductIdentifier( 2004, 0 ) );
        CHECK( id::ParticleID( "Al27_e1" ) == endf::read::createProductIdentifier( 13027, 1 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
