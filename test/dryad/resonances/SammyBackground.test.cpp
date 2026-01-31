// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/SammyBackground.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "SammyBackground" ) {

  GIVEN( "valid data for a SammyBackground" ) {

    std::array< double, 3 > polynomial_coefficients = { -0.043, 2.8e-8, 0 };
    std::array< double, 2 > logarithmic_coefficients = {  0.01, 0. };
    double lower_singularity = 0.;
    double upper_singularity = 9.55e5;

    THEN( "a SammyBackground can be constructed" ) {

      SammyBackground chunk( std::move( polynomial_coefficients ),
                             std::move( logarithmic_coefficients ),
                             lower_singularity, upper_singularity );

      CHECK_THAT( -0.043, WithinRel( chunk.polynomialCoefficients()[0] ) );
      CHECK_THAT( 2.8e-8, WithinRel( chunk.polynomialCoefficients()[1] ) );
      CHECK_THAT( 0.    , WithinRel( chunk.polynomialCoefficients()[2] ) );
      CHECK_THAT( 0.01  , WithinRel( chunk.logarithmicCoefficients()[0] ) );
      CHECK_THAT( 0.    , WithinRel( chunk.logarithmicCoefficients()[1] ) );
      CHECK_THAT( 0.    , WithinRel( chunk.lowerSingularity() ) );
      CHECK_THAT( 9.55e5, WithinRel( chunk.upperSingularity() ) );

      CHECK_THAT( -0.043 + 2.8e-8 - 0.01 * std::log( 9.55e5 - 1. / 1. ), WithinRel( chunk( 1. ) ) );
    } // THEN
  } // GIVEN
} // SCENARIO
