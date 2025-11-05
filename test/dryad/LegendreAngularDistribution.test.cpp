// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/LegendreAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const LegendreAngularDistribution&, bool );

SCENARIO( "LegendreAngularDistribution" ) {

  GIVEN( "coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > coefficients = { 1.0, 0.5 };

      LegendreAngularDistribution chunk1( coefficients, false );
      LegendreAngularDistribution chunk2( std::move( coefficients ), true );

      verifyChunk( chunk1, false );
      verifyChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyChunk( chunk1, true );
      verifyChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of LegendreAngularDistribution are given" ) {

      LegendreAngularDistribution left( { 0.5, 0.25 } );
      LegendreAngularDistribution equal( { 0.5, 0.25 } );
      LegendreAngularDistribution unnormalised( { 1., 0.5 }, true );
      LegendreAngularDistribution different( { 0.5, 0.1, 0.0001 } );

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

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};
        CHECK_THROWS( LegendreAngularDistribution( empty ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const LegendreAngularDistribution& chunk, bool normalise ) {

  double normalisation = normalise ? 2.0 : 1.0;

  CHECK_THAT( 1.0 / normalisation, WithinRel( chunk.coefficients()[0] ) );
  CHECK_THAT( 0.5 / normalisation, WithinRel( chunk.coefficients()[1] ) );

  auto pdf = chunk.pdf();
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 1 == pdf.order() );
  CHECK( 2 == pdf.coefficients().size() );
  CHECK_THAT( 1.0 / normalisation, WithinRel( pdf.coefficients()[0] ) );
  CHECK_THAT( 0.5 / normalisation, WithinRel( pdf.coefficients()[1] ) );

  CHECK_THAT( 2.0 / normalisation, WithinRel( pdf.integral() ) );

  auto cdf = chunk.cdf();
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

  // average cosine
  CHECK_THAT( 1. / 3. / normalisation, WithinRel( chunk.averageCosine() ) );

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
