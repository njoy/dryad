// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createEndfSublibraryType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createEndfSublibraryType" ) {

  GIVEN( "interaction types and projectile identifiers" ) {

    WHEN( "a single interaction type and projectile identifier value are given" ) {

      THEN( "it can be converted" ) {

        CHECK( 0     == format::endf::createEndfSublibraryType( id::ParticleID::photon(), InteractionType::Nuclear ) );
        CHECK( 3     == format::endf::createEndfSublibraryType( id::ParticleID::photon(), InteractionType::Atomic ) );
        CHECK( 10    == format::endf::createEndfSublibraryType( id::ParticleID::neutron(), InteractionType::Nuclear ) );
        CHECK( 113   == format::endf::createEndfSublibraryType( id::ParticleID::electron(), InteractionType::Atomic ) );
        CHECK( 10010 == format::endf::createEndfSublibraryType( id::ParticleID::proton(), InteractionType::Nuclear ) );
        CHECK( 10020 == format::endf::createEndfSublibraryType( id::ParticleID::deuteron(), InteractionType::Nuclear ) );
        CHECK( 10030 == format::endf::createEndfSublibraryType( id::ParticleID::triton(), InteractionType::Nuclear ) );
        CHECK( 20030 == format::endf::createEndfSublibraryType( id::ParticleID::helion(), InteractionType::Nuclear ) );
        CHECK( 20040 == format::endf::createEndfSublibraryType( id::ParticleID::alpha(), InteractionType::Nuclear ) );
      } // THEN

      THEN( "an exception is thrown for projectiles and interaction types not supported by ENDF" ) {

        CHECK_THROWS( format::endf::createEndfSublibraryType( id::ParticleID::neutron(), InteractionType::Atomic ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
