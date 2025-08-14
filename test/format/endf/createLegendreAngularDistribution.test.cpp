// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createLegendreAngularDistribution.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyMF4Chunk( const LegendreAngularDistribution& );
void verifyMF6LAW1Chunk( const LegendreAngularDistribution&, bool );
void verifyMF6LAW2Chunk( const LegendreAngularDistribution& );

SCENARIO( "createLegendreAngularDistribution" ) {

  GIVEN( "ENDF MF4 LegendreCoefficients" ) {

    using LegendreDistributions = njoy::ENDFtk::section::Type< 4 >::LegendreDistributions;

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto section = tape.materials().front().section( 4, 2 ).parse< 4 >();
    auto distribution = std::get< LegendreDistributions >( section.distributions() );

    WHEN( "a single parsed MF4 LegendreCoefficients is given" ) {

      THEN( "it can be converted" ) {

        auto coefficients = distribution.angularDistributions()[0].coefficients();
        auto chunk1 = format::endf::createLegendreAngularDistribution( coefficients, true, false );
        auto chunk2 = format::endf::createLegendreAngularDistribution( coefficients, true, true );

        verifyMF4Chunk( chunk1 );
        verifyMF4Chunk( chunk2 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF6 LAW=1 LegendreCoefficients" ) {

    using ContinuumEnergyAngle = njoy::ENDFtk::section::Type< 6 >::ContinuumEnergyAngle;
    using LegendreCoefficients = ContinuumEnergyAngle::LegendreCoefficients;

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto section = tape.materials().front().section( 6, 16 ).parse< 6 >();
    auto product = section.reactionProduct( 1 );
    auto distribution = std::get< ContinuumEnergyAngle >( product.distribution() );
    auto entry = std::get< LegendreCoefficients >( distribution.distributions()[0] );

    WHEN( "a single parsed MF6 LAW=1 LegendreCoefficients is given" ) {

      THEN( "it can be converted" ) {

        auto coefficients = entry.coefficients()[0];
        auto chunk1 = format::endf::createLegendreAngularDistribution( coefficients, false, false );
        auto chunk2 = format::endf::createLegendreAngularDistribution( coefficients, false, true );

        verifyMF6LAW1Chunk( chunk1, false );
        verifyMF6LAW1Chunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF6 LAW=2 LegendreCoefficients" ) {

    using DiscreteTwoBodyScattering = njoy::ENDFtk::section::Type< 6 >::DiscreteTwoBodyScattering;
    using LegendreCoefficients = DiscreteTwoBodyScattering::LegendreCoefficients;

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto section = tape.materials().front().section( 6, 102 ).parse< 6 >();
    auto distribution = std::get< DiscreteTwoBodyScattering >( section.reactionProduct( 0 ).distribution() );
    auto entry = std::get< LegendreCoefficients >( distribution.distributions()[0] );

    WHEN( "a single parsed MF6 LAW=2 LegendreCoefficients is given" ) {

      THEN( "it can be converted" ) {

        auto coefficients = entry.coefficients();
        auto chunk1 = format::endf::createLegendreAngularDistribution( coefficients, true, false );
        auto chunk2 = format::endf::createLegendreAngularDistribution( coefficients, true, true );

        verifyMF6LAW2Chunk( chunk1 );
        verifyMF6LAW2Chunk( chunk2 );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyMF4Chunk( const LegendreAngularDistribution& chunk ) {

  // MF4 sections assume that the first coefficient is 0.5 so it is always normalised

  auto pdf = chunk.pdf();
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 6 == pdf.order() );
  CHECK( 7 == pdf.coefficients().size() );
  CHECK_THAT( 0.5           , WithinRel( pdf.coefficients()[0] ) );
  CHECK_THAT( -1.7511000E-14, WithinRel( pdf.coefficients()[1] ) );
  CHECK_THAT( -2.5280750E-16, WithinRel( pdf.coefficients()[2] ) );
  CHECK_THAT( -6.4002050E-17, WithinRel( pdf.coefficients()[3] ) );
  CHECK_THAT(  1.3653765E-16, WithinRel( pdf.coefficients()[4] ) );
  CHECK_THAT( -1.7067215E-17, WithinRel( pdf.coefficients()[5] ) );
  CHECK_THAT(  2.5600835E-17, WithinRel( pdf.coefficients()[6] ) );

  auto cdf = chunk.cdf();
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 7 == cdf.order() );
  CHECK( 8 == cdf.coefficients().size() );
  CHECK_THAT( 0.5            , WithinRel( cdf.coefficients()[0] ) );
  CHECK_THAT( 0.5            , WithinRel( cdf.coefficients()[1] ) );
  CHECK_THAT( -5.82785685e-15, WithinRel( cdf.coefficients()[2] ) );
  CHECK_THAT( -6.57323500e-17, WithinRel( cdf.coefficients()[3] ) );
  CHECK_THAT( -7.59158500e-18, WithinRel( cdf.coefficients()[4] ) );
  CHECK_THAT(  1.32015550e-17, WithinRel( cdf.coefficients()[5] ) );
  CHECK_THAT( -1.55156500e-18, WithinRel( cdf.coefficients()[6] ) );
  CHECK_THAT(  1.96929500e-18, WithinRel( cdf.coefficients()[7] ) );
}

void verifyMF6LAW1Chunk( const LegendreAngularDistribution& chunk, bool normalise ) {

  double normalisation = normalise ? 100000. : 1.;

  auto pdf = chunk.pdf();
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 2 == pdf.order() );
  CHECK( 3 == pdf.coefficients().size() );
  CHECK_THAT( 100000. / 2. / normalisation  , WithinRel( pdf.coefficients()[0] ) );
  CHECK_THAT( 3014.8 * 3. / 2. / normalisation, WithinRel( pdf.coefficients()[1] ) );
  CHECK_THAT( 1696.9 * 5. / 2. / normalisation, WithinRel( pdf.coefficients()[2] ) );

  auto cdf = chunk.cdf();
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 3 == cdf.order() );
  CHECK( 4 == cdf.coefficients().size() );
  CHECK_THAT( 48492.6  / normalisation, WithinRel( cdf.coefficients()[0] ) );
  CHECK_THAT( 49151.55 / normalisation, WithinRel( cdf.coefficients()[1] ) );
  CHECK_THAT(  1507.4  / normalisation, WithinRel( cdf.coefficients()[2] ) );
  CHECK_THAT(   848.45 / normalisation, WithinRel( cdf.coefficients()[3] ) );
}

void verifyMF6LAW2Chunk( const LegendreAngularDistribution& chunk ) {

  // MF6 LAW=2 sections assume that the first coefficient is 0.5 so it is always normalised

  auto pdf = chunk.pdf();
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 2 == pdf.order() );
  CHECK( 3 == pdf.coefficients().size() );
  CHECK_THAT( 0.5           , WithinRel( pdf.coefficients()[0] ) );
  CHECK_THAT( -5.6557125e-08, WithinRel( pdf.coefficients()[1] ) );
  CHECK_THAT( -2.1856500e-12, WithinRel( pdf.coefficients()[2] ) );

  auto cdf = chunk.cdf();
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 3 == cdf.order() );
  CHECK( 4 == cdf.coefficients().size() );
  CHECK_THAT(  0.500000018852375, WithinRel( cdf.coefficients()[0] ) );
  CHECK_THAT(  0.500000000000437, WithinRel( cdf.coefficients()[1] ) );
  CHECK_THAT( -1.88523750000e-08, WithinRel( cdf.coefficients()[2] ) );
  CHECK_THAT( -4.37130000000e-13, WithinRel( cdf.coefficients()[3] ) );
}
