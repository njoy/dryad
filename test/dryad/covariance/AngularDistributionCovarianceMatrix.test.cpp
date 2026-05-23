// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::matrix;
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "AngularDistributionCovarianceMatrix" ) {

  GIVEN( "valid covariance data for an on-diagonal covariance matrix" ) {

    AngularDistributionMetadata metadata( { id::ReactionID( "n,U235->n,U235" ) },
                                          { 1e-5, 1., 1e+6, 2e+7 },
                                          { 1 } );

    Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    AngularDistributionCovarianceMatrix chunk( std::move( metadata ), std::move( matrix ) );

    THEN( "a AngularDistributionCovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
      CHECK( 1 == chunk.rowMetadata().moments().size() );
      CHECK( 1 == chunk.rowMetadata().moments()[0] );
      CHECK( chunk.columnMetadata() == chunk.rowMetadata() );

      CHECK( true == chunk.isRelativeMatrix() );
      CHECK( false == chunk.isAbsoluteMatrix() );
      CHECK( false == chunk.isOffDiagonal() );
      CHECK( true == chunk.isOnDiagonal() );

      CHECK( std::nullopt != chunk.standardDeviations() );
      CHECK( std::nullopt != chunk.correlations() );
      CHECK( std::nullopt != chunk.eigenvalues() );
      CHECK( std::nullopt != chunk.eigenvectors() );
      CHECK( std::nullopt != std::get< 0 >( chunk.eigendata() ) );
      CHECK( std::nullopt != std::get< 1 >( chunk.eigendata() ) );

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

      // eigenvector result provided by numpy
      CHECK( 3 == chunk.eigenvalues().value().size() );
      CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[0] ) );
      CHECK_THAT(  0., WithinAbs( chunk.eigenvalues().value()[1], 1e-12 ) );
      CHECK_THAT(  0., WithinAbs( chunk.eigenvalues().value()[2], 1e-12 ) );
      CHECK( 3 == chunk.eigenvectors().value().size() );
      CHECK_THAT( 0.2672612419124246, WithinRel( chunk.eigenvectors().value()[0](0) ) );
      CHECK_THAT( 0.5345224838248487, WithinRel( chunk.eigenvectors().value()[0](1) ) );
      CHECK_THAT( 0.8017837257372732, WithinRel( chunk.eigenvectors().value()[0](2) ) );

      CHECK( 3 == std::get< 0 >( chunk.eigendata() ).value().size() );
      CHECK_THAT( 14., WithinRel( std::get< 0 >( chunk.eigendata() ).value()[0] ) );
      CHECK_THAT(  0., WithinAbs( std::get< 0 >( chunk.eigendata() ).value()[1], 1e-12 ) );
      CHECK_THAT(  0., WithinAbs( std::get< 0 >( chunk.eigendata() ).value()[2], 1e-12 ) );
      CHECK( 3 == std::get< 1 >( chunk.eigendata() ).value().size() );
      CHECK_THAT( 0.2672612419124246, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](0) ) );
      CHECK_THAT( 0.5345224838248487, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](1) ) );
      CHECK_THAT( 0.8017837257372732, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](2) ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid correlation data for an on-diagonal covariance matrix" ) {

    AngularDistributionMetadata metadata( { id::ReactionID( "n,U235->n,U235" ) },
                                          { 1e-5, 1., 1e+6, 2e+7 },
                                          { 1 } );

    std::vector< double > deviations = { 1., 2., 3. };
    Matrix< double > correlations( 3, 3 );
    correlations << 1., 1., 1.,
                    1., 1., 1.,
                    1., 1., 1.;

    AngularDistributionCovarianceMatrix chunk( std::move( metadata ), std::move( deviations ),
                                               std::move( correlations ) );

    THEN( "a AngularDistributionCovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
      CHECK( 1 == chunk.rowMetadata().moments().size() );
      CHECK( 1 == chunk.rowMetadata().moments()[0] );
      CHECK( chunk.columnMetadata() == chunk.rowMetadata() );

      CHECK( true == chunk.isRelativeMatrix() );
      CHECK( false == chunk.isAbsoluteMatrix() );
      CHECK( false == chunk.isOffDiagonal() );
      CHECK( true == chunk.isOnDiagonal() );

      CHECK( std::nullopt != chunk.standardDeviations() );
      CHECK( std::nullopt != chunk.correlations() );
      CHECK( std::nullopt != chunk.eigenvalues() );
      CHECK( std::nullopt != chunk.eigenvectors() );
      CHECK( std::nullopt != std::get< 0 >( chunk.eigendata() ) );
      CHECK( std::nullopt != std::get< 1 >( chunk.eigendata() ) );

      CHECK( 3 == chunk.covariances().rows() );
      CHECK( 3 == chunk.covariances().cols() );
      CHECK_THAT( 1., WithinRel( chunk.covariances()(0,0) ) );
      CHECK_THAT( 2., WithinRel( chunk.covariances()(0,1) ) );
      CHECK_THAT( 3., WithinRel( chunk.covariances()(0,2) ) );
      CHECK_THAT( 2., WithinRel( chunk.covariances()(1,0) ) );
      CHECK_THAT( 4., WithinRel( chunk.covariances()(1,1) ) );
      CHECK_THAT( 6., WithinRel( chunk.covariances()(1,2) ) );
      CHECK_THAT( 3., WithinRel( chunk.covariances()(2,0) ) );
      CHECK_THAT( 6., WithinRel( chunk.covariances()(2,1) ) );
      CHECK_THAT( 9., WithinRel( chunk.covariances()(2,2) ) );

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

      // eigenvector result provided by numpy
      CHECK( 3 == chunk.eigenvalues().value().size() );
      CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[0] ) );
      CHECK_THAT(  0., WithinAbs( chunk.eigenvalues().value()[1], 1e-12 ) );
      CHECK_THAT(  0., WithinAbs( chunk.eigenvalues().value()[2], 1e-12 ) );
      CHECK( 3 == chunk.eigenvectors().value().size() );
      CHECK_THAT( 0.2672612419124246, WithinRel( chunk.eigenvectors().value()[0](0) ) );
      CHECK_THAT( 0.5345224838248487, WithinRel( chunk.eigenvectors().value()[0](1) ) );
      CHECK_THAT( 0.8017837257372732, WithinRel( chunk.eigenvectors().value()[0](2) ) );

      CHECK( 3 == std::get< 0 >( chunk.eigendata() ).value().size() );
      CHECK_THAT( 14., WithinRel( std::get< 0 >( chunk.eigendata() ).value()[0] ) );
      CHECK_THAT(  0., WithinAbs( std::get< 0 >( chunk.eigendata() ).value()[1], 1e-12 ) );
      CHECK_THAT(  0., WithinAbs( std::get< 0 >( chunk.eigendata() ).value()[2], 1e-12 ) );
      CHECK( 3 == std::get< 1 >( chunk.eigendata() ).value().size() );
      CHECK_THAT( 0.2672612419124246, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](0) ) );
      CHECK_THAT( 0.5345224838248487, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](1) ) );
      CHECK_THAT( 0.8017837257372732, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](2) ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid eigenvalues and eigenvectors for an on-diagonal covariance matrix" ) {

    AngularDistributionMetadata metadata( { id::ReactionID( "n,U235->n,U235" ) },
                                          { 1e-5, 1., 1e+6, 2e+7 },
                                          { 1 } );

    std::vector< double > eigenvalues = { 14. };
    std::vector< Vector< double > > eigenvectors( 1, Vector< double >( 3 ) );
    eigenvectors[0] << 0.2672612419124246, 0.5345224838248487, 0.8017837257372732;

    AngularDistributionCovarianceMatrix chunk( std::move( metadata ), std::move( eigenvalues ),
                                        std::move( eigenvectors ) );

    THEN( "a AngularDistributionCovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
      CHECK( 1 == chunk.rowMetadata().moments().size() );
      CHECK( 1 == chunk.rowMetadata().moments()[0] );
      CHECK( chunk.columnMetadata() == chunk.rowMetadata() );

      CHECK( true == chunk.isRelativeMatrix() );
      CHECK( false == chunk.isAbsoluteMatrix() );
      CHECK( false == chunk.isOffDiagonal() );
      CHECK( true == chunk.isOnDiagonal() );

      CHECK( std::nullopt != chunk.standardDeviations() );
      CHECK( std::nullopt != chunk.correlations() );
      CHECK( std::nullopt != chunk.eigenvalues() );
      CHECK( std::nullopt != chunk.eigenvectors() );
      CHECK( std::nullopt != std::get< 0 >( chunk.eigendata() ) );
      CHECK( std::nullopt != std::get< 1 >( chunk.eigendata() ) );

      CHECK( 3 == chunk.covariances().rows() );
      CHECK( 3 == chunk.covariances().cols() );
      CHECK_THAT( 1., WithinRel( chunk.covariances()(0,0) ) );
      CHECK_THAT( 2., WithinRel( chunk.covariances()(0,1) ) );
      CHECK_THAT( 3., WithinRel( chunk.covariances()(0,2) ) );
      CHECK_THAT( 2., WithinRel( chunk.covariances()(1,0) ) );
      CHECK_THAT( 4., WithinRel( chunk.covariances()(1,1) ) );
      CHECK_THAT( 6., WithinRel( chunk.covariances()(1,2) ) );
      CHECK_THAT( 3., WithinRel( chunk.covariances()(2,0) ) );
      CHECK_THAT( 6., WithinRel( chunk.covariances()(2,1) ) );
      CHECK_THAT( 9., WithinRel( chunk.covariances()(2,2) ) );

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

      CHECK( 1 == chunk.eigenvalues().value().size() );
      CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[0] ) );
      CHECK( 1 == chunk.eigenvectors().value().size() );
      CHECK_THAT( 0.2672612419124246, WithinRel( chunk.eigenvectors().value()[0](0) ) );
      CHECK_THAT( 0.5345224838248487, WithinRel( chunk.eigenvectors().value()[0](1) ) );
      CHECK_THAT( 0.8017837257372732, WithinRel( chunk.eigenvectors().value()[0](2) ) );

      CHECK( 1 == std::get< 0 >( chunk.eigendata() ).value().size() );
      CHECK_THAT( 14., WithinRel( std::get< 0 >( chunk.eigendata() ).value()[0] ) );
      CHECK( 1 == std::get< 1 >( chunk.eigendata() ).value().size() );
      CHECK_THAT( 0.2672612419124246, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](0) ) );
      CHECK_THAT( 0.5345224838248487, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](1) ) );
      CHECK_THAT( 0.8017837257372732, WithinRel( std::get< 1 >( chunk.eigendata() ).value()[0](2) ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an off-diagonal covariance matrix" ) {

    AngularDistributionMetadata rowMetadata( { id::ReactionID( "n,U235->n,U235" ) },
                                             { 1e-5, 1., 1e+6, 2e+7 },
                                             { 1 } );
    AngularDistributionMetadata columnMetadata( { id::ReactionID( "n,U235->fission(t)" ) },
                                                { 1e-5, 2., 2e+7 },
                                                { 2 } );

    Matrix< double > matrix( 3, 2 );
    matrix << 1., 2.,
              2., 4.,
              3., 6.;

    AngularDistributionCovarianceMatrix chunk( std::move( rowMetadata ),
                                               std::move( columnMetadata ),
                                               std::move( matrix ) );

    THEN( "a AngularDistributionCovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( chunk.columnMetadata() != chunk.rowMetadata() );

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
      CHECK( 1 == chunk.rowMetadata().moments().size() );
      CHECK( 1 == chunk.rowMetadata().moments()[0] );

      CHECK( 1 == chunk.columnMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->fission(t)" ) == chunk.columnMetadata().reactionIdentifiers()[0] );
      CHECK( 3 == chunk.columnMetadata().energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
      CHECK_THAT( 2.  , WithinRel( chunk.columnMetadata().energies()[1] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.columnMetadata().energies()[2] ) );
      CHECK( 1 == chunk.columnMetadata().moments().size() );
      CHECK( 2 == chunk.columnMetadata().moments()[0] );

      CHECK( true == chunk.isRelativeMatrix() );
      CHECK( false == chunk.isAbsoluteMatrix() );
      CHECK( true == chunk.isOffDiagonal() );
      CHECK( false == chunk.isOnDiagonal() );

      CHECK( std::nullopt == chunk.standardDeviations() );
      CHECK( std::nullopt == chunk.correlations() );
      CHECK( std::nullopt == chunk.eigenvalues() );
      CHECK( std::nullopt == chunk.eigenvectors() );
      CHECK( std::nullopt == std::get< 0 >( chunk.eigendata() ) );
      CHECK( std::nullopt == std::get< 1 >( chunk.eigendata() ) );

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
      CHECK( std::nullopt == chunk.eigenvectors() );
      CHECK( std::nullopt == std::get< 0 >( chunk.eigendata() ) );
      CHECK( std::nullopt == std::get< 1 >( chunk.eigendata() ) );
    } // THEN
  } // GIVEN
} // SCENARIO
