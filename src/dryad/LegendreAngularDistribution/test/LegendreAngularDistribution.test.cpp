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

  GIVEN( "Legendre coefficients for a normalised expansion" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > coefficients = { 0.5, 0.25 };

      LegendreAngularDistribution chunk( std::move( coefficients ) );

      THEN( "a LegendreAngularDistribution can be constructed and members can "
            "be tested" ) {

        auto pdf = chunk.pdf();
        CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
        CHECK( 1 == pdf.order() );
        CHECK( 2 == pdf.coefficients().size() );
        CHECK_THAT( 0.5 , WithinRel( pdf.coefficients()[0] ) );
        CHECK_THAT( 0.25, WithinRel( pdf.coefficients()[1] ) );

        CHECK_THAT( 1.0, WithinRel( pdf.integral() ) ); // normalised pdf

        auto cdf = chunk.cdf();
        CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
        CHECK( 2 == cdf.order() );
        CHECK( 3 == cdf.coefficients().size() );
        CHECK_THAT( 0.4166666666666666, WithinRel( cdf.coefficients()[0] ) );
        CHECK_THAT( 0.5               , WithinRel( cdf.coefficients()[1] ) );
        CHECK_THAT( 0.0833333333333333, WithinRel( cdf.coefficients()[2] ) );
        CHECK_THAT( 0., WithinRel( cdf( -1. ) ) );
        CHECK_THAT( 1., WithinRel( cdf(  1. ) ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be evaluated" ) {

        CHECK_THAT( 0.25, WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 0.5 , WithinRel( chunk(  0. ) ) );
        CHECK_THAT( 0.75, WithinRel( chunk(  1. ) ) );
      } // THEN

      THEN( "the average cosine can be calculated" ) {

        CHECK_THAT( 1. / 6., WithinRel( chunk.averageCosine() ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 2 == linear.pdf().numberPoints() );
        CHECK( 1 == linear.pdf().numberRegions() );

        CHECK( 2 == linear.pdf().cosines().size() );
        CHECK( 2 == linear.pdf().values().size() );
        CHECK( 1 == linear.pdf().boundaries().size() );
        CHECK( 1 == linear.pdf().interpolants().size() );

        CHECK( 1 == linear.pdf().boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.pdf().interpolants()[0] );

        CHECK_THAT( -1.0      , WithinRel( linear.pdf().cosines()[0] ) );
        CHECK_THAT(  1.0      , WithinRel( linear.pdf().cosines()[1] ) );

        CHECK_THAT( 0.25, WithinRel( linear.pdf().values()[0] ) );
        CHECK_THAT( 0.75, WithinRel( linear.pdf().values()[1] ) );

        CHECK( true == linear.pdf().isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "Legendre coefficients for an unnormalised expansion" ) {

    // the resulting distribution will be normalised, test results are equal to
    // the previous case

    WHEN( "the data is given explicitly" ) {

      std::vector< double > coefficients = { 1.0, 0.5 };

      LegendreAngularDistribution chunk( std::move( coefficients ) );

      THEN( "a LegendreAngularDistribution can be constructed and members can "
            "be tested" ) {

        auto pdf = chunk.pdf();
        CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
        CHECK( 1 == pdf.order() );
        CHECK( 2 == pdf.coefficients().size() );
        CHECK_THAT( 0.5 , WithinRel( pdf.coefficients()[0] ) );
        CHECK_THAT( 0.25, WithinRel( pdf.coefficients()[1] ) );

        CHECK_THAT( 1.0, WithinRel( pdf.integral() ) ); // normalised pdf

        auto cdf = chunk.cdf();
        CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
        CHECK( 2 == cdf.order() );
        CHECK( 3 == cdf.coefficients().size() );
        CHECK_THAT( 0.4166666666666666, WithinRel( cdf.coefficients()[0] ) );
        CHECK_THAT( 0.5               , WithinRel( cdf.coefficients()[1] ) );
        CHECK_THAT( 0.0833333333333333, WithinRel( cdf.coefficients()[2] ) );
        CHECK_THAT( 0., WithinRel( cdf( -1. ) ) );
        CHECK_THAT( 1., WithinRel( cdf(  1. ) ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be evaluated" ) {

        CHECK_THAT( 0.25, WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 0.5 , WithinRel( chunk(  0. ) ) );
        CHECK_THAT( 0.75, WithinRel( chunk(  1. ) ) );
      } // THEN

      THEN( "the average cosine can be calculated" ) {

        CHECK_THAT( 1. / 6., WithinRel( chunk.averageCosine() ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 2 == linear.pdf().numberPoints() );
        CHECK( 1 == linear.pdf().numberRegions() );

        CHECK( 2 == linear.pdf().cosines().size() );
        CHECK( 2 == linear.pdf().values().size() );
        CHECK( 1 == linear.pdf().boundaries().size() );
        CHECK( 1 == linear.pdf().interpolants().size() );

        CHECK( 1 == linear.pdf().boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.pdf().interpolants()[0] );

        CHECK_THAT( -1.0      , WithinRel( linear.pdf().cosines()[0] ) );
        CHECK_THAT(  1.0      , WithinRel( linear.pdf().cosines()[1] ) );

        CHECK_THAT( 0.25, WithinRel( linear.pdf().values()[0] ) );
        CHECK_THAT( 0.75, WithinRel( linear.pdf().values()[1] ) );

        CHECK( true == linear.pdf().isLinearised() );
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
