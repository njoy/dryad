// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/createParticles.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"
#include "ACEtk/PhotoatomicTable.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::constants;

// include common test verification functions

SCENARIO( "createParticles" ) {

  GIVEN( "instances of ContinuousEnergyTable" ) {

    WHEN( "a Lib81 formatted table is given" ) {

      njoy::ACEtk::ContinuousEnergyTable table( njoy::ACEtk::fromFile( "1001.10c" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        using namespace njoy;

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        auto particles = format::ace::createParticles( projectile, target, table );

        CHECK( 2 == particles.size() );

        CHECK( id::ParticleID::neutron() == particles[0].identifier() );
        CHECK_THAT( constants::neutron_mass, WithinRel( particles[0].mass().value() ) );
        CHECK_THAT( 0.5, WithinRel( particles[0].spin().value() ) );
        CHECK( +1 == particles[0].parity().value() );
        CHECK( std::nullopt == particles[0].energy() );
        CHECK( std::nullopt == particles[0].nuclearMass() );
        CHECK_THAT( constants::neutron_mass_uncertainty, WithinRel( particles[0].massUncertainty().value() ) );
        CHECK( std::nullopt == particles[0].nuclearMassUncertainty() );
        CHECK( std::nullopt == particles[0].energyUncertainty() );

        CHECK( id::ParticleID( "H1" ) == particles[1].identifier() );
        CHECK_THAT( 0.999167 * neutron_mass, WithinRel( particles[1].mass().value() ) );
        CHECK_THAT( 0.5, WithinRel( particles[1].spin().value() ) );
        CHECK( +1 == particles[1].parity().value() );
        CHECK_THAT( 0., WithinRel( particles[1].energy().value() ) );
        CHECK( std::nullopt == particles[1].nuclearMass() );
        CHECK( std::nullopt == particles[1].massUncertainty() );
        CHECK( std::nullopt == particles[1].nuclearMassUncertainty() );
        CHECK( std::nullopt == particles[1].energyUncertainty() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
