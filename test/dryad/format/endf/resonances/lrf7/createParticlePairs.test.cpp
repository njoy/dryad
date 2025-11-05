// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/resonances/lrf7/createParticlePairs.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const std::vector< std::optional< ParticlePair > >& );

SCENARIO( "createParticlePairs" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );
    auto pairs = parameters.particlePairs();

    WHEN( "a single parsed scattering radius from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Cl35" );
        auto chunk = format::endf::resonances::lrf7::createParticlePairs( projectile, target, pairs );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< std::optional< ParticlePair > >& chunk ) {

  CHECK( 3 == chunk.size() );
  // g,Cl36[all]
  CHECK( id::ParticleID::photon() == chunk[0]->lightParticle().identifier() );
  CHECK( 0 == chunk[0]->lightParticle().charge() );
  CHECK( 0 == chunk[0]->lightParticle().mass() );
  CHECK( 1 == chunk[0]->lightParticle().spin() );
  CHECK( +1 == chunk[0]->lightParticle().parity() );
  CHECK( id::ParticleID( "Cl36[all]" ) == chunk[0]->heavyParticle().identifier() );
  CHECK( 17 == chunk[0]->heavyParticle().charge() );
  CHECK( 35.65932 * constants::neutron_mass == chunk[0]->heavyParticle().mass() );
  CHECK( 0 == chunk[0]->heavyParticle().spin() );
  CHECK( +1 == chunk[0]->heavyParticle().parity() );
  // n,Cl35
  CHECK( id::ParticleID::neutron() == chunk[1]->lightParticle().identifier() );
  CHECK( 0 == chunk[1]->lightParticle().charge() );
  CHECK( constants::neutron_mass == chunk[1]->lightParticle().mass() );
  CHECK( 0.5 == chunk[1]->lightParticle().spin() );
  CHECK( +1 == chunk[1]->lightParticle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == chunk[1]->heavyParticle().identifier() );
  CHECK( 17 == chunk[1]->heavyParticle().charge() );
  CHECK( 34.66845 * constants::neutron_mass == chunk[1]->heavyParticle().mass() );
  CHECK( 1.5 == chunk[1]->heavyParticle().spin() );
  CHECK( +1 == chunk[1]->heavyParticle().parity() );
  // p,S35
  CHECK( id::ParticleID::proton() == chunk[2]->lightParticle().identifier() );
  CHECK( 1 == chunk[2]->lightParticle().charge() );
  CHECK( .9986235 * constants::neutron_mass == chunk[2]->lightParticle().mass() );
  CHECK( 0.5 == chunk[2]->lightParticle().spin() );
  CHECK( +1 == chunk[2]->lightParticle().parity() );
  CHECK( id::ParticleID( "S35" ) == chunk[2]->heavyParticle().identifier() );
  CHECK( 16 == chunk[2]->heavyParticle().charge() );
  CHECK( 34.66863 * constants::neutron_mass == chunk[2]->heavyParticle().mass() );
  CHECK( 1.5 == chunk[2]->heavyParticle().spin() );
  CHECK( +1 == chunk[2]->heavyParticle().parity() );
}
