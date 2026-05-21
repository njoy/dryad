// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/psychic/covariance/EigenvalueRatio.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad::covariance;

SCENARIO( "EigenvalueRatio" ) {

  GIVEN( "on-diagonal matrices covariance matrices" ) {

    // metadata for the covariance matrix
    njoy::dryad::covariance::CrossSectionMetadata metadata( { njoy::dryad::id::ReactionID( "n,U235->n,U235" ) },
                                                            { 1e-5, 1., 1e+6, 2e+7 } );

    njoy::matrix::Matrix< double > success( 3, 3 );
    success << 100.,  0.,  0.,
                 0., 50.,  0.,
                 0.,  0., 10.;

    njoy::matrix::Matrix< double > fail( 3, 3 );
    fail <<   1.,  0.,    0.,
              0.,  1.,    0.,
              0.,  0., 1e-10;

    njoy::psychic::covariance::EigenvalueRatio test;

    WHEN( "a covariance matrix with an eigenvalue ratio of 10" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( metadata, success );

      THEN( "the test returns a success" ) {

        CHECK( njoy::psychic::TestStatus::Success == test( matrix ) );
      } // THEN
    } // WHEN

    WHEN( "a covariance matrix with an eigenvalue ratio of 1e-10" ) {

      njoy::dryad::covariance::CrossSectionCovarianceMatrix matrix( metadata, fail );

      THEN( "the test returns a fail" ) {

        CHECK( njoy::psychic::TestStatus::Fail == test( matrix ).value() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
