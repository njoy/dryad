// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/psychic/covariance/BoundedCorrelations.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad::covariance;

SCENARIO( "BoundedCorrelations" ) {

  GIVEN( "on-diagonal matrices covariance matrices" ) {

    // metadata for the covariance matrix
    njoy::dryad::covariance::CrossSectionMetadata metadata( { njoy::dryad::id::ReactionID( "n,U235->n,U235" ) },
                                                            { 1e-5, 1., 1e+6, 2e+7 } );

    // metadata and standard deviations for the off-diagonal covariance matrix
    njoy::dryad::covariance::CrossSectionMetadata row_metadata( { njoy::dryad::id::ReactionID( "n,U235->n,U235" ), },
                                                                { 1e-5, 1., 1e+6, 2e+7 } );
    njoy::dryad::covariance::CrossSectionMetadata col_metadata( { njoy::dryad::id::ReactionID( "n,U235->g,U236" ), },
                                                                { 1e-5, 1., 1e+6, 2e+7 } );


    njoy::matrix::Matrix< double > success( 3, 3 );
    success << 1., 1., 1.,
               1., 1., 1.,
               1., 1., 1.;

    njoy::matrix::Matrix< double > warning( 3, 3 );
    warning << 1., 1., 1.,
               1., 1., 1.,
               1., 1., 1.00000000005;

    njoy::matrix::Matrix< double > fail( 3, 3 );
    fail << 1., 1., 1.,
            1., 1., 1.,
            1., 1., 1.5;

    std::vector< double > deviations = { 1., 2., 3. };
    std::vector< double > row_deviations = { 1., 2., 3. };
    std::vector< double > col_deviations = { 1., 2., 3. };

    njoy::psychic::covariance::BoundedCorrelations test;

    WHEN( "a on- and off-diagonal covariance matrix with all correlations between -1 and 1 is used" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( metadata, deviations, success );
      njoy::dryad::covariance::CrossSectionCovarianceMatrix off_diagonal( row_metadata, col_metadata,
                                                                          row_deviations, col_deviations, success );

      THEN( "the test returns a success" ) {

        CHECK( njoy::psychic::TestStatus::Success == test( matrix ) );
        CHECK( njoy::psychic::TestStatus::Success == test( off_diagonal ) );
      } // THEN
    } // WHEN

    WHEN( "a covariance matrix with all correlations between -1 and 1 (within tolerance) is used" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( metadata, deviations, warning );
      njoy::dryad::covariance::CrossSectionCovarianceMatrix off_diagonal( row_metadata, col_metadata,
                                                                          row_deviations, col_deviations, warning );

      THEN( "the test returns a warning" ) {

        CHECK( njoy::psychic::TestStatus::Warning == test( matrix ) );
        CHECK( njoy::psychic::TestStatus::Warning == test( off_diagonal ) );
      } // THEN
    } // WHEN

    WHEN( "a covariance matrix with correlations outside -1 and 1 is used" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( metadata, deviations, fail );
      njoy::dryad::covariance::CrossSectionCovarianceMatrix off_diagonal( row_metadata, col_metadata,
                                                                          row_deviations, col_deviations, fail );

      THEN( "the test returns a fail" ) {

        CHECK( njoy::psychic::TestStatus::Fail == test( matrix ) );
        CHECK( njoy::psychic::TestStatus::Fail == test( off_diagonal ) );
      } // THEN
    } // WHEN

    WHEN( "an off-diagonal covariance matrix is used that does not have correlations" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( row_metadata, col_metadata, success );

      THEN( "the test is skipped" ) {

        CHECK( njoy::psychic::TestStatus::Skipped == test( matrix ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
