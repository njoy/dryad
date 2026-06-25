// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/medic/covariance/pruneSmallEigenvalues.hpp"

// other includes

// convenience typedefs
using namespace njoy::matrix;
using namespace njoy::medic::covariance;
using namespace njoy::dryad::covariance;
using namespace njoy::dryad::id;

SCENARIO( "pruneSmallEigenvalues" ) {

  GIVEN( "a cross section covariance matrix" ) {

    CrossSectionMetadata metadata( { ReactionID( "n,U235->n,U235" ) },
                                   { 1e-5, 1., 1e+6, 2e+7 } );

    Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    CrossSectionCovarianceMatrix chunk( std::move( metadata ), std::move( matrix ) );

    THEN( "eigenvalues can be eliminated" ) {

      CHECK( 3 == chunk.eigenvalues().value().size() );
      CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[0] ) );
      CHECK_THAT(  0., WithinRel( chunk.eigenvalues().value()[1] ) );
      CHECK_THAT(  0., WithinRel( chunk.eigenvalues().value()[2] ) );

      CHECK( 3 == chunk.eigenvectors().value().size() );
      CHECK_THAT( 0.2672612419124246, WithinRel( chunk.eigenvectors().value()[0](0) ) );
      CHECK_THAT( 0.5345224838248487, WithinRel( chunk.eigenvectors().value()[0](1) ) );
      CHECK_THAT( 0.8017837257372732, WithinRel( chunk.eigenvectors().value()[0](2) ) );

      pruneSmallEigenvalues( 1e-8, chunk );

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
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

      CHECK( std::nullopt != chunk.standardDeviations() );
      CHECK( std::nullopt != chunk.correlations() );
      CHECK( std::nullopt != chunk.eigenvalues() );
      CHECK( std::nullopt != chunk.eigenvectors() );

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

      CHECK_THROWS( pruneSmallEigenvalues( 100., chunk ) );
    } // THEN
  } // GIVEN
} // SCENARIO
