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

SCENARIO( "CovarianceMatrix" ) {

  GIVEN( "valid covariance data for an on-diagonal CovarianceMatrix" ) {

    std::vector< int > keys{ 1, 2, 3 };

    Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    base::CovarianceMatrix chunk( std::move( keys ), std::move( matrix ) );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 3 == chunk.rowKeys().size() );
      CHECK( 3 == chunk.columnKeys().size() );

      CHECK( true == chunk.isRelativeBlock() );
      CHECK( false == chunk.isAbsoluteBlock() );
      CHECK( false == chunk.isOffDiagonal() );
      CHECK( true == chunk.isOnDiagonal() );

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

  GIVEN( "valid correlation and deviation data for an on-diagonal CovarianceMatrix" ) {

    std::vector< int > keys{ 1, 2, 3 };

    std::vector< double > deviations{ 1, 2, 3 };
    Matrix< double > matrix( 3, 3 );
    matrix << 1., 1., 1.,
              1., 1., 1.,
              1., 1., 1.;

    base::CovarianceMatrix chunk( std::move( keys ), std::move( deviations ),
                                  std::move( matrix ) );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 3 == chunk.rowKeys().size() );
      CHECK( 3 == chunk.columnKeys().size() );

      CHECK( true == chunk.isRelativeBlock() );
      CHECK( false == chunk.isAbsoluteBlock() );
      CHECK( false == chunk.isOffDiagonal() );
      CHECK( true == chunk.isOnDiagonal() );

      CHECK( std::nullopt == chunk.covariances() );
      CHECK( std::nullopt != chunk.standardDeviations() );
      CHECK( std::nullopt != chunk.correlations() );
      CHECK( std::nullopt == chunk.eigenvalues() );

      CHECK( 3 == chunk.standardDeviations().value().size() );
      CHECK_THAT( 1., WithinRel( chunk.standardDeviations().value()[0] ) );
      CHECK_THAT( 2., WithinRel( chunk.standardDeviations().value()[1] ) );
      CHECK_THAT( 3., WithinRel( chunk.standardDeviations().value()[2] ) );

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

    chunk.calculateCovariances();

    THEN( "covariances can be calculated" ) {

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

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues can be calculated" ) {

      CHECK( std::nullopt != chunk.eigenvalues() );

      CHECK( 3 == chunk.eigenvalues().value().size() );
      CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[0], 1e-12 ) );
      CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[1], 1e-12 ) );
      CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[2] ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid covariance data for an off-diagonal CovarianceMatrix" ) {

    std::vector< int > rows{ 1, 2, 3 };
    std::vector< int > columns{ 4, 5 };

    Matrix< double > matrix( 3, 2 );
    matrix << 1., 2.,
              2., 4.,
              3., 6.;

    base::CovarianceMatrix chunk( std::move( rows ),
                                  std::move( columns ),
                                  std::move( matrix ) );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 3 == chunk.rowKeys().size() );
      CHECK( 2 == chunk.columnKeys().size() );

      CHECK( true == chunk.isRelativeBlock() );
      CHECK( false == chunk.isAbsoluteBlock() );
      CHECK( true == chunk.isOffDiagonal() );
      CHECK( false == chunk.isOnDiagonal() );

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

      std::vector< int > keys{ 1, 2, 3 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( base::CovarianceMatrix( std::move( keys ), std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix is not symmetric for a diagonal covariance block" ) {

      std::vector< int > keys{ 1, 2, 3 };

      Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 6.,
           100000., 6., 9.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( base::CovarianceMatrix( std::move( keys ), std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the keys "
          "for a diagonal covariance block" ) {

      std::vector< int > keys{ 1, 2 };

      Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 5.,
                3., 5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( base::CovarianceMatrix( std::move( keys ), std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the keys "
          "for an off-diagonal covariance block (rows)" ) {

      std::vector< int > rows{ 1, 2 };
      std::vector< int > columns{ 3, 4 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(base::CovarianceMatrix( std::move( rows ),
                                             std::move( columns ),
                                             std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the keys "
          "for an off-diagonal covariance block (columns)" ) {

      std::vector< int > rows{ 1, 2, 3 };
      std::vector< int > columns{ 4 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( base::CovarianceMatrix( std::move( rows ),
                                              std::move( columns ),
                                              std::move( matrix ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO