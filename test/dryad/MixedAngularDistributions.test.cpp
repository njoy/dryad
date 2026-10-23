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
void verifyChunkWithJumpCurated( const MixedAngularDistributions& );
void verifyChunkWithJumpNotCurated( const MixedAngularDistributions& );
void verifyChunkWithDistributionJumpCurated( const MixedAngularDistributions& );
void verifyChunkWithDistributionJumpNotCurated( const MixedAngularDistributions& );
void verifyLinearisedChunkWithDistributionJump( const TabulatedAngularDistributions& );
void verifyLinearisedChunkWithJump( const TabulatedAngularDistributions& );

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

  GIVEN( "linearised data with a jump that consist of more than 2 points" ) {

    // note: by default (curate = false), the extraneous points in between the first and
    //       last x value in the jump are kept. boundaries always point to the first point
    //       in the jump, regardless of curation.

    WHEN( "the data is given explicitly and curate is not requested" ) {

      std::vector< double > grid = { 1., 2., 2., 2., 3., 4. };
      std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1.0 } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.05 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.01 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } }
      };

      MixedAngularDistributions chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a MixedAngularDistributions can be constructed and members can be tested" ) {

        verifyChunkWithJumpNotCurated( chunk );
      } // THEN

      THEN( "the table can be curated on demand and the extraneous points are removed" ) {

        chunk.curate();

        verifyChunkWithJumpCurated( chunk );
      } // THEN

      THEN( "the table can be linearised and the extraneous point in the jump is removed" ) {

        TabulatedAngularDistributions linear = chunk.linearise();

        verifyLinearisedChunkWithJump( linear );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and curate is requested" ) {

      std::vector< double > grid = { 1., 2., 2., 2., 3., 4. };
      std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1.0 } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.02 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.05 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.01 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } },
        { LegendreAngularDistributionFunction{ { 1.0, 0.8 } } }
      };

      MixedAngularDistributions chunk( std::move( grid ), std::move( distributions ),
                                       InterpolationType::LinearLinear, false, true );

      THEN( "a MixedAngularDistributions can be constructed and members can be tested" ) {

        verifyChunkWithJumpCurated( chunk );
      } // THEN

      THEN( "calling curate() again on an already curated table does not change anything" ) {

        chunk.curate();

        verifyChunkWithJumpCurated( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data with a jump that consist of more than 2 points in one of the distributions" ) {

    // note: by default (curate = false), the extraneous points in between the first and
    //       last x value in the jump of a distribution are kept. curation of the
    //       distributions removes them from both the pdf and the cdf of the tabulated
    //       distribution (the other distribution types are not affected).

    WHEN( "the data is given explicitly and curate is not requested" ) {

      std::vector< double > grid = { 1., 2., 3. };
      std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1. } },
        { TabulatedAngularDistributionFunction( { -1., -0.5, 0., 0., 0., +1. }, { 0., 1., 2., 3., 1., 2. } ) }, // <-- jump of 3 x values
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } }
      };

      MixedAngularDistributions chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a MixedAngularDistributions can be constructed and members can be tested" ) {

        verifyChunkWithDistributionJumpNotCurated( chunk );
      } // THEN

      THEN( "the table can be curated on demand and the extraneous points are removed" ) {

        chunk.curate();

        verifyChunkWithDistributionJumpCurated( chunk );
      } // THEN

      THEN( "the table can be linearised and the extraneous point in the jump is removed" ) {

        TabulatedAngularDistributions linear = chunk.linearise();

        verifyLinearisedChunkWithDistributionJump( linear );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and curate is requested" ) {

      std::vector< double > grid = { 1., 2., 3. };
      std::vector< MixedAngularDistribution > distributions = {

        { IsotropicAngularDistributionFunction{ 1. } },
        { TabulatedAngularDistributionFunction( { -1., -0.5, 0., 0., 0., +1. }, { 0., 1., 2., 3., 1., 2. } ) }, // <-- jump of 3 x values
        { LegendreAngularDistributionFunction{ { 1.0, 0.2 } } }
      };

      MixedAngularDistributions chunk( std::move( grid ), std::move( distributions ),
                                       InterpolationType::LinearLinear, false, true );

      THEN( "a MixedAngularDistributions can be constructed and members can be tested" ) {

        verifyChunkWithDistributionJumpCurated( chunk );
      } // THEN

      THEN( "calling curate() again on an already curated table does not change anything" ) {

        chunk.curate();

        verifyChunkWithDistributionJumpCurated( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the beginning" ) {

    // note: at construction time, the first point is removed

    WHEN( "the data is given explicitly" ) {

      std::vector< double > grid = { 1., 1., 2., 3., 4. };
      std::vector< MixedAngularDistribution > distributions = {

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

      std::vector< double > grid = { 1., 2., 3., 4., 4. };
      std::vector< MixedAngularDistribution > distributions = {

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

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< MixedAngularDistribution > distributions = {

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

      std::vector< double > grid = { 1., 3., 2., 4. };
      std::vector< MixedAngularDistribution > distributions = {

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

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< MixedAngularDistribution > distributions = {

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

void verifyChunkWithJumpCurated( const MixedAngularDistributions& chunk ) {

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

  auto pdf0 = std::get< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() );
  auto pdf1 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[1].pdf() );
  auto pdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() );
  auto pdf3 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[3].pdf() );
  auto pdf4 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[4].pdf() );

  CHECK( 1.0 == pdf0.value() );
  CHECK( 2 == pdf1.coefficients().size() );
  CHECK( 2 == pdf2.coefficients().size() );
  CHECK( 2 == pdf3.coefficients().size() );
  CHECK( 2 == pdf4.coefficients().size() );
  CHECK_THAT( 1.0 , WithinRel( pdf1.coefficients()[0] ) );
  CHECK_THAT( 0.02, WithinRel( pdf1.coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( pdf2.coefficients()[0] ) );
  CHECK_THAT( 0.01, WithinRel( pdf2.coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( pdf3.coefficients()[0] ) );
  CHECK_THAT( 0.2 , WithinRel( pdf3.coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( pdf4.coefficients()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( pdf4.coefficients()[1] ) );

  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[1].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[3].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[4].cdf() ) );

  auto cdf0 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() );
  auto cdf1 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[1].cdf() );
  auto cdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() );
  auto cdf3 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[3].cdf() );
  auto cdf4 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[4].cdf() );

  CHECK( 2 == cdf0.cosines().size() );
  CHECK( 2 == cdf0.values().size() );
  CHECK( 1 == cdf0.interpolants().size() );
  CHECK( 1 == cdf0.boundaries().size() );
  CHECK_THAT( -1., WithinRel( cdf0.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( cdf0.cosines()[1] ) );
  CHECK_THAT( 0.0, WithinRel( cdf0.values()[0] ) );
  CHECK_THAT( 2.0, WithinRel( cdf0.values()[1] ) );
  CHECK( 1 == cdf0.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf0.interpolants()[0] );
  CHECK( 3 == cdf1.coefficients().size() );
  CHECK( 3 == cdf2.coefficients().size() );
  CHECK( 3 == cdf3.coefficients().size() );
  CHECK( 3 == cdf4.coefficients().size() );
  CHECK_THAT( 1.0 - 0.02 / 3., WithinRel( cdf1.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf1.coefficients()[1] ) );
  CHECK_THAT( 0.02 / 3.      , WithinRel( cdf1.coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.01 / 3., WithinRel( cdf2.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf2.coefficients()[1] ) );
  CHECK_THAT( 0.01 / 3.      , WithinRel( cdf2.coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.2 / 3. , WithinRel( cdf3.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf3.coefficients()[1] ) );
  CHECK_THAT( 0.2 / 3.       , WithinRel( cdf3.coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.8 / 3. , WithinRel( cdf4.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf4.coefficients()[1] ) );
  CHECK_THAT( 0.8 / 3.       , WithinRel( cdf4.coefficients()[2] ) );
}

void verifyChunkWithJumpNotCurated( const MixedAngularDistributions& chunk ) {

  CHECK( 6 == chunk.numberPoints() );
  CHECK( 2 == chunk.numberRegions() );
  CHECK( 6 == chunk.grid().size() );
  CHECK( 6 == chunk.distributions().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[3] ) );
  CHECK_THAT( 3., WithinRel( chunk.grid()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.grid()[5] ) );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( 5 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

  CHECK( true == std::holds_alternative< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[1].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[3].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[4].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[5].pdf() ) );

  auto pdf0 = std::get< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() );
  auto pdf1 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[1].pdf() );
  auto pdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() );
  auto pdf3 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[3].pdf() );
  auto pdf4 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[4].pdf() );
  auto pdf5 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[5].pdf() );

  CHECK( 1.0 == pdf0.value() );
  CHECK( 2 == pdf1.coefficients().size() );
  CHECK( 2 == pdf2.coefficients().size() );
  CHECK( 2 == pdf3.coefficients().size() );
  CHECK( 2 == pdf4.coefficients().size() );
  CHECK( 2 == pdf5.coefficients().size() );
  CHECK_THAT( 1.0 , WithinRel( pdf1.coefficients()[0] ) );
  CHECK_THAT( 0.02, WithinRel( pdf1.coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( pdf2.coefficients()[0] ) );
  CHECK_THAT( 0.05, WithinRel( pdf2.coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( pdf3.coefficients()[0] ) );
  CHECK_THAT( 0.01, WithinRel( pdf3.coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( pdf4.coefficients()[0] ) );
  CHECK_THAT( 0.2 , WithinRel( pdf4.coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( pdf5.coefficients()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( pdf5.coefficients()[1] ) );

  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[1].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[3].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[4].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[5].cdf() ) );

  auto cdf0 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() );
  auto cdf1 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[1].cdf() );
  auto cdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() );
  auto cdf3 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[3].cdf() );
  auto cdf4 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[4].cdf() );
  auto cdf5 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[5].cdf() );

  CHECK( 2 == cdf0.cosines().size() );
  CHECK( 2 == cdf0.values().size() );
  CHECK( 1 == cdf0.interpolants().size() );
  CHECK( 1 == cdf0.boundaries().size() );
  CHECK_THAT( -1., WithinRel( cdf0.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( cdf0.cosines()[1] ) );
  CHECK_THAT( 0.0, WithinRel( cdf0.values()[0] ) );
  CHECK_THAT( 2.0, WithinRel( cdf0.values()[1] ) );
  CHECK( 1 == cdf0.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf0.interpolants()[0] );
  CHECK( 3 == cdf1.coefficients().size() );
  CHECK( 3 == cdf2.coefficients().size() );
  CHECK( 3 == cdf3.coefficients().size() );
  CHECK( 3 == cdf4.coefficients().size() );
  CHECK( 3 == cdf5.coefficients().size() );
  CHECK_THAT( 1.0 - 0.02 / 3., WithinRel( cdf1.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf1.coefficients()[1] ) );
  CHECK_THAT( 0.02 / 3.      , WithinRel( cdf1.coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.05 / 3., WithinRel( cdf2.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf2.coefficients()[1] ) );
  CHECK_THAT( 0.05 / 3.      , WithinRel( cdf2.coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.01 / 3., WithinRel( cdf3.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf3.coefficients()[1] ) );
  CHECK_THAT( 0.01 / 3.      , WithinRel( cdf3.coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.2 / 3. , WithinRel( cdf4.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf4.coefficients()[1] ) );
  CHECK_THAT( 0.2 / 3.       , WithinRel( cdf4.coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.8 / 3. , WithinRel( cdf5.coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( cdf5.coefficients()[1] ) );
  CHECK_THAT( 0.8 / 3.       , WithinRel( cdf5.coefficients()[2] ) );
}

void verifyLinearisedChunkWithJump( const TabulatedAngularDistributions& chunk ) {

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
  CHECK( true == chunk.distributions()[0].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[1].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[2].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[3].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[4].pdf().isLinearised() );
  CHECK( 2 == chunk.distributions()[0].pdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[4].pdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[4].pdf().values().size() );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[2].pdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[2].pdf().cosines()[1] ) );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[3].pdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[3].pdf().cosines()[1] ) );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[4].pdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[4].pdf().cosines()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( 0.98, WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( 1.02, WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 0.99, WithinRel( chunk.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT( 1.01, WithinRel( chunk.distributions()[2].pdf().values()[1] ) );
  CHECK_THAT( 0.8 , WithinRel( chunk.distributions()[3].pdf().values()[0] ) );
  CHECK_THAT( 1.2 , WithinRel( chunk.distributions()[3].pdf().values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( chunk.distributions()[4].pdf().values()[0] ) );
  CHECK_THAT( 1.8 , WithinRel( chunk.distributions()[4].pdf().values()[1] ) );
  CHECK( true == chunk.distributions()[0].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[1].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[2].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[3].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[4].cdf().isLinearised() );
  CHECK( 2 == chunk.distributions()[0].cdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[3].cdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[3].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[4].cdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[4].cdf().values().size() );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[0].cdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[0].cdf().cosines()[1] ) );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[1].cdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[1].cdf().cosines()[1] ) );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[2].cdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[2].cdf().cosines()[1] ) );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[3].cdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[3].cdf().cosines()[1] ) );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[4].cdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[4].cdf().cosines()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.distributions()[2].cdf().values()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.distributions()[2].cdf().values()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.distributions()[3].cdf().values()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.distributions()[3].cdf().values()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.distributions()[4].cdf().values()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.distributions()[4].cdf().values()[1] ) );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
}

