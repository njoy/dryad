// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/createParticleDatabase.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"
#include "njoy/dryad/format/ace/continuous/createReactions.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::constants;

// include common test verification functions

SCENARIO( "createParticles" ) {

  GIVEN( "instances of ContinuousEnergyTable" ) {

    WHEN( "a Lib81 formatted table is given" ) {

      njoy::ACEtk::ContinuousEnergyTable table( njoy::ACEtk::fromFile( "1001.10c" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        using namespace njoy::constants;

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        auto reactions = format::ace::continuous::createReactions( projectile, target, table, false );
        auto particles = format::ace::createParticleDatabase( target, reactions, table );

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
        CHECK_THAT( neutron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
        CHECK( std::nullopt == particle.nuclearMassUncertainty() );
        CHECK( std::nullopt == particle.energyUncertainty() );

        particle = particles.particle( id::ParticleID( "H1" ) );
        CHECK( id::ParticleID( "H1" ) == particle.identifier() );
        CHECK_THAT( 0.999167 * neutron_mass, WithinRel( particle.mass().value() ) );
        CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
        CHECK( +1 == particle.parity().value() );
        CHECK_THAT( 0., WithinRel( particle.energy().value() ) );
        CHECK( std::nullopt == particle.nuclearMass() );
        CHECK( std::nullopt == particle.massUncertainty() );
        CHECK( std::nullopt == particle.nuclearMassUncertainty() );
        CHECK( std::nullopt == particle.energyUncertainty() );

        particle = particles.particle( id::ParticleID( "H2[all]" ) );
        CHECK( id::ParticleID( "H2[all]" ) == particle.identifier() );
        CHECK_THAT( 2.014101777844, WithinRel( particle.mass().value() ) );
        CHECK( std::nullopt == particle.spin() );
        CHECK( std::nullopt == particle.parity() );
        CHECK( std::nullopt == particle.energy() );
        CHECK( std::nullopt == particle.nuclearMass() );
        CHECK_THAT( 0.000000000015, WithinRel( particle.massUncertainty().value() ) );
        CHECK( std::nullopt == particle.nuclearMassUncertainty() );
        CHECK( std::nullopt == particle.energyUncertainty() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
