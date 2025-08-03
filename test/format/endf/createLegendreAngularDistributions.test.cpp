// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createLegendreAngularDistributions.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const LegendreAngularDistributions& );

SCENARIO( "createLegendreAngularDistribution" ) {

  GIVEN( "ENDF MF4 LegendreDistributions" ) {

    using LegendreDistributions = njoy::ENDFtk::section::Type< 4 >::LegendreDistributions;

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto section = tape.materials().front().section( 4, 2 ).parse< 4 >();
    auto distribution = std::get< LegendreDistributions >( section.distributions() );

    WHEN( "a single parsed MF4 LegendreDistributions is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = format::endf::createLegendreAngularDistributions( distribution, false );
        auto chunk2 = format::endf::createLegendreAngularDistributions( distribution, true );

        verifyChunk( chunk1 );
        verifyChunk( chunk2 );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const LegendreAngularDistributions& chunk ) {

  // MF4 sections assume that the first coefficient is 0.5 so it is always normalised

  CHECK( 153 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 153 == chunk.grid().size() );
  CHECK( 153 == chunk.distributions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 1e-5   , WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 2e-5   , WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 1.95e+7, WithinRel( chunk.grid()[151] ) );
  CHECK_THAT( 2e+7   , WithinRel( chunk.grid()[152] ) );
  CHECK( 7 == chunk.distributions()[0].pdf().coefficients().size() );
  CHECK( 7 == chunk.distributions()[1].pdf().coefficients().size() );
  CHECK( 7 == chunk.distributions()[151].pdf().coefficients().size() );
  CHECK( 7 == chunk.distributions()[152].pdf().coefficients().size() );
  CHECK_THAT( 0.5             , WithinRel( chunk.distributions()[0].pdf().coefficients()[0] ) );
  CHECK_THAT( -1.7511000E-14  , WithinRel( chunk.distributions()[0].pdf().coefficients()[1] ) );
  CHECK_THAT( -2.5280750E-16  , WithinRel( chunk.distributions()[0].pdf().coefficients()[2] ) );
  CHECK_THAT( -6.4002050E-17  , WithinRel( chunk.distributions()[0].pdf().coefficients()[3] ) );
  CHECK_THAT(  1.3653765E-16  , WithinRel( chunk.distributions()[0].pdf().coefficients()[4] ) );
  CHECK_THAT( -1.7067215E-17  , WithinRel( chunk.distributions()[0].pdf().coefficients()[5] ) );
  CHECK_THAT(  2.5600835E-17  , WithinRel( chunk.distributions()[0].pdf().coefficients()[6] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.distributions()[1].pdf().coefficients()[0] ) );
  CHECK_THAT( -3.4846950E-14  , WithinRel( chunk.distributions()[1].pdf().coefficients()[1] ) );
  CHECK_THAT( -1.7387225E-16  , WithinRel( chunk.distributions()[1].pdf().coefficients()[2] ) );
  CHECK_THAT( -9.1736400E-17  , WithinRel( chunk.distributions()[1].pdf().coefficients()[3] ) );
  CHECK_THAT( -2.9867625E-17  , WithinRel( chunk.distributions()[1].pdf().coefficients()[4] ) );
  CHECK_THAT( -3.4134430E-17  , WithinRel( chunk.distributions()[1].pdf().coefficients()[5] ) );
  CHECK_THAT(  1.8773950E-16  , WithinRel( chunk.distributions()[1].pdf().coefficients()[6] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.distributions()[151].pdf().coefficients()[0] ) );
  CHECK_THAT( -2.4240045E-02  , WithinRel( chunk.distributions()[151].pdf().coefficients()[1] ) );
  CHECK_THAT(  1.7942750E-02  , WithinRel( chunk.distributions()[151].pdf().coefficients()[2] ) );
  CHECK_THAT( -2.54685165E-03 , WithinRel( chunk.distributions()[151].pdf().coefficients()[3] ) );
  CHECK_THAT(  1.54781595E-03 , WithinRel( chunk.distributions()[151].pdf().coefficients()[4] ) );
  CHECK_THAT(  4.91773975E-05 , WithinRel( chunk.distributions()[151].pdf().coefficients()[5] ) );
  CHECK_THAT(  3.82748535E-05 , WithinRel( chunk.distributions()[151].pdf().coefficients()[6] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.distributions()[152].pdf().coefficients()[0] ) );
  CHECK_THAT( -2.41945200E-02 , WithinRel( chunk.distributions()[152].pdf().coefficients()[1] ) );
  CHECK_THAT(  1.95173075E-02 , WithinRel( chunk.distributions()[152].pdf().coefficients()[2] ) );
  CHECK_THAT( -2.71943700E-03 , WithinRel( chunk.distributions()[152].pdf().coefficients()[3] ) );
  CHECK_THAT(  1.69449750E-03 , WithinRel( chunk.distributions()[152].pdf().coefficients()[4] ) );
  CHECK_THAT(  5.25219970E-05 , WithinRel( chunk.distributions()[152].pdf().coefficients()[5] ) );
  CHECK_THAT(  4.48370065E-05 , WithinRel( chunk.distributions()[152].pdf().coefficients()[6] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.distributions()[0].cdf().coefficients()[0] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.distributions()[0].cdf().coefficients()[1] ) );
  CHECK_THAT( -5.82785685e-15 , WithinRel( chunk.distributions()[0].cdf().coefficients()[2] ) );
  CHECK_THAT( -6.57323500e-17 , WithinRel( chunk.distributions()[0].cdf().coefficients()[3] ) );
  CHECK_THAT( -7.59158500e-18 , WithinRel( chunk.distributions()[0].cdf().coefficients()[4] ) );
  CHECK_THAT(  1.32015550e-17 , WithinRel( chunk.distributions()[0].cdf().coefficients()[5] ) );
  CHECK_THAT( -1.55156500e-18 , WithinRel( chunk.distributions()[0].cdf().coefficients()[6] ) );
  CHECK_THAT(  1.96929500e-18 , WithinRel( chunk.distributions()[0].cdf().coefficients()[7] ) );
  CHECK_THAT( 0.50000000000001, WithinRel( chunk.distributions()[1].cdf().coefficients()[0] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.distributions()[1].cdf().coefficients()[1] ) );
  CHECK_THAT( -1.16025448e-14 , WithinRel( chunk.distributions()[1].cdf().coefficients()[2] ) );
  CHECK_THAT( -3.14558250e-17 , WithinRel( chunk.distributions()[1].cdf().coefficients()[3] ) );
  CHECK_THAT( -1.00020700e-17 , WithinRel( chunk.distributions()[1].cdf().coefficients()[4] ) );
  CHECK_THAT( -1.77601250e-17 , WithinRel( chunk.distributions()[1].cdf().coefficients()[5] ) );
  CHECK_THAT( -3.10313000e-18 , WithinRel( chunk.distributions()[1].cdf().coefficients()[6] ) );
  CHECK_THAT(  1.44415000e-17 , WithinRel( chunk.distributions()[1].cdf().coefficients()[7] ) );
  CHECK_THAT(  5.08080015e-01 , WithinRel( chunk.distributions()[151].cdf().coefficients()[0] ) );
  CHECK_THAT(  4.96411450e-01 , WithinRel( chunk.distributions()[151].cdf().coefficients()[1] ) );
  CHECK_THAT( -7.71617905e-03 , WithinRel( chunk.distributions()[151].cdf().coefficients()[2] ) );
  CHECK_THAT(  3.41657045e-03 , WithinRel( chunk.distributions()[151].cdf().coefficients()[3] ) );
  CHECK_THAT( -3.683066225e-04, WithinRel( chunk.distributions()[151].cdf().coefficients()[4] ) );
  CHECK_THAT(  1.690353305e-04, WithinRel( chunk.distributions()[151].cdf().coefficients()[5] ) );
  CHECK_THAT(  4.47067250e-06 , WithinRel( chunk.distributions()[151].cdf().coefficients()[6] ) );
  CHECK_THAT(  2.94421950e-06 , WithinRel( chunk.distributions()[151].cdf().coefficients()[7] ) );
  CHECK_THAT(  5.08064840e-01 , WithinRel( chunk.distributions()[152].cdf().coefficients()[0] ) );
  CHECK_THAT(  4.960965385e-01, WithinRel( chunk.distributions()[152].cdf().coefficients()[1] ) );
  CHECK_THAT( -7.67634900e-03 , WithinRel( chunk.distributions()[152].cdf().coefficients()[2] ) );
  CHECK_THAT(  3.71518400e-03 , WithinRel( chunk.distributions()[152].cdf().coefficients()[3] ) );
  CHECK_THAT( -3.93265727e-04 , WithinRel( chunk.distributions()[152].cdf().coefficients()[4] ) );
  CHECK_THAT(  1.848284995e-04, WithinRel( chunk.distributions()[152].cdf().coefficients()[5] ) );
  CHECK_THAT(  4.77472700e-06 , WithinRel( chunk.distributions()[152].cdf().coefficients()[6] ) );
  CHECK_THAT(  3.44900050e-06 , WithinRel( chunk.distributions()[152].cdf().coefficients()[7] ) );
  CHECK( 152 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
}
