// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/ParticleDatabase.hpp"

// other includes
#include "njoy/constants.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const ParticleDatabase& );

SCENARIO( "ParticleDatabase" ) {

  GIVEN( "a set of Particle instances" ) {

    std::vector< Particle > particles = {

      Particle( id::ParticleID( "n" ), 1.008664, 0.5, +1 ),
      Particle( id::ParticleID( "p" ), 1.007276, 0.5, +1 ),
      Particle( id::ParticleID( "U235" ), 235.0439299, 0., +1, 0. ),
      Particle( id::ParticleID( "U235_e1" ), 235.0439299, 0., +1, 1e+6,
                std::nullopt, std::nullopt, std::nullopt, 1e+3 )
    };

    THEN( "a Particle can be constructed" ) {

      ParticleDatabase chunk( std::move( particles ) );

      verifyChunk( chunk );
    } // THEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const ParticleDatabase& chunk ) {

  CHECK( 4 == chunk.numberParticles() );

  CHECK( true == chunk.hasParticle( id::ParticleID( "n" ) ) );
  CHECK( true == chunk.hasParticle( id::ParticleID( "p" ) ) );
  CHECK( true == chunk.hasParticle( id::ParticleID( "U235" ) ) );
  CHECK( true == chunk.hasParticle( id::ParticleID( "U235_e1" ) ) );
  CHECK( false == chunk.hasParticle( id::ParticleID( "U235_e2" ) ) );

  auto neutron = chunk.particle( id::ParticleID( "n" ) );
  CHECK( id::ParticleID::neutron() == neutron.identifier() );
  CHECK_THAT( 1.008664, WithinRel( neutron.mass().value() ) );
  CHECK_THAT( 0.5, WithinRel( neutron.spin().value() ) );
  CHECK( 0.0 == neutron.charge() );
  CHECK( 0 == neutron.excitedState() );
  CHECK( +1 == neutron.parity().value() );
  CHECK( std::nullopt == neutron.energy() );
  CHECK( std::nullopt == neutron.nuclearMass() );
  CHECK( std::nullopt == neutron.massUncertainty() );
  CHECK( std::nullopt == neutron.nuclearMassUncertainty() );
  CHECK( std::nullopt == neutron.energyUncertainty() );

  auto proton = chunk.particle( id::ParticleID( "p" ) );
  CHECK( id::ParticleID::proton() == proton.identifier() );
  CHECK_THAT( 1.007276, WithinRel( proton.mass().value() ) );
  CHECK_THAT( 0.5, WithinRel( proton.spin().value() ) );
  CHECK( 1 == proton.charge() );
  CHECK( 0 == proton.excitedState() );
  CHECK( +1 == proton.parity().value() );
  CHECK( std::nullopt == proton.energy() );
  CHECK( std::nullopt == proton.nuclearMass() );
  CHECK( std::nullopt == proton.massUncertainty() );
  CHECK( std::nullopt == proton.nuclearMassUncertainty() );
  CHECK( std::nullopt == proton.energyUncertainty() );

  auto u235 = chunk.particle( id::ParticleID( "U235" ) );
  CHECK( id::ParticleID( "U235" ) == u235.identifier() );
  CHECK_THAT( 235.0439299, WithinRel( u235.mass().value() ) );
  CHECK_THAT( 0., WithinRel( u235.spin().value() ) );
  CHECK( 92 == u235.charge() );
  CHECK( 0 == u235.excitedState() );
  CHECK( +1 == u235.parity().value() );
  CHECK( 0.0 == u235.energy() );
  CHECK( std::nullopt == u235.nuclearMass() );
  CHECK( std::nullopt == u235.massUncertainty() );
  CHECK( std::nullopt == u235.nuclearMassUncertainty() );
  CHECK( std::nullopt == u235.energyUncertainty() );

  auto u235_e1 = chunk.particle( id::ParticleID( "U235_e1" ) );
  CHECK( id::ParticleID( "U235_e1" ) == u235_e1.identifier() );
  CHECK_THAT( 235.0439299, WithinRel( u235_e1.mass().value() ) );
  CHECK_THAT( 0., WithinRel( u235_e1.spin().value() ) );
  CHECK( 92 == u235_e1.charge() );
  CHECK( 1 == u235_e1.excitedState() );
  CHECK( +1 == u235_e1.parity().value() );
  CHECK( 1e+6 == u235_e1.energy() );
  CHECK( std::nullopt == u235_e1.nuclearMass() );
  CHECK( std::nullopt == u235_e1.massUncertainty() );
  CHECK( std::nullopt == u235_e1.nuclearMassUncertainty() );
  CHECK( std::nullopt != u235_e1.energyUncertainty() );
  CHECK_THAT( 1e+3, WithinRel( u235_e1.energyUncertainty().value() ) );
}
