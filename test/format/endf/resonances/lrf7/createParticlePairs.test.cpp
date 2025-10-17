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

        std::vector< id::ReactionID > reactions = {

          id::ReactionID( "n,Cl35->g,Cl36[all]" ),
          id::ReactionID( "n,Cl35->n,Cl35" ),
          id::ReactionID( "n,Cl35->p,S35" )
        };
        auto chunk = format::endf::resonances::lrf7::createParticlePairs( reactions, pairs );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< std::optional< ParticlePair > >& chunk ) {

  CHECK( 3 == chunk.size() );
  // g,Cl36[all]
  CHECK( id::ParticleID::photon() == chunk[0]->particle().identifier() );
  CHECK( 0 == chunk[0]->particle().charge() );
  CHECK( 0 == chunk[0]->particle().mass() );
  CHECK( 1 == chunk[0]->particle().spin() );
  CHECK( +1 == chunk[0]->particle().parity() );
  CHECK( id::ParticleID( "Cl36[all]" ) == chunk[0]->residual().identifier() );
  CHECK( 17 == chunk[0]->residual().charge() );
  CHECK( 35.65932 * constants::neutron_mass == chunk[0]->residual().mass() );
  CHECK( 0 == chunk[0]->residual().spin() );
  CHECK( +1 == chunk[0]->residual().parity() );
  // n,Cl35
  CHECK( id::ParticleID::neutron() == chunk[1]->particle().identifier() );
  CHECK( 0 == chunk[1]->particle().charge() );
  CHECK( constants::neutron_mass == chunk[1]->particle().mass() );
  CHECK( 0.5 == chunk[1]->particle().spin() );
  CHECK( +1 == chunk[1]->particle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == chunk[1]->residual().identifier() );
  CHECK( 17 == chunk[1]->residual().charge() );
  CHECK( 34.66845 * constants::neutron_mass == chunk[1]->residual().mass() );
  CHECK( 1.5 == chunk[1]->residual().spin() );
  CHECK( +1 == chunk[1]->residual().parity() );
  // p,S35
  CHECK( id::ParticleID::proton() == chunk[2]->particle().identifier() );
  CHECK( 1 == chunk[2]->particle().charge() );
  CHECK( .9986235 * constants::neutron_mass == chunk[2]->particle().mass() );
  CHECK( 0.5 == chunk[2]->particle().spin() );
  CHECK( +1 == chunk[2]->particle().parity() );
  CHECK( id::ParticleID( "S35" ) == chunk[2]->residual().identifier() );
  CHECK( 16 == chunk[2]->residual().charge() );
  CHECK( 34.66863 * constants::neutron_mass == chunk[2]->residual().mass() );
  CHECK( 1.5 == chunk[2]->residual().spin() );
  CHECK( +1 == chunk[2]->residual().parity() );
}
