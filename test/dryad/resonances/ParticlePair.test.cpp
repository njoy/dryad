// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/ParticlePair.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ParticlePair" ) {

  GIVEN( "valid data for a ParticlePair" ) {

    Particle neutron( id::ParticleID::neutron(), 1.008664, 0.5, +1 );
    Particle u235( id::ParticleID( "U235" ), 235.0439299, 0., +1 );

    THEN( "a ParticlePair can be constructed" ) {

      ParticlePair pair( std::move( neutron ), std::move( u235 ) );

      CHECK( id::ParticleID::neutron() == pair.lightParticle().identifier() );
      CHECK_THAT( 1.008664, WithinRel( pair.lightParticle().mass() ) );
      CHECK_THAT( 0.5, WithinRel( pair.lightParticle().spin().value() ) );
      CHECK( 0.0 == pair.lightParticle().charge() );
      CHECK( +1 == pair.lightParticle().parity().value() );

      CHECK( id::ParticleID( "U235" ) == pair.heavyParticle().identifier() );
      CHECK_THAT( 235.0439299, WithinRel( pair.heavyParticle().mass() ) );
      CHECK_THAT( 0., WithinRel( pair.heavyParticle().spin().value() ) );
      CHECK( 92 == pair.heavyParticle().charge() );
      CHECK( +1 == pair.heavyParticle().parity().value() );

      CHECK_THAT( 235.0439299 / ( 1.008664 + 235.0439299 ), WithinRel( pair.massRatio() ) );
      CHECK_THAT( 1.008664 * 235.0439299 / ( 1.008664 + 235.0439299 ), WithinRel( pair.reducedMass() ) );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Documentation are given" ) {

      Particle neutron( id::ParticleID::neutron(), 1.008664, 0.5, +1 );
      Particle proton( id::ParticleID::proton(), 1.007276, 0.5, +1 );
      Particle u235( id::ParticleID( "U235" ), 235.0439299, 0., +1 );

      ParticlePair left( neutron, u235 );
      ParticlePair equal( neutron, u235 );
      ParticlePair different( proton, u235 );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
