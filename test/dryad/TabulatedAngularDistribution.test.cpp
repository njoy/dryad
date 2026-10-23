// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/TabulatedAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedAngularDistribution&, bool );
void verifyChunkCurated( const TabulatedAngularDistribution& );
void verifyChunkNotCurated( const TabulatedAngularDistribution& );

SCENARIO( "TabulatedAngularDistribution" ) {

  GIVEN( "cosines and probabilities for a table" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1. };
      std::vector< double > values = { 0., 1., 1.5, 2. };

      TabulatedAngularDistribution chunk1( cosines, values, InterpolationType::LinearLinear, false );
      TabulatedAngularDistribution chunk2( std::move( cosines ), std::move( values ), InterpolationType::LinearLinear, true );

      verifyChunk( chunk1, false );
      verifyChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyChunk( chunk1, true );
      verifyChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "cosines and probabilities for a table with discontinuities" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > cosines = { -1., -0.5, 0., 0., 0., 1. };
      std::vector< double > values = { 0., 1., 2., 3., 1., 2. };

      // curation can be requested at construction time

      TabulatedAngularDistribution chunk1( cosines, values,
                                           InterpolationType::LinearLinear, false, false );
      TabulatedAngularDistribution chunk2( std::move( cosines ), std::move( values ),
                                           InterpolationType::LinearLinear, false, true );

      verifyChunkNotCurated( chunk1 );
      verifyChunkCurated( chunk2 );

      // curation happens when linearising

      auto linear1 = chunk1.linearise();
      auto linear2 = chunk2.linearise();

      verifyChunkCurated( linear1 );
      verifyChunkCurated( linear2 );

      // curation can be requested after construction

      chunk1.curate();
      chunk2.curate();

      verifyChunkCurated( chunk1 );
      verifyChunkCurated( chunk2 );
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedAngularDistribution are given" ) {

      TabulatedAngularDistribution left( { -1., 1. }, { 0.5, 0.5 } );
      TabulatedAngularDistribution equal( { -1., 1. }, { 0.5, 0.5 } );
      TabulatedAngularDistribution unnormalised( { -1., 1. }, { 1., 1. }, InterpolationType::LinearLinear, true );
      TabulatedAngularDistribution different( { -1., 1. }, { 0.25, 0.75 } );

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

    WHEN( "the cosine and values vector are not of the same length" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > cosines = { -1., 1. };
        std::vector< double > values = { 0., 0.5, 0.75, 1. };

        CHECK_THROWS( TabulatedAngularDistribution( cosines, values ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedAngularDistribution& chunk, bool normalise ) {

  double normalisation = normalise ? 2.0 : 1.0;

  CHECK( 4 == chunk.cosines().size() );
  CHECK( 4 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
  CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
  CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
  CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
  CHECK_THAT(  0.  / normalisation, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  1.  / normalisation, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  1.5 / normalisation, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(  2.  / normalisation, WithinRel( chunk.values()[3] ) );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

  auto pdf = chunk.pdf();
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

  auto cdf = chunk.cdf();
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

void verifyChunkNotCurated( const TabulatedAngularDistribution& chunk ) {

  CHECK( 6 == chunk.cosines().size() );
  CHECK( 6 == chunk.values().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( chunk.cosines()[1] ) );
  CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
  CHECK_THAT(  0. , WithinRel( chunk.cosines()[3] ) );
  CHECK_THAT(  0. , WithinRel( chunk.cosines()[4] ) );
  CHECK_THAT(  1. , WithinRel( chunk.cosines()[5] ) );
  CHECK_THAT( 0., WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 1., WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 2., WithinRel( chunk.values()[5] ) );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 5 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

  auto pdf = chunk.pdf();
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 6 == pdf.cosines().size() );
  CHECK( 6 == pdf.values().size() );
  CHECK( 2 == pdf.boundaries().size() );
  CHECK( 2 == pdf.interpolants().size() );
  CHECK_THAT( -1. , WithinRel( pdf.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( pdf.cosines()[1] ) );
  CHECK_THAT(  0. , WithinRel( pdf.cosines()[2] ) );
  CHECK_THAT(  0. , WithinRel( pdf.cosines()[3] ) );
  CHECK_THAT(  0. , WithinRel( pdf.cosines()[4] ) );
  CHECK_THAT(  1. , WithinRel( pdf.cosines()[5] ) );
  CHECK_THAT( 0., WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 1., WithinRel( pdf.values()[1] ) );
  CHECK_THAT( 2., WithinRel( pdf.values()[2] ) );
  CHECK_THAT( 3., WithinRel( pdf.values()[3] ) );
  CHECK_THAT( 1., WithinRel( pdf.values()[4] ) );
  CHECK_THAT( 2., WithinRel( pdf.values()[5] ) );
  CHECK( 2 == pdf.boundaries()[0] );
  CHECK( 5 == pdf.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[1] );
  CHECK( true == pdf.isLinearised() );
  CHECK( false == pdf.isCurated() );

  auto cdf = chunk.cdf();
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 6 == cdf.cosines().size() );
  CHECK( 6 == cdf.values().size() );
  CHECK( 2 == cdf.boundaries().size() );
  CHECK( 2 == cdf.interpolants().size() );
  CHECK_THAT( -1. , WithinRel( cdf.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( cdf.cosines()[1] ) );
  CHECK_THAT(  0. , WithinRel( cdf.cosines()[2] ) );
  CHECK_THAT(  0. , WithinRel( cdf.cosines()[3] ) );
  CHECK_THAT(  0. , WithinRel( cdf.cosines()[4] ) );
  CHECK_THAT(  1. , WithinRel( cdf.cosines()[5] ) );
  CHECK_THAT( 0.  , WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 0.25, WithinRel( cdf.values()[1] ) );
  CHECK_THAT( 1.  , WithinRel( cdf.values()[2] ) );
  CHECK_THAT( 1.  , WithinRel( cdf.values()[3] ) );
  CHECK_THAT( 1.  , WithinRel( cdf.values()[4] ) );
  CHECK_THAT( 2.5 , WithinRel( cdf.values()[5] ) );
  CHECK( 2 == cdf.boundaries()[0] );
  CHECK( 5 == cdf.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[1] );
  CHECK( true == cdf.isLinearised() );
  CHECK( false == cdf.isCurated() );
}

void verifyChunkCurated( const TabulatedAngularDistribution& chunk ) {

  CHECK( 5 == chunk.cosines().size() );
  CHECK( 5 == chunk.values().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( chunk.cosines()[1] ) );
  CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
  CHECK_THAT(  0. , WithinRel( chunk.cosines()[3] ) );
  CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
  CHECK_THAT( 0., WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

  auto pdf = chunk.pdf();
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 5 == pdf.cosines().size() );
  CHECK( 5 == pdf.values().size() );
  CHECK( 2 == pdf.boundaries().size() );
  CHECK( 2 == pdf.interpolants().size() );
  CHECK_THAT( -1. , WithinRel( pdf.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( pdf.cosines()[1] ) );
  CHECK_THAT(  0. , WithinRel( pdf.cosines()[2] ) );
  CHECK_THAT(  0. , WithinRel( pdf.cosines()[3] ) );
  CHECK_THAT(  1. , WithinRel( pdf.cosines()[4] ) );
  CHECK_THAT( 0., WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 1., WithinRel( pdf.values()[1] ) );
  CHECK_THAT( 2., WithinRel( pdf.values()[2] ) );
  CHECK_THAT( 1., WithinRel( pdf.values()[3] ) );
  CHECK_THAT( 2., WithinRel( pdf.values()[4] ) );
  CHECK( 2 == pdf.boundaries()[0] );
  CHECK( 4 == pdf.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[1] );
  CHECK( true == pdf.isLinearised() );
  CHECK( true == pdf.isCurated() );

  auto cdf = chunk.cdf();
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 5 == cdf.cosines().size() );
  CHECK( 5 == cdf.values().size() );
  CHECK( 2 == cdf.boundaries().size() );
  CHECK( 2 == cdf.interpolants().size() );
  CHECK_THAT( -1. , WithinRel( cdf.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( cdf.cosines()[1] ) );
  CHECK_THAT(  0. , WithinRel( cdf.cosines()[2] ) );
  CHECK_THAT(  0. , WithinRel( cdf.cosines()[3] ) );
  CHECK_THAT(  1. , WithinRel( cdf.cosines()[4] ) );
  CHECK_THAT( 0.  , WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 0.25, WithinRel( cdf.values()[1] ) );
  CHECK_THAT( 1.  , WithinRel( cdf.values()[2] ) );
  CHECK_THAT( 1.0 , WithinRel( cdf.values()[3] ) );
  CHECK_THAT( 2.5 , WithinRel( cdf.values()[4] ) );
  CHECK( 2 == cdf.boundaries()[0] );
  CHECK( 4 == cdf.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[1] );
  CHECK( true == cdf.isLinearised() );
  CHECK( true == cdf.isCurated() );
}
