// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/createSublibraryType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createSublibraryType" ) {

  GIVEN( "interaction types and projectile identifiers" ) {

    WHEN( "a single interaction type and projectile identifier value are given" ) {

      THEN( "it can be converted" ) {

        CHECK( 0     == endf::write::createSublibraryType( id::ParticleID::photon(), InteractionType::Nuclear ) );
        CHECK( 3     == endf::write::createSublibraryType( id::ParticleID::photon(), InteractionType::Atomic ) );
        CHECK( 10    == endf::write::createSublibraryType( id::ParticleID::neutron(), InteractionType::Nuclear ) );
        CHECK( 113   == endf::write::createSublibraryType( id::ParticleID::electron(), InteractionType::Atomic ) );
        CHECK( 10010 == endf::write::createSublibraryType( id::ParticleID::proton(), InteractionType::Nuclear ) );
        CHECK( 10020 == endf::write::createSublibraryType( id::ParticleID::deuteron(), InteractionType::Nuclear ) );
        CHECK( 10030 == endf::write::createSublibraryType( id::ParticleID::triton(), InteractionType::Nuclear ) );
        CHECK( 20030 == endf::write::createSublibraryType( id::ParticleID::helion(), InteractionType::Nuclear ) );
        CHECK( 20040 == endf::write::createSublibraryType( id::ParticleID::alpha(), InteractionType::Nuclear ) );
      } // THEN

      THEN( "an exception is thrown for projectiles and interaction types not supported by ENDF" ) {

        CHECK_THROWS( endf::write::createSublibraryType( id::ParticleID::neutron(), InteractionType::Atomic ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
