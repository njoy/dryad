// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/covariance/CrossSectionCovarianceData.hpp"

// other includes

// convenience typedefs
using namespace njoy::matrix;
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

void verifyChunk( const CrossSectionCovarianceData& );

SCENARIO( "CrossSectionCovarianceData" ) {

  GIVEN( "valid data" ) {

    WHEN( "the data is given explicitly" ) {

      id::ReactionID capture( "n,H1->g,H2" );
      id::ReactionID elastic( "n,H1->n,H1" );

      CrossSectionMetadata metadata11( { capture }, { 1e-5, 1., 2e+7 } );
      CrossSectionMetadata metadata12r( { capture }, { 1e-5, 0.5, 1., 5., 2e+7 } );
      CrossSectionMetadata metadata12c( { elastic }, { 1e-5, 2e+7 } );
      CrossSectionMetadata metadata22( { elastic }, { 1e-5, 1., 1e+6, 2e+7 } );

      Matrix< double > matrix11( 2, 2 );
      matrix11 << 1., 2.,
                  2., 3.;

      Matrix< double > matrix12( 4, 1 );
      matrix12 << 1.,
                  2.,
                  3.,
                  4.;

      Matrix< double > matrix22( 3, 3 );
      matrix22 << 1., 2., 3.,
                  2., 4., 6.,
                  3., 6., 9.;

      std::vector< covariance::CrossSectionCovarianceMatrix > matrices = {

        CrossSectionCovarianceMatrix( std::move( metadata22 ), std::move( matrix22 ) ),
        CrossSectionCovarianceMatrix( std::move( metadata12r ), std::move( metadata12c ), std::move( matrix12 ) ),
        CrossSectionCovarianceMatrix( std::move( metadata11 ), std::move( matrix11 ) )
      };

      CrossSectionCovarianceData chunk( std::move( matrices ) );

      verifyChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of CrossSectionCovarianceData are given" ) {

      id::ReactionID capture( "n,H1->g,H2" );
      id::ReactionID elastic( "n,H1->n,H1" );
      CrossSectionMetadata metadata11( { capture }, { 1e-5, 1., 2e+7 } );
      CrossSectionMetadata metadata12r( { capture }, { 1e-5, 0.5, 1., 5., 2e+7 } );
      CrossSectionMetadata metadata12c( { elastic }, { 1e-5, 2e+7 } );
      CrossSectionMetadata metadata22( { elastic }, { 1e-5, 1., 1e+6, 2e+7 } );
      Matrix< double > matrix11( 2, 2 );
      matrix11 << 1., 2.,
                  2., 3.;
      Matrix< double > matrix12( 4, 1 );
      matrix12 << 1.,
                  2.,
                  3.,
                  4.;
      Matrix< double > matrix22( 3, 3 );
      matrix22 << 1., 2., 3.,
                  2., 4., 6.,
                  3., 6., 9.;

      CrossSectionCovarianceData left(

        { CrossSectionCovarianceMatrix( metadata22, matrix22 ),
          CrossSectionCovarianceMatrix( metadata12r, metadata12c,  matrix12 ),
          CrossSectionCovarianceMatrix( metadata11, matrix11 ) }
      );
      CrossSectionCovarianceData equal(

        { CrossSectionCovarianceMatrix( metadata22, matrix22 ),
          CrossSectionCovarianceMatrix( metadata12r, metadata12c,  matrix12 ),
          CrossSectionCovarianceMatrix( metadata11, matrix11 ) }
      );
      CrossSectionCovarianceData different(

        { CrossSectionCovarianceMatrix( metadata22, matrix22 ) }
      );

      THEN( "they can be compared" ) {

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

void verifyChunk( const CrossSectionCovarianceData& chunk ) {

  id::ReactionID capture( "n,H1->g,H2" );
  id::ReactionID elastic( "n,H1->n,H1" );

  CHECK( true == chunk.hasCovarianceMatrix( capture ) );
  CHECK( true == chunk.hasCovarianceMatrix( capture, capture ) );
  CHECK( true == chunk.hasCovarianceMatrix( elastic ) );
  CHECK( true == chunk.hasCovarianceMatrix( elastic, elastic ) );
  CHECK( true == chunk.hasCovarianceMatrix( capture, elastic ) );
  CHECK( false == chunk.hasCovarianceMatrix( elastic, capture ) );

  CHECK( 2 == chunk.numberReactions() );
  CHECK( 2 == chunk.reactionIdentifiers().size() );
  CHECK( capture == chunk.reactionIdentifiers()[0] );
  CHECK( elastic == chunk.reactionIdentifiers()[1] );

  CHECK( 3 == chunk.numberCovarianceMatrices() );
  CHECK( 3 == chunk.covariances().size() );

  auto matrix = std::get< covariance::CrossSectionCovarianceMatrix >( chunk.covariances()[0] );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( capture == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 3 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt == matrix.varianceScaling() );
  CHECK( std::nullopt != matrix.standardDeviations() );
  CHECK( std::nullopt != matrix.correlations() );
  CHECK( std::nullopt != matrix.eigenvalues() );
  CHECK( 2 == matrix.covariances().rows() );
  CHECK( 2 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(0,1) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(1,1) );

  matrix = std::get< covariance::CrossSectionCovarianceMatrix >( chunk.covariances()[1] );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( capture == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 5 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 5.  , WithinRel( matrix.rowMetadata().energies()[3] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[4] ) );
  CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
  CHECK( elastic == matrix.columnMetadata().reactionIdentifiers()[0] );
  CHECK( 2 == matrix.columnMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.columnMetadata().energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.columnMetadata().energies()[1] ) );
  CHECK( std::nullopt == matrix.varianceScaling() );
  CHECK( std::nullopt == matrix.standardDeviations() );
  CHECK( std::nullopt == matrix.correlations() );
  CHECK( std::nullopt == matrix.eigenvalues() );
  CHECK( 4 == matrix.covariances().rows() );
  CHECK( 1 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(2,0) );
  CHECK( 4. == matrix.covariances()(3,0) );

  matrix = std::get< covariance::CrossSectionCovarianceMatrix >( chunk.covariances()[2] );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( elastic == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 4 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 1e+6, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[3] ) );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt == matrix.varianceScaling() );
  CHECK( std::nullopt != matrix.standardDeviations() );
  CHECK( std::nullopt != matrix.correlations() );
  CHECK( std::nullopt != matrix.eigenvalues() );
  CHECK( 3 == matrix.covariances().rows() );
  CHECK( 3 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(0,1) );
  CHECK( 3. == matrix.covariances()(0,2) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 4. == matrix.covariances()(1,1) );
  CHECK( 6. == matrix.covariances()(1,2) );
  CHECK( 3. == matrix.covariances()(2,0) );
  CHECK( 6. == matrix.covariances()(2,1) );
  CHECK( 9. == matrix.covariances()(2,2) );

  matrix = std::get< covariance::CrossSectionCovarianceMatrix >( chunk.covarianceMatrix( capture ) );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( capture == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 3 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt == matrix.varianceScaling() );
  CHECK( std::nullopt != matrix.standardDeviations() );
  CHECK( std::nullopt != matrix.correlations() );
  CHECK( std::nullopt != matrix.eigenvalues() );
  CHECK( 2 == matrix.covariances().rows() );
  CHECK( 2 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(0,1) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(1,1) );

  matrix = std::get< covariance::CrossSectionCovarianceMatrix >( chunk.covarianceMatrix( capture, elastic ) );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( capture == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 5 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 5.  , WithinRel( matrix.rowMetadata().energies()[3] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[4] ) );
  CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
  CHECK( elastic == matrix.columnMetadata().reactionIdentifiers()[0] );
  CHECK( 2 == matrix.columnMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.columnMetadata().energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.columnMetadata().energies()[1] ) );
  CHECK( std::nullopt == matrix.varianceScaling() );
  CHECK( std::nullopt == matrix.standardDeviations() );
  CHECK( std::nullopt == matrix.correlations() );
  CHECK( std::nullopt == matrix.eigenvalues() );
  CHECK( 4 == matrix.covariances().rows() );
  CHECK( 1 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(2,0) );
  CHECK( 4. == matrix.covariances()(3,0) );

  matrix = std::get< covariance::CrossSectionCovarianceMatrix >( chunk.covarianceMatrix( elastic ) );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( elastic == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 4 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 1e+6, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[3] ) );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt == matrix.varianceScaling() );
  CHECK( std::nullopt != matrix.standardDeviations() );
  CHECK( std::nullopt != matrix.correlations() );
  CHECK( std::nullopt != matrix.eigenvalues() );
  CHECK( 3 == matrix.covariances().rows() );
  CHECK( 3 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(0,1) );
  CHECK( 3. == matrix.covariances()(0,2) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 4. == matrix.covariances()(1,1) );
  CHECK( 6. == matrix.covariances()(1,2) );
  CHECK( 3. == matrix.covariances()(2,0) );
  CHECK( 6. == matrix.covariances()(2,1) );
  CHECK( 9. == matrix.covariances()(2,2) );
}
