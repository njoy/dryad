// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedFormFactor.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedFormFactor& );

SCENARIO( "createTabulatedFormFactor" ) {

  GIVEN( "ENDF MF3 sections" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto section = tape.materials().front().section( 27, 505 );

    WHEN( "a single unparsed MF27 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedFormFactor( section );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single parsed MF27 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedFormFactor( section.parse< 27 >() );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedFormFactor& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 297 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 297 == chunk.energies().size() );
  CHECK( 297 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 296 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(          1, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT(          2, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 9549925.86, WithinRel( chunk.energies()[295] ) );
  CHECK_THAT(   10000000, WithinRel( chunk.energies()[296] ) );
  CHECK_THAT(          0, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(          0, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 8.9767e-15, WithinRel( chunk.values()[295] ) );
  CHECK_THAT(        0, WithinRel( chunk.values()[296] ) );
}
