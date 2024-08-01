// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/TabulatedEnergyDistributions.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "TabulatedEnergyDistributions" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > grid = { 1., 2., 3., 4. };
      const std::vector< TabulatedEnergyDistribution > distributions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } },
        { { 0., 4. }, { 0.1, 0.9 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      TabulatedEnergyDistributions
      chunk( std::move( grid ), std::move( distributions ), interpolant );

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
        CHECK( 2 == chunk.distributions()[0].energies().size() );
        CHECK( 2 == chunk.distributions()[0].values().size() );
        CHECK( 3 == chunk.distributions()[1].energies().size() );
        CHECK( 3 == chunk.distributions()[1].values().size() );
        CHECK( 3 == chunk.distributions()[2].energies().size() );
        CHECK( 3 == chunk.distributions()[2].values().size() );
        CHECK( 2 == chunk.distributions()[3].energies().size() );
        CHECK( 2 == chunk.distributions()[3].values().size() );
        CHECK_THAT( 0.  , WithinRel( chunk.distributions()[0].energies()[0] ) );
        CHECK_THAT( 4.  , WithinRel( chunk.distributions()[0].energies()[1] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[0].values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[0].values()[1] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.distributions()[1].energies()[0] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.distributions()[1].energies()[1] ) );
        CHECK_THAT( 4.  , WithinRel( chunk.distributions()[1].energies()[2] ) );
        CHECK_THAT( 0.49, WithinRel( chunk.distributions()[1].values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[1].values()[1] ) );
        CHECK_THAT( 0.51, WithinRel( chunk.distributions()[1].values()[2] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.distributions()[2].energies()[0] ) );
        CHECK_THAT( 2.  , WithinRel( chunk.distributions()[2].energies()[1] ) );
        CHECK_THAT( 4.  , WithinRel( chunk.distributions()[2].energies()[2] ) );
        CHECK_THAT( 0.4 , WithinRel( chunk.distributions()[2].values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.distributions()[2].values()[1] ) );
        CHECK_THAT( 0.6 , WithinRel( chunk.distributions()[2].values()[2] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.distributions()[3].energies()[0] ) );
        CHECK_THAT( 4.  , WithinRel( chunk.distributions()[3].energies()[1] ) );
        CHECK_THAT( 0.1 , WithinRel( chunk.distributions()[3].values()[0] ) );
        CHECK_THAT( 0.9 , WithinRel( chunk.distributions()[3].values()[1] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN

      THEN( "an InterpolationTableFunction can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.5             , WithinRel( chunk( 1., 3. ) ) );
        CHECK_THAT( 0.50666666666667, WithinRel( chunk( 2., 3. ) ) );
        CHECK_THAT( 0.55            , WithinRel( chunk( 3., 3. ) ) );
        CHECK_THAT( 0.7             , WithinRel( chunk( 4., 3. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0.              , WithinRel( chunk( 0., 3. ) ) );
        CHECK_THAT( 0.              , WithinRel( chunk( 5., 3. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.50333333333334, WithinRel( chunk( 1.5, 3. ) ) );
        CHECK_THAT( 0.52833333333334, WithinRel( chunk( 2.5, 3. ) ) );
        CHECK_THAT( 0.625           , WithinRel( chunk( 3.5, 3. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

//  GIVEN( "invalid data for an InterpolationTableFunction object" ) {
//
//    WHEN( "there are not enough values in the x or f(y) grid" ) {
//
//      std::vector< double > xempty = {};
//      std::vector< double > xone = { 1. };
//      std::vector< InterpolationTable< double > > fempty = {};
//      std::vector< InterpolationTable< double > > fone = { { { 1., 2. }, { 3., 4. } } };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( Table2D( xempty, fempty ) );
//        CHECK_THROWS( Table2D( xone, fone ) );
//        CHECK_THROWS( Table2D( xempty, fone ) );
//        CHECK_THROWS( Table2D( xone, fempty ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x and f(y) grid do not have the same number of points" ) {
//
//      std::vector< double > x = { 1., 2., 3., 4. };
//      std::vector< InterpolationTable< double > > f = {
//
//        { { -1., +1. }, { 0.5, 0.5 } },
//        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
//        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } }
//      };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the boundaries and interpolants do not have the same size" ) {
//
//      const std::vector< double > x = { 1., 2., 3., 4. };
//      const std::vector< InterpolationTable< double > > f = {
//
//        { { -1., +1. }, { 0.5, 0.5 } },
//        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
//        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
//        { { -1., +1. }, { 0.1, 0.9 } }
//      };
//      std::vector< std::size_t > boundaries = { 3 };
//      std::vector< InterpolationType > interpolants = {};
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( Table2D( std::move( x ), std::move( f ),
//                                 std::move( boundaries ),
//                                 std::move( interpolants ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x grid is not sorted" ) {
//
//      const std::vector< double > x = { 1., 3., 2., 4. };
//      const std::vector< InterpolationTable< double > > f = {
//
//        { { -1., +1. }, { 0.5, 0.5 } },
//        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
//        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
//        { { -1., +1. }, { 0.1, 0.9 } }
//      };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x grid contains a triple x value" ) {
//
//      const std::vector< double > x = { 1., 2., 2., 2., 4. };
//      const std::vector< InterpolationTable< double > > f = {
//
//        { { -1., +1. }, { 0.5, 0.5 } },
//        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
//        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
//        { { -1., +1. }, { 0.1, 0.9 } },
//        { { -1., +1. }, { 0.3, 0.7 } }
//      };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x grid has a jump at the beginning" ) {
//
//      const std::vector< double > x = { 1., 1., 3., 4. };
//      const std::vector< InterpolationTable< double > > f = {
//
//        { { -1., +1. }, { 0.5, 0.5 } },
//        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
//        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
//        { { -1., +1. }, { 0.1, 0.9 } }
//      };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x grid has a jump at the end" ) {
//
//      const std::vector< double > x = { 1., 2., 4., 4. };
//      const std::vector< InterpolationTable< double > > f = {
//
//        { { -1., +1. }, { 0.5, 0.5 } },
//        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
//        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
//        { { -1., +1. }, { 0.1, 0.9 } }
//      };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the last boundary does not point to the last point" ) {
//
//      const std::vector< double > x = { 1., 2., 3., 4. };
//      const std::vector< InterpolationTable< double > > f = {
//
//        { { -1., +1. }, { 0.5, 0.5 } },
//        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
//        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
//        { { -1., +1. }, { 0.1, 0.9 } }
//      };
//      std::vector< std::size_t > boundaries = { 2 };
//      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( Table2D( std::move( x ), std::move( f ),
//                               std::move( boundaries ), std::move( interpolants ) ) );
//      } // THEN
//    } // WHEN
//  } // GIVEN
} // SCENARIO