// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createParticleDatabase.hpp"

// other includes
#include "njoy/format/endf/read/createReactions.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;
using namespace njoy::constants;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createParticles" ) {

  GIVEN( "ENDF materials - incident neutrons - stable target" ) {

    WHEN( "a single ENDF material is given" ) {

      using Tape = njoy::ENDFtk::tree::Tape;
      auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-001_H_001.endf" );
      auto material = tape.materials().front();
      auto information = material.section( 1, 451 ).parse< 1, 451 >();

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        std::map< id::ParticleID, double > masses;
        auto reactions = endf::read::createReactions( projectile, target, material, false, masses );
        auto particles = endf::read::createParticleDatabase( projectile, target, reactions, information, masses );

        CHECK( 4 == particles.numberParticles() );

        CHECK( true == particles.hasParticle( id::ParticleID( "g" ) ) );
        CHECK( true == particles.hasParticle( id::ParticleID( "n" ) ) );
        CHECK( true == particles.hasParticle( id::ParticleID( "H1" ) ) );
        CHECK( true == particles.hasParticle( id::ParticleID( "H2[all]" ) ) );

        auto particle = particles.particle( id::ParticleID( "g" ) );
        CHECK( id::ParticleID::photon() == particle.identifier() );
        CHECK_THAT( 0., WithinRel( particle.mass().value() ) );
        CHECK_THAT( 1.0, WithinRel( particle.spin().value() ) );
        CHECK( +1 == particle.parity().value() );
        CHECK( std::nullopt == particle.energy() );
        CHECK( std::nullopt == particle.nuclearMass() );
        CHECK_THAT( 0., WithinRel( particle.massUncertainty().value() ) );
        CHECK( std::nullopt == particle.nuclearMassUncertainty() );
        CHECK( std::nullopt == particle.energyUncertainty() );

        particle = particles.particle( id::ParticleID( "n" ) );
        CHECK( id::ParticleID::neutron() == particle.identifier() );
        CHECK_THAT( neutron_mass, WithinRel( particle.mass().value() ) );
        CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
        CHECK( +1 == particle.parity().value() );
        CHECK( std::nullopt == particle.energy() );
        CHECK( std::nullopt == particle.nuclearMass() );
        CHECK( std::nullopt == particle.massUncertainty() );
        CHECK( std::nullopt == particle.nuclearMassUncertainty() );
        CHECK( std::nullopt == particle.energyUncertainty() );

        particle = particles.particle( id::ParticleID( "H1" ) );
        CHECK( id::ParticleID( "H1" ) == particle.identifier() );
        CHECK_THAT( 0.9991673 * neutron_mass, WithinRel( particle.mass().value() ) );
        CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
        CHECK( +1 == particle.parity().value() );
        CHECK_THAT( 0., WithinRel( particle.energy().value() ) );
        CHECK( std::nullopt == particle.nuclearMass() );
        CHECK( std::nullopt == particle.massUncertainty() );
        CHECK( std::nullopt == particle.nuclearMassUncertainty() );
        CHECK( std::nullopt == particle.energyUncertainty() );

        particle = particles.particle( id::ParticleID( "H2[all]" ) );
        CHECK( id::ParticleID( "H2[all]" ) == particle.identifier() );
        CHECK_THAT( 1.996256 * neutron_mass , WithinRel( particle.mass().value() ) );
        CHECK( std::nullopt == particle.spin() );
        CHECK( std::nullopt == particle.parity() );
        CHECK( std::nullopt == particle.energy() );
        CHECK( std::nullopt == particle.nuclearMass() );
        CHECK( std::nullopt == particle.massUncertainty() );
        CHECK( std::nullopt == particle.nuclearMassUncertainty() );
        CHECK( std::nullopt == particle.energyUncertainty() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
