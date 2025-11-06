// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createReactionIdentifiers.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const std::vector< id::ReactionID >& );

SCENARIO( "createReactionIdentifiers" ) {

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
        auto chunk = format::endf::resonances::lrf7::createReactionIdentifiers( projectile, target, pairs );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< id::ReactionID >& chunk ) {

  CHECK( 3 == chunk.size() );
  CHECK( id::ReactionID( "n,Cl35->g,Cl36[all]" ) == chunk[0] );
  CHECK( id::ReactionID( "n,Cl35->n,Cl35" ) == chunk[1] );
  CHECK( id::ReactionID( "n,Cl35->p,S35" ) == chunk[2] );
}
