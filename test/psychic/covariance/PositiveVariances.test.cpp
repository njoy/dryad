// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/psychic/covariance/PositiveVariances.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad::covariance;

SCENARIO( "PositiveVariances" ) {

  GIVEN( "on-diagonal matrices covariance matrices" ) {

    // metadata for the covariance matrix
    njoy::dryad::covariance::CrossSectionMetadata metadata( { njoy::dryad::id::ReactionID( "n,U235->n,U235" ) },
                                                            { 1e-5, 1., 1e+6, 2e+7 } );

    njoy::matrix::Matrix< double > success( 3, 3 );
    success << 1., 2., 3.,
               2., 4., 6.,
               3., 6., 9.;

    njoy::matrix::Matrix< double > warning( 3, 3 );
    warning << 1., 2., 3.,
               2., 4., 6.,
               3., 6., 0.;

    // not positive semi-definite
    njoy::matrix::Matrix< double > fail( 3, 3 );
    fail << 1., 2.,  3.,
            2., 4.,  6.,
            3., 6., -9.;

    njoy::psychic::covariance::PositiveVariances test;

    WHEN( "a covariance matrix with strictly positive variances is used" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( metadata, success );

      THEN( "the test returns a success" ) {

        CHECK( njoy::psychic::TestStatus::Success == test( matrix ) );
      } // THEN
    } // WHEN

    WHEN( "a covariance matrix with positive variances is used" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( metadata, warning );

      THEN( "the test returns a warning" ) {

        CHECK( njoy::psychic::TestStatus::Warning == test( matrix ) );
      } // THEN
    } // WHEN

    WHEN( "a covariance matrix with negative variances is used" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( metadata, fail );

      THEN( "the test returns a fail" ) {

        CHECK( njoy::psychic::TestStatus::Fail == test( matrix ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
