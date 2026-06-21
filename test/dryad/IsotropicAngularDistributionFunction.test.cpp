// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/IsotropicAngularDistributionFunction.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "IsotropicAngularDistributionFunction" ) {

  GIVEN( "an isotropic angular distribution - normalised" ) {

    WHEN( "the function is constructed" ) {

      IsotropicAngularDistributionFunction chunk;

      THEN( "basic functionality can be tested" ) {

        CHECK_THAT( 0.5, WithinRel( chunk.value() ) );

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );

        // evaluation - inside the domain
        CHECK_THAT( 0.5, WithinRel( chunk( -1.0 ) ) );
        CHECK_THAT( 0.5, WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 0.5, WithinRel( chunk(  0.0 ) ) );
        CHECK_THAT( 0.5, WithinRel( chunk(  0.5 ) ) );
        CHECK_THAT( 0.5, WithinRel( chunk(  1.0 ) ) );

        // evaluation - outside the domain
        CHECK_THAT( 0.0, WithinRel( chunk( -2.0 ) ) );
        CHECK_THAT( 0.0, WithinRel( chunk(  2.0 ) ) );

        CHECK_THAT( 1.0, WithinRel( chunk.integral() ) );
        CHECK_THAT( 0.0, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "an IsotropicAngularDistributionFunction can be normalized" ) {

        chunk.normalise();

        CHECK_THAT( 0.5, WithinRel( chunk.value() ) );
        CHECK_THAT( 1.0, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "an IsotropicAngularDistributionFunction can be converted to a Legendre distribution" ) {

        LegendreAngularDistributionFunction legendre = chunk.toLegendreDistribution();

        CHECK( 0 == legendre.order() );
        CHECK( 1 == legendre.coefficients().size() );
        CHECK_THAT( 0.5, WithinRel( legendre.coefficients()[0] ) );
      } // THEN

      THEN( "an IsotropicAngularDistributionFunction can be converted to a table" ) {

        TabulatedAngularDistributionFunction tabulated = chunk.toTabulatedDistribution();

        CHECK( 2 == tabulated.numberPoints() );
        CHECK( 1 == tabulated.numberRegions() );
        CHECK( 2 == tabulated.cosines().size() );
        CHECK( 2 == tabulated.values().size() );

        CHECK_THAT( -1.0, WithinRel( tabulated.cosines()[0] ) );
        CHECK_THAT(  1.0, WithinRel( tabulated.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( tabulated.values()[0] ) );
        CHECK_THAT(  0.5, WithinRel( tabulated.values()[1] ) );
      } // THEN

      THEN( "an IsotropicAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK( 2 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );
        CHECK( 2 == linear.cosines().size() );
        CHECK( 2 == linear.values().size() );

        CHECK_THAT( -1.0, WithinRel( linear.cosines()[0] ) );
        CHECK_THAT(  1.0, WithinRel( linear.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( linear.values()[0] ) );
        CHECK_THAT(  0.5, WithinRel( linear.values()[1] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an isotropic angular distribution - not normalised" ) {

    WHEN( "the function is constructed" ) {

      IsotropicAngularDistributionFunction chunk( 1. );

      THEN( "basic functionality can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.value() ) );

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );

        // evaluation - inside the domain
        CHECK_THAT( 1., WithinRel( chunk( -1.0 ) ) );
        CHECK_THAT( 1., WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 1., WithinRel( chunk(  0.0 ) ) );
        CHECK_THAT( 1., WithinRel( chunk(  0.5 ) ) );
        CHECK_THAT( 1., WithinRel( chunk(  1.0 ) ) );

        // evaluation - outside the domain
        CHECK_THAT( 0.0, WithinRel( chunk( -2.0 ) ) );
        CHECK_THAT( 0.0, WithinRel( chunk(  2.0 ) ) );

        CHECK_THAT( 2.0, WithinRel( chunk.integral() ) );
        CHECK_THAT( 0.0, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "an IsotropicAngularDistributionFunction can be normalized" ) {

        chunk.normalise();

        CHECK_THAT( 0.5, WithinRel( chunk.value() ) );
        CHECK_THAT( 1.0, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "an IsotropicAngularDistributionFunction can be converted to a Legendre distribution" ) {

        LegendreAngularDistributionFunction legendre = chunk.toLegendreDistribution();

        CHECK( 0 == legendre.order() );
        CHECK( 1 == legendre.coefficients().size() );
        CHECK_THAT( 1., WithinRel( legendre.coefficients()[0] ) );
      } // THEN

      THEN( "an IsotropicAngularDistributionFunction can be converted to a table" ) {

        TabulatedAngularDistributionFunction tabulated = chunk.toTabulatedDistribution();

        CHECK( 2 == tabulated.numberPoints() );
        CHECK( 1 == tabulated.numberRegions() );
        CHECK( 2 == tabulated.cosines().size() );
        CHECK( 2 == tabulated.values().size() );

        CHECK_THAT( -1.0, WithinRel( tabulated.cosines()[0] ) );
        CHECK_THAT(  1.0, WithinRel( tabulated.cosines()[1] ) );
        CHECK_THAT(  1., WithinRel( tabulated.values()[0] ) );
        CHECK_THAT(  1., WithinRel( tabulated.values()[1] ) );
      } // THEN

      THEN( "an IsotropicAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK( 2 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );
        CHECK( 2 == linear.cosines().size() );
        CHECK( 2 == linear.values().size() );

        CHECK_THAT( -1.0, WithinRel( linear.cosines()[0] ) );
        CHECK_THAT(  1.0, WithinRel( linear.cosines()[1] ) );
        CHECK_THAT(  1., WithinRel( linear.values()[0] ) );
        CHECK_THAT(  1., WithinRel( linear.values()[1] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of IsotropicAngularDistributionFunction are given" ) {

      IsotropicAngularDistributionFunction left;
      IsotropicAngularDistributionFunction right;

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == right ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != right ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
