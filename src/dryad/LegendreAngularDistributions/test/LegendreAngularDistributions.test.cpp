// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/LegendreAngularDistributions.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "LegendreAngularDistributions" ) {

  GIVEN( "legendre series without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 1., 2., 3., 4. };
      const std::vector< LegendreAngularDistribution > distributions = {

        { { 0.5 } },
        { { 0.5, 0.01 } },
        { { 0.5, 0.1 } },
        { { 0.5, 0.4 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      LegendreAngularDistributions
      chunk( std::move( energies ), std::move( distributions ), interpolant );

      THEN( "an InterpolationTableFunction can be constructed and members can be tested" ) {

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
        CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[0].pdf().coefficients()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[1].pdf().coefficients()[0] ) );
        CHECK_THAT( 0.01, WithinRel( chunk.distributions()[1].pdf().coefficients()[1] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[2].pdf().coefficients()[0] ) );
        CHECK_THAT( 0.1 , WithinRel( chunk.distributions()[2].pdf().coefficients()[1] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[3].pdf().coefficients()[0] ) );
        CHECK_THAT( 0.4 , WithinRel( chunk.distributions()[3].pdf().coefficients()[1] ) );
        CHECK( std::nullopt == chunk.distributions()[0].cdf() );
        CHECK( std::nullopt == chunk.distributions()[1].cdf() );
        CHECK( std::nullopt == chunk.distributions()[2].cdf() );
        CHECK( std::nullopt == chunk.distributions()[3].cdf() );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN

      THEN( "an InterpolationTableFunction can be evaluated" ) {

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

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< LegendreAngularDistribution > distributions = {

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

      const std::vector< double > grid = { 1., 3., 2., 4. };
      const std::vector< LegendreAngularDistribution > distributions = {

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

    WHEN( "the x grid contains a triple x value" ) {

      const std::vector< double > grid = { 1., 2., 2., 2., 4. };
      const std::vector< LegendreAngularDistribution > distributions = {

        { { 0.5 } },
        { { 0.5, 0.001 } },
        { { 0.5, 0.01 } },
        { { 0.5, 0.1 } },
        { { 0.5, 0.4 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreAngularDistributions( std::move( grid ),
                                                    std::move( distributions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the beginning" ) {

      const std::vector< double > grid = { 1., 1., 3., 4. };
      const std::vector< LegendreAngularDistribution > distributions = {

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

    WHEN( "the x grid has a jump at the end" ) {

      const std::vector< double > grid = { 1., 2., 4., 4. };
      const std::vector< LegendreAngularDistribution > distributions = {

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

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< LegendreAngularDistribution > distributions = {

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
