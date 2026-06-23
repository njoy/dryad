// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/createParticles.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
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
        auto particles = format::endf::createParticles( projectile, target, information );

        CHECK( 2 == particles.size() );

        CHECK( id::ParticleID::neutron() == particles[0].identifier() );
        CHECK_THAT( neutron_mass, WithinRel( particles[0].mass().value() ) );
        CHECK( std::nullopt == particles[0].spin() );
        CHECK( std::nullopt == particles[0].parity() );
        CHECK( std::nullopt == particles[0].energy() );
        CHECK( std::nullopt == particles[0].nuclearMass() );
        CHECK( std::nullopt == particles[0].massUncertainty() );
        CHECK( std::nullopt == particles[0].nuclearMassUncertainty() );
        CHECK( std::nullopt == particles[0].energyUncertainty() );

        CHECK( id::ParticleID( "H1" ) == particles[1].identifier() );
        CHECK_THAT( 9.991673e-1 * neutron_mass, WithinRel( particles[1].mass().value() ) );
        CHECK( std::nullopt == particles[1].spin() );
        CHECK( std::nullopt == particles[1].parity() );
        CHECK_THAT( 0. , WithinRel( particles[1].energy().value() ) );
        CHECK( std::nullopt == particles[1].nuclearMass() );
        CHECK( std::nullopt == particles[1].massUncertainty() );
        CHECK( std::nullopt == particles[1].nuclearMassUncertainty() );
        CHECK( std::nullopt == particles[1].energyUncertainty() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
