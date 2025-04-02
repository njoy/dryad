// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/TabulatedAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "TabulatedAngularDistribution" ) {

  GIVEN( "Cosines and probabilities for a normalised table" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > cosines = { -1., 0., 0.5, 1. };
      const std::vector< double > values = { 0., 0.5, 0.75, 1. };

      TabulatedAngularDistribution chunk( std::move( cosines ), std::move( values ) );

      THEN( "a TabulatedAngularDistribution can be constructed and members can "
            "be tested" ) {

        auto pdf = chunk.pdf();
        CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
        CHECK_THAT( -1.  , WithinRel( pdf.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( pdf.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( pdf.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( pdf.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( pdf.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( pdf.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( pdf.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( pdf.values()[3] ) );

        CHECK_THROWS( chunk.cdf() );
      } // THEN

      THEN( "a TabulatedAngularDistribution can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0. , WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 0.5, WithinRel( chunk(  0. ) ) );
        CHECK_THAT( 0.75, WithinRel( chunk( 0.5 ) ) );
        CHECK_THAT( 1. , WithinRel( chunk(  1. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( -5. ) ) );
        CHECK_THAT( 0., WithinRel( chunk(  5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.25 , WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 0.875, WithinRel( chunk(  0.75 ) ) );
      } // THEN

      THEN( "the average cosine can be calculated" ) {

        CHECK_THAT( 1. / 3., WithinRel( chunk.averageCosine() ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 4 == linear.pdf().numberPoints() );
        CHECK( 1 == linear.pdf().numberRegions() );

        CHECK( 4 == linear.pdf().cosines().size() );
        CHECK( 4 == linear.pdf().values().size() );
        CHECK( 1 == linear.pdf().boundaries().size() );
        CHECK( 1 == linear.pdf().interpolants().size() );

        CHECK( 3 == linear.pdf().boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.pdf().interpolants()[0] );

        CHECK_THAT( -1.  , WithinRel( linear.pdf().cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( linear.pdf().cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( linear.pdf().cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( linear.pdf().cosines()[3] ) );

        CHECK_THAT(  0.  , WithinRel( linear.pdf().values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( linear.pdf().values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( linear.pdf().values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( linear.pdf().values()[3] ) );

        CHECK( true == linear.pdf().isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "Cosines and probabilities for an unnormalised table" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > cosines = { -1., 0., 0.5, 1. };
      const std::vector< double > values = { 0., 1.0, 1.5, 2. };

      TabulatedAngularDistribution chunk( std::move( cosines ), std::move( values ) );

      THEN( "a TabulatedAngularDistribution can be constructed and members can "
            "be tested" ) {

        auto pdf = chunk.pdf();
        CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
        CHECK_THAT( -1.  , WithinRel( pdf.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( pdf.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( pdf.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( pdf.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( pdf.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( pdf.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( pdf.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( pdf.values()[3] ) );

        CHECK_THROWS( chunk.cdf() );
      } // THEN

      THEN( "a TabulatedAngularDistribution can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0. , WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 0.5, WithinRel( chunk(  0. ) ) );
        CHECK_THAT( 0.75, WithinRel( chunk( 0.5 ) ) );
        CHECK_THAT( 1. , WithinRel( chunk(  1. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( -5. ) ) );
        CHECK_THAT( 0., WithinRel( chunk(  5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.25 , WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 0.875, WithinRel( chunk(  0.75 ) ) );
      } // THEN

      THEN( "the average cosine can be calculated" ) {

        CHECK_THAT( 1. / 3., WithinRel( chunk.averageCosine() ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 4 == linear.pdf().numberPoints() );
        CHECK( 1 == linear.pdf().numberRegions() );

        CHECK( 4 == linear.pdf().cosines().size() );
        CHECK( 4 == linear.pdf().values().size() );
        CHECK( 1 == linear.pdf().boundaries().size() );
        CHECK( 1 == linear.pdf().interpolants().size() );

        CHECK( 3 == linear.pdf().boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.pdf().interpolants()[0] );

        CHECK_THAT( -1.  , WithinRel( linear.pdf().cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( linear.pdf().cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( linear.pdf().cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( linear.pdf().cosines()[3] ) );

        CHECK_THAT(  0.  , WithinRel( linear.pdf().values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( linear.pdf().values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( linear.pdf().values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( linear.pdf().values()[3] ) );

        CHECK( true == linear.pdf().isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the cosine and values vector are not of the same length" ) {

      THEN( "an exception is thrown" ) {

        const std::vector< double > cosines = { -1., 1. };
        const std::vector< double > values = { 0., 0.5, 0.75, 1. };

        CHECK_THROWS( TabulatedAngularDistribution( cosines, values ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
