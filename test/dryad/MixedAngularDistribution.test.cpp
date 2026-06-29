// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/MixedAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyIsotropicChunk( const MixedAngularDistribution&, bool );
void verifyLegendreChunk( const MixedAngularDistribution&, bool );
void verifyTabulatedChunk( const MixedAngularDistribution&, bool );

SCENARIO( "MixedAngularDistribution" ) {

  GIVEN( "an IsotropicAngularDistributionFunction instance" ) {

    WHEN( "the data is given explicitly" ) {

      MixedAngularDistribution chunk1( IsotropicAngularDistributionFunction(), false );
      MixedAngularDistribution chunk2( IsotropicAngularDistributionFunction(), true );

      verifyIsotropicChunk( chunk1, false );
      verifyIsotropicChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyIsotropicChunk( chunk1, true );
      verifyIsotropicChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "a LegendreAngularDistributionFunction instance" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > coefficients = { 1.0, 0.5 };

      MixedAngularDistribution chunk1( LegendreAngularDistributionFunction( coefficients ), false );
      MixedAngularDistribution chunk2( LegendreAngularDistributionFunction( coefficients ), true );

      verifyLegendreChunk( chunk1, false );
      verifyLegendreChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyLegendreChunk( chunk1, true );
      verifyLegendreChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "a TabulatedAngularDistributionFunction instance" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > cosines = { -1., 0., 0.5, 1. };
      const std::vector< double > values = { 0., 1., 1.5, 2. };

      MixedAngularDistribution chunk1( TabulatedAngularDistributionFunction( cosines, values, InterpolationType::LinearLinear ), false );
      MixedAngularDistribution chunk2( TabulatedAngularDistributionFunction( cosines, values, InterpolationType::LinearLinear ), true );

      verifyTabulatedChunk( chunk1, false );
      verifyTabulatedChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyTabulatedChunk( chunk1, true );
      verifyTabulatedChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedAngularDistribution are given" ) {

     MixedAngularDistribution left( TabulatedAngularDistributionFunction( { -1., 1. }, { 0.5, 0.5 } ) );
     MixedAngularDistribution equal( TabulatedAngularDistributionFunction( { -1., 1. }, { 0.5, 0.5 } ) );
     MixedAngularDistribution unnormalised( TabulatedAngularDistributionFunction( { -1., 1. }, { 1., 1. }, InterpolationType::LinearLinear ), true );
     MixedAngularDistribution different( LegendreAngularDistributionFunction( { 0.5, 1. } ) );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( true == ( left == unnormalised ) ); // normalised under the hood, so equal
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( false == ( left != unnormalised ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyIsotropicChunk( const MixedAngularDistribution& chunk, bool normalise ) {

  CHECK( true == std::holds_alternative< IsotropicAngularDistributionFunction >( chunk.pdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.cdf() ) );

  auto cdf = std::get< TabulatedAngularDistributionFunction >( chunk.cdf() );
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 2 == cdf.cosines().size() );
  CHECK( 2 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK_THAT( -1., WithinRel( cdf.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( cdf.cosines()[1] ) );
  CHECK_THAT(  0., WithinRel( cdf.values()[0] ) );
  CHECK_THAT(  1., WithinRel( cdf.values()[1] ) );
  CHECK( 1 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );

  // evaluate
  CHECK_THAT( 0.5, WithinRel( chunk( -1. ) ) );
  CHECK_THAT( 0.5, WithinRel( chunk(  0. ) ) );
  CHECK_THAT( 0.5, WithinRel( chunk(  1. ) ) );

  // average cosine - always the mean value even for unnormalised distributions
  CHECK_THAT( 0., WithinRel( chunk.averageCosine() ) );

  // linearisation
  auto linear = chunk.linearise();

  auto linearpdf = linear.pdf();
  CHECK_THAT( -1., WithinRel( linearpdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( linearpdf.upperCosineLimit() ) );
  CHECK( 2 == linearpdf.cosines().size() );
  CHECK( 2 == linearpdf.values().size() );
  CHECK( 1 == linearpdf.boundaries().size() );
  CHECK( 1 == linearpdf.interpolants().size() );
  CHECK_THAT( -1., WithinRel( linearpdf.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( linearpdf.cosines()[1] ) );
  CHECK_THAT(  0.5, WithinRel( linearpdf.values()[0] ) );
  CHECK_THAT(  0.5, WithinRel( linearpdf.values()[1] ) );
  CHECK( 1 == linearpdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == linearpdf.interpolants()[0] );

  auto linearcdf = linear.cdf();
  CHECK_THAT( -1., WithinRel( linearcdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( linearcdf.upperCosineLimit() ) );
  CHECK( 2 == linearcdf.cosines().size() );
  CHECK( 2 == linearcdf.values().size() );
  CHECK( 1 == linearcdf.boundaries().size() );
  CHECK( 1 == linearcdf.interpolants().size() );
  CHECK_THAT( -1., WithinRel( linearcdf.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( linearcdf.cosines()[1] ) );
  CHECK_THAT(  0., WithinRel( linearcdf.values()[0] ) );
  CHECK_THAT(  1., WithinRel( linearcdf.values()[1] ) );
  CHECK( 1 == linearcdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == linearcdf.interpolants()[0] );
}

void verifyLegendreChunk( const MixedAngularDistribution& chunk, bool normalise ) {

  double normalisation = normalise ? 2.0 : 1.0;

  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.cdf() ) );

  auto pdf = std::get< LegendreAngularDistributionFunction >( chunk.pdf() );
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 1 == pdf.order() );
  CHECK( 2 == pdf.coefficients().size() );
  CHECK_THAT( 1.0 / normalisation, WithinRel( pdf.coefficients()[0] ) );
  CHECK_THAT( 0.5 / normalisation, WithinRel( pdf.coefficients()[1] ) );

  CHECK_THAT( 2.0 / normalisation, WithinRel( pdf.integral() ) );

  auto cdf = std::get< LegendreAngularDistributionFunction >( chunk.cdf() );
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 2 == cdf.order() );
  CHECK( 3 == cdf.coefficients().size() );
  CHECK_THAT( 0.8333333333333333 / normalisation, WithinRel( cdf.coefficients()[0] ) );
  CHECK_THAT( 1. / normalisation                , WithinRel( cdf.coefficients()[1] ) );
  CHECK_THAT( 0.1666666666666666 / normalisation, WithinRel( cdf.coefficients()[2] ) );
  CHECK_THAT( 0., WithinRel( cdf( -1. ) ) );
  CHECK_THAT( 2. / normalisation, WithinRel( cdf(  1. ) ) );

  // evaluate
  CHECK_THAT( 0.5 / normalisation, WithinRel( chunk( -1. ) ) );
  CHECK_THAT( 1.0 / normalisation, WithinRel( chunk(  0. ) ) );
  CHECK_THAT( 1.5 / normalisation, WithinRel( chunk(  1. ) ) );

  // average cosine - always the mean value even for unnormalised distributions
  CHECK_THAT( 1. / 3. / 2., WithinRel( chunk.averageCosine() ) );

  // linearisation
  auto linear = chunk.linearise();

  auto linearpdf = linear.pdf();
  CHECK_THAT( -1., WithinRel( linearpdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( linearpdf.upperCosineLimit() ) );
  CHECK( 2 == linearpdf.cosines().size() );
  CHECK( 2 == linearpdf.values().size() );
  CHECK( 1 == linearpdf.boundaries().size() );
  CHECK( 1 == linearpdf.interpolants().size() );
  CHECK_THAT( -1., WithinRel( linearpdf.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( linearpdf.cosines()[1] ) );
  CHECK_THAT(  0.5 / normalisation, WithinRel( linearpdf.values()[0] ) );
  CHECK_THAT(  1.5 / normalisation, WithinRel( linearpdf.values()[1] ) );
  CHECK( 1 == linearpdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == linearpdf.interpolants()[0] );

  auto linearcdf = linear.cdf();
  CHECK_THAT( -1., WithinRel( linearcdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( linearcdf.upperCosineLimit() ) );
  CHECK( 2 == linearcdf.cosines().size() );
  CHECK( 2 == linearcdf.values().size() );
  CHECK( 1 == linearcdf.boundaries().size() );
  CHECK( 1 == linearcdf.interpolants().size() );
  CHECK_THAT( -1., WithinRel( linearcdf.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( linearcdf.cosines()[1] ) );
  CHECK_THAT(  0. / normalisation, WithinRel( linearcdf.values()[0] ) );
  CHECK_THAT(  2. / normalisation, WithinRel( linearcdf.values()[1] ) );
  CHECK( 1 == linearcdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == linearcdf.interpolants()[0] );
}

void verifyTabulatedChunk( const MixedAngularDistribution& chunk, bool normalise ) {

  double normalisation = normalise ? 2.0 : 1.0;

  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.pdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.cdf() ) );

  auto pdf = std::get< TabulatedAngularDistributionFunction >( chunk.pdf() );
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 4 == pdf.cosines().size() );
  CHECK( 4 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK_THAT( -1.  , WithinRel( pdf.cosines()[0] ) );
  CHECK_THAT(  0.  , WithinRel( pdf.cosines()[1] ) );
  CHECK_THAT(  0.5 , WithinRel( pdf.cosines()[2] ) );
  CHECK_THAT(  1.  , WithinRel( pdf.cosines()[3] ) );
  CHECK_THAT(  0.  / normalisation, WithinRel( pdf.values()[0] ) );
  CHECK_THAT(  1.  / normalisation, WithinRel( pdf.values()[1] ) );
  CHECK_THAT(  1.5 / normalisation, WithinRel( pdf.values()[2] ) );
  CHECK_THAT(  2.  / normalisation, WithinRel( pdf.values()[3] ) );
  CHECK( 3 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );

  auto cdf = std::get< TabulatedAngularDistributionFunction >( chunk.cdf() );
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 4 == cdf.cosines().size() );
  CHECK( 4 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK_THAT( -1.  , WithinRel( cdf.cosines()[0] ) );
  CHECK_THAT(  0.  , WithinRel( cdf.cosines()[1] ) );
  CHECK_THAT(  0.5 , WithinRel( cdf.cosines()[2] ) );
  CHECK_THAT(  1.  , WithinRel( cdf.cosines()[3] ) );
  CHECK_THAT(  0.    / normalisation, WithinRel( cdf.values()[0] ) );
  CHECK_THAT(  0.5   / normalisation, WithinRel( cdf.values()[1] ) );
  CHECK_THAT(  1.125 / normalisation, WithinRel( cdf.values()[2] ) );
  CHECK_THAT(  2.    / normalisation, WithinRel( cdf.values()[3] ) );
  CHECK( 3 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );

  CHECK_THAT( 2.0 / normalisation, WithinRel( pdf.integral() ) );

  // evaluation

  // values of x in the x grid
  CHECK_THAT( 0.  / normalisation, WithinRel( chunk( -1. ) ) );
  CHECK_THAT( 1.  / normalisation, WithinRel( chunk(  0. ) ) );
  CHECK_THAT( 1.5 / normalisation, WithinRel( chunk( 0.5 ) ) );
  CHECK_THAT( 2.  / normalisation, WithinRel( chunk(  1. ) ) );

  // values of x outside the x grid
  CHECK_THAT( 0., WithinRel( chunk( -5. ) ) );
  CHECK_THAT( 0., WithinRel( chunk(  5. ) ) );

  // values of x inside the x grid
  CHECK_THAT( 0.5  / normalisation, WithinRel( chunk( -0.5 ) ) );
  CHECK_THAT( 1.75 / normalisation, WithinRel( chunk(  0.75 ) ) );

  // average cosine - always the mean value even for unnormalised distributions
  CHECK_THAT( 2. / 3. / 2., WithinRel( chunk.averageCosine() ) );

  // linearisation
  auto linear = chunk.linearise();

  pdf = linear.pdf();
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 4 == pdf.cosines().size() );
  CHECK( 4 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK_THAT( -1.  , WithinRel( pdf.cosines()[0] ) );
  CHECK_THAT(  0.  , WithinRel( pdf.cosines()[1] ) );
  CHECK_THAT(  0.5 , WithinRel( pdf.cosines()[2] ) );
  CHECK_THAT(  1.  , WithinRel( pdf.cosines()[3] ) );
  CHECK_THAT(  0.  / normalisation, WithinRel( pdf.values()[0] ) );
  CHECK_THAT(  1.  / normalisation, WithinRel( pdf.values()[1] ) );
  CHECK_THAT(  1.5 / normalisation, WithinRel( pdf.values()[2] ) );
  CHECK_THAT(  2.  / normalisation, WithinRel( pdf.values()[3] ) );
  CHECK( 3 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );

  cdf = linear.cdf();
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 4 == cdf.cosines().size() );
  CHECK( 4 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK_THAT( -1.  , WithinRel( cdf.cosines()[0] ) );
  CHECK_THAT(  0.  , WithinRel( cdf.cosines()[1] ) );
  CHECK_THAT(  0.5 , WithinRel( cdf.cosines()[2] ) );
  CHECK_THAT(  1.  , WithinRel( cdf.cosines()[3] ) );
  CHECK_THAT(  0.    / normalisation, WithinRel( cdf.values()[0] ) );
  CHECK_THAT(  0.5   / normalisation, WithinRel( cdf.values()[1] ) );
  CHECK_THAT(  1.125 / normalisation, WithinRel( cdf.values()[2] ) );
  CHECK_THAT(  2.    / normalisation, WithinRel( cdf.values()[3] ) );
  CHECK( 3 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
}
