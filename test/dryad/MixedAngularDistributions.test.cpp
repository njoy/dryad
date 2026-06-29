// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/MixedAngularDistributions.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const MixedAngularDistributions&, bool );
void verifyChunkWithJump( const MixedAngularDistributions&, bool );

SCENARIO( "MixedAngularDistributions" ) {

  GIVEN( "distributions and energy values" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 1., 2., 3., 4. };
      std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1. } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      MixedAngularDistributions chunk1( energies, distributions, interpolant, false );
      MixedAngularDistributions chunk2( energies, distributions, interpolant, true );

      verifyChunk( chunk1, false );
      verifyChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyChunk( chunk1, true );
      verifyChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump that consist of more than 2 points" ) {

    // note: at construction time, the extraneous points in between the first and last
    //       x value in the jump are removed. boundaries always point to the first point
    //       in the jump

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 2., 2., 3., 4. };
      const std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1.0 } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.05 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.01 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } }
      };

      MixedAngularDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a MixedAngularDistributions can be constructed and members can be tested" ) {

        verifyChunkWithJump( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the beginning" ) {

    // note: at construction time, the first point is removed

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 1., 2., 3., 4. };
      const std::vector< MixedAngularDistribution > distributions = {

        { LegendreAngularDistributionFunction{ { 1.0, 0.01 } } },
        { IsotropicAngularDistributionFunction{ 1.0 } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } }
      };

      MixedAngularDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a MixedAngularDistributions can be constructed and members can be tested" ) {

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the end" ) {

    // note: at construction time, the last point is removed

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 3., 4., 4. };
      const std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1. } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.01 } } }
      };

      MixedAngularDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a MixedAngularDistributions can be constructed and members can be tested" ) {

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of MixedAngularDistributions are given" ) {

      MixedAngularDistributions left( { 1., 2., 3., 4. },
                                      { { LegendreAngularDistributionFunction{ { 0.5 } } },
                                        { LegendreAngularDistributionFunction{ { 0.5, 0.01 } } },
                                        { LegendreAngularDistributionFunction{ { 0.5, 0.1 } } },
                                        { LegendreAngularDistributionFunction{ { 0.5, 0.4 } } } } );
      MixedAngularDistributions equal( { 1., 2., 3., 4. },
                                       { { LegendreAngularDistributionFunction{ { 0.5 } } },
                                         { LegendreAngularDistributionFunction{ { 0.5, 0.01 } } },
                                         { LegendreAngularDistributionFunction{ { 0.5, 0.1 } } },
                                         { LegendreAngularDistributionFunction{ { 0.5, 0.4 } } } } );
      MixedAngularDistributions unnormalised( { 1., 2., 3., 4. },
                                              { { LegendreAngularDistributionFunction{ { 1. } } },
                                                { LegendreAngularDistributionFunction{ { 1., 0.02 } } },
                                                { LegendreAngularDistributionFunction{ { 1., 0.2 } } },
                                                { LegendreAngularDistributionFunction{ { 1., 0.8 } } } },
                                              InterpolationType::LinearLinear,
                                              true );
      MixedAngularDistributions different( { 1., 4. },
                                           { { LegendreAngularDistributionFunction{ { 0.5 } } },
                                             { LegendreAngularDistributionFunction{ { 0.5, 0.4 } } } } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( true == ( left == unnormalised ) ); // normalised under the hood, so equal
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( false == ( left != unnormalised ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an InterpolationTableFunction object" ) {

    WHEN( "there are not enough values in the x or f(y) grid" ) {

      std::vector< double > gempty = {};
      std::vector< double > gone = { 1. };
      std::vector< MixedAngularDistribution > dempty = {};
      std::vector< MixedAngularDistribution > done = { { LegendreAngularDistributionFunction{ { 0.5 } } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MixedAngularDistributions( gempty, dempty ) );
        CHECK_THROWS( MixedAngularDistributions( gone, done ) );
        CHECK_THROWS( MixedAngularDistributions( gempty, done ) );
        CHECK_THROWS( MixedAngularDistributions( gone, dempty ) );
      } // THEN
    } // WHEN

    WHEN( "the x and f(y) grid do not have the same number of points" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< MixedAngularDistribution > distributions = {

        { LegendreAngularDistributionFunction{ { 0.5 } } },
        { LegendreAngularDistributionFunction{ { 0.5, 0.01 } } },
        { LegendreAngularDistributionFunction{ { 0.5, 0.1 } } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MixedAngularDistributions( std::move( grid ),
                                                 std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1. } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } }
      };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MixedAngularDistributions( std::move( grid ),
                                                    std::move( distributions ),
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      const std::vector< double > grid = { 1., 3., 2., 4. };
      const std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1. } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MixedAngularDistributions( std::move( grid ),
                                                 std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1. } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } }
      };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MixedAngularDistributions( std::move( grid ),
                                                    std::move( distributions ),
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const MixedAngularDistributions& chunk, bool normalise ) {

  double normalisation = normalise ? 2.0 : 1.0;

  CHECK( 4 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 4 == chunk.grid().size() );
  CHECK( 4 == chunk.distributions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.grid()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.grid()[3] ) );

  CHECK( true == std::holds_alternative< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[1].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[3].pdf() ) );

  auto pdf0 = std::get< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() );
  auto pdf1 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[1].pdf() );
  auto pdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() );
  auto pdf3 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[3].pdf() );

  CHECK( 1.0 / normalisation == pdf0.value() );
  CHECK( 2 == pdf1.coefficients().size() );
  CHECK( 2 == pdf2.coefficients().size() );
  CHECK( 2 == pdf3.coefficients().size() );
  CHECK_THAT( 1.0  / normalisation, WithinRel( pdf1.coefficients()[0] ) );
  CHECK_THAT( 0.02 / normalisation, WithinRel( pdf1.coefficients()[1] ) );
  CHECK_THAT( 1.0  / normalisation, WithinRel( pdf2.coefficients()[0] ) );
  CHECK_THAT( 0.2  / normalisation, WithinRel( pdf2.coefficients()[1] ) );
  CHECK_THAT( 1.0  / normalisation, WithinRel( pdf3.coefficients()[0] ) );
  CHECK_THAT( 0.8  / normalisation, WithinRel( pdf3.coefficients()[1] ) );

  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[1].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[3].cdf() ) );

  auto cdf0 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() );
  auto cdf1 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[1].cdf() );
  auto cdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() );
  auto cdf3 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[3].cdf() );

  CHECK( 2 == cdf0.cosines().size() );
  CHECK( 2 == cdf0.values().size() );
  CHECK( 1 == cdf0.interpolants().size() );
  CHECK( 1 == cdf0.boundaries().size() );
  CHECK( 3 == cdf1.coefficients().size() );
  CHECK( 3 == cdf2.coefficients().size() );
  CHECK( 3 == cdf3.coefficients().size() );
  CHECK_THAT( -1., WithinRel( cdf0.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( cdf0.cosines()[1] ) );
  CHECK_THAT( 0.0                , WithinRel( cdf0.values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( cdf0.values()[1] ) );
  CHECK( 1 == cdf0.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf0.interpolants()[0] );
  CHECK_THAT( 0.9933333333333333 / normalisation, WithinRel( cdf1.coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( cdf1.coefficients()[1] ) );
  CHECK_THAT( 0.0066666666666666 / normalisation, WithinRel( cdf1.coefficients()[2] ) );
  CHECK_THAT( 0.9333333333333333 / normalisation, WithinRel( cdf2.coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( cdf2.coefficients()[1] ) );
  CHECK_THAT( 0.0666666666666666 / normalisation, WithinRel( cdf2.coefficients()[2] ) );
  CHECK_THAT( 0.7333333333333333 / normalisation, WithinRel( cdf3.coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( cdf3.coefficients()[1] ) );
  CHECK_THAT( 0.2666666666666666 / normalisation, WithinRel( cdf3.coefficients()[2] ) );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

  // evaluate

  // values of x in the x grid
  CHECK_THAT( 1.0  / normalisation, WithinRel( chunk( 1., -0.5 ) ) );
  CHECK_THAT( 0.99 / normalisation, WithinRel( chunk( 2., -0.5 ) ) );
  CHECK_THAT( 0.9  / normalisation, WithinRel( chunk( 3., -0.5 ) ) );
  CHECK_THAT( 0.6  / normalisation, WithinRel( chunk( 4., -0.5 ) ) );

  // values of x outside the x grid
  CHECK_THAT( 0., WithinRel( chunk( 0., -0.5 ) ) );
  CHECK_THAT( 0., WithinRel( chunk( 5., -0.5 ) ) );

  // values of x inside the x grid
  CHECK_THAT( 0.995 / normalisation, WithinRel( chunk( 1.5, -0.5 ) ) );
  CHECK_THAT( 0.945 / normalisation, WithinRel( chunk( 2.5, -0.5 ) ) );
  CHECK_THAT( 0.75  / normalisation, WithinRel( chunk( 3.5, -0.5 ) ) );

  // average cosine - always the mean value even for unnormalised distributions
  auto cosines = chunk.averageCosines();

  CHECK_THAT( 1., WithinRel( cosines.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( cosines.upperEnergyLimit() ) );
  CHECK( 4 == cosines.numberPoints() );
  CHECK( 1 == cosines.numberRegions() );
  CHECK( 4 == cosines.energies().size() );
  CHECK( 4 == cosines.values().size() );
  CHECK( 1 == cosines.boundaries().size() );
  CHECK( 1 == cosines.interpolants().size() );
  CHECK_THAT( 1., WithinRel( cosines.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( cosines.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( cosines.energies()[2] ) );
  CHECK_THAT( 4., WithinRel( cosines.energies()[3] ) );
  CHECK_THAT( 0.        / 2., WithinRel( cosines.values()[0] ) );
  CHECK_THAT( 0.04 / 3. / 2., WithinRel( cosines.values()[1] ) );
  CHECK_THAT( 0.4 / 3.  / 2., WithinRel( cosines.values()[2] ) );
  CHECK_THAT( 1.6 / 3.  / 2., WithinRel( cosines.values()[3] ) );
  CHECK( 3 == cosines.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cosines.interpolants()[0] );
  CHECK( true == cosines.isLinearised() );

  // linearisation
  auto linear = chunk.linearise();

  CHECK( 4 == linear.numberPoints() );
  CHECK( 1 == linear.numberRegions() );
  CHECK( 4 == linear.grid().size() );
  CHECK( 4 == linear.distributions().size() );
  CHECK( 1 == linear.boundaries().size() );
  CHECK( 1 == linear.interpolants().size() );
  CHECK_THAT( 1., WithinRel( linear.grid()[0] ) );
  CHECK_THAT( 2., WithinRel( linear.grid()[1] ) );
  CHECK_THAT( 3., WithinRel( linear.grid()[2] ) );
  CHECK_THAT( 4., WithinRel( linear.grid()[3] ) );
  CHECK( true == linear.distributions()[0].pdf().isLinearised() );
  CHECK( true == linear.distributions()[1].pdf().isLinearised() );
  CHECK( true == linear.distributions()[2].pdf().isLinearised() );
  CHECK( true == linear.distributions()[3].pdf().isLinearised() );
  CHECK( 2 == linear.distributions()[0].pdf().cosines().size() );
  CHECK( 2 == linear.distributions()[1].pdf().cosines().size() );
  CHECK( 2 == linear.distributions()[2].pdf().cosines().size() );
  CHECK( 2 == linear.distributions()[3].pdf().cosines().size() );
  CHECK( 2 == linear.distributions()[0].pdf().values().size() );
  CHECK( 2 == linear.distributions()[1].pdf().values().size() );
  CHECK( 2 == linear.distributions()[2].pdf().values().size() );
  CHECK( 2 == linear.distributions()[3].pdf().values().size() );
  CHECK_THAT( -1.0, WithinRel( linear.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  1.0, WithinRel( linear.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT( -1.0, WithinRel( linear.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT(  1.0, WithinRel( linear.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT( -1.0, WithinRel( linear.distributions()[2].pdf().cosines()[0] ) );
  CHECK_THAT(  1.0, WithinRel( linear.distributions()[2].pdf().cosines()[1] ) );
  CHECK_THAT( -1.0, WithinRel( linear.distributions()[3].pdf().cosines()[0] ) );
  CHECK_THAT(  1.0, WithinRel( linear.distributions()[3].pdf().cosines()[1] ) );
  CHECK_THAT(  1.0  / normalisation, WithinRel( linear.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  1.0  / normalisation, WithinRel( linear.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT(  0.98 / normalisation, WithinRel( linear.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  1.02 / normalisation, WithinRel( linear.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT(  0.8  / normalisation, WithinRel( linear.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT(  1.2  / normalisation, WithinRel( linear.distributions()[2].pdf().values()[1] ) );
  CHECK_THAT(  0.2  / normalisation, WithinRel( linear.distributions()[3].pdf().values()[0] ) );
  CHECK_THAT(  1.8  / normalisation, WithinRel( linear.distributions()[3].pdf().values()[1] ) );
  CHECK( true == linear.distributions()[0].cdf().isLinearised() );
  CHECK( true == linear.distributions()[1].cdf().isLinearised() );
  CHECK( true == linear.distributions()[2].cdf().isLinearised() );
  CHECK( true == linear.distributions()[3].cdf().isLinearised() );
  CHECK( 2 == linear.distributions()[0].cdf().cosines().size() );
  CHECK( 2 == linear.distributions()[1].cdf().cosines().size() );
  CHECK( 2 == linear.distributions()[2].cdf().cosines().size() );
  CHECK( 2 == linear.distributions()[3].cdf().cosines().size() );
  CHECK( 2 == linear.distributions()[0].cdf().values().size() );
  CHECK( 2 == linear.distributions()[1].cdf().values().size() );
  CHECK( 2 == linear.distributions()[2].cdf().values().size() );
  CHECK( 2 == linear.distributions()[3].cdf().values().size() );
  CHECK_THAT( -1.0, WithinRel( linear.distributions()[0].cdf().cosines()[0] ) );
  CHECK_THAT(  1.0, WithinRel( linear.distributions()[0].cdf().cosines()[1] ) );
  CHECK_THAT( -1.0, WithinRel( linear.distributions()[1].cdf().cosines()[0] ) );
  CHECK_THAT(  1.0, WithinRel( linear.distributions()[1].cdf().cosines()[1] ) );
  CHECK_THAT( -1.0, WithinRel( linear.distributions()[2].cdf().cosines()[0] ) );
  CHECK_THAT(  1.0, WithinRel( linear.distributions()[2].cdf().cosines()[1] ) );
  CHECK_THAT( -1.0, WithinRel( linear.distributions()[3].cdf().cosines()[0] ) );
  CHECK_THAT(  1.0, WithinRel( linear.distributions()[3].cdf().cosines()[1] ) );
  CHECK_THAT( 0.0 / normalisation, WithinRel( linear.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( linear.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT( 0.0 / normalisation, WithinRel( linear.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( linear.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT( 0.0 / normalisation, WithinRel( linear.distributions()[2].cdf().values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( linear.distributions()[2].cdf().values()[1] ) );
  CHECK_THAT( 0.0 / normalisation, WithinRel( linear.distributions()[3].cdf().values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( linear.distributions()[3].cdf().values()[1] ) );
  CHECK( 3 == linear.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
}

void verifyChunkWithJump( const MixedAngularDistributions& chunk, bool normalise ) {

  double normalisation = normalise ? 2.0 : 1.0;

  CHECK( 5 == chunk.numberPoints() );
  CHECK( 2 == chunk.numberRegions() );
  CHECK( 5 == chunk.grid().size() );
  CHECK( 5 == chunk.distributions().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.grid()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.grid()[4] ) );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

  CHECK( true == std::holds_alternative< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[1].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[3].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[4].pdf() ) );
}