void verifyChunkWithDistributionJumpCurated( const MixedAngularDistributions& chunk ) {

  CHECK( 3 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 3 == chunk.grid().size() );
  CHECK( 3 == chunk.distributions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.grid()[2] ) );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

  CHECK( true == std::holds_alternative< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[1].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[1].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() ) );

  auto pdf0 = std::get< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() );
  auto pdf1 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[1].pdf() );
  auto pdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() );
  auto cdf0 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() );
  auto cdf1 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[1].cdf() );
  auto cdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() );

  // distribution 0: isotropic (not affected by curation)
  CHECK_THAT( 1., WithinRel( pdf0.value() ) );
  CHECK( 2 == cdf0.cosines().size() );
  CHECK( 2 == cdf0.values().size() );
  CHECK( 1 == cdf0.boundaries().size() );
  CHECK( 1 == cdf0.interpolants().size() );
  CHECK_THAT( -1., WithinRel( cdf0.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( cdf0.cosines()[1] ) );
  CHECK_THAT( 0., WithinRel( cdf0.values()[0] ) );
  CHECK_THAT( 2., WithinRel( cdf0.values()[1] ) );
  CHECK( 1 == cdf0.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf0.interpolants()[0] );
  CHECK( true == cdf0.isLinearised() );
  CHECK( true == cdf0.isCurated() );

  // distribution 1: curated jump
  CHECK( 5 == pdf1.cosines().size() );
  CHECK( 5 == pdf1.values().size() );
  CHECK( 2 == pdf1.boundaries().size() );
  CHECK( 2 == pdf1.interpolants().size() );
  CHECK_THAT(  -1., WithinRel( pdf1.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( pdf1.cosines()[1] ) );
  CHECK_THAT(   0., WithinRel( pdf1.cosines()[2] ) );
  CHECK_THAT(   0., WithinRel( pdf1.cosines()[3] ) );
  CHECK_THAT(   1., WithinRel( pdf1.cosines()[4] ) );
  CHECK_THAT( 0., WithinRel( pdf1.values()[0] ) );
  CHECK_THAT( 1., WithinRel( pdf1.values()[1] ) );
  CHECK_THAT( 2., WithinRel( pdf1.values()[2] ) );
  CHECK_THAT( 1., WithinRel( pdf1.values()[3] ) );
  CHECK_THAT( 2., WithinRel( pdf1.values()[4] ) );
  CHECK( 2 == pdf1.boundaries()[0] );
  CHECK( 4 == pdf1.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == pdf1.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == pdf1.interpolants()[1] );
  CHECK( true == pdf1.isLinearised() );
  CHECK( true == pdf1.isCurated() );
  CHECK( 5 == cdf1.cosines().size() );
  CHECK( 5 == cdf1.values().size() );
  CHECK( 2 == cdf1.boundaries().size() );
  CHECK( 2 == cdf1.interpolants().size() );
  CHECK_THAT(  -1., WithinRel( cdf1.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( cdf1.cosines()[1] ) );
  CHECK_THAT(   0., WithinRel( cdf1.cosines()[2] ) );
  CHECK_THAT(   0., WithinRel( cdf1.cosines()[3] ) );
  CHECK_THAT(   1., WithinRel( cdf1.cosines()[4] ) );
  CHECK_THAT( 0.  , WithinRel( cdf1.values()[0] ) );
  CHECK_THAT( 0.25, WithinRel( cdf1.values()[1] ) );
  CHECK_THAT( 1.  , WithinRel( cdf1.values()[2] ) );
  CHECK_THAT( 1.  , WithinRel( cdf1.values()[3] ) );
  CHECK_THAT( 2.5 , WithinRel( cdf1.values()[4] ) );
  CHECK( 2 == cdf1.boundaries()[0] );
  CHECK( 4 == cdf1.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == cdf1.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == cdf1.interpolants()[1] );
  CHECK( true == cdf1.isLinearised() );
  CHECK( true == cdf1.isCurated() );

  // distribution 2: legendre (not affected by curation)
  CHECK( 2 == pdf2.coefficients().size() );
  CHECK_THAT( 1.0, WithinRel( pdf2.coefficients()[0] ) );
  CHECK_THAT( 0.2, WithinRel( pdf2.coefficients()[1] ) );
  CHECK( 3 == cdf2.coefficients().size() );
  CHECK_THAT( 1.0 - 0.2 / 3., WithinRel( cdf2.coefficients()[0] ) );
  CHECK_THAT( 1.0           , WithinRel( cdf2.coefficients()[1] ) );
  CHECK_THAT( 0.2 / 3.      , WithinRel( cdf2.coefficients()[2] ) );
}

void verifyChunkWithDistributionJumpNotCurated( const MixedAngularDistributions& chunk ) {

  CHECK( 3 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 3 == chunk.grid().size() );
  CHECK( 3 == chunk.distributions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.grid()[2] ) );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

  CHECK( true == std::holds_alternative< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[1].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[1].cdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() ) );

  auto pdf0 = std::get< IsotropicAngularDistributionFunction >( chunk.distributions()[0].pdf() );
  auto pdf1 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[1].pdf() );
  auto pdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].pdf() );
  auto cdf0 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[0].cdf() );
  auto cdf1 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[1].cdf() );
  auto cdf2 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[2].cdf() );

  // distribution 0: isotropic (not affected by curation)
  CHECK_THAT( 1., WithinRel( pdf0.value() ) );
  CHECK( 2 == cdf0.cosines().size() );
  CHECK( 2 == cdf0.values().size() );
  CHECK( 1 == cdf0.boundaries().size() );
  CHECK( 1 == cdf0.interpolants().size() );
  CHECK_THAT( -1., WithinRel( cdf0.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( cdf0.cosines()[1] ) );
  CHECK_THAT( 0., WithinRel( cdf0.values()[0] ) );
  CHECK_THAT( 2., WithinRel( cdf0.values()[1] ) );
  CHECK( 1 == cdf0.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf0.interpolants()[0] );
  CHECK( true == cdf0.isLinearised() );
  CHECK( true == cdf0.isCurated() );

  // distribution 1: tabulated with a uncurated jump
  CHECK( 6 == pdf1.cosines().size() );
  CHECK( 6 == pdf1.values().size() );
  CHECK( 2 == pdf1.boundaries().size() );
  CHECK( 2 == pdf1.interpolants().size() );
  CHECK_THAT(  -1., WithinRel( pdf1.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( pdf1.cosines()[1] ) );
  CHECK_THAT(   0., WithinRel( pdf1.cosines()[2] ) );
  CHECK_THAT(   0., WithinRel( pdf1.cosines()[3] ) );
  CHECK_THAT(   0., WithinRel( pdf1.cosines()[4] ) );
  CHECK_THAT(   1., WithinRel( pdf1.cosines()[5] ) );
  CHECK_THAT( 0., WithinRel( pdf1.values()[0] ) );
  CHECK_THAT( 1., WithinRel( pdf1.values()[1] ) );
  CHECK_THAT( 2., WithinRel( pdf1.values()[2] ) );
  CHECK_THAT( 3., WithinRel( pdf1.values()[3] ) );
  CHECK_THAT( 1., WithinRel( pdf1.values()[4] ) );
  CHECK_THAT( 2., WithinRel( pdf1.values()[5] ) );
  CHECK( 2 == pdf1.boundaries()[0] );
  CHECK( 5 == pdf1.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == pdf1.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == pdf1.interpolants()[1] );
  CHECK( true == pdf1.isLinearised() );
  CHECK( false == pdf1.isCurated() );
  CHECK( 6 == cdf1.cosines().size() );
  CHECK( 6 == cdf1.values().size() );
  CHECK( 2 == cdf1.boundaries().size() );
  CHECK( 2 == cdf1.interpolants().size() );
  CHECK_THAT(  -1., WithinRel( cdf1.cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( cdf1.cosines()[1] ) );
  CHECK_THAT(   0., WithinRel( cdf1.cosines()[2] ) );
  CHECK_THAT(   0., WithinRel( cdf1.cosines()[3] ) );
  CHECK_THAT(   0., WithinRel( cdf1.cosines()[4] ) );
  CHECK_THAT(   1., WithinRel( cdf1.cosines()[5] ) );
  CHECK_THAT( 0.  , WithinRel( cdf1.values()[0] ) );
  CHECK_THAT( 0.25, WithinRel( cdf1.values()[1] ) );
  CHECK_THAT( 1.  , WithinRel( cdf1.values()[2] ) );
  CHECK_THAT( 1.  , WithinRel( cdf1.values()[3] ) );
  CHECK_THAT( 1.  , WithinRel( cdf1.values()[4] ) );
  CHECK_THAT( 2.5 , WithinRel( cdf1.values()[5] ) );
  CHECK( 2 == cdf1.boundaries()[0] );
  CHECK( 5 == cdf1.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == cdf1.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == cdf1.interpolants()[1] );
  CHECK( true == cdf1.isLinearised() );
  CHECK( false == cdf1.isCurated() );

  // distribution 2: legendre (not affected by curation)
  CHECK( 2 == pdf2.coefficients().size() );
  CHECK_THAT( 1.0, WithinRel( pdf2.coefficients()[0] ) );
  CHECK_THAT( 0.2, WithinRel( pdf2.coefficients()[1] ) );
  CHECK( 3 == cdf2.coefficients().size() );
  CHECK_THAT( 1.0 - 0.2 / 3., WithinRel( cdf2.coefficients()[0] ) );
  CHECK_THAT( 1.0           , WithinRel( cdf2.coefficients()[1] ) );
  CHECK_THAT( 0.2 / 3.      , WithinRel( cdf2.coefficients()[2] ) );
}

void verifyLinearisedChunkWithDistributionJump( const TabulatedAngularDistributions& chunk ) {

  CHECK( 3 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 3 == chunk.grid().size() );
  CHECK( 3 == chunk.distributions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.grid()[2] ) );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

  // distribution 0: linearised isotropic distribution
  CHECK( 2 == chunk.distributions()[0].pdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 1 == chunk.distributions()[0].pdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[0].pdf().interpolants().size() );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[0].pdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[0].pdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[0].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[0].pdf().isCurated() );
  CHECK( 2 == chunk.distributions()[0].cdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 1 == chunk.distributions()[0].cdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[0].cdf().interpolants().size() );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[0].cdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[0].cdf().cosines()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[0].cdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[0].cdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[0].cdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[0].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[0].cdf().isCurated() );

  // distribution 1: curated jump
  CHECK( 5 == chunk.distributions()[1].pdf().cosines().size() );
  CHECK( 5 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().boundaries().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().interpolants().size() );
  CHECK_THAT(  -1., WithinRel( chunk.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( chunk.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT(   0., WithinRel( chunk.distributions()[1].pdf().cosines()[2] ) );
  CHECK_THAT(   0., WithinRel( chunk.distributions()[1].pdf().cosines()[3] ) );
  CHECK_THAT(   1., WithinRel( chunk.distributions()[1].pdf().cosines()[4] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().values()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[1].pdf().values()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().values()[4] ) );
  CHECK( 2 == chunk.distributions()[1].pdf().boundaries()[0] );
  CHECK( 4 == chunk.distributions()[1].pdf().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].pdf().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].pdf().interpolants()[1] );
  CHECK( true == chunk.distributions()[1].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[1].pdf().isCurated() );
  CHECK( 5 == chunk.distributions()[1].cdf().cosines().size() );
  CHECK( 5 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().boundaries().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().interpolants().size() );
  CHECK_THAT(  -1., WithinRel( chunk.distributions()[1].cdf().cosines()[0] ) );
  CHECK_THAT( -0.5, WithinRel( chunk.distributions()[1].cdf().cosines()[1] ) );
  CHECK_THAT(   0., WithinRel( chunk.distributions()[1].cdf().cosines()[2] ) );
  CHECK_THAT(   0., WithinRel( chunk.distributions()[1].cdf().cosines()[3] ) );
  CHECK_THAT(   1., WithinRel( chunk.distributions()[1].cdf().cosines()[4] ) );
  CHECK_THAT( 0.  , WithinRel( chunk.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT( 0.25, WithinRel( chunk.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT( 1.  , WithinRel( chunk.distributions()[1].cdf().values()[2] ) );
  CHECK_THAT( 1.  , WithinRel( chunk.distributions()[1].cdf().values()[3] ) );
  CHECK_THAT( 2.5 , WithinRel( chunk.distributions()[1].cdf().values()[4] ) );
  CHECK( 2 == chunk.distributions()[1].cdf().boundaries()[0] );
  CHECK( 4 == chunk.distributions()[1].cdf().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].cdf().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].cdf().interpolants()[1] );
  CHECK( true == chunk.distributions()[1].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[1].cdf().isCurated() );

  // distribution 2: linearised legendre distribution
  CHECK( 2 == chunk.distributions()[2].pdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().values().size() );
  CHECK( 1 == chunk.distributions()[2].pdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[2].pdf().interpolants().size() );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[2].pdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[2].pdf().cosines()[1] ) );
  CHECK_THAT( 0.8, WithinRel( chunk.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT( 1.2, WithinRel( chunk.distributions()[2].pdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[2].pdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[2].pdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[2].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[2].pdf().isCurated() );
  CHECK( 2 == chunk.distributions()[2].cdf().cosines().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().values().size() );
  CHECK( 1 == chunk.distributions()[2].cdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[2].cdf().interpolants().size() );
  CHECK_THAT( -1., WithinRel( chunk.distributions()[2].cdf().cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( chunk.distributions()[2].cdf().cosines()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].cdf().values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[2].cdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[2].cdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[2].cdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[2].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[2].cdf().isCurated() );
}
