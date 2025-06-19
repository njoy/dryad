// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedScatteringFunction.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedScatteringFunction& );

SCENARIO( "createTabulatedScatteringFunction" ) {

  GIVEN( "ENDF MF3 sections" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto section = tape.materials().front().section( 27, 502 );

    WHEN( "a single unparsed MF27 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedScatteringFunction( section );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single parsed MF27 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedScatteringFunction( section.parse< 27 >() );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedScatteringFunction& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 1253 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 1253 == chunk.inverseLengths().size() );
  CHECK( 1253 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1252 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(          0, WithinRel( chunk.inverseLengths()[0] ) );
  CHECK_THAT(      0.001, WithinRel( chunk.inverseLengths()[1] ) );
  CHECK_THAT(  512000000, WithinRel( chunk.inverseLengths()[1251] ) );
  CHECK_THAT(       1e+9, WithinRel( chunk.inverseLengths()[1252] ) );
  CHECK_THAT(          1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(          1, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 1.1908e-37, WithinRel( chunk.values()[1251] ) );
  CHECK_THAT( 8.1829e-39, WithinRel( chunk.values()[1252] ) );
}
