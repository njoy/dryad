// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/base/CovarianceMatrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad::covariance;
using List = std::vector< int >;

SCENARIO( "CovarianceMatrix" ) {

  GIVEN( "valid covariance data for an on-diagonal CovarianceMatrix" ) {

    List structure{ 1, 2, 3 };

    Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    base::CovarianceMatrix< List > chunk( std::move( structure ), std::move( matrix ) );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 3 == chunk.rowMetadata().size() );
      CHECK( 3 == chunk.columnMetadata().size() );

      CHECK( true == chunk.isRelativeBlock() );
      CHECK( false == chunk.isAbsoluteBlock() );
      CHECK( false == chunk.isOffDiagonalBlock() );
      CHECK( true == chunk.isDiagonalBlock() );

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.standardDeviations() );
      CHECK( std::nullopt == chunk.correlations() );
      CHECK( std::nullopt == chunk.eigenvalues() );

      CHECK( 3 == chunk.covariances().value().rows() );
      CHECK( 3 == chunk.covariances().value().cols() );
      CHECK( 1. == chunk.covariances().value()(0,0) );
      CHECK( 2. == chunk.covariances().value()(0,1) );
      CHECK( 3. == chunk.covariances().value()(0,2) );
      CHECK( 2. == chunk.covariances().value()(1,0) );
      CHECK( 4. == chunk.covariances().value()(1,1) );
      CHECK( 6. == chunk.covariances().value()(1,2) );
      CHECK( 3. == chunk.covariances().value()(2,0) );
      CHECK( 6. == chunk.covariances().value()(2,1) );
      CHECK( 9. == chunk.covariances().value()(2,2) );
    } // THEN

    chunk.calculateStandardDeviations();

    THEN( "Standard deviations can be calculated" ) {

      CHECK( std::nullopt != chunk.standardDeviations() );

      CHECK( 3 == chunk.standardDeviations().value().size() );
      CHECK_THAT( 1., WithinRel( chunk.standardDeviations().value()[0] ) );
      CHECK_THAT( 2., WithinRel( chunk.standardDeviations().value()[1] ) );
      CHECK_THAT( 3., WithinRel( chunk.standardDeviations().value()[2] ) );
    } // THEN

    chunk.calculateCorrelations();

    THEN( "Correlations can be calculated" ) {

      CHECK( std::nullopt != chunk.correlations() );

      CHECK( 3 == chunk.correlations().value().rows() );
      CHECK( 3 == chunk.correlations().value().cols() );
      CHECK( 1. == chunk.correlations().value()(0,0) );
      CHECK( 1. == chunk.correlations().value()(0,1) );
      CHECK( 1. == chunk.correlations().value()(0,2) );
      CHECK( 1. == chunk.correlations().value()(1,0) );
      CHECK( 1. == chunk.correlations().value()(1,1) );
      CHECK( 1. == chunk.correlations().value()(1,2) );
      CHECK( 1. == chunk.correlations().value()(2,0) );
      CHECK( 1. == chunk.correlations().value()(2,1) );
      CHECK( 1. == chunk.correlations().value()(2,2) );
    } // THEN

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues can be calculated" ) {

      CHECK( std::nullopt != chunk.eigenvalues() );

      CHECK( 3 == chunk.eigenvalues().value().size() );
      CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[0], 1e-12 ) );
      CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[1], 1e-12 ) );
      CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[2] ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an off-diagonal CovarianceMatrix" ) {

    Structure rows{ 1, 2, 3 };
    Structure columns{ 4, 5 };

    Matrix< double > matrix( 3, 2 );
    matrix << 1., 2.,
              2., 4.,
              3., 6.;

    base::CovarianceMatrix< Structure > chunk( std::move( rows ),
                                               std::move( columns ),
                                               std::move( matrix ) );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 3 == chunk.rowMetadata().size() );
      CHECK( 2 == chunk.columnMetadata().size() );

      CHECK( true == chunk.isRelativeBlock() );
      CHECK( false == chunk.isAbsoluteBlock() );
      CHECK( true == chunk.isOffDiagonalBlock() );
      CHECK( false == chunk.isDiagonalBlock() );

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.standardDeviations() );
      CHECK( std::nullopt == chunk.correlations() );

      CHECK( 3 == chunk.covariances().value().rows() );
      CHECK( 2 == chunk.covariances().value().cols() );
      CHECK( 1. == chunk.covariances().value()(0,0) );
      CHECK( 2. == chunk.covariances().value()(0,1) );
      CHECK( 2. == chunk.covariances().value()(1,0) );
      CHECK( 4. == chunk.covariances().value()(1,1) );
      CHECK( 3. == chunk.covariances().value()(2,0) );
      CHECK( 6. == chunk.covariances().value()(2,1) );
    } // THEN

    chunk.calculateStandardDeviations();

    THEN( "Standard deviations cannot be calculated" ) {

      CHECK( std::nullopt == chunk.standardDeviations() );
    } // THEN

    std::vector< double > row = { 1., 2., 3. };
    std::vector< double > column = { 1., 2. };
    chunk.calculateCorrelations( row, column );

    THEN( "Correlations can be calculated" ) {

      CHECK( std::nullopt != chunk.correlations() );

      CHECK( 3 == chunk.correlations().value().rows() );
      CHECK( 2 == chunk.correlations().value().cols() );
      CHECK( 1. == chunk.correlations().value()(0,0) );
      CHECK( 1. == chunk.correlations().value()(0,1) );
      CHECK( 1. == chunk.correlations().value()(1,0) );
      CHECK( 1. == chunk.correlations().value()(1,1) );
      CHECK( 1. == chunk.correlations().value()(2,0) );
      CHECK( 1. == chunk.correlations().value()(2,1) );
    } // THEN

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues cannot be calculated" ) {

      CHECK( std::nullopt == chunk.eigenvalues() );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a CovarianceMatrix" ) {

    WHEN( "the matrix is not square for a diagonal covariance block" ) {

      Metadata metadata{ 3 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix< Metadata >( std::move( metadata ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix is not symmetric for a diagonal covariance block" ) {

      Metadata metadata{ 3 };

      Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 6.,
           100000., 6., 9.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix< Metadata >( std::move( metadata ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for a diagonal covariance block" ) {

      Metadata metadata{ 2 };

      Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 5.,
                3., 5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix< Metadata >( std::move( metadata ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for an off-diagonal covariance block (rows)" ) {

      Metadata rows{ 2 };
      Metadata columns{ 2 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix< Metadata >( std::move( rows ),
                                                   std::move( columns ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for an off-diagonal covariance block (columns)" ) {

      Metadata rows{ 3 };
      Metadata columns{ 1 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix< Metadata >( std::move( rows ),
                                                   std::move( columns ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO