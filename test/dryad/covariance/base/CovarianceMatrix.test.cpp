// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/base/CovarianceMatrix.hpp"

// other includes
#include "dryad/covariance/base/Metadata.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "CovarianceMatrix" ) {

  GIVEN( "valid covariance data for a 1D covariance matrix" ) {

    using Key = std::tuple< int >;
    using Metadata = base::Metadata< int >;
    using CovarianceMatrix = base::CovarianceMatrix< Metadata, int >;

    WHEN( "using covariance data for an on-diagonal matrix" ) {

      Metadata metadata( { Key{ 0 }, Key{ 1 }, Key{ 2 } } );

      matrix::Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 6.,
                3., 6., 9.;

      CovarianceMatrix chunk( std::move( metadata ),
                              std::move( matrix ) );

      THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.rowMetadata().keys().size() );
        CHECK( 3 == chunk.columnMetadata().keys().size() );
        CHECK( chunk.rowMetadata() == chunk.columnMetadata() );
        CHECK( std::tuple{ 0 } == chunk.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 1 } == chunk.rowMetadata().keys()[1] );
        CHECK( std::tuple{ 2 } == chunk.rowMetadata().keys()[2] );

        CHECK( true == chunk.isRelativeMatrix() );
        CHECK( false == chunk.isAbsoluteMatrix() );
        CHECK( false == chunk.isOffDiagonal() );
        CHECK( true == chunk.isOnDiagonal() );

        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 3 == chunk.covariances().rows() );
        CHECK( 3 == chunk.covariances().cols() );
        CHECK( 1. == chunk.covariances()(0,0) );
        CHECK( 2. == chunk.covariances()(0,1) );
        CHECK( 3. == chunk.covariances()(0,2) );
        CHECK( 2. == chunk.covariances()(1,0) );
        CHECK( 4. == chunk.covariances()(1,1) );
        CHECK( 6. == chunk.covariances()(1,2) );
        CHECK( 3. == chunk.covariances()(2,0) );
        CHECK( 6. == chunk.covariances()(2,1) );
        CHECK( 9. == chunk.covariances()(2,2) );
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
    } // WHEN

    WHEN( "using correlation data for an on-diagonal matrix" ) {

      Metadata metadata( { Key{ 0 }, Key{ 1 }, Key{ 2 } } );

      std::vector< double > deviations{ 1, 2, 3 };
      matrix::Matrix< double > matrix( 3, 3 );
      matrix << 1., 1., 1.,
                1., 1., 1.,
                1., 1., 1.;

      CovarianceMatrix chunk( std::move( metadata ),
                              std::move( deviations ),
                              std::move( matrix ) );

      THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.rowMetadata().keys().size() );
        CHECK( 3 == chunk.columnMetadata().keys().size() );
        CHECK( chunk.rowMetadata() == chunk.columnMetadata() );
        CHECK( std::tuple{ 0 } == chunk.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 1 } == chunk.rowMetadata().keys()[1] );
        CHECK( std::tuple{ 2 } == chunk.rowMetadata().keys()[2] );

        CHECK( true == chunk.isRelativeMatrix() );
        CHECK( false == chunk.isAbsoluteMatrix() );
        CHECK( false == chunk.isOffDiagonal() );
        CHECK( true == chunk.isOnDiagonal() );

        CHECK( std::nullopt != chunk.standardDeviations() );
        CHECK( std::nullopt != chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 3 == chunk.covariances().rows() );
        CHECK( 3 == chunk.covariances().cols() );
        CHECK( 1. == chunk.covariances()(0,0) );
        CHECK( 2. == chunk.covariances()(0,1) );
        CHECK( 3. == chunk.covariances()(0,2) );
        CHECK( 2. == chunk.covariances()(1,0) );
        CHECK( 4. == chunk.covariances()(1,1) );
        CHECK( 6. == chunk.covariances()(1,2) );
        CHECK( 3. == chunk.covariances()(2,0) );
        CHECK( 6. == chunk.covariances()(2,1) );
        CHECK( 9. == chunk.covariances()(2,2) );

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

      chunk.calculateEigenvalues();

      THEN( "Eigenvalues can be calculated" ) {

        CHECK( std::nullopt != chunk.eigenvalues() );

        CHECK( 3 == chunk.eigenvalues().value().size() );
        CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[0], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[1], 1e-12 ) );
        CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[2] ) );
      } // THEN
    } // WHEN

    WHEN( "using covariance data for an off-diagonal matrix" ) {

      Metadata rowMetadata( { Key{ 0 }, Key{ 1 }, Key{ 2 } } );
      Metadata columnMetadata( { Key{ 3 }, Key{ 4 } } );

      matrix::Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                2., 4.,
                3., 6.;

      CovarianceMatrix chunk( std::move( rowMetadata ),
                              std::move( columnMetadata ),
                              std::move( matrix ) );

      THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {


        CHECK( 3 == chunk.rowMetadata().keys().size() );
        CHECK( 2 == chunk.columnMetadata().keys().size() );
        CHECK( chunk.rowMetadata() != chunk.columnMetadata() );
        CHECK( std::tuple{ 0 } == chunk.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 1 } == chunk.rowMetadata().keys()[1] );
        CHECK( std::tuple{ 2 } == chunk.rowMetadata().keys()[2] );
        CHECK( std::tuple{ 3 } == chunk.columnMetadata().keys()[0] );
        CHECK( std::tuple{ 4 } == chunk.columnMetadata().keys()[1] );

        CHECK( true == chunk.isRelativeMatrix() );
        CHECK( false == chunk.isAbsoluteMatrix() );
        CHECK( true == chunk.isOffDiagonal() );
        CHECK( false == chunk.isOnDiagonal() );

        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 3 == chunk.covariances().rows() );
        CHECK( 2 == chunk.covariances().cols() );
        CHECK( 1. == chunk.covariances()(0,0) );
        CHECK( 2. == chunk.covariances()(0,1) );
        CHECK( 2. == chunk.covariances()(1,0) );
        CHECK( 4. == chunk.covariances()(1,1) );
        CHECK( 3. == chunk.covariances()(2,0) );
        CHECK( 6. == chunk.covariances()(2,1) );
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
    } // WHEN

    WHEN( "using correlation data for an off-diagonal matrix" ) {

      Metadata rowMetadata( { Key{ 0 }, Key{ 1 }, Key{ 2 } } );
      Metadata columnMetadata( { Key{ 3 }, Key{ 4 } } );

      std::vector< double > rowDeviations = { 1., 2., 3. };
      std::vector< double > columnDeviations = { 1., 2. };

      matrix::Matrix< double > matrix( 3, 2 );
      matrix << 1., 1.,
                1., 1.,
                1., 1.;

      CovarianceMatrix chunk( std::move( rowMetadata ),
                              std::move( columnMetadata ),
                              rowDeviations,
                              columnDeviations,
                              std::move( matrix ) );

      THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.rowMetadata().keys().size() );
        CHECK( 2 == chunk.columnMetadata().keys().size() );
        CHECK( chunk.rowMetadata() != chunk.columnMetadata() );
        CHECK( std::tuple{ 0 } == chunk.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 1 } == chunk.rowMetadata().keys()[1] );
        CHECK( std::tuple{ 2 } == chunk.rowMetadata().keys()[2] );
        CHECK( std::tuple{ 3 } == chunk.columnMetadata().keys()[0] );
        CHECK( std::tuple{ 4 } == chunk.columnMetadata().keys()[1] );

        CHECK( true == chunk.isRelativeMatrix() );
        CHECK( false == chunk.isAbsoluteMatrix() );
        CHECK( true == chunk.isOffDiagonal() );
        CHECK( false == chunk.isOnDiagonal() );

        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt != chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 3 == chunk.covariances().rows() );
        CHECK( 2 == chunk.covariances().cols() );
        CHECK( 1. == chunk.covariances()(0,0) );
        CHECK( 2. == chunk.covariances()(0,1) );
        CHECK( 2. == chunk.covariances()(1,0) );
        CHECK( 4. == chunk.covariances()(1,1) );
        CHECK( 3. == chunk.covariances()(2,0) );
        CHECK( 6. == chunk.covariances()(2,1) );

        CHECK( 3 == chunk.correlations().value().rows() );
        CHECK( 2 == chunk.correlations().value().cols() );
        CHECK( 1. == chunk.correlations().value()(0,0) );
        CHECK( 1. == chunk.correlations().value()(0,1) );
        CHECK( 1. == chunk.correlations().value()(1,0) );
        CHECK( 1. == chunk.correlations().value()(1,1) );
        CHECK( 1. == chunk.correlations().value()(2,0) );
        CHECK( 1. == chunk.correlations().value()(2,1) );
      } // THEN

      chunk.calculateStandardDeviations();

      THEN( "Standard deviations cannot be calculated" ) {

        CHECK( std::nullopt == chunk.standardDeviations() );
      } // THEN

      chunk.calculateEigenvalues();

      THEN( "Eigenvalues cannot be calculated" ) {

        CHECK( std::nullopt == chunk.eigenvalues() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid covariance data for a higher dimensional covariance matrix" ) {

    using Key = std::tuple< int, int >;
    using Metadata = base::Metadata< int, int >;
    using CovarianceMatrix = base::CovarianceMatrix< Metadata, int, int >;

    WHEN( "using covariance data for an on-diagonal matrix" ) {

      Metadata metadata( { Key{ 0, 0 }, Key{ 0, 1 }, Key{ 0, 2 },
                           Key{ 1, 0 }, Key{ 1, 1 }, Key{ 1, 2 } } );

      matrix::Matrix< double > matrix( 6, 6 );
      matrix <<  1.,  2.,  3.,    4.,  5.,  6.,
                 2.,  4.,  6.,    8., 10., 12.,
                 3.,  6.,  9.,   12., 15., 18.,

                 4.,  8., 12.,   16., 20., 24.,
                 5., 10., 15.,   20., 25., 30.,
                 6., 12., 18.,   24., 30., 36.;

      CovarianceMatrix chunk( std::move( metadata ),
                              std::move( matrix ) );

      THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

        CHECK( 6 == chunk.rowMetadata().keys().size() );
        CHECK( 6 == chunk.columnMetadata().keys().size() );
        CHECK( chunk.rowMetadata() == chunk.columnMetadata() );
        CHECK( std::tuple{ 0, 0 } == chunk.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 0, 1 } == chunk.rowMetadata().keys()[1] );
        CHECK( std::tuple{ 0, 2 } == chunk.rowMetadata().keys()[2] );
        CHECK( std::tuple{ 1, 0 } == chunk.rowMetadata().keys()[3] );
        CHECK( std::tuple{ 1, 1 } == chunk.rowMetadata().keys()[4] );
        CHECK( std::tuple{ 1, 2 } == chunk.rowMetadata().keys()[5] );

        CHECK( true == chunk.isRelativeMatrix() );
        CHECK( false == chunk.isAbsoluteMatrix() );
        CHECK( false == chunk.isOffDiagonal() );
        CHECK( true == chunk.isOnDiagonal() );

        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 6 == chunk.covariances().rows() );
        CHECK( 6 == chunk.covariances().cols() );
        CHECK(  1. == chunk.covariances()(0,0) );
        CHECK(  2. == chunk.covariances()(0,1) );
        CHECK(  3. == chunk.covariances()(0,2) );
        CHECK(  4. == chunk.covariances()(0,3) );
        CHECK(  5. == chunk.covariances()(0,4) );
        CHECK(  6. == chunk.covariances()(0,5) );
        CHECK(  2. == chunk.covariances()(1,0) );
        CHECK(  4. == chunk.covariances()(1,1) );
        CHECK(  6. == chunk.covariances()(1,2) );
        CHECK(  8. == chunk.covariances()(1,3) );
        CHECK( 10. == chunk.covariances()(1,4) );
        CHECK( 12. == chunk.covariances()(1,5) );
        CHECK(  3. == chunk.covariances()(2,0) );
        CHECK(  6. == chunk.covariances()(2,1) );
        CHECK(  9. == chunk.covariances()(2,2) );
        CHECK( 12. == chunk.covariances()(2,3) );
        CHECK( 15. == chunk.covariances()(2,4) );
        CHECK( 18. == chunk.covariances()(2,5) );
        CHECK(  4. == chunk.covariances()(3,0) );
        CHECK(  8. == chunk.covariances()(3,1) );
        CHECK( 12. == chunk.covariances()(3,2) );
        CHECK( 16. == chunk.covariances()(3,3) );
        CHECK( 20. == chunk.covariances()(3,4) );
        CHECK( 24. == chunk.covariances()(3,5) );
        CHECK(  5. == chunk.covariances()(4,0) );
        CHECK( 10. == chunk.covariances()(4,1) );
        CHECK( 15. == chunk.covariances()(4,2) );
        CHECK( 20. == chunk.covariances()(4,3) );
        CHECK( 25. == chunk.covariances()(4,4) );
        CHECK( 30. == chunk.covariances()(4,5) );
        CHECK(  6. == chunk.covariances()(5,0) );
        CHECK( 12. == chunk.covariances()(5,1) );
        CHECK( 18. == chunk.covariances()(5,2) );
        CHECK( 24. == chunk.covariances()(5,3) );
        CHECK( 30. == chunk.covariances()(5,4) );
        CHECK( 36. == chunk.covariances()(5,5) );
      } // THEN

      chunk.calculateStandardDeviations();

      THEN( "Standard deviations can be calculated" ) {

        CHECK( std::nullopt != chunk.standardDeviations() );

        CHECK( 6 == chunk.standardDeviations().value().size() );
        CHECK_THAT( 1., WithinRel( chunk.standardDeviations().value()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.standardDeviations().value()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.standardDeviations().value()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.standardDeviations().value()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.standardDeviations().value()[4] ) );
        CHECK_THAT( 6., WithinRel( chunk.standardDeviations().value()[5] ) );
      } // THEN

      chunk.calculateCorrelations();

      THEN( "Correlations can be calculated" ) {

        CHECK( std::nullopt != chunk.correlations() );

        CHECK( 6 == chunk.correlations().value().rows() );
        CHECK( 6 == chunk.correlations().value().cols() );
        CHECK( 1. == chunk.correlations().value()(0,0) );
        CHECK( 1. == chunk.correlations().value()(0,1) );
        CHECK( 1. == chunk.correlations().value()(0,2) );
        CHECK( 1. == chunk.correlations().value()(0,3) );
        CHECK( 1. == chunk.correlations().value()(0,4) );
        CHECK( 1. == chunk.correlations().value()(0,5) );
        CHECK( 1. == chunk.correlations().value()(1,0) );
        CHECK( 1. == chunk.correlations().value()(1,1) );
        CHECK( 1. == chunk.correlations().value()(1,2) );
        CHECK( 1. == chunk.correlations().value()(1,3) );
        CHECK( 1. == chunk.correlations().value()(1,4) );
        CHECK( 1. == chunk.correlations().value()(1,5) );
        CHECK( 1. == chunk.correlations().value()(2,0) );
        CHECK( 1. == chunk.correlations().value()(2,1) );
        CHECK( 1. == chunk.correlations().value()(2,2) );
        CHECK( 1. == chunk.correlations().value()(2,3) );
        CHECK( 1. == chunk.correlations().value()(2,4) );
        CHECK( 1. == chunk.correlations().value()(2,5) );
        CHECK( 1. == chunk.correlations().value()(3,0) );
        CHECK( 1. == chunk.correlations().value()(3,1) );
        CHECK( 1. == chunk.correlations().value()(3,2) );
        CHECK( 1. == chunk.correlations().value()(3,3) );
        CHECK( 1. == chunk.correlations().value()(3,4) );
        CHECK( 1. == chunk.correlations().value()(3,5) );
        CHECK( 1. == chunk.correlations().value()(4,0) );
        CHECK( 1. == chunk.correlations().value()(4,1) );
        CHECK( 1. == chunk.correlations().value()(4,2) );
        CHECK( 1. == chunk.correlations().value()(4,3) );
        CHECK( 1. == chunk.correlations().value()(4,4) );
        CHECK( 1. == chunk.correlations().value()(4,5) );
        CHECK( 1. == chunk.correlations().value()(5,0) );
        CHECK( 1. == chunk.correlations().value()(5,1) );
        CHECK( 1. == chunk.correlations().value()(5,2) );
        CHECK( 1. == chunk.correlations().value()(5,3) );
        CHECK( 1. == chunk.correlations().value()(5,4) );
        CHECK( 1. == chunk.correlations().value()(5,5) );
      } // THEN

      chunk.calculateEigenvalues();

      THEN( "Eigenvalues can be calculated" ) {

        CHECK( std::nullopt != chunk.eigenvalues() );

        CHECK( 6 == chunk.eigenvalues().value().size() );
        CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[0], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[1], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[4], 1e-12 ) );
        CHECK_THAT( 91., WithinRel( chunk.eigenvalues().value()[5] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid covariance matrix" ) {

    using Key = std::tuple< int, int >;
    using Metadata = base::Metadata< int, int >;
    using CovarianceMatrix = base::CovarianceMatrix< Metadata, int, int >;

    Metadata metadata( { Key{ 0, 0 }, Key{ 0, 1 }, Key{ 0, 2 },
                         Key{ 1, 0 }, Key{ 1, 1 }, Key{ 1, 2 } } );

    matrix::Matrix< double > matrix( 6, 6 );
    matrix <<  1.,  2.,  3.,    4.,  5.,  6.,
               2.,  4.,  6.,    8., 10., 12.,
               3.,  6.,  9.,   12., 15., 18.,

               4.,  8., 12.,   16., 20., 24.,
               5., 10., 15.,   20., 25., 30.,
               6., 12., 18.,   24., 30., 36.;

    bool relative = false;

    CovarianceMatrix chunk( std::move( metadata ), std::move( matrix ), relative );

    WHEN( "extract row arguments - extracting on the first dimension" ) {

      auto submatrix = chunk.extract( std::nullopt, 0 );

      THEN( "A submatrix can be extracted" ) {

        CHECK( 2 == submatrix.rowMetadata().keys().size() );
        CHECK( 2 == submatrix.columnMetadata().keys().size() );
        CHECK( submatrix.rowMetadata() == submatrix.columnMetadata() );
        CHECK( std::tuple{ 0, 0 } == submatrix.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 1, 0 } == submatrix.rowMetadata().keys()[1] );

        CHECK( false == submatrix.isRelativeMatrix() );
        CHECK( true == submatrix.isAbsoluteMatrix() );
        CHECK( false == submatrix.isOffDiagonal() );
        CHECK( true == submatrix.isOnDiagonal() );

        CHECK( std::nullopt == submatrix.standardDeviations() );
        CHECK( std::nullopt == submatrix.correlations() );
        CHECK( std::nullopt == submatrix.eigenvalues() );

        CHECK( 2 == submatrix.covariances().rows() );
        CHECK( 2 == submatrix.covariances().cols() );
        CHECK(  1. == submatrix.covariances()(0,0) );
        CHECK(  4. == submatrix.covariances()(0,1) );
        CHECK(  4. == submatrix.covariances()(1,0) );
        CHECK( 16. == submatrix.covariances()(1,1) );
      } // THEN
    } // WHEN

    WHEN( "extracting on the second dimension" ) {

      auto submatrix = chunk.extract( 0, std::nullopt );

      THEN( "A submatrix can be extracted" ) {

        CHECK( 3 == submatrix.rowMetadata().keys().size() );
        CHECK( 3 == submatrix.columnMetadata().keys().size() );
        CHECK( submatrix.rowMetadata() == submatrix.columnMetadata() );
        CHECK( std::tuple{ 0, 0 } == chunk.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 0, 1 } == chunk.rowMetadata().keys()[1] );
        CHECK( std::tuple{ 0, 2 } == chunk.rowMetadata().keys()[2] );

        CHECK( false == submatrix.isRelativeMatrix() );
        CHECK( true == submatrix.isAbsoluteMatrix() );
        CHECK( false == submatrix.isOffDiagonal() );
        CHECK( true == submatrix.isOnDiagonal() );

        CHECK( std::nullopt == submatrix.standardDeviations() );
        CHECK( std::nullopt == submatrix.correlations() );
        CHECK( std::nullopt == submatrix.eigenvalues() );

        CHECK( 3 == submatrix.covariances().rows() );
        CHECK( 3 == submatrix.covariances().cols() );
        CHECK(  1. == submatrix.covariances()(0,0) );
        CHECK(  2. == submatrix.covariances()(0,1) );
        CHECK(  3. == submatrix.covariances()(0,2) );
        CHECK(  2. == submatrix.covariances()(1,0) );
        CHECK(  4. == submatrix.covariances()(1,1) );
        CHECK(  6. == submatrix.covariances()(1,2) );
        CHECK(  3. == submatrix.covariances()(2,0) );
        CHECK(  6. == submatrix.covariances()(2,1) );
        CHECK(  9. == submatrix.covariances()(2,2) );
      } // THEN
    } // WHEN

    WHEN( "all arguments are std::nullopt" ) {

      auto submatrix = chunk.extract( std::nullopt, std::nullopt );

      THEN( "A submatrix can be extracted and it is the same as the original matrix" ) {

        CHECK( 6 == submatrix.rowMetadata().keys().size() );
        CHECK( 6 == submatrix.columnMetadata().keys().size() );
        CHECK( submatrix.rowMetadata() == submatrix.columnMetadata() );
        CHECK( std::tuple{ 0, 0 } == submatrix.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 0, 1 } == submatrix.rowMetadata().keys()[1] );
        CHECK( std::tuple{ 0, 2 } == submatrix.rowMetadata().keys()[2] );
        CHECK( std::tuple{ 1, 0 } == submatrix.rowMetadata().keys()[3] );
        CHECK( std::tuple{ 1, 1 } == submatrix.rowMetadata().keys()[4] );
        CHECK( std::tuple{ 1, 2 } == submatrix.rowMetadata().keys()[5] );

        CHECK( false == submatrix.isRelativeMatrix() );
        CHECK( true == submatrix.isAbsoluteMatrix() );
        CHECK( false == submatrix.isOffDiagonal() );
        CHECK( true == submatrix.isOnDiagonal() );

        CHECK( std::nullopt == submatrix.standardDeviations() );
        CHECK( std::nullopt == submatrix.correlations() );
        CHECK( std::nullopt == submatrix.eigenvalues() );

        CHECK( 6 == submatrix.covariances().rows() );
        CHECK( 6 == submatrix.covariances().cols() );
        CHECK(  1. == submatrix.covariances()(0,0) );
        CHECK(  2. == submatrix.covariances()(0,1) );
        CHECK(  3. == submatrix.covariances()(0,2) );
        CHECK(  4. == submatrix.covariances()(0,3) );
        CHECK(  5. == submatrix.covariances()(0,4) );
        CHECK(  6. == submatrix.covariances()(0,5) );
        CHECK(  2. == submatrix.covariances()(1,0) );
        CHECK(  4. == submatrix.covariances()(1,1) );
        CHECK(  6. == submatrix.covariances()(1,2) );
        CHECK(  8. == submatrix.covariances()(1,3) );
        CHECK( 10. == submatrix.covariances()(1,4) );
        CHECK( 12. == submatrix.covariances()(1,5) );
        CHECK(  3. == submatrix.covariances()(2,0) );
        CHECK(  6. == submatrix.covariances()(2,1) );
        CHECK(  9. == submatrix.covariances()(2,2) );
        CHECK( 12. == submatrix.covariances()(2,3) );
        CHECK( 15. == submatrix.covariances()(2,4) );
        CHECK( 18. == submatrix.covariances()(2,5) );
        CHECK(  4. == submatrix.covariances()(3,0) );
        CHECK(  8. == submatrix.covariances()(3,1) );
        CHECK( 12. == submatrix.covariances()(3,2) );
        CHECK( 16. == submatrix.covariances()(3,3) );
        CHECK( 20. == submatrix.covariances()(3,4) );
        CHECK( 24. == submatrix.covariances()(3,5) );
        CHECK(  5. == submatrix.covariances()(4,0) );
        CHECK( 10. == submatrix.covariances()(4,1) );
        CHECK( 15. == submatrix.covariances()(4,2) );
        CHECK( 20. == submatrix.covariances()(4,3) );
        CHECK( 25. == submatrix.covariances()(4,4) );
        CHECK( 30. == submatrix.covariances()(4,5) );
        CHECK(  6. == submatrix.covariances()(5,0) );
        CHECK( 12. == submatrix.covariances()(5,1) );
        CHECK( 18. == submatrix.covariances()(5,2) );
        CHECK( 24. == submatrix.covariances()(5,3) );
        CHECK( 30. == submatrix.covariances()(5,4) );
        CHECK( 36. == submatrix.covariances()(5,5) );
      } // THEN
    } // WHEN

    WHEN( "extract row and column arguments: cross term" ) {

      auto submatrix = chunk.extract( 0, std::nullopt,
                                      1, std::nullopt );

      THEN( "A submatrix can be extracted" ) {

        CHECK( 3 == submatrix.rowMetadata().keys().size() );
        CHECK( 3 == submatrix.columnMetadata().keys().size() );
        CHECK( submatrix.rowMetadata() != submatrix.columnMetadata() );
        CHECK( std::tuple{ 0, 0 } == submatrix.rowMetadata().keys()[0] );
        CHECK( std::tuple{ 0, 1 } == submatrix.rowMetadata().keys()[1] );
        CHECK( std::tuple{ 0, 2 } == submatrix.rowMetadata().keys()[2] );
        CHECK( std::tuple{ 1, 0 } == submatrix.columnMetadata().keys()[0] );
        CHECK( std::tuple{ 1, 1 } == submatrix.columnMetadata().keys()[1] );
        CHECK( std::tuple{ 1, 2 } == submatrix.columnMetadata().keys()[2] );

        CHECK( false == submatrix.isRelativeMatrix() );
        CHECK( true == submatrix.isAbsoluteMatrix() );
        CHECK( true == submatrix.isOffDiagonal() );
        CHECK( false == submatrix.isOnDiagonal() );

        CHECK( std::nullopt == submatrix.standardDeviations() );
        CHECK( std::nullopt == submatrix.correlations() );
        CHECK( std::nullopt == submatrix.eigenvalues() );

        CHECK( 3 == submatrix.covariances().rows() );
        CHECK( 3 == submatrix.covariances().cols() );
        CHECK(  4. == submatrix.covariances()(0,0) );
        CHECK(  5. == submatrix.covariances()(0,1) );
        CHECK(  6. == submatrix.covariances()(0,2) );
        CHECK(  8. == submatrix.covariances()(1,0) );
        CHECK( 10. == submatrix.covariances()(1,1) );
        CHECK( 12. == submatrix.covariances()(1,2) );
        CHECK( 12. == submatrix.covariances()(2,0) );
        CHECK( 15. == submatrix.covariances()(2,1) );
        CHECK( 18. == submatrix.covariances()(2,2) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a CovarianceMatrix" ) {

    using Key = std::tuple< int >;
    using Metadata = base::Metadata< int >;
    using CovarianceMatrix = base::CovarianceMatrix< Metadata, int >;

    WHEN( "the matrix is not square for a diagonal covariance block" ) {

      Metadata metadata( { Key{ 0 }, Key{ 1 }, Key{ 2 } } );

      matrix::Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( std::move( metadata ), std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix is not symmetric for a diagonal covariance block" ) {

      Metadata metadata( { Key{ 0 }, Key{ 1 }, Key{ 2 } } );

      matrix::Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 6.,
           100000., 6., 9.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( std::move( metadata ), std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the keys "
          "for a diagonal covariance block" ) {

      Metadata metadata( { Key{ 0 }, Key{ 1 } } );

      matrix::Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 5.,
                3., 5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( std::move( metadata ), std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the keys "
          "for an off-diagonal covariance block (rows)" ) {

      Metadata rows( { Key{ 0 }, Key{ 1 } } );
      Metadata columns( { Key{ 3 }, Key{ 4 } } );

      matrix::Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(CovarianceMatrix( std::move( rows ),
                                       std::move( columns ),
                                       std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the keys "
          "for an off-diagonal covariance block (columns)" ) {

      Metadata rows( { Key{ 0 }, Key{ 1 }, Key{ 2 } } );
      Metadata columns( { Key{ 4 } } );

      matrix::Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( std::move( rows ),
                                        std::move( columns ),
                                        std::move( matrix ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO