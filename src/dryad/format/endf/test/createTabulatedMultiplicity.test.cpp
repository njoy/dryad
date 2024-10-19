// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedMultiplicity.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyNeutronChunk( const TabulatedMultiplicity& );
void verifyElectronChunk( const TabulatedMultiplicity& );

SCENARIO( "createTabulatedMultiplicity" ) {

  GIVEN( "ENDF MF6 multiplicities" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto section = tape.materials().front().section( 6, 102 ).parse< 6 >();
    auto multiplicity = section.reactionProduct( 0 ).multiplicity();

    WHEN( "a single parsed MF6 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedMultiplicity( multiplicity );

        verifyNeutronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF26 multiplicities" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 26, 527 ).parse< 26 >();
    auto multiplicity = section.reactionProduct( 11 ).multiplicity();

    WHEN( "a single parsed MF26 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedMultiplicity( multiplicity );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyNeutronChunk( const TabulatedMultiplicity& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 2 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[1] ) );
}

void verifyElectronChunk( const TabulatedMultiplicity& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 2 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(    10, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[1] ) );
}
