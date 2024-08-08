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

  CHECK( true == chunk.isLinearised() );
  CHECK( 17 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 17 == chunk.energies().size() );
  CHECK( 17 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 16 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(  0.1     , WithinRel( chunk.energies()[0] ) );
  CHECK_THAT(  0.133352, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT(  9.9     , WithinRel( chunk.energies()[15] ) );
  CHECK_THAT( 10.      , WithinRel( chunk.energies()[16] ) );
  CHECK_THAT( 2.1394   , WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1.60421  , WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  .0214392, WithinRel( chunk.values()[15] ) );
  CHECK_THAT(  .0212245, WithinRel( chunk.values()[16] ) );
}
