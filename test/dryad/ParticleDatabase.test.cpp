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

      Particle::defaultParticle( id::ParticleID( "U235" ) ),
      Particle::defaultParticle( id::ParticleID( "U235_e1" ) ),
      Particle::neutron(),
      Particle::proton()
    };

    THEN( "a ParticleDatabase can be constructed" ) {

      ParticleDatabase chunk( std::move( particles ) );

      verifyChunk( chunk );
    } // THEN
  } // GIVEN

  GIVEN( "a set of particle identifiers" ) {

    std::vector< id::ParticleID > particles = {

      id::ParticleID( "U235" ),
      id::ParticleID( "U235_e1" ),
      id::ParticleID::neutron(),
      id::ParticleID::neutron(), // duplicate, will be erased
      id::ParticleID::proton()
    };

    THEN( "a ParticleDatabase can be constructed" ) {

      ParticleDatabase chunk( std::move( particles ) );

      verifyChunk( chunk );
    } // THEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const ParticleDatabase& chunk ) {

  using namespace njoy;

  CHECK( 4 == chunk.numberParticles() );

  CHECK( true == chunk.hasParticle( id::ParticleID( "n" ) ) );
  CHECK( true == chunk.hasParticle( id::ParticleID( "p" ) ) );
  CHECK( true == chunk.hasParticle( id::ParticleID( "U235" ) ) );
  CHECK( true == chunk.hasParticle( id::ParticleID( "U235_e1" ) ) );
  CHECK( false == chunk.hasParticle( id::ParticleID( "U235_e2" ) ) );

  auto particle = chunk.particle( id::ParticleID( "n" ) );
  CHECK( id::ParticleID::neutron() == particle.identifier() );
  CHECK_THAT( constants::neutron_mass, WithinRel( particle.mass().value() ) );
  CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
  CHECK( +1 == particle.parity().value() );
  CHECK( std::nullopt == particle.energy() );
  CHECK( std::nullopt == particle.nuclearMass() );
  CHECK_THAT( constants::neutron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
  CHECK( std::nullopt == particle.nuclearMassUncertainty() );
  CHECK( std::nullopt == particle.energyUncertainty() );

  particle = chunk.particle( id::ParticleID( "p" ) );
  CHECK( id::ParticleID::proton() == particle.identifier() );
  CHECK_THAT( constants::proton_mass, WithinRel( particle.mass().value() ) );
  CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
  CHECK( +1 == particle.parity().value() );
  CHECK( std::nullopt == particle.energy() );
  CHECK( std::nullopt == particle.nuclearMass() );
  CHECK_THAT( constants::proton_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
  CHECK( std::nullopt == particle.nuclearMassUncertainty() );
  CHECK( std::nullopt == particle.energyUncertainty() );

  particle = chunk.particle( id::ParticleID( "U235" ) );
  CHECK( id::ParticleID( "U235" ) == particle.identifier() );
  CHECK_THAT( 235.043928117, WithinRel( particle.mass().value() ) );
  CHECK_THAT( 3.5, WithinRel( particle.spin().value() ) );
  CHECK( -1 == particle.parity().value() );
  CHECK_THAT( 0., WithinRel( particle.energy().value() ) );
  CHECK( std::nullopt == particle.nuclearMass() );
  CHECK_THAT( 1.198e-6, WithinRel( particle.massUncertainty().value() ) );
  CHECK( std::nullopt == particle.nuclearMassUncertainty() );
  CHECK( std::nullopt == particle.energyUncertainty() );

  particle = chunk.particle( id::ParticleID( "U235_e1" ) );
  CHECK( id::ParticleID( "U235_e1" ) == particle.identifier() );
  CHECK_THAT( 235.043928117, WithinRel( particle.mass().value() ) );
  CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
  CHECK( +1 == particle.parity().value() );
  CHECK_THAT( 76., WithinRel( particle.energy().value() ) );
  CHECK( std::nullopt == particle.nuclearMass() );
  CHECK_THAT( 1.198e-6, WithinRel( particle.massUncertainty().value() ) );
  CHECK( std::nullopt == particle.nuclearMassUncertainty() );
  CHECK( std::nullopt == particle.energyUncertainty() );
}
