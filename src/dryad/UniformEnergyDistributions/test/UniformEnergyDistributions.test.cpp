// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/UniformEnergyDistributions.hpp"

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

        auto cosines = chunk.averageEnergies();

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
        CHECK_THAT( 2.875, WithinRel( cosines.values()[0] ) );
        CHECK_THAT( 1.5  , WithinRel( cosines.values()[1] ) );
        CHECK_THAT( 5.   , WithinRel( cosines.values()[2] ) );
        CHECK_THAT( 7.5  , WithinRel( cosines.values()[3] ) );
        CHECK( 3 == cosines.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == cosines.interpolants()[0] );
        CHECK( true == cosines.isLinearised() );
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

    WHEN( "the x grid contains a triple x value" ) {

      const std::vector< double > grid = { 1., 2., 2., 2., 4. };
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

    WHEN( "the x grid has a jump at the beginning" ) {

      const std::vector< double > grid = { 1., 1., 3., 4. };
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

    WHEN( "the x grid has a jump at the end" ) {

      const std::vector< double > grid = { 1., 2., 4., 4. };
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
