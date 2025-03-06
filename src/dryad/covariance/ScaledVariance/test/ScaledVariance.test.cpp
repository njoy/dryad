// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/ScaledVariance.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "ScaledVariance" ) {

  GIVEN( "valid covariance data for a diagonal ScaledVariance" ) {

    std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };
    std::vector< double > factors = { .1, .2, .3 };

    ScaledVariance chunk( ScalingType::Inverse, std::move( energies ), std::move( factors ) );

    THEN( "a ScaledVariance can be constructed and members can be tested" ) {

      CHECK( 4 == chunk.energies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.energies()[3] ) );

      CHECK( 3 == chunk.factors().size() );
      CHECK_THAT( 0.1, WithinRel( chunk.factors()[0] ) );
      CHECK_THAT( 0.2, WithinRel( chunk.factors()[1] ) );
      CHECK_THAT( 0.3, WithinRel( chunk.factors()[2] ) );

      CHECK( ScalingType::Inverse == chunk.type() );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a ScaledVariance" ) {

    WHEN( "the number of groups is zero or one" ) {

      std::vector< double > zero = {};
      std::vector< double > one = { 1. };
      std::vector< double > factors = { .1, .2, .3 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ScaledVariance( ScalingType::Inverse,
                                      std::move( zero ),
                                      std::move( factors ) ) );
        CHECK_THROWS( ScaledVariance( ScalingType::Inverse,
                                      std::move( zero ),
                                      std::move( factors ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix is not symmetric for a diagonal covariance block" ) {

      std::vector< double > energies = { 1e-5, 1., 2e+7 };
      std::vector< double > factors = { .1, .2, .3 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ScaledVariance( ScalingType::Inverse,
                                      std::move( energies ),
                                      std::move( factors ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO