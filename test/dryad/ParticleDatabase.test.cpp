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

      Particle( id::ParticleID( "n" ), njoy::constants::neutron_mass, 0.5, +1 ),
      Particle( id::ParticleID( "p" ), njoy::constants::neutron_mass, 0.5, +1 ),
      Particle( id::ParticleID( "U235" ), njoy::constants::neutron_mass, 0., +1 ),
      Particle( id::ParticleID( "U235_e1" ), njoy::constants::neutron_mass, 0., +1, 1e+6 )
    };

    THEN( "a Particle can be constructed" ) {

      ParticleDatabase chunk( std::move( particles ) );

      verifyChunk( chunk );
    } // THEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const ParticleDatabase& chunk ) {


}
