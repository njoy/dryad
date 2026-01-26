// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/UniformEnergyDistributions.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "UniformEnergyDistributions" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< UniformEnergyDistribution > distributions = {

        { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
        { { 1., 2. }, UniformDistributionType::Discrete },
        { { 3., 5., 7. }, UniformDistributionType::Discrete },
        { { 5., 10. }, UniformDistributionType::Discrete }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      UniformEnergyDistributions
      chunk( std::move( grid ), std::move( distributions ), interpolant );

      THEN( "a UniformEnergyDistributions can be constructed and members can be tested" ) {

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
        CHECK_THAT(  0.5, WithinRel( chunk.distributions()[0].energies()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.distributions()[0].energies()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.distributions()[0].energies()[2] ) );
        CHECK_THAT(  6. , WithinRel( chunk.distributions()[0].energies()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.distributions()[1].energies()[0] ) );
        CHECK_THAT(  2. , WithinRel( chunk.distributions()[1].energies()[1] ) );
        CHECK_THAT(  3. , WithinRel( chunk.distributions()[2].energies()[0] ) );
        CHECK_THAT(  5. , WithinRel( chunk.distributions()[2].energies()[1] ) );
        CHECK_THAT(  7. , WithinRel( chunk.distributions()[2].energies()[2] ) );
        CHECK_THAT(  5. , WithinRel( chunk.distributions()[3].energies()[0] ) );
        CHECK_THAT( 10. , WithinRel( chunk.distributions()[3].energies()[1] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN

      THEN( "average energies can be calculated" ) {

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
        CHECK_THAT( 2.875, WithinRel( energies.values()[0] ) );
        CHECK_THAT( 1.5  , WithinRel( energies.values()[1] ) );
        CHECK_THAT( 5.   , WithinRel( energies.values()[2] ) );
        CHECK_THAT( 7.5  , WithinRel( energies.values()[3] ) );
        CHECK( 3 == energies.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == energies.interpolants()[0] );
        CHECK( true == energies.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump that consist of more than 2 points" ) {

    // note: at construction time, the extraneous points in between the first and last
    //       x value in the jump are removed. boundaries always point to the first point
    //       in the jump

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 2., 2., 3., 4. };
      const std::vector< UniformEnergyDistribution > distributions = {

        { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
        { { 1., 2. }, UniformDistributionType::Discrete },
        { { 2., 4., 6. }, UniformDistributionType::Discrete },
        { { 4., 6., 8. }, UniformDistributionType::Discrete },
        { { 3., 5., 7. }, UniformDistributionType::Discrete },
        { { 5., 10. }, UniformDistributionType::Discrete }
      };

      UniformEnergyDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a UniformEnergyDistributions can be constructed and members can be tested" ) {

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
        CHECK_THAT(  0.5, WithinRel( chunk.distributions()[0].energies()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.distributions()[0].energies()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.distributions()[0].energies()[2] ) );
        CHECK_THAT(  6. , WithinRel( chunk.distributions()[0].energies()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.distributions()[1].energies()[0] ) );
        CHECK_THAT(  2. , WithinRel( chunk.distributions()[1].energies()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.distributions()[2].energies()[0] ) );
        CHECK_THAT(  6. , WithinRel( chunk.distributions()[2].energies()[1] ) );
        CHECK_THAT(  8. , WithinRel( chunk.distributions()[2].energies()[2] ) );
        CHECK_THAT(  3. , WithinRel( chunk.distributions()[3].energies()[0] ) );
        CHECK_THAT(  5. , WithinRel( chunk.distributions()[3].energies()[1] ) );
        CHECK_THAT(  7. , WithinRel( chunk.distributions()[3].energies()[2] ) );
        CHECK_THAT(  5. , WithinRel( chunk.distributions()[4].energies()[0] ) );
        CHECK_THAT( 10. , WithinRel( chunk.distributions()[4].energies()[1] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the beginning" ) {

    // note: at construction time, the first point is removed

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 1., 2., 3., 4. };
      const std::vector< UniformEnergyDistribution > distributions = {

        { { 2., 4., 6. }, UniformDistributionType::Discrete },
        { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
        { { 1., 2. }, UniformDistributionType::Discrete },
        { { 3., 5., 7. }, UniformDistributionType::Discrete },
        { { 5., 10. }, UniformDistributionType::Discrete }
      };

      UniformEnergyDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a UniformEnergyDistributions can be constructed and members can be tested" ) {

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
        CHECK_THAT(  0.5, WithinRel( chunk.distributions()[0].energies()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.distributions()[0].energies()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.distributions()[0].energies()[2] ) );
        CHECK_THAT(  6. , WithinRel( chunk.distributions()[0].energies()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.distributions()[1].energies()[0] ) );
        CHECK_THAT(  2. , WithinRel( chunk.distributions()[1].energies()[1] ) );
        CHECK_THAT(  3. , WithinRel( chunk.distributions()[2].energies()[0] ) );
        CHECK_THAT(  5. , WithinRel( chunk.distributions()[2].energies()[1] ) );
        CHECK_THAT(  7. , WithinRel( chunk.distributions()[2].energies()[2] ) );
        CHECK_THAT(  5. , WithinRel( chunk.distributions()[3].energies()[0] ) );
        CHECK_THAT( 10. , WithinRel( chunk.distributions()[3].energies()[1] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the end" ) {

    // note: at construction time, the last point is removed

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 3., 4., 4. };
      const std::vector< UniformEnergyDistribution > distributions = {

        { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
        { { 1., 2. }, UniformDistributionType::Discrete },
        { { 3., 5., 7. }, UniformDistributionType::Discrete },
        { { 5., 10. }, UniformDistributionType::Discrete },
        { { 2., 4., 6. }, UniformDistributionType::Discrete }
      };

      UniformEnergyDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a UniformEnergyDistributions can be constructed and members can be tested" ) {

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
        CHECK_THAT(  0.5, WithinRel( chunk.distributions()[0].energies()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.distributions()[0].energies()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.distributions()[0].energies()[2] ) );
        CHECK_THAT(  6. , WithinRel( chunk.distributions()[0].energies()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.distributions()[1].energies()[0] ) );
        CHECK_THAT(  2. , WithinRel( chunk.distributions()[1].energies()[1] ) );
        CHECK_THAT(  3. , WithinRel( chunk.distributions()[2].energies()[0] ) );
        CHECK_THAT(  5. , WithinRel( chunk.distributions()[2].energies()[1] ) );
        CHECK_THAT(  7. , WithinRel( chunk.distributions()[2].energies()[2] ) );
        CHECK_THAT(  5. , WithinRel( chunk.distributions()[3].energies()[0] ) );
        CHECK_THAT( 10. , WithinRel( chunk.distributions()[3].energies()[1] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of UniformEnergyDistributions are given" ) {

      UniformEnergyDistributions left( { 1., 2., 3., 4. },
                                       { { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
                                         { { 1., 2. }, UniformDistributionType::Discrete },
                                         { { 3., 5., 7. }, UniformDistributionType::Discrete },
                                         { { 5., 10. }, UniformDistributionType::Discrete } } );
      UniformEnergyDistributions equal( { 1., 2., 3., 4. },
                                        { { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
                                          { { 1., 2. }, UniformDistributionType::Discrete },
                                          { { 3., 5., 7. }, UniformDistributionType::Discrete },
                                          { { 5., 10. }, UniformDistributionType::Discrete } } );
      UniformEnergyDistributions different(  { 1., 4. },
                                             { { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
                                               { { 5., 10. }, UniformDistributionType::Discrete } } );

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

  GIVEN( "invalid data for a UniformEnergyDistributions object" ) {

    WHEN( "there are not enough values in the x or f(y) grid" ) {

      std::vector< double > gempty = {};
      std::vector< double > gone = { 1. };
      std::vector< UniformEnergyDistribution > dempty = {};
      std::vector< UniformEnergyDistribution > done = { { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformEnergyDistributions( gempty, dempty ) );
        CHECK_THROWS( UniformEnergyDistributions( gone, done ) );
        CHECK_THROWS( UniformEnergyDistributions( gempty, done ) );
        CHECK_THROWS( UniformEnergyDistributions( gone, dempty ) );
      } // THEN
    } // WHEN

    WHEN( "the x and f(y) grid do not have the same number of points" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< UniformEnergyDistribution > distributions = {

        { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
        { { 1., 2. }, UniformDistributionType::Discrete },
        { { 3., 5., 7. }, UniformDistributionType::Discrete }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformEnergyDistributions( std::move( grid ),
                                                  std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< UniformEnergyDistribution > distributions = {

        { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
        { { 1., 2. }, UniformDistributionType::Discrete },
        { { 3., 5., 7. }, UniformDistributionType::Discrete },
        { { 5., 10. }, UniformDistributionType::Discrete }
      };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformEnergyDistributions( std::move( grid ),
                                                  std::move( distributions ),
                                                  std::move( boundaries ),
                                                  std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      const std::vector< double > grid = { 1., 3., 2., 4. };
      const std::vector< UniformEnergyDistribution > distributions = {

        { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
        { { 1., 2. }, UniformDistributionType::Discrete },
        { { 3., 5., 7. }, UniformDistributionType::Discrete },
        { { 5., 10. }, UniformDistributionType::Discrete }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformEnergyDistributions( std::move( grid ),
                                                  std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< UniformEnergyDistribution > distributions = {

        { { 0.5, 1., 4., 6. }, UniformDistributionType::Discrete },
        { { 1., 2. }, UniformDistributionType::Discrete },
        { { 3., 5., 7. }, UniformDistributionType::Discrete },
        { { 5., 10. }, UniformDistributionType::Discrete }
      };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformEnergyDistributions( std::move( grid ),
                                                  std::move( distributions ),
                                                  std::move( boundaries ),
                                                  std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
