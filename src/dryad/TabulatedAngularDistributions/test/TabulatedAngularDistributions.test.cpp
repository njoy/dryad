// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/TabulatedAngularDistributions.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "TabulatedAngularDistributions" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< TabulatedAngularDistribution > distributions = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., +1. }, { 0.49, 0.51 } },
        { { -1., +1. }, { 0.4, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      TabulatedAngularDistributions
      chunk( std::move( grid ), std::move( distributions ), interpolant );

      THEN( "a TabulatedAngularDistributions can be constructed and members can be tested" ) {

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
        CHECK( 2 == chunk.distributions()[0].pdf().cosines().size() );
        CHECK( 2 == chunk.distributions()[0].pdf().values().size() );
        CHECK( 2 == chunk.distributions()[1].pdf().cosines().size() );
        CHECK( 2 == chunk.distributions()[1].pdf().values().size() );
        CHECK( 2 == chunk.distributions()[2].pdf().cosines().size() );
        CHECK( 2 == chunk.distributions()[2].pdf().values().size() );
        CHECK( 2 == chunk.distributions()[3].pdf().cosines().size() );
        CHECK( 2 == chunk.distributions()[3].pdf().values().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.distributions()[0].pdf().cosines()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.distributions()[0].pdf().cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[0].pdf().values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.distributions()[0].pdf().values()[1] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.distributions()[1].pdf().cosines()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.distributions()[1].pdf().cosines()[1] ) );
        CHECK_THAT(  0.49, WithinRel( chunk.distributions()[1].pdf().values()[0] ) );
        CHECK_THAT(  0.51, WithinRel( chunk.distributions()[1].pdf().values()[1] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.distributions()[2].pdf().cosines()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.distributions()[2].pdf().cosines()[1] ) );
        CHECK_THAT(  0.4 , WithinRel( chunk.distributions()[2].pdf().values()[0] ) );
        CHECK_THAT(  0.6 , WithinRel( chunk.distributions()[2].pdf().values()[1] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.distributions()[3].pdf().cosines()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.distributions()[3].pdf().cosines()[1] ) );
        CHECK_THAT(  0.1 , WithinRel( chunk.distributions()[3].pdf().values()[0] ) );
        CHECK_THAT(  0.9 , WithinRel( chunk.distributions()[3].pdf().values()[1] ) );
        CHECK( std::nullopt == chunk.distributions()[0].cdf() );
        CHECK( std::nullopt == chunk.distributions()[1].cdf() );
        CHECK( std::nullopt == chunk.distributions()[2].cdf() );
        CHECK( std::nullopt == chunk.distributions()[3].cdf() );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN

      THEN( "a TabulatedAngularDistributions can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.5  , WithinRel( chunk( 1., -0.5 ) ) );
        CHECK_THAT( 0.495, WithinRel( chunk( 2., -0.5 ) ) );
        CHECK_THAT( 0.45 , WithinRel( chunk( 3., -0.5 ) ) );
        CHECK_THAT( 0.3  , WithinRel( chunk( 4., -0.5 ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0., -0.5 ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5., -0.5 ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.4975, WithinRel( chunk( 1.5, -0.5 ) ) );
        CHECK_THAT( 0.4725, WithinRel( chunk( 2.5, -0.5 ) ) );
        CHECK_THAT( 0.375 , WithinRel( chunk( 3.5, -0.5 ) ) );
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
      }

      THEN( "a TabulatedAngularDistributions can be linearised" ) {

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
        CHECK_THAT(  0.5 , WithinRel( linear.distributions()[0].pdf().values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( linear.distributions()[0].pdf().values()[1] ) );
        CHECK_THAT(  0.49, WithinRel( linear.distributions()[1].pdf().values()[0] ) );
        CHECK_THAT(  0.51, WithinRel( linear.distributions()[1].pdf().values()[1] ) );
        CHECK_THAT(  0.4 , WithinRel( linear.distributions()[2].pdf().values()[0] ) );
        CHECK_THAT(  0.6 , WithinRel( linear.distributions()[2].pdf().values()[1] ) );
        CHECK_THAT(  0.1 , WithinRel( linear.distributions()[3].pdf().values()[0] ) );
        CHECK_THAT(  0.9 , WithinRel( linear.distributions()[3].pdf().values()[1] ) );
        CHECK( std::nullopt == linear.distributions()[0].cdf() );
        CHECK( std::nullopt == linear.distributions()[1].cdf() );
        CHECK( std::nullopt == linear.distributions()[2].cdf() );
        CHECK( std::nullopt == linear.distributions()[3].cdf() );
        CHECK( 3 == linear.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedAngularDistributions are given" ) {

      TabulatedAngularDistributions left( { 1., 2., 3., 4. },
                                          { { { -1., +1. }, { 0.5, 0.5 } },
                                            { { -1., +1. }, { 0.49, 0.51 } },
                                            { { -1., +1. }, { 0.4, 0.6 } },
                                            { { -1., +1. }, { 0.1, 0.9 } } } );
      TabulatedAngularDistributions equal( { 1., 2., 3., 4. },
                                           { { { -1., +1. }, { 0.5, 0.5 } },
                                             { { -1., +1. }, { 0.49, 0.51 } },
                                             { { -1., +1. }, { 0.4, 0.6 } },
                                             { { -1., +1. }, { 0.1, 0.9 } } } );
      TabulatedAngularDistributions unnormalised( { 1., 2., 3., 4. },
                                                  { { { -1., +1. }, { 1.0, 1.0 } },
                                                    { { -1., +1. }, { 0.49, 0.51 } },
                                                    { { -1., +1. }, { 0.4, 0.6 } },
                                                    { { -1., +1. }, { 0.1, 0.9 } } } );
      TabulatedAngularDistributions different( { 1., 4. },
                                               { { { -1., +1. }, { 0.5, 0.5 } },
                                                 { { -1., +1. }, { 0.1, 0.9 } } } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( true == ( left == unnormalised ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( false == ( left != unnormalised ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a TabulatedAngularDistributions object" ) {

    WHEN( "there are not enough values in the x or f(y) grid" ) {

      std::vector< double > gempty = {};
      std::vector< double > gone = { 1. };
      std::vector< TabulatedAngularDistribution > dempty = {};
      std::vector< TabulatedAngularDistribution > done = { { { -1., +1. }, { 0.5, 0.5 } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributions( gempty, dempty ) );
        CHECK_THROWS( TabulatedAngularDistributions( gone, done ) );
        CHECK_THROWS( TabulatedAngularDistributions( gempty, done ) );
        CHECK_THROWS( TabulatedAngularDistributions( gone, dempty ) );
      } // THEN
    } // WHEN

    WHEN( "the x and f(y) grid do not have the same number of points" ) {

      std::vector< double > grid = { 1., 2., 3., 4. };
      std::vector< TabulatedAngularDistribution > distributions = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributions( std::move( grid ),
                                                     std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< TabulatedAngularDistribution > distributions = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributions( std::move( grid ),
                                                     std::move( distributions ),
                                                     std::move( boundaries ),
                                                     std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      const std::vector< double > grid = { 1., 3., 2., 4. };
      const std::vector< TabulatedAngularDistribution > distributions = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributions( std::move( grid ),
                                                     std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid contains a triple x value" ) {

      const std::vector< double > grid = { 1., 2., 2., 2., 4. };
      const std::vector< TabulatedAngularDistribution > distributions = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., 0.5, +1. }, { 0.49, 0.5, 0.505, 0.51 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributions( std::move( grid ),
                                                     std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the beginning" ) {

      const std::vector< double > grid = { 1., 1., 3., 4. };
      const std::vector< TabulatedAngularDistribution > distributions = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributions( std::move( grid ),
                                                     std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the end" ) {

      const std::vector< double > grid = { 1., 2., 4., 4. };
      const std::vector< TabulatedAngularDistribution > distributions = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributions( std::move( grid ),
                                                     std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< TabulatedAngularDistribution > distributions = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributions( std::move( grid ),
                                                     std::move( distributions ),
                                                     std::move( boundaries ),
                                                     std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
