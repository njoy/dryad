// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/covariance/AngularDistributionCovarianceData.hpp"

// other includes

// convenience typedefs
using namespace njoy::matrix;
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

void verifyChunk( const AngularDistributionCovarianceData& );

SCENARIO( "AngularDistributionCovarianceData" ) {

  GIVEN( "valid data" ) {

    WHEN( "the data is given explicitly" ) {

      id::ReactionID elastic( "n,H1->n(0)" );
      id::ReactionID inelastic( "n,H1->n(1)" );

      AngularDistributionMetadata metadata11( elastic, 1, { 1e-5, 1., 2e+7 } );
      AngularDistributionMetadata metadata12r( elastic, 1, { 1e-5, 0.5, 1., 5., 2e+7 } );
      AngularDistributionMetadata metadata12c( inelastic, 2, { 1e-5, 2e+7 } );
      AngularDistributionMetadata metadata22( inelastic, 2, { 1e-5, 1., 1e+6, 2e+7 } );

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

      std::vector< covariance::AngularDistributionCovarianceMatrix > matrices = {

        AngularDistributionCovarianceMatrix( std::move( metadata22 ), std::move( matrix22 ) ),
        AngularDistributionCovarianceMatrix( std::move( metadata12r ), std::move( metadata12c ), std::move( matrix12 ) ),
        AngularDistributionCovarianceMatrix( std::move( metadata11 ), std::move( matrix11 ) )
      };

      AngularDistributionCovarianceData chunk( std::move( matrices ) );

      verifyChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of AngularDistributionCovarianceData are given" ) {

      id::ReactionID elastic( "n,H1->n(0)" );
      id::ReactionID inelastic( "n,H1->n(1)" );
      AngularDistributionMetadata metadata11( elastic, 1, { 1e-5, 1., 2e+7 } );
      AngularDistributionMetadata metadata12r( elastic, 1, { 1e-5, 0.5, 1., 5., 2e+7 } );
      AngularDistributionMetadata metadata12c( inelastic, 2, { 1e-5, 2e+7 } );
      AngularDistributionMetadata metadata22( inelastic, 2, { 1e-5, 1., 1e+6, 2e+7 } );
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

      AngularDistributionCovarianceData left(

        { AngularDistributionCovarianceMatrix( metadata22, matrix22 ),
          AngularDistributionCovarianceMatrix( metadata12r, metadata12c,  matrix12 ),
          AngularDistributionCovarianceMatrix( metadata11, matrix11 ) }
      );
      AngularDistributionCovarianceData equal(

        { AngularDistributionCovarianceMatrix( metadata22, matrix22 ),
          AngularDistributionCovarianceMatrix( metadata12r, metadata12c,  matrix12 ),
          AngularDistributionCovarianceMatrix( metadata11, matrix11 ) }
      );
      AngularDistributionCovarianceData different(

        { AngularDistributionCovarianceMatrix( metadata22, matrix22 ) }
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

void verifyChunk( const AngularDistributionCovarianceData& chunk ) {

  id::ReactionID elastic( "n,H1->n(0)" );
  id::ReactionID inelastic( "n,H1->n(1)" );

  CHECK( true == chunk.hasCovarianceMatrix( elastic ) );
  CHECK( true == chunk.hasCovarianceMatrix( elastic, elastic ) );
  CHECK( true == chunk.hasCovarianceMatrix( inelastic ) );
  CHECK( true == chunk.hasCovarianceMatrix( inelastic, inelastic ) );
  CHECK( true == chunk.hasCovarianceMatrix( elastic, inelastic ) );
  CHECK( false == chunk.hasCovarianceMatrix( inelastic, elastic ) );

  CHECK( 2 == chunk.numberReactions() );
  CHECK( 2 == chunk.reactionIdentifiers().size() );
  CHECK( elastic == chunk.reactionIdentifiers()[0] );
  CHECK( inelastic == chunk.reactionIdentifiers()[1] );

  CHECK( 3 == chunk.numberCovarianceMatrices() );
  CHECK( 3 == chunk.covariances().size() );

  auto matrix = std::get< covariance::AngularDistributionCovarianceMatrix >( chunk.covariances()[0] );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( elastic == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 3 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK( 1 == matrix.rowMetadata().moments().size() );
  CHECK( 1 == matrix.rowMetadata().moments()[0] );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt != matrix.standardDeviations() );
  CHECK( std::nullopt != matrix.correlations() );
  CHECK( std::nullopt != matrix.eigenvalues() );
  CHECK( std::nullopt != matrix.eigenvectors() );
  CHECK( 2 == matrix.covariances().rows() );
  CHECK( 2 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(0,1) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(1,1) );

  matrix = std::get< covariance::AngularDistributionCovarianceMatrix >( chunk.covariances()[1] );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( elastic == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 5 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 5.  , WithinRel( matrix.rowMetadata().energies()[3] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[4] ) );
  CHECK( 1 == matrix.rowMetadata().moments().size() );
  CHECK( 1 == matrix.rowMetadata().moments()[0] );
  CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
  CHECK( inelastic == matrix.columnMetadata().reactionIdentifiers()[0] );
  CHECK( 2 == matrix.columnMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.columnMetadata().energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.columnMetadata().energies()[1] ) );
  CHECK( 1 == matrix.columnMetadata().moments().size() );
  CHECK( 2 == matrix.columnMetadata().moments()[0] );
  CHECK( std::nullopt == matrix.standardDeviations() );
  CHECK( std::nullopt == matrix.correlations() );
  CHECK( std::nullopt == matrix.eigenvalues() );
  CHECK( std::nullopt == matrix.eigenvectors() );
  CHECK( 4 == matrix.covariances().rows() );
  CHECK( 1 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(2,0) );
  CHECK( 4. == matrix.covariances()(3,0) );

  matrix = std::get< covariance::AngularDistributionCovarianceMatrix >( chunk.covariances()[2] );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( inelastic == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 4 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 1e+6, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[3] ) );
  CHECK( 1 == matrix.columnMetadata().moments().size() );
  CHECK( 2 == matrix.columnMetadata().moments()[0] );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt != matrix.standardDeviations() );
  CHECK( std::nullopt != matrix.correlations() );
  CHECK( std::nullopt != matrix.eigenvalues() );
  CHECK( std::nullopt != matrix.eigenvectors() );
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

  matrix = std::get< covariance::AngularDistributionCovarianceMatrix >( chunk.covarianceMatrix( elastic ) );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( elastic == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 3 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK( 1 == matrix.rowMetadata().moments().size() );
  CHECK( 1 == matrix.rowMetadata().moments()[0] );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt != matrix.standardDeviations() );
  CHECK( std::nullopt != matrix.correlations() );
  CHECK( std::nullopt != matrix.eigenvalues() );
  CHECK( std::nullopt != matrix.eigenvectors() );
  CHECK( 2 == matrix.covariances().rows() );
  CHECK( 2 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(0,1) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(1,1) );

  matrix = std::get< covariance::AngularDistributionCovarianceMatrix >( chunk.covarianceMatrix( elastic, inelastic ) );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( elastic == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 5 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 5.  , WithinRel( matrix.rowMetadata().energies()[3] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[4] ) );
  CHECK( 1 == matrix.rowMetadata().moments().size() );
  CHECK( 1 == matrix.rowMetadata().moments()[0] );
  CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
  CHECK( inelastic == matrix.columnMetadata().reactionIdentifiers()[0] );
  CHECK( 2 == matrix.columnMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.columnMetadata().energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.columnMetadata().energies()[1] ) );
  CHECK( 1 == matrix.columnMetadata().moments().size() );
  CHECK( 2 == matrix.columnMetadata().moments()[0] );
  CHECK( std::nullopt == matrix.standardDeviations() );
  CHECK( std::nullopt == matrix.correlations() );
  CHECK( std::nullopt == matrix.eigenvalues() );
  CHECK( std::nullopt == matrix.eigenvectors() );
  CHECK( 4 == matrix.covariances().rows() );
  CHECK( 1 == matrix.covariances().cols() );
  CHECK( 1. == matrix.covariances()(0,0) );
  CHECK( 2. == matrix.covariances()(1,0) );
  CHECK( 3. == matrix.covariances()(2,0) );
  CHECK( 4. == matrix.covariances()(3,0) );

  matrix = std::get< covariance::AngularDistributionCovarianceMatrix >( chunk.covarianceMatrix( inelastic ) );
  CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( inelastic == matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 4 == matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 1e+6, WithinRel( matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( matrix.rowMetadata().energies()[3] ) );
  CHECK( 1 == matrix.columnMetadata().moments().size() );
  CHECK( 2 == matrix.columnMetadata().moments()[0] );
  CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
  CHECK( std::nullopt != matrix.standardDeviations() );
  CHECK( std::nullopt != matrix.correlations() );
  CHECK( std::nullopt != matrix.eigenvalues() );
  CHECK( std::nullopt != matrix.eigenvectors() );
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
