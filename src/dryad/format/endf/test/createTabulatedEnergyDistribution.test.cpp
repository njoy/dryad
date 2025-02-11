// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedEnergyDistribution.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyElectronChunk( const TabulatedEnergyDistribution& );

SCENARIO( "createTabulatedEnergyDistribution" ) {

  GIVEN( "ENDF MF26 LAW = 1 LegendreCoefficients with NA = 0" ) {

    using ContinuumEnergyAngle = njoy::ENDFtk::section::Type< 26 >::ContinuumEnergyAngle;

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 26, 527 ).parse< 26 >();
    auto distribution = std::get< ContinuumEnergyAngle >( section.reactionProducts()[0].distribution() );

    WHEN( "a single parsed MF26 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedEnergyDistribution( distribution.distributions()[0] );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyElectronChunk( const TabulatedEnergyDistribution& chunk ) {

  decltype(auto) pdf = chunk.pdf();
  CHECK( true == pdf.isLinearised() );
  CHECK( 17 == pdf.numberPoints() );
  CHECK( 1 == pdf.numberRegions() );
  CHECK( 17 == pdf.energies().size() );
  CHECK( 17 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK( 16 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );
  CHECK_THAT(  0.1     , WithinRel( pdf.energies()[0] ) );
  CHECK_THAT(  0.133352, WithinRel( pdf.energies()[1] ) );
  CHECK_THAT(  9.9     , WithinRel( pdf.energies()[15] ) );
  CHECK_THAT( 10.      , WithinRel( pdf.energies()[16] ) );
  CHECK_THAT( 2.1394   , WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 1.60421  , WithinRel( pdf.values()[1] ) );
  CHECK_THAT(  .0214392, WithinRel( pdf.values()[15] ) );
  CHECK_THAT(  .0212245, WithinRel( pdf.values()[16] ) );

  CHECK( std::nullopt == chunk.cdf() );
}
