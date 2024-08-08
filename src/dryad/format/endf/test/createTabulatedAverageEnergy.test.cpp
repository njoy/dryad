// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedAverageEnergy.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyElectronChunk( const TabulatedAverageEnergy& );

SCENARIO( "createTabulatedAverageEnergy" ) {

  GIVEN( "ENDF MF26 LAW = 1 LegendreCoefficients with NA = 0" ) {

    using EnergyTransfer = njoy::ENDFtk::section::Type< 26 >::EnergyTransfer;

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 26, 527 ).parse< 26 >();
    auto distribution = std::get< EnergyTransfer >( section.reactionProducts()[1].distribution() );

    WHEN( "a single parsed MF26 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedAverageEnergy( distribution );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyElectronChunk( const TabulatedAverageEnergy& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 82 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 82 == chunk.energies().size() );
  CHECK( 82 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 81 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 10.        , WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 14.4       , WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 7.86876E+10, WithinRel( chunk.energies()[80] ) );
  CHECK_THAT(       1e+11, WithinRel( chunk.energies()[81] ) );
  CHECK_THAT(  10.         - 2.14426   , WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  14.4        - 2.87181   , WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  7.86876E+10 - 2.11850E+9, WithinRel( chunk.values()[80] ) );
  CHECK_THAT(  1e+11       - 2.66810E+9, WithinRel( chunk.values()[81] ) );
}
