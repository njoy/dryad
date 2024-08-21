// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedAngularDistributions.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyElectronChunk( const TabulatedAngularDistributions& );

SCENARIO( "createTabulatedAngularDistribution" ) {

  GIVEN( "ENDF MF26 LAW = 2" ) {

    using DiscreteTwoBodyScattering = njoy::ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering;

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 26, 525 ).parse< 26 >();
    auto distribution = std::get< DiscreteTwoBodyScattering >( section.reactionProduct( 11 ).distribution() );

    WHEN( "a single parsed MF26 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedAngularDistributions( distribution );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyElectronChunk( const TabulatedAngularDistributions& chunk ) {

  CHECK( 16 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 16 == chunk.grid().size() );
  CHECK( 16 == chunk.distributions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT(       10., WithinRel( chunk.grid()[0] ) );
  CHECK_THAT(     1000., WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 66250000., WithinRel( chunk.grid()[14] ) );
  CHECK_THAT(     1e+11, WithinRel( chunk.grid()[15] ) );
  CHECK(  2 == chunk.distributions()[0].pdf().cosines().size() );
  CHECK(  2 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 30 == chunk.distributions()[1].pdf().cosines().size() );
  CHECK( 30 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 95 == chunk.distributions()[14].pdf().cosines().size() );
  CHECK( 95 == chunk.distributions()[14].pdf().values().size() );
  CHECK( 96 == chunk.distributions()[15].pdf().cosines().size() );
  CHECK( 96 == chunk.distributions()[15].pdf().values().size() );
  CHECK_THAT( -1.          , WithinRel( chunk.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  0.999999    , WithinRel( chunk.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT(  0.5         , WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.5         , WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( -1.          , WithinRel( chunk.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT( -0.93        , WithinRel( chunk.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9962001   , WithinRel( chunk.distributions()[1].pdf().cosines()[28] ) );
  CHECK_THAT(  0.999999    , WithinRel( chunk.distributions()[1].pdf().cosines()[29] ) );
  CHECK_THAT(  0.00293923  , WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.00314865  , WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 42.358       , WithinRel( chunk.distributions()[1].pdf().values()[28] ) );
  CHECK_THAT( 62.1102      , WithinRel( chunk.distributions()[1].pdf().values()[29] ) );
  CHECK_THAT( -1.          , WithinRel( chunk.distributions()[14].pdf().cosines()[0] ) );
  CHECK_THAT( -0.995       , WithinRel( chunk.distributions()[14].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( chunk.distributions()[14].pdf().cosines()[93] ) );
  CHECK_THAT(  0.999999    , WithinRel( chunk.distributions()[14].pdf().cosines()[94] ) );
  CHECK_THAT(  1.51157e-11 , WithinRel( chunk.distributions()[14].pdf().values()[0] ) );
  CHECK_THAT(  6.43040e-10 , WithinRel( chunk.distributions()[14].pdf().values()[1] ) );
  CHECK_THAT(   8.14179e+5 , WithinRel( chunk.distributions()[14].pdf().values()[93] ) );
  CHECK_THAT(   9.84753e+5 , WithinRel( chunk.distributions()[14].pdf().values()[94] ) );
  CHECK_THAT( -1.          , WithinRel( chunk.distributions()[15].pdf().cosines()[0] ) );
  CHECK_THAT( -0.9999      , WithinRel( chunk.distributions()[15].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( chunk.distributions()[15].pdf().cosines()[94] ) );
  CHECK_THAT(  0.999999    , WithinRel( chunk.distributions()[15].pdf().cosines()[95] ) );
  CHECK_THAT(  6.25670e-13 , WithinRel( chunk.distributions()[15].pdf().values()[0] ) );
  CHECK_THAT(  1.25808e-11 , WithinRel( chunk.distributions()[15].pdf().values()[1] ) );
  CHECK_THAT(   8.15658e+5 , WithinRel( chunk.distributions()[15].pdf().values()[94] ) );
  CHECK_THAT(   9.86945e+5 , WithinRel( chunk.distributions()[15].pdf().values()[95] ) );
  CHECK( std::nullopt == chunk.distributions()[0].cdf() );
  CHECK( std::nullopt == chunk.distributions()[1].cdf() );
  CHECK( std::nullopt == chunk.distributions()[14].cdf() );
  CHECK( std::nullopt == chunk.distributions()[15].cdf() );
  CHECK( 15 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
}
