// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/TabulatedEnergyDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedEnergyDistribution&, bool );
void verifyChunkCurated( const TabulatedEnergyDistribution& );
void verifyChunkNotCurated( const TabulatedEnergyDistribution& );

SCENARIO( "TabulatedEnergyDistribution" ) {

  GIVEN( "energies and probabilities for a table" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 0., 2., 3., 4. };
      std::vector< double > values = { 0., 0.5, 0.75, 1. };

      TabulatedEnergyDistribution chunk1( energies, values,
                                          InterpolationType::LinearLinear, false );
      TabulatedEnergyDistribution chunk2( std::move( energies ), std::move( values ),
                                          InterpolationType::LinearLinear, true );

      verifyChunk( chunk1, false );
      verifyChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyChunk( chunk1, true );
      verifyChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "energies and probabilities for a table with discontinuities" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 0., 2., 3., 3., 3., 4. };
      std::vector< double > values = { 0., 1., 2., 3., 1., 2. };

      // curation can be requested at construction time

      TabulatedEnergyDistribution chunk1( energies, values,
                                          InterpolationType::LinearLinear, false, false );
      TabulatedEnergyDistribution chunk2( std::move( energies ), std::move( values ),
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

    WHEN( "the pdf and cdf are given explicitly and only one of them is curated" ) {

      std::vector< double > energies = { 0., 2., 3., 3., 3., 4. };
      std::vector< double > pdfValues = { 0., 1., 2., 3., 1., 2. };
      std::vector< double > cdfValues = { 0., 1., 2.5, 2.5, 2.5, 4. };
      InterpolationType interpolation = InterpolationType::LinearLinear;

      TabulatedEnergyDistributionFunction curatedPdf( energies, pdfValues, interpolation, true );
      TabulatedEnergyDistributionFunction curatedCdf( energies, cdfValues, interpolation, true );
      TabulatedEnergyDistributionFunction notCuratedPdf( energies, pdfValues, interpolation, false );
      TabulatedEnergyDistributionFunction notCuratedCdf( energies, cdfValues, interpolation, false );

      TabulatedEnergyDistribution chunk1( curatedPdf, notCuratedCdf );
      TabulatedEnergyDistribution chunk2( notCuratedPdf, curatedCdf );

      THEN( "the distribution is not curated" ) {

        CHECK( true == chunk1.pdf().isCurated() );
        CHECK( false == chunk1.cdf().isCurated() );
        CHECK( false == chunk1.isCurated() );

        CHECK( false == chunk2.pdf().isCurated() );
        CHECK( true == chunk2.cdf().isCurated() );
        CHECK( false == chunk2.isCurated() );
      } // THEN

      THEN( "the distribution can be curated on demand" ) {

        chunk1.curate();
        chunk2.curate();

        verifyChunkCurated( chunk1 );
        verifyChunkCurated( chunk2 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedEnergyDistribution are given" ) {

      TabulatedEnergyDistribution left( { 1., 3. }, { 0.5, 0.5 } );
      TabulatedEnergyDistribution equal( { 1., 3. }, { 0.5, 0.5 } );
      TabulatedEnergyDistribution unnormalised( { 1., 3. }, { 1., 1. },
                                                InterpolationType::LinearLinear, true );
      TabulatedEnergyDistribution different( { 1., 3. }, { 0.25, 0.75 } );

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

    WHEN( "the energies and values vector are not of the same length" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > energies = { 1., 2. };
        std::vector< double > values = { 0., 0.5, 0.75, 1. };

        CHECK_THROWS( TabulatedEnergyDistribution( energies, values ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedEnergyDistribution& chunk, bool normalise ) {

  double normalisation = normalise ? 2.0 : 1.0;

  CHECK( 4 == chunk.energies().size() );
  CHECK( 4 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 0.   / normalisation, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 0.5  / normalisation, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 0.75 / normalisation, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 1.   / normalisation, WithinRel( chunk.values()[3] ) );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( true == chunk.isCurated() );

  auto pdf = chunk.pdf();
  CHECK_THAT( 0., WithinRel( pdf.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( pdf.upperEnergyLimit() ) );
  CHECK( 4 == pdf.energies().size() );
  CHECK( 4 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK_THAT( 0., WithinRel( pdf.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( pdf.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( pdf.energies()[2] ) );
  CHECK_THAT( 4., WithinRel( pdf.energies()[3] ) );
  CHECK_THAT( 0.   / normalisation, WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 0.5  / normalisation, WithinRel( pdf.values()[1] ) );
  CHECK_THAT( 0.75 / normalisation, WithinRel( pdf.values()[2] ) );
  CHECK_THAT( 1.   / normalisation, WithinRel( pdf.values()[3] ) );
  CHECK( 3 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );
  CHECK( true == pdf.isLinearised() );
  CHECK( true == pdf.isCurated() );

  auto cdf = chunk.cdf();
  CHECK_THAT( 0., WithinRel( cdf.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( cdf.upperEnergyLimit() ) );
  CHECK( 4 == cdf.energies().size() );
  CHECK( 4 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK_THAT( 0., WithinRel( cdf.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( cdf.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( cdf.energies()[2] ) );
  CHECK_THAT( 4., WithinRel( cdf.energies()[3] ) );
  CHECK_THAT( 0.    / normalisation, WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 0.5   / normalisation, WithinRel( cdf.values()[1] ) );
  CHECK_THAT( 1.125 / normalisation, WithinRel( cdf.values()[2] ) );
  CHECK_THAT( 2.    / normalisation, WithinRel( cdf.values()[3] ) );
  CHECK( 3 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
  CHECK( true == cdf.isLinearised() );
  CHECK( true == cdf.isCurated() );

  CHECK_THAT( 2.0 / normalisation, WithinRel( pdf.integral() ) );

  // evaluation

  // values of x in the x grid
  CHECK_THAT( 0.   / normalisation, WithinRel( chunk( 0. ) ) );
  CHECK_THAT( 0.5  / normalisation, WithinRel( chunk( 2. ) ) );
  CHECK_THAT( 0.75 / normalisation, WithinRel( chunk( 3. ) ) );
  CHECK_THAT( 1.   / normalisation, WithinRel( chunk( 4. ) ) );

  // values of x outside the x grid
  CHECK_THAT( 0., WithinRel( chunk( -5. ) ) );
  CHECK_THAT( 0., WithinRel( chunk(  5. ) ) );

  // values of x inside the x grid
  CHECK_THAT( 0.25  / normalisation, WithinRel( chunk( 1.  ) ) );
  CHECK_THAT( 0.875 / normalisation, WithinRel( chunk( 3.5 ) ) );

  // average energy - always the mean value even for unnormalised distributions
  CHECK_THAT( 128. / 24. / 2., WithinRel( chunk.averageEnergy() ) );

  // linearisation
  auto linear = chunk.linearise();

  pdf = linear.pdf();
  CHECK_THAT( 0., WithinRel( pdf.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( pdf.upperEnergyLimit() ) );
  CHECK( 4 == pdf.energies().size() );
  CHECK( 4 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK_THAT( 0., WithinRel( pdf.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( pdf.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( pdf.energies()[2] ) );
  CHECK_THAT( 4., WithinRel( pdf.energies()[3] ) );
  CHECK_THAT( 0.   / normalisation, WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 0.5  / normalisation, WithinRel( pdf.values()[1] ) );
  CHECK_THAT( 0.75 / normalisation, WithinRel( pdf.values()[2] ) );
  CHECK_THAT( 1.   / normalisation, WithinRel( pdf.values()[3] ) );
  CHECK( 3 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );

  cdf = linear.cdf();
  CHECK_THAT( 0., WithinRel( cdf.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( cdf.upperEnergyLimit() ) );
  CHECK( 4 == cdf.energies().size() );
  CHECK( 4 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK_THAT( 0., WithinRel( cdf.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( cdf.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( cdf.energies()[2] ) );
  CHECK_THAT( 4., WithinRel( cdf.energies()[3] ) );
  CHECK_THAT( 0.    / normalisation, WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 0.5   / normalisation, WithinRel( cdf.values()[1] ) );
  CHECK_THAT( 1.125 / normalisation, WithinRel( cdf.values()[2] ) );
  CHECK_THAT( 2.    / normalisation, WithinRel( cdf.values()[3] ) );
  CHECK( 3 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
}

void verifyChunkNotCurated( const TabulatedEnergyDistribution& chunk ) {

  CHECK( 6 == chunk.energies().size() );
  CHECK( 6 == chunk.values().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.energies()[5] ) );
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
  CHECK( false == chunk.isCurated() );

  auto pdf = chunk.pdf();
  CHECK_THAT( 0., WithinRel( pdf.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( pdf.upperEnergyLimit() ) );
  CHECK( 6 == pdf.energies().size() );
  CHECK( 6 == pdf.values().size() );
  CHECK( 2 == pdf.boundaries().size() );
  CHECK( 2 == pdf.interpolants().size() );
  CHECK_THAT( 0., WithinRel( pdf.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( pdf.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( pdf.energies()[2] ) );
  CHECK_THAT( 3., WithinRel( pdf.energies()[3] ) );
  CHECK_THAT( 3., WithinRel( pdf.energies()[4] ) );
  CHECK_THAT( 4., WithinRel( pdf.energies()[5] ) );
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
  CHECK_THAT( 0., WithinRel( cdf.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( cdf.upperEnergyLimit() ) );
  CHECK( 6 == cdf.energies().size() );
  CHECK( 6 == cdf.values().size() );
  CHECK( 2 == cdf.boundaries().size() );
  CHECK( 2 == cdf.interpolants().size() );
  CHECK_THAT( 0., WithinRel( cdf.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( cdf.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( cdf.energies()[2] ) );
  CHECK_THAT( 3., WithinRel( cdf.energies()[3] ) );
  CHECK_THAT( 3., WithinRel( cdf.energies()[4] ) );
  CHECK_THAT( 4., WithinRel( cdf.energies()[5] ) );
  CHECK_THAT( 0. , WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 1. , WithinRel( cdf.values()[1] ) );
  CHECK_THAT( 2.5, WithinRel( cdf.values()[2] ) );
  CHECK_THAT( 2.5, WithinRel( cdf.values()[3] ) );
  CHECK_THAT( 2.5, WithinRel( cdf.values()[4] ) );
  CHECK_THAT( 4. , WithinRel( cdf.values()[5] ) );
  CHECK( 2 == cdf.boundaries()[0] );
  CHECK( 5 == cdf.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[1] );
  CHECK( true == cdf.isLinearised() );
  CHECK( false == cdf.isCurated() );
}

void verifyChunkCurated( const TabulatedEnergyDistribution& chunk ) {

  CHECK( 5 == chunk.energies().size() );
  CHECK( 5 == chunk.values().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
  CHECK_THAT( 0., WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
  CHECK( true == chunk.isCurated() );

  auto pdf = chunk.pdf();
  CHECK_THAT( 0., WithinRel( pdf.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( pdf.upperEnergyLimit() ) );
  CHECK( 5 == pdf.energies().size() );
  CHECK( 5 == pdf.values().size() );
  CHECK( 2 == pdf.boundaries().size() );
  CHECK( 2 == pdf.interpolants().size() );
  CHECK_THAT( 0., WithinRel( pdf.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( pdf.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( pdf.energies()[2] ) );
  CHECK_THAT( 3., WithinRel( pdf.energies()[3] ) );
  CHECK_THAT( 4., WithinRel( pdf.energies()[4] ) );
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
  CHECK_THAT( 0., WithinRel( cdf.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( cdf.upperEnergyLimit() ) );
  CHECK( 5 == cdf.energies().size() );
  CHECK( 5 == cdf.values().size() );
  CHECK( 2 == cdf.boundaries().size() );
  CHECK( 2 == cdf.interpolants().size() );
  CHECK_THAT( 0., WithinRel( cdf.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( cdf.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( cdf.energies()[2] ) );
  CHECK_THAT( 3., WithinRel( cdf.energies()[3] ) );
  CHECK_THAT( 4., WithinRel( cdf.energies()[4] ) );
  CHECK_THAT( 0. , WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 1. , WithinRel( cdf.values()[1] ) );
  CHECK_THAT( 2.5, WithinRel( cdf.values()[2] ) );
  CHECK_THAT( 2.5, WithinRel( cdf.values()[3] ) );
  CHECK_THAT( 4. , WithinRel( cdf.values()[4] ) );
  CHECK( 2 == cdf.boundaries()[0] );
  CHECK( 4 == cdf.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[1] );
  CHECK( true == cdf.isLinearised() );
  CHECK( true == cdf.isCurated() );
}
