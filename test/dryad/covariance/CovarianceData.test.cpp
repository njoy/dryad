// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/covariance/CovarianceData.hpp"

// other includes

// convenience typedefs
using namespace njoy::matrix;
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

void verifyChunk( const CovarianceData& );

SCENARIO( "CovarianceData" ) {

  GIVEN( "valid data" ) {

    WHEN( "the data is given explicitly as a map" ) {

      id::ReactionID capture( "n,H1->g,H2" );
      CrossSectionMetadata metadata( { capture }, { 1e-5, 1., 2e+7 } );
      Matrix< double > matrix( 2, 2 );
      matrix << 1., 2.,
                  2., 3.;
      CrossSectionCovarianceData xs( { CrossSectionCovarianceMatrix( std::move( metadata ), std::move( matrix ) ) } );

      CovarianceData chunk( std::move( xs ) );

      verifyChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of CovarianceData are given" ) {

      THEN( "they can be compared" ) {

        id::ReactionID capture( "n,H1->g,H2" );
        CrossSectionMetadata metadata( { capture }, { 1e-5, 1., 2e+7 } );
        Matrix< double > matrix( 2, 2 );
        matrix << 1., 2.,
                    2., 3.;
        CrossSectionCovarianceData xs( { CrossSectionCovarianceMatrix( std::move( metadata ), std::move( matrix ) ) } );

        CovarianceData left( xs );
        CovarianceData equal( xs );
        CovarianceData different( std::nullopt );

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const CovarianceData& chunk ) {

  id::ReactionID capture( "n,H1->g,H2" );
  id::ReactionID elastic( "n,H1->n,H1" );

  CHECK( std::nullopt != chunk.crossSection() );

  decltype(auto) xs = chunk.crossSection().value();
  CHECK( true == xs.hasCovarianceMatrix( capture ) );
  CHECK( false == xs.hasCovarianceMatrix( elastic ) );

  CHECK( 1 == xs.numberReactions() );
  CHECK( 1 == xs.reactionIdentifiers().size() );
  CHECK( capture == xs.reactionIdentifiers()[0] );

  CHECK( 1 == xs.numberCovarianceMatrices() );
  CHECK( 1 == xs.covariances().size() );

  decltype(auto) data = xs.covarianceMatrix( capture );
  auto matrix = std::get< covariance::CrossSectionCovarianceMatrix >( data );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( capture == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 3 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt == matrix.varianceScaling() );
  CHECK( std::nullopt == matrix.standardDeviations() );
  CHECK( std::nullopt == matrix.correlations() );
  CHECK( std::nullopt == matrix.eigenvalues() );
  CHECK( 2 == matrix.covariances().rows() );
  CHECK( 2 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(0,1) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(1,1) );
}
