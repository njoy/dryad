// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createComplexBreakUpParticles.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createComplexBreakUpParticles" ) {

  GIVEN( "ENDF complex breakup flag value" ) {

    WHEN( "a residual is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID residual( "Li7" );
        std::map< id::ParticleID, std::size_t > particles = endf::read::createComplexBreakUpParticles( residual, 22 );
        CHECK( 2 == particles.size() );
        CHECK( 1 == particles[ id::ParticleID( "a" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "t" ) ] );

        residual = id::ParticleID( "C13" );
        particles = endf::read::createComplexBreakUpParticles( residual, 23 );
        CHECK( 2 == particles.size() );
        CHECK( 3 == particles[ id::ParticleID( "a" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "n" ) ] );

        residual = id::ParticleID( "Be8" );
        particles = endf::read::createComplexBreakUpParticles( residual, 24 );
        CHECK( 3 == particles.size() );
        CHECK( 1 == particles[ id::ParticleID( "a" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "n" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "h" ) ] );

        residual = id::ParticleID( "Li8" );
        particles = endf::read::createComplexBreakUpParticles( residual, 25 );
        CHECK( 3 == particles.size() );
        CHECK( 1 == particles[ id::ParticleID( "a" ) ] );
        CHECK( 2 == particles[ id::ParticleID( "n" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "d" ) ] );

        residual = id::ParticleID( "Be9" );
        particles = endf::read::createComplexBreakUpParticles( residual, 28 );
        CHECK( 2 == particles.size() );
        CHECK( 1 == particles[ id::ParticleID( "p" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "Li8[all]" ) ] );

        residual = id::ParticleID( "Be8" );
        particles = endf::read::createComplexBreakUpParticles( residual, 29 );
        CHECK( 1 == particles.size() );
        CHECK( 2 == particles[ id::ParticleID( "a" ) ] );

        residual = id::ParticleID( "C14" );
        particles = endf::read::createComplexBreakUpParticles( residual, 30 );
        CHECK( 3 == particles.size() );
        CHECK( 2 == particles[ id::ParticleID( "a" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "n" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "He5[all]" ) ] );

        residual = id::ParticleID( "C14" );
        particles = endf::read::createComplexBreakUpParticles( residual, 32 );
        CHECK( 2 == particles.size() );
        CHECK( 1 == particles[ id::ParticleID( "d" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "B12[all]" ) ] );

        residual = id::ParticleID( "C14" );
        particles = endf::read::createComplexBreakUpParticles( residual, 33 );
        CHECK( 2 == particles.size() );
        CHECK( 1 == particles[ id::ParticleID( "t" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "B11[all]" ) ] );

        residual = id::ParticleID( "C14" );
        particles = endf::read::createComplexBreakUpParticles( residual, 34 );
        CHECK( 2 == particles.size() );
        CHECK( 1 == particles[ id::ParticleID( "h" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "Be11[all]" ) ] );

        residual = id::ParticleID( "C13" );
        particles = endf::read::createComplexBreakUpParticles( residual, 35 );
        CHECK( 3 == particles.size() );
        CHECK( 2 == particles[ id::ParticleID( "a" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "d" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "t" ) ] );

        residual = id::ParticleID( "C13" );
        particles = endf::read::createComplexBreakUpParticles( residual, 36 );
        CHECK( 3 == particles.size() );
        CHECK( 2 == particles[ id::ParticleID( "a" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "d" ) ] );
        CHECK( 1 == particles[ id::ParticleID( "t" ) ] );
      } // THEN

      THEN( "an exception is thrown for invalid breakup values" ) {

        id::ParticleID residual( "Li7" );
        CHECK_THROWS( endf::read::createComplexBreakUpParticles( residual, 1 ) );
      } // THEN

      THEN( "an exception is thrown when the residual is too small" ) {

        id::ParticleID residual( "H3" );
        CHECK_THROWS( endf::read::createComplexBreakUpParticles( residual, 22 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
