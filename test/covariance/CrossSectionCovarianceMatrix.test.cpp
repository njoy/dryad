// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/CrossSectionCovarianceMatrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "CrossSectionCovarianceMatrix" ) {

  GIVEN( "valid covariance data for an on-diagonal covariance matrix without "
         "variance scaling information" ) {

    CrossSectionMetadata metadata( { id::ReactionID( "n,U235->n,U235" ) },
                                   { 1e-5, 1., 1e+6, 2e+7 } );

    matrix::Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    CrossSectionCovarianceMatrix chunk( std::move( metadata ), std::move( matrix ) );

    THEN( "a CrossSectionCovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
      CHECK( chunk.columnMetadata() == chunk.rowMetadata() );

      CHECK( false == chunk.hasVarianceScaling() );
      CHECK( std::nullopt == chunk.varianceScaling() );

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
  } // GIVEN

  GIVEN( "valid covariance data for an on-diagonal covariance matrix with "
         "variance scaling information" ) {

    CrossSectionMetadata metadata( { id::ReactionID( "n,U235->n,U235" ) },
                                   { 1e-5, 1., 1e+6, 2e+7 } );

    matrix::Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    bool relative = true;
    VarianceScaling scaling( ScalingType::Inverse,
                             { 1e-5, 5., 2e+7 }, { 0.001, 0.1 } );

    CrossSectionCovarianceMatrix chunk( std::move( metadata ), std::move( matrix ),
                                        relative, std::move( scaling ) );

    THEN( "a CrossSectionCovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
      CHECK( chunk.columnMetadata() == chunk.rowMetadata() );

      CHECK( true == chunk.hasVarianceScaling() );
      CHECK( std::nullopt != chunk.varianceScaling() );
      auto scaling = chunk.varianceScaling().value();
      CHECK( 2 == scaling.numberGroups() );
      CHECK( 3 == scaling.energies().size() );
      CHECK_THAT( 1e-5, WithinRel( scaling.energies()[0] ) );
      CHECK_THAT( 5.  , WithinRel( scaling.energies()[1] ) );
      CHECK_THAT( 2e+7, WithinRel( scaling.energies()[2] ) );
      CHECK( 2 == scaling.factors().size() );
      CHECK_THAT( 0.001, WithinRel( scaling.factors()[0] ) );
      CHECK_THAT( 0.1  , WithinRel( scaling.factors()[1] ) );
      CHECK( ScalingType::Inverse == scaling.type() );

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
  } // GIVEN

  GIVEN( "valid data for an off-diagonal covariance matrix" ) {

    CrossSectionMetadata rowMetadata( { id::ReactionID( "n,U235->n,U235" ) },
                                      { 1e-5, 1., 1e+6, 2e+7 } );
    CrossSectionMetadata columnMetadata( { id::ReactionID( "n,U235->fission(t)" ) },
                                         { 1e-5, 2., 2e+7 } );

    matrix::Matrix< double > matrix( 3, 2 );
    matrix << 1., 2.,
              2., 4.,
              3., 6.;

    CrossSectionCovarianceMatrix chunk( std::move( rowMetadata ),
                                        std::move( columnMetadata ),
                                        std::move( matrix ) );

    THEN( "a CrossSectionCovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( chunk.columnMetadata() != chunk.rowMetadata() );

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );

      CHECK( 1 == chunk.columnMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->fission(t)" ) == chunk.columnMetadata().reactionIdentifiers()[0] );
      CHECK( 3 == chunk.columnMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
      CHECK_THAT( 2.  , WithinRel( chunk.columnMetadata().energies()[1] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.columnMetadata().energies()[2] ) );

      CHECK( std::nullopt == chunk.varianceScaling() );

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
  } // GIVEN
} // SCENARIO