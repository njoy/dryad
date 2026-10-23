// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/LegendreAngularDistributions.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const LegendreAngularDistributions&, bool );
void verifyChunkWithJumpCurated( const LegendreAngularDistributions& );
void verifyChunkWithJumpNotCurated( const LegendreAngularDistributions& );
void verifyLinearisedChunkWithJump( const TabulatedAngularDistributions& );

SCENARIO( "LegendreAngularDistributions" ) {

  GIVEN( "legendre series and energy values" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 1., 2., 3., 4. };
      std::vector< LegendreAngularDistribution > distributions = {

        { { 1.0 } },
        { { 1.0, 0.02 } },
        { { 1.0, 0.2 } },
        { { 1.0, 0.8 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      LegendreAngularDistributions chunk1( energies, distributions,
                                           interpolant, false );
      LegendreAngularDistributions chunk2( std::move( energies ), std::move( distributions ),
                                           interpolant, true );

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
      std::vector< LegendreAngularDistribution > distributions = {

        { { 1.0 } },
        { { 1.0, 0.02 } },
        { { 1.0, 0.05 } },
        { { 1.0, 0.01 } },
        { { 1.0, 0.2 } },
        { { 1.0, 0.8 } }
      };

      LegendreAngularDistributions chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a LegendreAngularDistributions can be constructed and members can be tested" ) {

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
      std::vector< LegendreAngularDistribution > distributions = {

        { { 1.0 } },
        { { 1.0, 0.02 } },
        { { 1.0, 0.05 } },
        { { 1.0, 0.01 } },
        { { 1.0, 0.2 } },
        { { 1.0, 0.8 } }
      };

      LegendreAngularDistributions chunk( std::move( grid ), std::move( distributions ),
                                          InterpolationType::LinearLinear, false, true );

      THEN( "a LegendreAngularDistributions can be constructed and members can be tested" ) {

        verifyChunkWithJumpCurated( chunk );
      } // THEN

      THEN( "calling curate() again on an already curated table does not change anything" ) {

        chunk.curate();

        verifyChunkWithJumpCurated( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the beginning" ) {

    // note: at construction time, the first point is removed

    WHEN( "the data is given explicitly" ) {

      std::vector< double > grid = { 1., 1., 2., 3., 4. };
      std::vector< LegendreAngularDistribution > distributions = {

        { { 1.0, 0.01 } },
        { { 1.0 } },
        { { 1.0, 0.02 } },
        { { 1.0, 0.2 } },
        { { 1.0, 0.8 } }
      };

      LegendreAngularDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a LegendreAngularDistributions can be constructed and members can be tested" ) {

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the end" ) {

    // note: at construction time, the last point is removed

    WHEN( "the data is given explicitly" ) {

      std::vector< double > grid = { 1., 2., 3., 4., 4. };
      std::vector< LegendreAngularDistribution > distributions = {

        { { 1.0 } },
        { { 1.0, 0.02 } },
        { { 1.0, 0.2 } },
        { { 1.0, 0.8 } },
        { { 1.0, 0.01 } }
      };

      LegendreAngularDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a LegendreAngularDistributions can be constructed and members can be tested" ) {

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of LegendreAngularDistributions are given" ) {

      LegendreAngularDistributions left( { 1., 2., 3., 4. },
                                         { { { 0.5 } },
                                           { { 0.5, 0.01 } },
                                           { { 0.5, 0.1 } },
                                           { { 0.5, 0.4 } } } );
      LegendreAngularDistributions equal( { 1., 2., 3., 4. },
                                          { { { 0.5 } },
                                            { { 0.5, 0.01 } },
                                            { { 0.5, 0.1 } },
                                            { { 0.5, 0.4 } } } );
      LegendreAngularDistributions unnormalised( { 1., 2., 3., 4. },
                                                 { { { 1.0 } },
                                                   { { 0.5, 0.01 } },
                                                   { { 0.5, 0.1 } },
                                                   { { 0.5, 0.4 } } },
                                                 InterpolationType::LinearLinear,
                                                 true );
      LegendreAngularDistributions different( { 1., 4. },
                                              { { { 0.5 } },
                                                { { 0.5, 0.4 } } } );

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
      std::vector< LegendreAngularDistribution > dempty = {};
      std::vector< LegendreAngularDistribution > done = { { { 0.5 } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreAngularDistributions( gempty, dempty ) );
        CHECK_THROWS( LegendreAngularDistributions( gone, done ) );
        CHECK_THROWS( LegendreAngularDistributions( gempty, done ) );
        CHECK_THROWS( LegendreAngularDistributions( gone, dempty ) );
      } // THEN
    } // WHEN

    WHEN( "the x and f(y) grid do not have the same number of points" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< LegendreAngularDistribution > distributions = {

        { { 0.5 } },
        { { 0.5, 0.01 } },
        { { 0.5, 0.1 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreAngularDistributions( std::move( grid ),
                                                    std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< LegendreAngularDistribution > distributions = {

        { { 0.5 } },
        { { 0.5, 0.01 } },
        { { 0.5, 0.1 } },
        { { 0.5, 0.4 } }
      };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreAngularDistributions( std::move( grid ),
                                                    std::move( distributions ),
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > grid = { 1., 3., 2., 4. };
      std::vector< LegendreAngularDistribution > distributions = {

        { { 0.5 } },
        { { 0.5, 0.01 } },
        { { 0.5, 0.1 } },
        { { 0.5, 0.4 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreAngularDistributions( std::move( grid ),
                                                    std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< LegendreAngularDistribution > distributions = {

        { { 0.5 } },
        { { 0.5, 0.01 } },
        { { 0.5, 0.1 } },
        { { 0.5, 0.4 } }
      };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreAngularDistributions( std::move( grid ),
                                                    std::move( distributions ),
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const LegendreAngularDistributions& chunk, bool normalise ) {

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
  CHECK( 1 == chunk.distributions()[0].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().coefficients().size() );
  CHECK_THAT( 1.0  / normalisation, WithinRel( chunk.distributions()[0].pdf().coefficients()[0] ) );
  CHECK_THAT( 1.0  / normalisation, WithinRel( chunk.distributions()[1].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.02 / normalisation, WithinRel( chunk.distributions()[1].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0  / normalisation, WithinRel( chunk.distributions()[2].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.2  / normalisation, WithinRel( chunk.distributions()[2].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0  / normalisation, WithinRel( chunk.distributions()[3].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.8  / normalisation, WithinRel( chunk.distributions()[3].pdf().coefficients()[1] ) );
  CHECK( 2 == chunk.distributions()[0].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[1].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[2].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[3].cdf().coefficients().size() );
  CHECK_THAT( 1.0                / normalisation, WithinRel( chunk.distributions()[0].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( chunk.distributions()[0].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.9933333333333333 / normalisation, WithinRel( chunk.distributions()[1].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( chunk.distributions()[1].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.0066666666666666 / normalisation, WithinRel( chunk.distributions()[1].cdf().coefficients()[2] ) );
  CHECK_THAT( 0.9333333333333333 / normalisation, WithinRel( chunk.distributions()[2].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( chunk.distributions()[2].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.0666666666666666 / normalisation, WithinRel( chunk.distributions()[2].cdf().coefficients()[2] ) );
  CHECK_THAT( 0.7333333333333333 / normalisation, WithinRel( chunk.distributions()[3].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( chunk.distributions()[3].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.2666666666666666 / normalisation, WithinRel( chunk.distributions()[3].cdf().coefficients()[2] ) );
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

void verifyChunkWithJumpCurated( const LegendreAngularDistributions& chunk ) {

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
  CHECK( 1 == chunk.distributions()[0].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[4].pdf().coefficients().size() );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[0].pdf().coefficients()[0] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[1].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.02, WithinRel( chunk.distributions()[1].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[2].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.01, WithinRel( chunk.distributions()[2].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[3].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.2 , WithinRel( chunk.distributions()[3].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[4].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( chunk.distributions()[4].pdf().coefficients()[1] ) );
  CHECK( 2 == chunk.distributions()[0].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[1].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[2].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[3].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[4].cdf().coefficients().size() );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[0].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[0].cdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 - 0.02 / 3., WithinRel( chunk.distributions()[1].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[1].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.02 / 3.      , WithinRel( chunk.distributions()[1].cdf().coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.01 / 3., WithinRel( chunk.distributions()[2].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[2].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.01 / 3.      , WithinRel( chunk.distributions()[2].cdf().coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.2 / 3. , WithinRel( chunk.distributions()[3].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[3].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.2 / 3.       , WithinRel( chunk.distributions()[3].cdf().coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.8 / 3. , WithinRel( chunk.distributions()[4].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[4].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.8 / 3.       , WithinRel( chunk.distributions()[4].cdf().coefficients()[2] ) );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
}

void verifyChunkWithJumpNotCurated( const LegendreAngularDistributions& chunk ) {

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
  CHECK( 1 == chunk.distributions()[0].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[4].pdf().coefficients().size() );
  CHECK( 2 == chunk.distributions()[5].pdf().coefficients().size() );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[0].pdf().coefficients()[0] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[1].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.02, WithinRel( chunk.distributions()[1].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[2].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.05, WithinRel( chunk.distributions()[2].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[3].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.01, WithinRel( chunk.distributions()[3].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[4].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.2 , WithinRel( chunk.distributions()[4].pdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 , WithinRel( chunk.distributions()[5].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( chunk.distributions()[5].pdf().coefficients()[1] ) );
  CHECK( 2 == chunk.distributions()[0].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[1].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[2].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[3].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[4].cdf().coefficients().size() );
  CHECK( 3 == chunk.distributions()[5].cdf().coefficients().size() );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[0].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[0].cdf().coefficients()[1] ) );
  CHECK_THAT( 1.0 - 0.02 / 3., WithinRel( chunk.distributions()[1].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[1].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.02 / 3.      , WithinRel( chunk.distributions()[1].cdf().coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.05 / 3., WithinRel( chunk.distributions()[2].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[2].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.05 / 3.      , WithinRel( chunk.distributions()[2].cdf().coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.01 / 3., WithinRel( chunk.distributions()[3].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[3].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.01 / 3.      , WithinRel( chunk.distributions()[3].cdf().coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.2 / 3. , WithinRel( chunk.distributions()[4].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[4].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.2 / 3.       , WithinRel( chunk.distributions()[4].cdf().coefficients()[2] ) );
  CHECK_THAT( 1.0 - 0.8 / 3. , WithinRel( chunk.distributions()[5].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0            , WithinRel( chunk.distributions()[5].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.8 / 3.       , WithinRel( chunk.distributions()[5].cdf().coefficients()[2] ) );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( 5 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
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