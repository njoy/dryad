// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/TabulatedEnergyDistributions.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedEnergyDistributions&, bool );
void verifyChunkWithJumpCurated( const TabulatedEnergyDistributions& );
void verifyChunkWithJumpNotCurated( const TabulatedEnergyDistributions& );
void verifyChunkWithDistributionJumpCurated( const TabulatedEnergyDistributions& );
void verifyChunkWithDistributionJumpNotCurated( const TabulatedEnergyDistributions& );

SCENARIO( "TabulatedEnergyDistributions" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      TabulatedEnergyDistributions
      chunk1( grid, distributions, interpolant, false );
      TabulatedEnergyDistributions
      chunk2( std::move( grid ), std::move( distributions ), interpolant, true );

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
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.51, 0.49 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };

      TabulatedEnergyDistributions chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a TabulatedEnergyDistributions can be constructed and members can be tested" ) {

        verifyChunkWithJumpNotCurated( chunk );
      } // THEN

      THEN( "the table can be curated on demand and the extraneous points are removed" ) {

        chunk.curate();

        verifyChunkWithJumpCurated( chunk );
      } // THEN

      THEN( "the table can be linearised and the extraneous point in the jump is removed" ) {

        TabulatedEnergyDistributions linear = chunk.linearise();

        verifyChunkWithJumpCurated( linear );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and curate is requested" ) {

      std::vector< double > grid = { 1., 2., 2., 2., 3., 4. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.51, 0.49 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };

      TabulatedEnergyDistributions chunk( std::move( grid ), std::move( distributions ),
                                          InterpolationType::LinearLinear, false, true );

      THEN( "a TabulatedEnergyDistributions can be constructed and members can be tested" ) {

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
    //       distributions removes them from both the pdf and the cdf.

    WHEN( "the data is given explicitly and curate is not requested" ) {

      std::vector< double > grid = { 1., 2., 3. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 2., 2., 2., 4. }, { 0., 1., 2., 3., 1., 2. } }, // <-- jump of 3 x values
        { { 0., 4. }, { 0.2, 0.8 } }
      };

      TabulatedEnergyDistributions chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a TabulatedEnergyDistributions can be constructed and members can be tested" ) {

        verifyChunkWithDistributionJumpNotCurated( chunk );
      } // THEN

      THEN( "the table can be curated on demand and the extraneous points are removed" ) {

        chunk.curate();

        verifyChunkWithDistributionJumpCurated( chunk );
      } // THEN

      THEN( "the table can be linearised and the extraneous point in the jump is removed" ) {

        TabulatedEnergyDistributions linear = chunk.linearise();

        verifyChunkWithDistributionJumpCurated( linear );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and curate is requested" ) {

      std::vector< double > grid = { 1., 2., 3. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 2., 2., 2., 4. }, { 0., 1., 2., 3., 1., 2. } }, // <-- jump of 3 x values
        { { 0., 4. }, { 0.2, 0.8 } }
      };

      TabulatedEnergyDistributions chunk( std::move( grid ), std::move( distributions ),
                                          InterpolationType::LinearLinear, false, true );

      THEN( "a TabulatedEnergyDistributions can be constructed and members can be tested" ) {

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
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 1. }, { 0.1, 0.1 } },
        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };

      TabulatedEnergyDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a TabulatedEnergyDistributions can be constructed and members can be tested" ) {

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the end" ) {

    // note: at construction time, the last point is removed

    WHEN( "the data is given explicitly" ) {

      std::vector< double > grid = { 1., 2., 3., 4., 4. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } },
        { { 0., 1. }, { 0.1, 0.1 } }
      };

      TabulatedEnergyDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a TabulatedEnergyDistributions can be constructed and members can be tested" ) {

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedEnergyDistributions are given" ) {

      TabulatedEnergyDistributions left( { 1., 2., 3., 4. },
                                         { { { 1., 3. }, { 0.5, 0.5 } },
                                           { { 1., 3. }, { 0.49, 0.51 } },
                                           { { 1., 3. }, { 0.4, 0.6 } },
                                           { { 1., 3. }, { 0.1, 0.9 } } } );
      TabulatedEnergyDistributions equal( { 1., 2., 3., 4. },
                                          { { { 1., 3. }, { 0.5, 0.5 } },
                                            { { 1., 3. }, { 0.49, 0.51 } },
                                            { { 1., 3. }, { 0.4, 0.6 } },
                                            { { 1., 3. }, { 0.1, 0.9 } } } );
      TabulatedEnergyDistributions different( { 1., 4. },
                                              { { { 1., 3. }, { 0.5, 0.5 } },
                                                { { 1., 3. }, { 0.1, 0.9 } } } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an InterpolationTableFunction object" ) {

    WHEN( "there are not enough values in the x or f(y) grid" ) {

      std::vector< double > gempty = {};
      std::vector< double > gone = { 1. };
      std::vector< TabulatedEnergyDistribution > dempty = {};
      std::vector< TabulatedEnergyDistribution > done = { { { 0., 4. }, { 0.5, 0.5 } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedEnergyDistributions( gempty, dempty ) );
        CHECK_THROWS( TabulatedEnergyDistributions( gone, done ) );
        CHECK_THROWS( TabulatedEnergyDistributions( gempty, done ) );
        CHECK_THROWS( TabulatedEnergyDistributions( gone, dempty ) );
      } // THEN
    } // WHEN

    WHEN( "the x and f(y) grid do not have the same number of points" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedEnergyDistributions( std::move( grid ),
                                                    std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } },
        { { 0., 4. }, { 0.1, 0.9 } }
      };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedEnergyDistributions( std::move( grid ),
                                                    std::move( distributions ),
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > grid = { 1., 3., 2., 4. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } },
        { { 0., 4. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedEnergyDistributions( std::move( grid ),
                                                    std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } },
        { { 0., 4. }, { 0.1, 0.9 } }
      };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedEnergyDistributions( std::move( grid ),
                                                    std::move( distributions ),
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedEnergyDistributions& chunk, bool normalise ) {

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
  CHECK( 2 == chunk.distributions()[0].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().values().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[3].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[3].pdf().energies()[1] ) );
  CHECK_THAT( 0.5  / normalisation, WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 0.5  / normalisation, WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( 0.52 / normalisation, WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( 0.48 / normalisation, WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 0.48 / normalisation, WithinRel( chunk.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT( 0.52 / normalisation, WithinRel( chunk.distributions()[2].pdf().values()[1] ) );
  CHECK_THAT( 0.2  / normalisation, WithinRel( chunk.distributions()[3].pdf().values()[0] ) );
  CHECK_THAT( 0.8  / normalisation, WithinRel( chunk.distributions()[3].pdf().values()[1] ) );
  CHECK( 2 == chunk.distributions()[0].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[3].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[3].cdf().values().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[3].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[3].cdf().energies()[1] ) );
  CHECK_THAT( 0.0 / normalisation, WithinRel( chunk.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( chunk.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT( 0.0 / normalisation, WithinRel( chunk.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( chunk.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT( 0.0 / normalisation, WithinRel( chunk.distributions()[2].cdf().values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( chunk.distributions()[2].cdf().values()[1] ) );
  CHECK_THAT( 0.0 / normalisation, WithinRel( chunk.distributions()[3].cdf().values()[0] ) );
  CHECK_THAT( 2.0 / normalisation, WithinRel( chunk.distributions()[3].cdf().values()[1] ) );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

  // evaluate

  // values of x in the x grid
  CHECK_THAT( 0.5  / normalisation, WithinRel( chunk( 1., 3. ) ) );
  CHECK_THAT( 0.49 / normalisation, WithinRel( chunk( 2., 3. ) ) );
  CHECK_THAT( 0.51 / normalisation, WithinRel( chunk( 3., 3. ) ) );
  CHECK_THAT( 0.65 / normalisation, WithinRel( chunk( 4., 3. ) ) );

  // values of x outside the x grid
  CHECK_THAT( 0., WithinRel( chunk( 0., 3. ) ) );
  CHECK_THAT( 0., WithinRel( chunk( 5., 3. ) ) );

  // values of x inside the x grid
  CHECK_THAT( 0.495 / normalisation, WithinRel( chunk( 1.5, 3. ) ) );
  CHECK_THAT( 0.5   / normalisation, WithinRel( chunk( 2.5, 3. ) ) );
  CHECK_THAT( 0.58  / normalisation, WithinRel( chunk( 3.5, 3. ) ) );

  // average energy - always the mean value even for unnormalised distributions
  auto energies = chunk.averageEnergies();

  CHECK_THAT( 1., WithinRel( energies.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( energies.upperEnergyLimit() ) );
  CHECK( 4 == energies.numberPoints() );
  CHECK( 1 == energies.numberRegions() );
  CHECK( 4 == energies.energies().size() );
  CHECK( 4 == energies.values().size() );
  CHECK( 1 == energies.boundaries().size() );
  CHECK( 1 == energies.interpolants().size() );
  CHECK_THAT( 1., WithinRel( energies.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( energies.energies()[1] ) );
  CHECK_THAT( 3., WithinRel( energies.energies()[2] ) );
  CHECK_THAT( 4., WithinRel( energies.energies()[3] ) );
  CHECK_THAT( 2. * 2. / 2.          , WithinRel( energies.values()[0] ) );
  CHECK_THAT( 2. * 1184. / 600. / 2., WithinRel( energies.values()[1] ) );
  CHECK_THAT( 2. * 1216. / 600. / 2., WithinRel( energies.values()[2] ) );
  CHECK_THAT( 2. * 2.4          / 2., WithinRel( energies.values()[3] ) );
  CHECK( 3 == energies.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energies.interpolants()[0] );
  CHECK( true == energies.isLinearised() );

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
  CHECK( 2 == linear.distributions()[0].pdf().energies().size() );
  CHECK( 2 == linear.distributions()[1].pdf().energies().size() );
  CHECK( 2 == linear.distributions()[2].pdf().energies().size() );
  CHECK( 2 == linear.distributions()[3].pdf().energies().size() );
  CHECK( 2 == linear.distributions()[0].pdf().values().size() );
  CHECK( 2 == linear.distributions()[1].pdf().values().size() );
  CHECK( 2 == linear.distributions()[2].pdf().values().size() );
  CHECK( 2 == linear.distributions()[3].pdf().values().size() );
  CHECK_THAT( 0., WithinRel( linear.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.distributions()[2].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.distributions()[2].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.distributions()[3].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.distributions()[3].pdf().energies()[1] ) );
  CHECK_THAT( 0.5  / normalisation, WithinRel( linear.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 0.5  / normalisation, WithinRel( linear.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( 0.52 / normalisation, WithinRel( linear.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( 0.48 / normalisation, WithinRel( linear.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 0.48 / normalisation, WithinRel( linear.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT( 0.52 / normalisation, WithinRel( linear.distributions()[2].pdf().values()[1] ) );
  CHECK_THAT( 0.2  / normalisation, WithinRel( linear.distributions()[3].pdf().values()[0] ) );
  CHECK_THAT( 0.8  / normalisation, WithinRel( linear.distributions()[3].pdf().values()[1] ) );
  CHECK( true == linear.distributions()[0].cdf().isLinearised() );
  CHECK( true == linear.distributions()[1].cdf().isLinearised() );
  CHECK( true == linear.distributions()[2].cdf().isLinearised() );
  CHECK( true == linear.distributions()[3].cdf().isLinearised() );
  CHECK( 2 == linear.distributions()[0].cdf().energies().size() );
  CHECK( 2 == linear.distributions()[1].cdf().energies().size() );
  CHECK( 2 == linear.distributions()[2].cdf().energies().size() );
  CHECK( 2 == linear.distributions()[3].cdf().energies().size() );
  CHECK( 2 == linear.distributions()[0].cdf().values().size() );
  CHECK( 2 == linear.distributions()[1].cdf().values().size() );
  CHECK( 2 == linear.distributions()[2].cdf().values().size() );
  CHECK( 2 == linear.distributions()[3].cdf().values().size() );
  CHECK_THAT( 0., WithinRel( linear.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.distributions()[2].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.distributions()[2].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.distributions()[3].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.distributions()[3].cdf().energies()[1] ) );
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

void verifyChunkWithJumpCurated( const TabulatedEnergyDistributions& chunk ) {

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
  CHECK( 2 == chunk.distributions()[0].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[4].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[4].pdf().values().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[3].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[3].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[4].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[4].pdf().energies()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 0.51, WithinRel( chunk.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT( 0.49, WithinRel( chunk.distributions()[2].pdf().values()[1] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.distributions()[3].pdf().values()[0] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.distributions()[3].pdf().values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( chunk.distributions()[4].pdf().values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( chunk.distributions()[4].pdf().values()[1] ) );
  CHECK( 2 == chunk.distributions()[0].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[3].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[3].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[4].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[4].cdf().values().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[3].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[3].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[4].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[4].cdf().energies()[1] ) );
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

void verifyChunkWithJumpNotCurated( const TabulatedEnergyDistributions& chunk ) {

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
  CHECK( 2 == chunk.distributions()[0].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[3].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[4].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[4].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[5].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[5].pdf().values().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[3].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[3].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[4].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[4].pdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[5].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[5].pdf().energies()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[2].pdf().values()[1] ) );
  CHECK_THAT( 0.51, WithinRel( chunk.distributions()[3].pdf().values()[0] ) );
  CHECK_THAT( 0.49, WithinRel( chunk.distributions()[3].pdf().values()[1] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.distributions()[4].pdf().values()[0] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.distributions()[4].pdf().values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( chunk.distributions()[5].pdf().values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( chunk.distributions()[5].pdf().values()[1] ) );
  CHECK( 2 == chunk.distributions()[0].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[3].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[3].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[4].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[4].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[5].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[5].cdf().values().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[3].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[3].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[4].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[4].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[5].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[5].cdf().energies()[1] ) );
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
  CHECK_THAT( 0.0, WithinRel( chunk.distributions()[5].cdf().values()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.distributions()[5].cdf().values()[1] ) );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( 5 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
}

void verifyChunkWithDistributionJumpCurated( const TabulatedEnergyDistributions& chunk ) {

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

  // distribution 0: no jump
  CHECK( 2 == chunk.distributions()[0].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 1 == chunk.distributions()[0].pdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[0].pdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[0].pdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[0].pdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[0].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[0].pdf().isCurated() );
  CHECK( 2 == chunk.distributions()[0].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 1 == chunk.distributions()[0].cdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[0].cdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[0].cdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[0].cdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[0].cdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[0].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[0].cdf().isCurated() );

  // distribution 1: curated jump
  CHECK( 5 == chunk.distributions()[1].pdf().energies().size() );
  CHECK( 5 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().boundaries().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().energies()[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().energies()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].pdf().energies()[4] ) );
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
  CHECK( 5 == chunk.distributions()[1].cdf().energies().size() );
  CHECK( 5 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().boundaries().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].cdf().energies()[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].cdf().energies()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].cdf().energies()[4] ) );
  CHECK_THAT( 0. , WithinRel( chunk.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT( 2. , WithinRel( chunk.distributions()[1].cdf().values()[2] ) );
  CHECK_THAT( 2. , WithinRel( chunk.distributions()[1].cdf().values()[3] ) );
  CHECK_THAT( 5. , WithinRel( chunk.distributions()[1].cdf().values()[4] ) );
  CHECK( 2 == chunk.distributions()[1].cdf().boundaries()[0] );
  CHECK( 4 == chunk.distributions()[1].cdf().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].cdf().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].cdf().interpolants()[1] );
  CHECK( true == chunk.distributions()[1].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[1].cdf().isCurated() );

  // distribution 2: no jump
  CHECK( 2 == chunk.distributions()[2].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().values().size() );
  CHECK( 1 == chunk.distributions()[2].pdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[2].pdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].pdf().energies()[1] ) );
  CHECK_THAT( 0.2, WithinRel( chunk.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT( 0.8, WithinRel( chunk.distributions()[2].pdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[2].pdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[2].pdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[2].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[2].pdf().isCurated() );
  CHECK( 2 == chunk.distributions()[2].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().values().size() );
  CHECK( 1 == chunk.distributions()[2].cdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[2].cdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].cdf().values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[2].cdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[2].cdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[2].cdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[2].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[2].cdf().isCurated() );
}

void verifyChunkWithDistributionJumpNotCurated( const TabulatedEnergyDistributions& chunk ) {

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

  // distribution 0: no jump
  CHECK( 2 == chunk.distributions()[0].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].pdf().values().size() );
  CHECK( 1 == chunk.distributions()[0].pdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[0].pdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[0].pdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[0].pdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[0].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[0].pdf().isCurated() );
  CHECK( 2 == chunk.distributions()[0].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[0].cdf().values().size() );
  CHECK( 1 == chunk.distributions()[0].cdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[0].cdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[0].cdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[0].cdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[0].cdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[0].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[0].cdf().isCurated() );

  // distribution 1: uncurated jump
  CHECK( 6 == chunk.distributions()[1].pdf().energies().size() );
  CHECK( 6 == chunk.distributions()[1].pdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().boundaries().size() );
  CHECK( 2 == chunk.distributions()[1].pdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().energies()[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().energies()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().energies()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].pdf().energies()[5] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().values()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.distributions()[1].pdf().values()[3] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[1].pdf().values()[4] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].pdf().values()[5] ) );
  CHECK( 2 == chunk.distributions()[1].pdf().boundaries()[0] );
  CHECK( 5 == chunk.distributions()[1].pdf().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].pdf().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].pdf().interpolants()[1] );
  CHECK( true == chunk.distributions()[1].pdf().isLinearised() );
  CHECK( false == chunk.distributions()[1].pdf().isCurated() );
  CHECK( 6 == chunk.distributions()[1].cdf().energies().size() );
  CHECK( 6 == chunk.distributions()[1].cdf().values().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().boundaries().size() );
  CHECK( 2 == chunk.distributions()[1].cdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].cdf().energies()[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].cdf().energies()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[1].cdf().energies()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[1].cdf().energies()[5] ) );
  CHECK_THAT( 0. , WithinRel( chunk.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT( 2. , WithinRel( chunk.distributions()[1].cdf().values()[2] ) );
  CHECK_THAT( 2. , WithinRel( chunk.distributions()[1].cdf().values()[3] ) );
  CHECK_THAT( 2. , WithinRel( chunk.distributions()[1].cdf().values()[4] ) );
  CHECK_THAT( 5. , WithinRel( chunk.distributions()[1].cdf().values()[5] ) );
  CHECK( 2 == chunk.distributions()[1].cdf().boundaries()[0] );
  CHECK( 5 == chunk.distributions()[1].cdf().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].cdf().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[1].cdf().interpolants()[1] );
  CHECK( true == chunk.distributions()[1].cdf().isLinearised() );
  CHECK( false == chunk.distributions()[1].cdf().isCurated() );

  // distribution 2: no jump
  CHECK( 2 == chunk.distributions()[2].pdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].pdf().values().size() );
  CHECK( 1 == chunk.distributions()[2].pdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[2].pdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].pdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].pdf().energies()[1] ) );
  CHECK_THAT( 0.2, WithinRel( chunk.distributions()[2].pdf().values()[0] ) );
  CHECK_THAT( 0.8, WithinRel( chunk.distributions()[2].pdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[2].pdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[2].pdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[2].pdf().isLinearised() );
  CHECK( true == chunk.distributions()[2].pdf().isCurated() );
  CHECK( 2 == chunk.distributions()[2].cdf().energies().size() );
  CHECK( 2 == chunk.distributions()[2].cdf().values().size() );
  CHECK( 1 == chunk.distributions()[2].cdf().boundaries().size() );
  CHECK( 1 == chunk.distributions()[2].cdf().interpolants().size() );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].cdf().energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.distributions()[2].cdf().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.distributions()[2].cdf().values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.distributions()[2].cdf().values()[1] ) );
  CHECK( 1 == chunk.distributions()[2].cdf().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.distributions()[2].cdf().interpolants()[0] );
  CHECK( true == chunk.distributions()[2].cdf().isLinearised() );
  CHECK( true == chunk.distributions()[2].cdf().isCurated() );
}
