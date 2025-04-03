// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/PolynomialMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "PolynomialMultiplicity" ) {

  GIVEN( "Legendre coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      // the 3rd order polynomial was designed to have 3 real roots: 1, 2 and 4

      double lower = 1e-5;
      double upper = 2e+7;
      std::vector< double > coefficients = { 2., 1e-6 };

      PolynomialMultiplicity chunk( lower, upper, std::move( coefficients ) );

      THEN( "a PolynomialMultiplicity can be constructed and members can be tested" ) {

        CHECK( 1 == chunk.order() );

        CHECK( 2 == chunk.coefficients().size() );
        CHECK_THAT( 2., WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 1e-6, WithinRel( chunk.coefficients()[1] ) );
      } // THEN

      THEN( "a PolynomialMultiplicity can be evaluated" ) {

        CHECK_THAT( 2. + 1e-11, WithinRel( chunk( 1e-5 ) ) );
        CHECK_THAT(   2.000003, WithinRel( chunk( 3. ) ) );
        CHECK_THAT(       22.0, WithinRel( chunk( 2.0e+7 ) ) );
      } // THEN

      THEN( "a PolynomialMultiplicity can be linearised" ) {

        TabulatedMultiplicity linear = chunk.linearise();

        CHECK( 2 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 2 == linear.energies().size() );
        CHECK( 2 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 1 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( 1e-5, WithinRel( linear.energies()[0] ) );
        CHECK_THAT( 2e+7, WithinRel( linear.energies()[1] ) );

        CHECK_THAT(  2. + 1e-11, WithinRel( linear.values()[0] ) );
        CHECK_THAT( 22., WithinRel( linear.values()[1] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
