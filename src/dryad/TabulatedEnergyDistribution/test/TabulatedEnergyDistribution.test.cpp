// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/TabulatedEnergyDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "TabulatedEnergyDistribution" ) {

  GIVEN( "Energies and probabilities for a normalised table" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 0., 2., 3., 4. };
      const std::vector< double > values = { 0., 0.25, 0.375, 0.5 };

      TabulatedEnergyDistribution chunk( std::move( energies ), std::move( values ) );

      THEN( "a TabulatedEnergyDistribution can be constructed and members can "
            "be tested" ) {

        auto pdf = chunk.pdf();
        CHECK_THAT(  0., WithinRel( pdf.lowerEnergyLimit() ) );
        CHECK_THAT(  4., WithinRel( pdf.upperEnergyLimit() ) );
        CHECK_THAT(  0.   , WithinRel( pdf.energies()[0] ) );
        CHECK_THAT(  2.   , WithinRel( pdf.energies()[1] ) );
        CHECK_THAT(  3.   , WithinRel( pdf.energies()[2] ) );
        CHECK_THAT(  4.   , WithinRel( pdf.energies()[3] ) );
        CHECK_THAT(  0.   , WithinRel( pdf.values()[0] ) );
        CHECK_THAT(  0.25 , WithinRel( pdf.values()[1] ) );
        CHECK_THAT(  0.375, WithinRel( pdf.values()[2] ) );
        CHECK_THAT(  0.5  , WithinRel( pdf.values()[3] ) );

        CHECK( std::nullopt == chunk.cdf() );
      } // THEN

      THEN( "a TabulatedEnergyDistribution can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.   , WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0.25 , WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 0.375, WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 0.5  , WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( -5. ) ) );
        CHECK_THAT( 0., WithinRel( chunk(  5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.125 , WithinRel( chunk( 1.  ) ) );
        CHECK_THAT( 0.4375, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "the average energy can be calculated" ) {

        CHECK_THAT( 64. / 24., WithinRel( chunk.averageEnergy() ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 4 == linear.pdf().numberPoints() );
        CHECK( 1 == linear.pdf().numberRegions() );

        CHECK( 4 == linear.pdf().energies().size() );
        CHECK( 4 == linear.pdf().values().size() );
        CHECK( 1 == linear.pdf().boundaries().size() );
        CHECK( 1 == linear.pdf().interpolants().size() );

        CHECK( 3 == linear.pdf().boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.pdf().interpolants()[0] );

        CHECK_THAT(  0.   , WithinRel( linear.pdf().energies()[0] ) );
        CHECK_THAT(  2.   , WithinRel( linear.pdf().energies()[1] ) );
        CHECK_THAT(  3.   , WithinRel( linear.pdf().energies()[2] ) );
        CHECK_THAT(  4.   , WithinRel( linear.pdf().energies()[3] ) );

        CHECK_THAT(  0.   , WithinRel( linear.pdf().values()[0] ) );
        CHECK_THAT(  0.25 , WithinRel( linear.pdf().values()[1] ) );
        CHECK_THAT(  0.375, WithinRel( linear.pdf().values()[2] ) );
        CHECK_THAT(  0.5  , WithinRel( linear.pdf().values()[3] ) );

        CHECK( true == linear.pdf().isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "Energies and probabilities for an unnormalised table" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 0., 2., 3., 4. };
      const std::vector< double > values = { 0., 0.5, 0.75, 1.0 };

      TabulatedEnergyDistribution chunk( std::move( energies ), std::move( values ) );

      THEN( "a TabulatedEnergyDistribution can be constructed and members can "
        "be tested" ) {

        auto pdf = chunk.pdf();
        CHECK_THAT(  0., WithinRel( pdf.lowerEnergyLimit() ) );
        CHECK_THAT(  4., WithinRel( pdf.upperEnergyLimit() ) );
        CHECK_THAT(  0.   , WithinRel( pdf.energies()[0] ) );
        CHECK_THAT(  2.   , WithinRel( pdf.energies()[1] ) );
        CHECK_THAT(  3.   , WithinRel( pdf.energies()[2] ) );
        CHECK_THAT(  4.   , WithinRel( pdf.energies()[3] ) );
        CHECK_THAT(  0.   , WithinRel( pdf.values()[0] ) );
        CHECK_THAT(  0.25 , WithinRel( pdf.values()[1] ) );
        CHECK_THAT(  0.375, WithinRel( pdf.values()[2] ) );
        CHECK_THAT(  0.5  , WithinRel( pdf.values()[3] ) );

        CHECK( std::nullopt == chunk.cdf() );
      } // THEN

      THEN( "a TabulatedEnergyDistribution can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.   , WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0.25 , WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 0.375, WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 0.5  , WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( -5. ) ) );
        CHECK_THAT( 0., WithinRel( chunk(  5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.125 , WithinRel( chunk( 1.  ) ) );
        CHECK_THAT( 0.4375, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "the average energy can be calculated" ) {

        CHECK_THAT( 64. / 24., WithinRel( chunk.averageEnergy() ) );
      } // THEN

      THEN( "a LegendreAngularDistribution can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 4 == linear.pdf().numberPoints() );
        CHECK( 1 == linear.pdf().numberRegions() );

        CHECK( 4 == linear.pdf().energies().size() );
        CHECK( 4 == linear.pdf().values().size() );
        CHECK( 1 == linear.pdf().boundaries().size() );
        CHECK( 1 == linear.pdf().interpolants().size() );

        CHECK( 3 == linear.pdf().boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.pdf().interpolants()[0] );

        CHECK_THAT(  0.   , WithinRel( linear.pdf().energies()[0] ) );
        CHECK_THAT(  2.   , WithinRel( linear.pdf().energies()[1] ) );
        CHECK_THAT(  3.   , WithinRel( linear.pdf().energies()[2] ) );
        CHECK_THAT(  4.   , WithinRel( linear.pdf().energies()[3] ) );

        CHECK_THAT(  0.   , WithinRel( linear.pdf().values()[0] ) );
        CHECK_THAT(  0.25 , WithinRel( linear.pdf().values()[1] ) );
        CHECK_THAT(  0.375, WithinRel( linear.pdf().values()[2] ) );
        CHECK_THAT(  0.5  , WithinRel( linear.pdf().values()[3] ) );

        CHECK( true == linear.pdf().isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the cosine and values vector are not of the same length" ) {

      THEN( "an exception is thrown" ) {

        const std::vector< double > energies = { -1., 1. };
        const std::vector< double > values = { 0., 0.5, 0.75, 1. };

        CHECK_THROWS( TabulatedEnergyDistribution( energies, values ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
