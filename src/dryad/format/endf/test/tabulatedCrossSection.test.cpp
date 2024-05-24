// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/tabulatedCrossSection.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedCrossSection& );

SCENARIO( "tabulatedCrossSection" ) {

  GIVEN( "ENDF MF3 sections" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto section = tape.materials().front().section( 3, 102 );

    WHEN( "a single unparsed MF3 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::tabulatedCrossSection( section );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single parsed MF3 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::tabulatedCrossSection( section.parse< 3 >() );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedCrossSection& chunk ) {

  CHECK( false == chunk.isLinearised() );
  CHECK( 153 == chunk.numberPoints() );
  CHECK( 2 == chunk.numberRegions() );
  CHECK( 153 == chunk.energies().size() );
  CHECK( 153 == chunk.values().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK( 32 == chunk.boundaries()[0] );
  CHECK( 152 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LogLog == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1e+4, WithinRel( chunk.energies()[32] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[152] ) );
  CHECK_THAT( 1.672869e+1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 4.950573e-4, WithinRel( chunk.values()[32] ) );
  CHECK_THAT( 2.710792e-5, WithinRel( chunk.values()[152] ) );
}
