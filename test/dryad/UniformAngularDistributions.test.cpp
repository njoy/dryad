// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/UniformAngularDistributions.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "UniformAngularDistributions" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< UniformAngularDistribution > distributions = {

        { { -0.5, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
        { { -1., 0.8, 1. }, UniformDistributionType::Discrete }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      UniformAngularDistributions
      chunk( std::move( grid ), std::move( distributions ), interpolant );

      THEN( "a UniformAngularDistributions can be constructed and members can be tested" ) {

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
        CHECK_THAT( -0.5  , WithinRel( chunk.distributions()[0].cosines()[0] ) );
        CHECK_THAT(  0.5  , WithinRel( chunk.distributions()[0].cosines()[1] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[1].cosines()[0] ) );
        CHECK_THAT(  0.02, WithinRel( chunk.distributions()[1].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[1].cosines()[2] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[2].cosines()[0] ) );
        CHECK_THAT(  0.2 , WithinRel( chunk.distributions()[2].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[2].cosines()[2] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.distributions()[3].cosines()[0] ) );
        CHECK_THAT(  0.8 , WithinRel( chunk.distributions()[3].cosines()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.distributions()[3].cosines()[2] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN

      THEN( "average cosines can be calculated" ) {

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
        CHECK_THAT( 0.       , WithinRel( cosines.values()[0] ) );
        CHECK_THAT( 0.02 / 3., WithinRel( cosines.values()[1] ) );
        CHECK_THAT( 0.2 / 3. , WithinRel( cosines.values()[2] ) );
        CHECK_THAT( 0.8 / 3. , WithinRel( cosines.values()[3] ) );
        CHECK( 3 == cosines.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == cosines.interpolants()[0] );
        CHECK( true == cosines.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump that consist of more than 2 points" ) {

    // note: at construction time, the extraneous points in between the first and last
    //       x value in the jump are removed. boundaries always point to the first point
    //       in the jump

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 2., 2., 3., 4. };
      const std::vector< UniformAngularDistribution > distributions = {

        { { -0.5, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
        { { -0.9, 0.8, 0.9 }, UniformDistributionType::Discrete },
        { { -0.5, 1., 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
        { { -1., 0.8, 1. }, UniformDistributionType::Discrete }
      };

      UniformAngularDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a UniformAngularDistributions can be constructed and members can be tested" ) {
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
        CHECK_THAT( -0.5  , WithinRel( chunk.distributions()[0].cosines()[0] ) );
        CHECK_THAT(  0.5  , WithinRel( chunk.distributions()[0].cosines()[1] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[1].cosines()[0] ) );
        CHECK_THAT(  0.02, WithinRel( chunk.distributions()[1].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[1].cosines()[2] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[2].cosines()[0] ) );
        CHECK_THAT(  1.0 , WithinRel( chunk.distributions()[2].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[2].cosines()[2] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[3].cosines()[0] ) );
        CHECK_THAT(  0.2 , WithinRel( chunk.distributions()[3].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[3].cosines()[2] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.distributions()[4].cosines()[0] ) );
        CHECK_THAT(  0.8 , WithinRel( chunk.distributions()[4].cosines()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.distributions()[4].cosines()[2] ) );
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
      const std::vector< UniformAngularDistribution > distributions = {

        { { -0.5, 1., 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
        { { -1., 0.8, 1. }, UniformDistributionType::Discrete }
      };

      UniformAngularDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a UniformAngularDistributions can be constructed and members can be tested" ) {

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
        CHECK_THAT( -0.5  , WithinRel( chunk.distributions()[0].cosines()[0] ) );
        CHECK_THAT(  0.5  , WithinRel( chunk.distributions()[0].cosines()[1] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[1].cosines()[0] ) );
        CHECK_THAT(  0.02, WithinRel( chunk.distributions()[1].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[1].cosines()[2] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[2].cosines()[0] ) );
        CHECK_THAT(  0.2 , WithinRel( chunk.distributions()[2].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[2].cosines()[2] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.distributions()[3].cosines()[0] ) );
        CHECK_THAT(  0.8 , WithinRel( chunk.distributions()[3].cosines()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.distributions()[3].cosines()[2] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the end" ) {

    // note: at construction time, the last point is removed

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 3., 4., 4. };
      const std::vector< UniformAngularDistribution > distributions = {

        { { -0.5, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
        { { -1., 0.8, 1. }, UniformDistributionType::Discrete },
        { { -0.5, 1., 0.5 }, UniformDistributionType::Discrete }
      };

      UniformAngularDistributions
      chunk( std::move( grid ), std::move( distributions ) );

      THEN( "a UniformAngularDistributions can be constructed and members can be tested" ) {

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
        CHECK_THAT( -0.5  , WithinRel( chunk.distributions()[0].cosines()[0] ) );
        CHECK_THAT(  0.5  , WithinRel( chunk.distributions()[0].cosines()[1] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[1].cosines()[0] ) );
        CHECK_THAT(  0.02, WithinRel( chunk.distributions()[1].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[1].cosines()[2] ) );
        CHECK_THAT( -0.5 , WithinRel( chunk.distributions()[2].cosines()[0] ) );
        CHECK_THAT(  0.2 , WithinRel( chunk.distributions()[2].cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[2].cosines()[2] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.distributions()[3].cosines()[0] ) );
        CHECK_THAT(  0.8 , WithinRel( chunk.distributions()[3].cosines()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.distributions()[3].cosines()[2] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of UniformAngularDistributions are given" ) {

      UniformAngularDistributions left( { 1., 2., 3., 4. },
                                        { { { -0.5, 0.5 }, UniformDistributionType::Discrete },
                                          { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
                                          { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
                                          { { -1., 0.8, 1. }, UniformDistributionType::Discrete } } );
      UniformAngularDistributions equal( { 1., 2., 3., 4. },
                                         { { { -0.5, 0.5 }, UniformDistributionType::Discrete },
                                           { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
                                           { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
                                           { { -1., 0.8, 1. }, UniformDistributionType::Discrete } } );
      UniformAngularDistributions different(  { 1., 4. },
                                              { { { -0.5, 0.5 }, UniformDistributionType::Discrete },
                                                { { -1., 0.8, 1. }, UniformDistributionType::Discrete } } );

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

  GIVEN( "invalid data for a UniformAngularDistributions object" ) {

    WHEN( "there are not enough values in the x or f(y) grid" ) {

      std::vector< double > gempty = {};
      std::vector< double > gone = { 1. };
      std::vector< UniformAngularDistribution > dempty = {};
      std::vector< UniformAngularDistribution > done = { { { -0.5, 0.5 }, UniformDistributionType::Discrete } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformAngularDistributions( gempty, dempty ) );
        CHECK_THROWS( UniformAngularDistributions( gone, done ) );
        CHECK_THROWS( UniformAngularDistributions( gempty, done ) );
        CHECK_THROWS( UniformAngularDistributions( gone, dempty ) );
      } // THEN
    } // WHEN

    WHEN( "the x and f(y) grid do not have the same number of points" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< UniformAngularDistribution > distributions = {

        { { -0.5, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformAngularDistributions( std::move( grid ),
                                                   std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< UniformAngularDistribution > distributions = {

        { { -0.5, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
        { { -1., 0.8, 1. }, UniformDistributionType::Discrete }
      };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformAngularDistributions( std::move( grid ),
                                                   std::move( distributions ),
                                                   std::move( boundaries ),
                                                   std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      const std::vector< double > grid = { 1., 3., 2., 4. };
      const std::vector< UniformAngularDistribution > distributions = {

        { { -0.5, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
        { { -1., 0.8, 1. }, UniformDistributionType::Discrete }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformAngularDistributions( std::move( grid ),
                                                   std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< UniformAngularDistribution > distributions = {

        { { -0.5, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.02, 0.5 }, UniformDistributionType::Discrete },
        { { -0.5, 0.2, 0.5 }, UniformDistributionType::Discrete },
        { { -1., 0.8, 1. }, UniformDistributionType::Discrete }
      };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformAngularDistributions( std::move( grid ),
                                                   std::move( distributions ),
                                                   std::move( boundaries ),
                                                   std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
