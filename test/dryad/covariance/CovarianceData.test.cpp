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
      CrossSectionMetadata xs_metadata( { capture }, { 1e-5, 1., 2e+7 } );
      Matrix< double > xs_matrix( 2, 2 );
      xs_matrix << 1., 2.,
                   2., 3.;
      CrossSectionCovarianceData
      xs( { CrossSectionCovarianceMatrix( std::move( xs_metadata ), std::move( xs_matrix ) ) } );

      id::ReactionID elastic( "n,H1->n(0)" );
      AngularDistributionMetadata ang_metadata( elastic, 1, { 1e-5, 1., 10., 2e+7 } );
      Matrix< double > ang_matrix( 3, 3 );
      ang_matrix << 1., 2., 3.,
                    2., 4., 5.,
                    3., 5., 6.;
      AngularDistributionCovarianceData
      angular( { AngularDistributionCovarianceMatrix( std::move( ang_metadata ), std::move( ang_matrix ) ) } );

      CovarianceData chunk( std::move( xs ), std::move( angular ) );

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

        CovarianceData left( xs, std::nullopt );
        CovarianceData equal( xs, std::nullopt );
        CovarianceData different( std::nullopt, std::nullopt );

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
  CHECK( std::nullopt != chunk.angularDistribution() );

  CHECK( true == chunk.hasCrossSectionCovariances() );
  CHECK( true == chunk.hasAngularDistributionCovariances() );

  decltype(auto) xs = chunk.crossSection().value();
  CHECK( true == xs.hasCovarianceMatrix( capture ) );
  CHECK( false == xs.hasCovarianceMatrix( elastic ) );

  CHECK( 1 == xs.numberReactions() );
  CHECK( 1 == xs.reactionIdentifiers().size() );
  CHECK( capture == xs.reactionIdentifiers()[0] );

  CHECK( 1 == xs.numberCovarianceMatrices() );
  CHECK( 1 == xs.covariances().size() );

  decltype(auto) xs_data = xs.covarianceMatrix( capture );
  auto xs_matrix = std::get< covariance::CrossSectionCovarianceMatrix >( xs_data );
  CHECK( 1 == xs_matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( capture == xs_matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 3 == xs_matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( xs_matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( xs_matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( xs_matrix.rowMetadata().energies()[2] ) );
  CHECK( xs_matrix.columnMetadata() == xs_matrix.rowMetadata() );
  CHECK( std::nullopt == xs_matrix.varianceScaling() );
  CHECK( std::nullopt != xs_matrix.standardDeviations() );
  CHECK( std::nullopt != xs_matrix.correlations() );
  CHECK( std::nullopt != xs_matrix.eigenvalues() );
  CHECK( 2 == xs_matrix.covariances().rows() );
  CHECK( 2 == xs_matrix.covariances().cols() );
  CHECK( 1. == xs_matrix.covariances()(0,0) );
  CHECK( 2. == xs_matrix.covariances()(0,1) );
  CHECK( 2. == xs_matrix.covariances()(1,0) );
  CHECK( 3. == xs_matrix.covariances()(1,1) );

  decltype(auto) angular = chunk.angularDistribution().value();
  CHECK( false == angular.hasCovarianceMatrix( capture ) );
  CHECK( true == angular.hasCovarianceMatrix( elastic ) );

  CHECK( 1 == angular.numberReactions() );
  CHECK( 1 == angular.reactionIdentifiers().size() );
  CHECK( elastic == angular.reactionIdentifiers()[0] );

  CHECK( 1 == angular.numberCovarianceMatrices() );
  CHECK( 1 == angular.covariances().size() );

  decltype(auto) ang_data = angular.covarianceMatrix( elastic );
  auto ang_matrix = std::get< covariance::AngularDistributionCovarianceMatrix >( ang_data );
  CHECK( 1 == ang_matrix.rowMetadata().reactionIdentifiers().size() );
  CHECK( elastic == ang_matrix.rowMetadata().reactionIdentifiers()[0] );
  CHECK( 4 == ang_matrix.rowMetadata().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( ang_matrix.rowMetadata().energies()[0] ) );
  CHECK_THAT( 1.  , WithinRel( ang_matrix.rowMetadata().energies()[1] ) );
  CHECK_THAT( 10. , WithinRel( ang_matrix.rowMetadata().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( ang_matrix.rowMetadata().energies()[3] ) );
  CHECK( ang_matrix.columnMetadata() == ang_matrix.rowMetadata() );
  CHECK( std::nullopt != ang_matrix.standardDeviations() );
  CHECK( std::nullopt != ang_matrix.correlations() );
  CHECK( std::nullopt != ang_matrix.eigenvalues() );
  CHECK( 3 == ang_matrix.covariances().rows() );
  CHECK( 3 == ang_matrix.covariances().cols() );
  CHECK( 1. == ang_matrix.covariances()(0,0) );
  CHECK( 2. == ang_matrix.covariances()(0,1) );
  CHECK( 3. == ang_matrix.covariances()(0,2) );
  CHECK( 2. == ang_matrix.covariances()(1,0) );
  CHECK( 4. == ang_matrix.covariances()(1,1) );
  CHECK( 5. == ang_matrix.covariances()(1,2) );
  CHECK( 3. == ang_matrix.covariances()(2,0) );
  CHECK( 5. == ang_matrix.covariances()(2,1) );
  CHECK( 6. == ang_matrix.covariances()(2,2) );
}
