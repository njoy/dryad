// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/LegendreAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "LegendreAngularDistribution" ) {

  GIVEN( "Legendre coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > coefficients = { -31./3., 73./5., -14./3., 2./5. };

      LegendreAngularDistribution chunk( std::move( coefficients ) );

      THEN( "a LegendreAngularDistribution can be constructed and members can "
            "be tested" ) {

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );

        CHECK( 3 == chunk.order() );

        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -10.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( chunk.coefficients()[3] ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be evaluated" ) {

        CHECK_THAT(  -8., WithinRel( chunk(  0. ) ) );
        CHECK_THAT(   0., WithinAbs( chunk(  1. ), 1e-12 ) );
        CHECK_THAT( -30., WithinRel( chunk( -1. ) ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be linearised" ) {

        ToleranceConvergence convergence( 0.01 );
        TabulatedAngularDistribution linear = chunk.linearise( convergence );

        CHECK( 21 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 21 == linear.cosines().size() );
        CHECK( 21 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 20 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( -1.0      , WithinRel( linear.cosines()[0] ) );
        CHECK_THAT( -0.75     , WithinRel( linear.cosines()[1] ) );
        CHECK_THAT( -0.5      , WithinRel( linear.cosines()[2] ) );
        CHECK_THAT( -0.25     , WithinRel( linear.cosines()[3] ) );
        CHECK_THAT( -0.125    , WithinRel( linear.cosines()[4] ) );
        CHECK_THAT(  0.0      , WithinRel( linear.cosines()[5] ) );
        CHECK_THAT(  0.125    , WithinRel( linear.cosines()[6] ) );
        CHECK_THAT(  0.25     , WithinRel( linear.cosines()[7] ) );
        CHECK_THAT(  0.375    , WithinRel( linear.cosines()[8] ) );
        CHECK_THAT(  0.5      , WithinRel( linear.cosines()[9] ) );
        CHECK_THAT(  0.625    , WithinRel( linear.cosines()[10] ) );
        CHECK_THAT(  0.6875   , WithinRel( linear.cosines()[11] ) );
        CHECK_THAT(  0.75     , WithinRel( linear.cosines()[12] ) );
        CHECK_THAT(  0.8125   , WithinRel( linear.cosines()[13] ) );
        CHECK_THAT(  0.875    , WithinRel( linear.cosines()[14] ) );
        CHECK_THAT(  0.90625  , WithinRel( linear.cosines()[15] ) );
        CHECK_THAT(  0.9375   , WithinRel( linear.cosines()[16] ) );
        CHECK_THAT(  0.96875  , WithinRel( linear.cosines()[17] ) );
        CHECK_THAT(  0.984375 , WithinRel( linear.cosines()[18] ) );
        CHECK_THAT(  0.9921875, WithinRel( linear.cosines()[19] ) );
        CHECK_THAT(  1.0      , WithinRel( linear.cosines()[20] ) );

        CHECK_THAT( -30.0             , WithinRel( linear.values()[0] ) );
        CHECK_THAT( -22.859375        , WithinRel( linear.values()[1] ) );
        CHECK_THAT( -16.875           , WithinRel( linear.values()[2] ) );
        CHECK_THAT( -11.953125        , WithinRel( linear.values()[3] ) );
        CHECK_THAT( -9.861328125      , WithinRel( linear.values()[4] ) );
        CHECK_THAT( -8.0              , WithinRel( linear.values()[5] ) );
        CHECK_THAT( -6.357421875      , WithinRel( linear.values()[6] ) );
        CHECK_THAT( -4.921875         , WithinRel( linear.values()[7] ) );
        CHECK_THAT( -3.681640625      , WithinRel( linear.values()[8] ) );
        CHECK_THAT( -2.625            , WithinRel( linear.values()[9] ) );
        CHECK_THAT( -1.740234375      , WithinRel( linear.values()[10] ) );
        CHECK_THAT( -1.358642578125   , WithinRel( linear.values()[11] ) );
        CHECK_THAT( -1.015625         , WithinRel( linear.values()[12] ) );
        CHECK_THAT( -0.709716796875   , WithinRel( linear.values()[13] ) );
        CHECK_THAT( -0.439453125      , WithinRel( linear.values()[14] ) );
        CHECK_THAT( -0.317230224609375, WithinRel( linear.values()[15] ) );
        CHECK_THAT( -0.203369140625   , WithinRel( linear.values()[16] ) );
        CHECK_THAT( -0.097686767578125, WithinRel( linear.values()[17] ) );
        CHECK_THAT( -0.047855377197266, WithinRel( linear.values()[18], 1e-12 ) );
        CHECK_THAT( -0.023682117462158, WithinRel( linear.values()[19], 1e-12 ) );
        CHECK_THAT(  0.0              , WithinAbs( linear.values()[20], 1e-12 ) );

        CHECK( true == linear.isLinearised() );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        LegendreAngularDistribution small( { 3., 0., 1. } );
        LegendreAngularDistribution equal( { 3., 0., 0., 1. } );
        LegendreAngularDistribution large( { 3., 0., 0., 0., 1. } );
        LegendreAngularDistribution result( { 0. } );

        result = -chunk;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT(  10.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( -14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(   4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  -0.4             , WithinRel( result.coefficients()[3] ) );

        chunk += 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -8.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(  0.4             , WithinRel( chunk.coefficients()[3] ) );

        chunk -= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -10.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( chunk.coefficients()[3] ) );

        chunk += small;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -7.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( -3.66666666666667, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(  0.4             , WithinRel( chunk.coefficients()[3] ) );

        chunk -= small;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -10.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( chunk.coefficients()[3] ) );

        chunk += equal;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -7.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(  1.4             , WithinRel( chunk.coefficients()[3] ) );

        chunk -= equal;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -10.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( chunk.coefficients()[3] ) );

        chunk += large;

        CHECK( 4 == chunk.order() );
        CHECK(  5 == chunk.coefficients().size() );
        CHECK_THAT( -7.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(  0.4             , WithinRel( chunk.coefficients()[3] ) );
        CHECK_THAT(  1.              , WithinRel( chunk.coefficients()[4] ) );

        chunk -= large;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -10.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( chunk.coefficients()[3] ) );

        chunk *= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -20.66666666666666, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  29.2             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -9.33333333333333, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.8             , WithinRel( chunk.coefficients()[3] ) );

        chunk /= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -10.33333333333333, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( chunk.coefficients()[3] ) );

        result = chunk + 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -8.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.4             , WithinRel( result.coefficients()[3] ) );

        result = 2. + chunk;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -8.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.4             , WithinRel( result.coefficients()[3] ) );

        result = chunk - 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -12.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( result.coefficients()[3] ) );

        result = 2. - chunk;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT(  12.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( -14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(   4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  -0.4             , WithinRel( result.coefficients()[3] ) );

        result = chunk * 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -20.66666666666666, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  29.2             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -9.33333333333333, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.8             , WithinRel( result.coefficients()[3] ) );

        result = 2. * chunk;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -20.66666666666666, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  29.2             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -9.33333333333333, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.8             , WithinRel( result.coefficients()[3] ) );

        result = chunk / 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -5.16666666666666, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  7.3             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -2.33333333333333, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.2             , WithinRel( result.coefficients()[3] ) );

        result = chunk + small;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -7.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -3.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.4             , WithinRel( result.coefficients()[3] ) );

        result = chunk - small;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -13.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -5.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( result.coefficients()[3] ) );

        result = chunk + equal;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -7.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  1.4             , WithinRel( result.coefficients()[3] ) );

        result = chunk - equal;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -13.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  -0.6             , WithinRel( result.coefficients()[3] ) );

        result = chunk + large;

        CHECK( 4 == result.order() );
        CHECK(  5 == result.coefficients().size() );
        CHECK_THAT(  -7.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( result.coefficients()[3] ) );
        CHECK_THAT(   1.              , WithinRel( result.coefficients()[4] ) );

        result = chunk - large;

        CHECK( 4 == result.order() );
        CHECK(  5 == result.coefficients().size() );
        CHECK_THAT( -13.33333333333333, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.6             , WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -4.66666666666666, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.4             , WithinRel( result.coefficients()[3] ) );
        CHECK_THAT(  -1.              , WithinRel( result.coefficients()[4] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};
        CHECK_THROWS( LegendreAngularDistribution( empty ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
