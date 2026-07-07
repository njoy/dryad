// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createMixedAngularDistribution.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyLegendreChunk( const MixedAngularDistribution& );
void verifyTabulatedChunk( const MixedAngularDistribution&, bool );

SCENARIO( "createMixedAngularDistribution" ) {

  GIVEN( "ENDF MF4 LegendreCoefficients" ) {

    using LegendreDistributions = njoy::ENDFtk::section::Type< 4 >::LegendreDistributions;

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-001_H_001.endf" );
    auto section = tape.materials().front().section( 4, 2 ).parse< 4 >();
    auto distribution = std::get< LegendreDistributions >( section.distributions() );

    WHEN( "a single parsed MF4 LegendreCoefficients is given" ) {

      THEN( "it can be converted" ) {

        auto entry = distribution.angularDistributions()[0];
        auto chunk1 = endf::read::createMixedAngularDistribution( entry, false );
        auto chunk2 = endf::read::createMixedAngularDistribution( entry, true );

        verifyLegendreChunk( chunk1 );
        verifyLegendreChunk( chunk2 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF4 TabulatedDistribution" ) {

    using TabulatedDistributions = njoy::ENDFtk::section::Type< 4 >::TabulatedDistributions;

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-003_Li_007.endf" );
    auto section = tape.materials().front().section( 4, 16 ).parse< 4 >();
    auto distribution = std::get< TabulatedDistributions >( section.distributions() );

    WHEN( "a single parsed MF4 LTT = 2 distribution is given" ) {

      THEN( "it can be converted" ) {

        auto entry = distribution.angularDistributions().back();
        auto chunk1 = endf::read::createMixedAngularDistribution( entry, false );
        auto chunk2 = endf::read::createMixedAngularDistribution( entry, true );

        verifyTabulatedChunk( chunk1, false );
        verifyTabulatedChunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyLegendreChunk( const MixedAngularDistribution& chunk ) {

  // MF4 sections assume that the first coefficient is 0.5 so it is always normalised

  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.pdf() ) );

  auto pdf = std::get< LegendreAngularDistributionFunction >( chunk.pdf() );
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

  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.cdf() ) );

  auto cdf = std::get< LegendreAngularDistributionFunction >( chunk.cdf() );
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

void verifyTabulatedChunk( const MixedAngularDistribution& chunk, bool normalise ) {

  double normalisation = normalise ? .999998 : 1.;

  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.pdf() ) );

  auto pdf = std::get< TabulatedAngularDistributionFunction >( chunk.pdf() );
  CHECK( true == pdf.isLinearised() );
  CHECK( 11 == pdf.numberPoints() );
  CHECK( 1 == pdf.numberRegions() );
  CHECK( 11 == pdf.cosines().size() );
  CHECK( 11 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK( 10 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );
  CHECK_THAT( -1., WithinRel( pdf.cosines().front() ) );
  CHECK_THAT(  1., WithinRel( pdf.cosines().back() ) );
  CHECK_THAT( 2.533600e-1 / normalisation, WithinRel( pdf.values().front() ) );
  CHECK_THAT( 8.672000e-1 / normalisation, WithinRel( pdf.values().back() ) );

  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.cdf() ) );

  auto cdf = std::get< TabulatedAngularDistributionFunction >( chunk.cdf() );
  CHECK( true == cdf.isLinearised() );
  CHECK( 11 == cdf.numberPoints() );
  CHECK( 1 == cdf.numberRegions() );
  CHECK( 11 == cdf.cosines().size() );
  CHECK( 11 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK( 10 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
  CHECK_THAT( -1., WithinRel( cdf.cosines().front() ) );
  CHECK_THAT(  1., WithinRel( cdf.cosines().back() ) );
  CHECK_THAT( 0. / normalisation, WithinRel( cdf.values().front() ) );
  CHECK_THAT( .999998 / normalisation, WithinRel( cdf.values().back() ) );
}
