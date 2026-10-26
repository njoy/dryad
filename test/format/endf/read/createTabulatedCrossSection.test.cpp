// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createTabulatedCrossSection.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyNeutronChunk( const TabulatedCrossSection& );
void verifyDeuteronChunk( const TabulatedCrossSection& );
void verifyElectronChunk( const TabulatedCrossSection& );

SCENARIO( "createTabulatedCrossSection" ) {

  GIVEN( "ENDF MF3 sections" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-001_H_001.endf" );
    auto section = tape.materials().front().section( 3, 102 );

    WHEN( "a single unparsed MF3 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::createTabulatedCrossSection( section, true );

        verifyNeutronChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single parsed MF3 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::createTabulatedCrossSection( section.parse< 3 >(), true );

        verifyNeutronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF3 sections with Coulomb penetrability interpolation" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "d-001_H_003.endf" );
    auto section = tape.materials().front().section( 3, 50 );

    WHEN( "a single unparsed MF3 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::createTabulatedCrossSection( section, true );

        verifyDeuteronChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single parsed MF3 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::createTabulatedCrossSection( section.parse< 3 >(), true );

        verifyDeuteronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF23 sections" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 23, 527 );

    WHEN( "a single unparsed MF23 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::createTabulatedCrossSection( section, true );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single parsed MF23 section is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::createTabulatedCrossSection( section.parse< 23 >(), true );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyNeutronChunk( const TabulatedCrossSection& chunk ) {

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
  CHECK( std::nullopt == chunk.threshold() );
}

void verifyDeuteronChunk( const TabulatedCrossSection& chunk ) {

  CHECK( false == chunk.isLinearised() );
  CHECK( 210 == chunk.numberPoints() );
  CHECK( 2 == chunk.numberRegions() );
  CHECK( 210 == chunk.energies().size() );
  CHECK( 210 == chunk.values().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK( 29 == chunk.boundaries()[0] );
  CHECK( 209 == chunk.boundaries()[1] );
  CHECK( InterpolationType::CoulombPenetrability == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
  CHECK_THAT( 1e+2, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 4e+7, WithinRel( chunk.energies()[209] ) );
  CHECK_THAT( 2.04690e-56, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1.496200e-2, WithinRel( chunk.values()[209] ) );
  CHECK( 0 == chunk.threshold() );
}

void verifyElectronChunk( const TabulatedCrossSection& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 96 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 96 == chunk.energies().size() );
  CHECK( 96 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 95 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(    10, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT(  1e+6, WithinRel( chunk.energies()[65] ) );
  CHECK_THAT( 1e+11, WithinRel( chunk.energies()[95] ) );
  CHECK_THAT(  29.7832, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 0.552449, WithinRel( chunk.values()[65] ) );
  CHECK_THAT( 0.990621, WithinRel( chunk.values()[95] ) );
  CHECK( std::nullopt == chunk.threshold() );
}
