// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedEnergyDistributions.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyElectronChunk( const TabulatedEnergyDistributions& );

SCENARIO( "createTabulatedEnergyDistribution" ) {

  GIVEN( "ENDF MF26 LAW = 1 LegendreCoefficients with NA = 0" ) {

    using ContinuumEnergyAngle = njoy::ENDFtk::section::Type< 26 >::ContinuumEnergyAngle;

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 26, 527 ).parse< 26 >();
    auto distribution = std::get< ContinuumEnergyAngle >( section.reactionProducts()[0].distribution() );

    WHEN( "a single parsed MF26 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedEnergyDistributions( distribution );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyElectronChunk( const TabulatedEnergyDistributions& chunk ) {

  CHECK( 10 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 10 == chunk.grid().size() );
  CHECK( 10 == chunk.distributions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT(   10.   , WithinRel( chunk.grid()[0] ) );
  CHECK_THAT(   20.736, WithinRel( chunk.grid()[1] ) );
  CHECK_THAT(   1e+7  , WithinRel( chunk.grid()[8] ) );
  CHECK_THAT(   1e+11 , WithinRel( chunk.grid()[9] ) );
  CHECK(  17 == chunk.distributions()[0].energies().size() );
  CHECK(  17 == chunk.distributions()[0].values().size() );
  CHECK(  19 == chunk.distributions()[1].energies().size() );
  CHECK(  19 == chunk.distributions()[1].values().size() );
  CHECK(  85 == chunk.distributions()[8].energies().size() );
  CHECK(  85 == chunk.distributions()[8].values().size() );
  CHECK( 111 == chunk.distributions()[9].energies().size() );
  CHECK( 111 == chunk.distributions()[9].values().size() );
  CHECK_THAT(  0.1       , WithinRel( chunk.distributions()[0].energies()[0] ) );
  CHECK_THAT(  0.133352  , WithinRel( chunk.distributions()[0].energies()[1] ) );
  CHECK_THAT(  9.9       , WithinRel( chunk.distributions()[0].energies()[15] ) );
  CHECK_THAT( 10.        , WithinRel( chunk.distributions()[0].energies()[16] ) );
  CHECK_THAT( 2.1394     , WithinRel( chunk.distributions()[0].values()[0] ) );
  CHECK_THAT( 1.60421    , WithinRel( chunk.distributions()[0].values()[1] ) );
  CHECK_THAT(  .0214392  , WithinRel( chunk.distributions()[0].values()[15] ) );
  CHECK_THAT(  .0212245  , WithinRel( chunk.distributions()[0].values()[16] ) );
  CHECK_THAT(  0.1       , WithinRel( chunk.distributions()[1].energies()[0] ) );
  CHECK_THAT(  0.14608   , WithinRel( chunk.distributions()[1].energies()[1] ) );
  CHECK_THAT( 20.5286    , WithinRel( chunk.distributions()[1].energies()[17] ) );
  CHECK_THAT( 20.736     , WithinRel( chunk.distributions()[1].energies()[18] ) );
  CHECK_THAT( 1.84823    , WithinRel( chunk.distributions()[1].values()[0] ) );
  CHECK_THAT( 1.26507    , WithinRel( chunk.distributions()[1].values()[1] ) );
  CHECK_THAT(  .00885527 , WithinRel( chunk.distributions()[1].values()[17] ) );
  CHECK_THAT(  .00876641 , WithinRel( chunk.distributions()[1].values()[18] ) );
  CHECK_THAT( .100000000 , WithinRel( chunk.distributions()[8].energies()[0] ) );
  CHECK_THAT( .128640000 , WithinRel( chunk.distributions()[8].energies()[1] ) );
  CHECK_THAT(  9981470.  , WithinRel( chunk.distributions()[8].energies()[83] ) );
  CHECK_THAT(  1e+7      , WithinRel( chunk.distributions()[8].energies()[84] ) );
  CHECK_THAT( .608334000 , WithinRel( chunk.distributions()[8].values()[0] ) );
  CHECK_THAT( .472898000 , WithinRel( chunk.distributions()[8].values()[1] ) );
  CHECK_THAT( 9.28343e-12, WithinRel( chunk.distributions()[8].values()[83] ) );
  CHECK_THAT( 5.8374e-12 , WithinRel( chunk.distributions()[8].values()[84] ) );
  CHECK_THAT(  .100000000, WithinRel( chunk.distributions()[9].energies()[0] ) );
  CHECK_THAT(  .148551000, WithinRel( chunk.distributions()[9].energies()[1] ) );
  CHECK_THAT( 9.99082E+10, WithinRel( chunk.distributions()[9].energies()[109] ) );
  CHECK_THAT(       1e+11, WithinRel( chunk.distributions()[9].energies()[110] ) );
  CHECK_THAT(  .365591000, WithinRel( chunk.distributions()[9].values()[0] ) );
  CHECK_THAT(  .246105000, WithinRel( chunk.distributions()[9].values()[1] ) );
  CHECK_THAT( 9.06486E-16, WithinRel( chunk.distributions()[9].values()[109] ) );
  CHECK_THAT( 5.16344E-16, WithinRel( chunk.distributions()[9].values()[110] ) );
  CHECK( 9 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
}
