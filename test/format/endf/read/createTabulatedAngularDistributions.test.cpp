// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/createTabulatedAngularDistributions.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyNeutronMF4LTT2Chunk( const TabulatedAngularDistributions&, bool );
void verifyElectronChunk( const TabulatedAngularDistributions&, bool );

SCENARIO( "createTabulatedAngularDistribution" ) {

  GIVEN( "ENDF MF4 LTT = 2" ) {

    using TabulatedDistributions = njoy::ENDFtk::section::Type< 4 >::TabulatedDistributions;

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-003_Li_007.endf" );
    auto section = tape.materials().front().section( 4, 16 ).parse< 4 >();
    auto distribution = std::get< TabulatedDistributions >( section.distributions() );

    WHEN( "a single parsed MF4 LTT = 2 is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = format::endf::createTabulatedAngularDistributions( distribution, false );
        auto chunk2 = format::endf::createTabulatedAngularDistributions( distribution, true );

        verifyNeutronMF4LTT2Chunk( chunk1, false );
        verifyNeutronMF4LTT2Chunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF26 LAW = 2" ) {

    using DiscreteTwoBodyScattering = njoy::ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering;

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 26, 525 ).parse< 26 >();
    auto distribution = std::get< DiscreteTwoBodyScattering >( section.reactionProduct( 11 ).distribution() );

    WHEN( "a single parsed MF26 LAW = 2 is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = format::endf::createTabulatedAngularDistributions( distribution, false );
        auto chunk2 = format::endf::createTabulatedAngularDistributions( distribution, true );

        verifyElectronChunk( chunk1, false );
        verifyElectronChunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyNeutronMF4LTT2Chunk( const TabulatedAngularDistributions& chunk, bool normalise ) {

  CHECK( 10 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 10 == chunk.grid().size() );
  CHECK( 10 == chunk.distributions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 8.292880e+6, WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 8.500000e+6, WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 1.800000e+7, WithinRel( chunk.grid()[8] ) );
  CHECK_THAT( 2.000000e+7, WithinRel( chunk.grid()[9] ) );
  CHECK( 11 == chunk.distributions()[0].pdf().cosines().size() );
  CHECK( 11 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 11 == chunk.distributions()[1].pdf().cosines().size() );
  CHECK( 11 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 11 == chunk.distributions()[8].pdf().cosines().size() );
  CHECK( 11 == chunk.distributions()[8].pdf().values().size() );
  CHECK( 11 == chunk.distributions()[9].pdf().cosines().size() );
  CHECK( 11 == chunk.distributions()[9].pdf().values().size() );

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation00 = 1.;
  double normalisation01 = normalise ? .9999958 : 1.;
  double normalisation08 = normalise ? 1.000002 : 1.;
  double normalisation09 = normalise ? .999998 : 1.;

  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT( -0.8                          , WithinRel( chunk.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT(  0.8                          , WithinRel( chunk.distributions()[0].pdf().cosines()[9] ) );
  CHECK_THAT(  1.                           , WithinRel( chunk.distributions()[0].pdf().cosines()[10] ) );
  CHECK_THAT(  0. / normalisation00         , WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0. / normalisation00         , WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT(  0. / normalisation00         , WithinRel( chunk.distributions()[0].pdf().values()[9] ) );
  CHECK_THAT(  10. / normalisation00        , WithinRel( chunk.distributions()[0].pdf().values()[10] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT( -0.8                          , WithinRel( chunk.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT(  0.8                          , WithinRel( chunk.distributions()[1].pdf().cosines()[9] ) );
  CHECK_THAT(  1.                           , WithinRel( chunk.distributions()[1].pdf().cosines()[10] ) );
  CHECK_THAT(  0. / normalisation01         , WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0. / normalisation01         , WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT(  2.16660 / normalisation01    , WithinRel( chunk.distributions()[1].pdf().values()[9] ) );
  CHECK_THAT(  4.19050 / normalisation01    , WithinRel( chunk.distributions()[1].pdf().values()[10] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[8].pdf().cosines()[0] ) );
  CHECK_THAT( -0.8                          , WithinRel( chunk.distributions()[8].pdf().cosines()[1] ) );
  CHECK_THAT(  0.8                          , WithinRel( chunk.distributions()[8].pdf().cosines()[9] ) );
  CHECK_THAT(  1.                           , WithinRel( chunk.distributions()[8].pdf().cosines()[10] ) );
  CHECK_THAT(  2.452200e-1 / normalisation08, WithinRel( chunk.distributions()[8].pdf().values()[0] ) );
  CHECK_THAT(  2.707000e-1 / normalisation08, WithinRel( chunk.distributions()[8].pdf().values()[1] ) );
  CHECK_THAT(  7.996600e-1 / normalisation08, WithinRel( chunk.distributions()[8].pdf().values()[9] ) );
  CHECK_THAT(  8.857000e-1 / normalisation08, WithinRel( chunk.distributions()[8].pdf().values()[10] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[9].pdf().cosines()[0] ) );
  CHECK_THAT( -0.8                          , WithinRel( chunk.distributions()[9].pdf().cosines()[1] ) );
  CHECK_THAT(  0.8                          , WithinRel( chunk.distributions()[9].pdf().cosines()[9] ) );
  CHECK_THAT(  1.                           , WithinRel( chunk.distributions()[9].pdf().cosines()[10] ) );
  CHECK_THAT(  2.533600e-1 / normalisation09, WithinRel( chunk.distributions()[9].pdf().values()[0] ) );
  CHECK_THAT(  2.785700e-1 / normalisation09, WithinRel( chunk.distributions()[9].pdf().values()[1] ) );
  CHECK_THAT(  7.863000e-1 / normalisation09, WithinRel( chunk.distributions()[9].pdf().values()[9] ) );
  CHECK_THAT(  8.672000e-1 / normalisation09, WithinRel( chunk.distributions()[9].pdf().values()[10] ) );

  CHECK( 11 == chunk.distributions()[0].cdf().cosines().size() );
  CHECK( 11 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 11 == chunk.distributions()[1].cdf().cosines().size() );
  CHECK( 11 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 11 == chunk.distributions()[8].cdf().cosines().size() );
  CHECK( 11 == chunk.distributions()[8].cdf().values().size() );
  CHECK( 11 == chunk.distributions()[9].cdf().cosines().size() );
  CHECK( 11 == chunk.distributions()[9].cdf().values().size() );

  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[0].cdf().cosines()[0] ) );
  CHECK_THAT( -0.8                          , WithinRel( chunk.distributions()[0].cdf().cosines()[1] ) );
  CHECK_THAT(  0.8                          , WithinRel( chunk.distributions()[0].cdf().cosines()[9] ) );
  CHECK_THAT(  1.                           , WithinRel( chunk.distributions()[0].cdf().cosines()[10] ) );
  CHECK_THAT(  0. / normalisation00         , WithinRel( chunk.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(  0. / normalisation00         , WithinRel( chunk.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT(  0. / normalisation00         , WithinRel( chunk.distributions()[0].cdf().values()[9] ) );
  CHECK_THAT(  1. / normalisation00         , WithinRel( chunk.distributions()[0].cdf().values()[10] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[1].cdf().cosines()[0] ) );
  CHECK_THAT( -0.8                          , WithinRel( chunk.distributions()[1].cdf().cosines()[1] ) );
  CHECK_THAT(  0.8                          , WithinRel( chunk.distributions()[1].cdf().cosines()[9] ) );
  CHECK_THAT(  1.                           , WithinRel( chunk.distributions()[1].cdf().cosines()[10] ) );
  CHECK_THAT(  0. / normalisation01         , WithinRel( chunk.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(  0. / normalisation01         , WithinRel( chunk.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT(  0.3642858 / normalisation01  , WithinRel( chunk.distributions()[1].cdf().values()[9] ) );
  CHECK_THAT(  0.9999958 / normalisation01  , WithinRel( chunk.distributions()[1].cdf().values()[10] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[8].cdf().cosines()[0] ) );
  CHECK_THAT( -0.8                          , WithinRel( chunk.distributions()[8].cdf().cosines()[1] ) );
  CHECK_THAT(  0.8                          , WithinRel( chunk.distributions()[8].cdf().cosines()[9] ) );
  CHECK_THAT(  1.                           , WithinRel( chunk.distributions()[8].cdf().cosines()[10] ) );
  CHECK_THAT(  0.       / normalisation08   , WithinRel( chunk.distributions()[8].cdf().values()[0] ) );
  CHECK_THAT(  0.051592 / normalisation08   , WithinRel( chunk.distributions()[8].cdf().values()[1] ) );
  CHECK_THAT(  0.831466 / normalisation08   , WithinRel( chunk.distributions()[8].cdf().values()[9] ) );
  CHECK_THAT(  1.000002 / normalisation08   , WithinRel( chunk.distributions()[8].cdf().values()[10] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[9].cdf().cosines()[0] ) );
  CHECK_THAT( -0.8                          , WithinRel( chunk.distributions()[9].cdf().cosines()[1] ) );
  CHECK_THAT(  0.8                          , WithinRel( chunk.distributions()[9].cdf().cosines()[9] ) );
  CHECK_THAT(  1.                           , WithinRel( chunk.distributions()[9].cdf().cosines()[10] ) );
  CHECK_THAT(  0.       / normalisation09   , WithinRel( chunk.distributions()[9].cdf().values()[0] ) );
  CHECK_THAT(  0.053193 / normalisation09   , WithinRel( chunk.distributions()[9].cdf().values()[1] ) );
  CHECK_THAT(  0.834648 / normalisation09   , WithinRel( chunk.distributions()[9].cdf().values()[9] ) );
  CHECK_THAT(  0.999998 / normalisation09   , WithinRel( chunk.distributions()[9].cdf().values()[10] ) );

  CHECK( 9 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
}

void verifyElectronChunk( const TabulatedAngularDistributions& chunk, bool normalise ) {

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

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation00 = normalise ? 1.999999 / 2. : 1.;
  double normalisation01 = normalise ? 1.00000016366000 : 1.;
  double normalisation14 = normalise ? 1.00000048323214 : 1.;
  double normalisation15 = normalise ? 1.00000000937718 : 1.;

  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  0.999999                     , WithinRel( chunk.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT(  0.5 / normalisation00        , WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.5 / normalisation00        , WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT( -0.93                         , WithinRel( chunk.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9962001                    , WithinRel( chunk.distributions()[1].pdf().cosines()[28] ) );
  CHECK_THAT(  0.999999                     , WithinRel( chunk.distributions()[1].pdf().cosines()[29] ) );
  CHECK_THAT(  0.00293923 / normalisation01 , WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.00314865 / normalisation01 , WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 42.358      / normalisation01 , WithinRel( chunk.distributions()[1].pdf().values()[28] ) );
  CHECK_THAT( 62.1102     / normalisation01 , WithinRel( chunk.distributions()[1].pdf().values()[29] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[14].pdf().cosines()[0] ) );
  CHECK_THAT( -0.995                        , WithinRel( chunk.distributions()[14].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                    , WithinRel( chunk.distributions()[14].pdf().cosines()[93] ) );
  CHECK_THAT(  0.999999                     , WithinRel( chunk.distributions()[14].pdf().cosines()[94] ) );
  CHECK_THAT(  1.51157e-11 / normalisation14, WithinRel( chunk.distributions()[14].pdf().values()[0] ) );
  CHECK_THAT(  6.43040e-10 / normalisation14, WithinRel( chunk.distributions()[14].pdf().values()[1] ) );
  CHECK_THAT(  8.14179e+5 / normalisation14 , WithinRel( chunk.distributions()[14].pdf().values()[93] ) );
  CHECK_THAT(  9.84753e+5 / normalisation14 , WithinRel( chunk.distributions()[14].pdf().values()[94] ) );
  CHECK_THAT( -1.                           , WithinRel( chunk.distributions()[15].pdf().cosines()[0] ) );
  CHECK_THAT( -0.9999                       , WithinRel( chunk.distributions()[15].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                    , WithinRel( chunk.distributions()[15].pdf().cosines()[94] ) );
  CHECK_THAT(  0.999999                     , WithinRel( chunk.distributions()[15].pdf().cosines()[95] ) );
  CHECK_THAT(  6.25670e-13 / normalisation15, WithinRel( chunk.distributions()[15].pdf().values()[0] ) );
  CHECK_THAT(  1.25808e-11 / normalisation15, WithinRel( chunk.distributions()[15].pdf().values()[1] ) );
  CHECK_THAT(  8.15658e+5 / normalisation15 , WithinRel( chunk.distributions()[15].pdf().values()[94] ) );
  CHECK_THAT(  9.86945e+5 / normalisation15 , WithinRel( chunk.distributions()[15].pdf().values()[95] ) );

  CHECK(  2 == chunk.distributions()[0].cdf().cosines().size() );
  CHECK(  2 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 30 == chunk.distributions()[1].cdf().cosines().size() );
  CHECK( 30 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 95 == chunk.distributions()[14].cdf().cosines().size() );
  CHECK( 95 == chunk.distributions()[14].cdf().values().size() );
  CHECK( 96 == chunk.distributions()[15].cdf().cosines().size() );
  CHECK( 96 == chunk.distributions()[15].cdf().values().size() );

  CHECK_THAT( -1.                                    , WithinRel( chunk.distributions()[0].cdf().cosines()[0] ) );
  CHECK_THAT(  0.999999                              , WithinRel( chunk.distributions()[0].cdf().cosines()[1] ) );
  CHECK_THAT(  0.            / normalisation00       , WithinRel( chunk.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(  1.999999 / 2. / normalisation00       , WithinRel( chunk.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT( -1.                                    , WithinRel( chunk.distributions()[1].cdf().cosines()[0] ) );
  CHECK_THAT( -0.93                                  , WithinRel( chunk.distributions()[1].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9962001                             , WithinRel( chunk.distributions()[1].cdf().cosines()[28] ) );
  CHECK_THAT(  0.999999                              , WithinRel( chunk.distributions()[1].cdf().cosines()[29] ) );
  CHECK_THAT(  0.0           / normalisation01       , WithinRel( chunk.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(  0.0002130758  / normalisation01       , WithinRel( chunk.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT(  0.80156804117 / normalisation01       , WithinRel( chunk.distributions()[1].cdf().values()[28] ) );
  CHECK_THAT(  1.00000016366 / normalisation01       , WithinRel( chunk.distributions()[1].cdf().values()[29] ) );
  CHECK_THAT( -1.                                    , WithinRel( chunk.distributions()[14].cdf().cosines()[0] ) );
  CHECK_THAT( -0.995                                 , WithinRel( chunk.distributions()[14].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                             , WithinRel( chunk.distributions()[14].cdf().cosines()[93] ) );
  CHECK_THAT(  0.999999                              , WithinRel( chunk.distributions()[14].cdf().cosines()[94] ) );
  CHECK_THAT(  0.               / normalisation14    , WithinRel( chunk.distributions()[14].cdf().values()[0] ) );
  CHECK_THAT(  1.645389250e-12  / normalisation14    , WithinRel( chunk.distributions()[14].cdf().values()[1] ) );
  CHECK_THAT(  0.91005388327948 / normalisation14    , WithinRel( chunk.distributions()[14].cdf().values()[93] ) );
  CHECK_THAT(  1.00000048323214 / normalisation14    , WithinRel( chunk.distributions()[14].cdf().values()[94] ) );
  CHECK_THAT( -1.                                    , WithinRel( chunk.distributions()[15].cdf().cosines()[0] ) );
  CHECK_THAT( -0.9999                                , WithinRel( chunk.distributions()[15].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                             , WithinRel( chunk.distributions()[15].cdf().cosines()[94] ) );
  CHECK_THAT(  0.999999                              , WithinRel( chunk.distributions()[15].cdf().cosines()[95] ) );
  CHECK_THAT(  0.                   / normalisation15, WithinRel( chunk.distributions()[15].cdf().values()[0] ) );
  CHECK_THAT(  6.60323499999927e-16 / normalisation15, WithinRel( chunk.distributions()[15].cdf().values()[1] ) );
  CHECK_THAT(  0.90986985942462     / normalisation15, WithinRel( chunk.distributions()[15].cdf().values()[94] ) );
  CHECK_THAT(  1.00000000937718     / normalisation15, WithinRel( chunk.distributions()[15].cdf().values()[95] ) );

  CHECK( 15 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
}
