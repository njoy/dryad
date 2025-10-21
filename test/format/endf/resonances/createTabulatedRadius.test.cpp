// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/resonances/createTabulatedRadius.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const TabulatedRadius& );

SCENARIO( "createTabulatedRadius" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-069_Tm_168.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto radius = section.isotopes().front().resonanceRanges().front().scatteringRadius().value();

    WHEN( "a single parsed scattering radius from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::resonances::createTabulatedRadius( radius );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedRadius& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 50 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 50 == chunk.energies().size() );
  CHECK( 50 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 49 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 9e+3, WithinRel( chunk.energies()[24] ) );
  CHECK_THAT( 2e+5, WithinRel( chunk.energies()[49] ) );
  CHECK_THAT( 12.381, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  7.844, WithinRel( chunk.values()[24] ) );
  CHECK_THAT(  5.803, WithinRel( chunk.values()[49] ) );
}
