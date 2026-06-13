// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createParticleIdentifier.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;
using namespace njoy::dryad;

SCENARIO( "createParticleIdentifier" ) {

  GIVEN( "GNDS interpolation values" ) {

    WHEN( "an interpolation value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ParticleID( "g" ) == gnds::read::createParticleIdentifier( "photon" ) );
        CHECK( id::ParticleID( "n" ) == gnds::read::createParticleIdentifier( "n" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
