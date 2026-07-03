// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/thermal/TabulatedScatteringKernel.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const TabulatedScatteringKernel& );
void verifyChunkWithJump( const TabulatedScatteringKernel& );

SCENARIO( "TabulatedScatteringKernel" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      double temperature = 293.6;
      const std::vector< double > energyTransfers = { 1., 2., 3., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      TabulatedScatteringKernel
      chunk( temperature,
             std::move( energyTransfers ),
             std::move( functions ), interpolant );

      verifyChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump that consist of more than 2 points" ) {

    // note: at construction time, the extraneous points in between the first and last
    //       x value in the jump are removed. boundaries always point to the first point
    //       in the jump

    WHEN( "the data is given explicitly" ) {

      double temperature = 293.6;
      const std::vector< double > energyTransfers = { 1., 2., 2., 2., 3., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.51, 0.49 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };

      TabulatedScatteringKernel
      chunk( temperature,
             std::move( energyTransfers ),
             std::move( functions ) );

      THEN( "a TabulatedScatteringKernel can be constructed and members can be tested" ) {

        verifyChunkWithJump( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the beginning" ) {

    // note: at construction time, the first point is removed

    WHEN( "the data is given explicitly" ) {

      double temperature = 293.6;
      const std::vector< double > energyTransfers = { 1., 1., 2., 3., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 1. }, { 0.1, 0.1 } },
        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };

      TabulatedScatteringKernel
      chunk( temperature,
             std::move( energyTransfers ), std::move( functions ) );

      THEN( "a TabulatedScatteringKernel can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump at the end" ) {

    // note: at construction time, the last point is removed

    WHEN( "the data is given explicitly" ) {

      double temperature = 293.6;
      const std::vector< double > energyTransfers = { 1., 2., 3., 4., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } },
        { { 0., 1. }, { 0.1, 0.1 } }
      };

      TabulatedScatteringKernel
      chunk( temperature,
             std::move( energyTransfers ), std::move( functions ) );

      THEN( "a TabulatedScatteringKernel can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedScatteringKernel are given" ) {

      TabulatedScatteringKernel left( 293.6,
                                      { 1., 2., 3., 4. },
                                      { { { 1., 3. }, { 0.5, 0.5 } },
                                        { { 1., 3. }, { 0.49, 0.51 } },
                                        { { 1., 3. }, { 0.4, 0.6 } },
                                        { { 1., 3. }, { 0.1, 0.9 } } } );
      TabulatedScatteringKernel equal( 293.6,
                                       { 1., 2., 3., 4. },
                                       { { { 1., 3. }, { 0.5, 0.5 } },
                                         { { 1., 3. }, { 0.49, 0.51 } },
                                         { { 1., 3. }, { 0.4, 0.6 } },
                                         { { 1., 3. }, { 0.1, 0.9 } } } );
      TabulatedScatteringKernel different( 293.6,
                                           { 1., 4. },
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

    WHEN( "there are not enough values in the x or f(y) energyTransfers" ) {

      std::vector< double > gempty = {};
      std::vector< double > gone = { 1. };
      std::vector< TabulatedScatteringKernelFunction > dempty = {};
      std::vector< TabulatedScatteringKernelFunction > done = { { { 0., 4. }, { 0.5, 0.5 } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedScatteringKernel( 293.6, gempty, dempty ) );
        CHECK_THROWS( TabulatedScatteringKernel( 293.6, gone, done ) );
        CHECK_THROWS( TabulatedScatteringKernel( 293.6, gempty, done ) );
        CHECK_THROWS( TabulatedScatteringKernel( 293.6, gone, dempty ) );
      } // THEN
    } // WHEN

    WHEN( "the x and f(y) energyTransfers do not have the same number of points" ) {

      std::vector< double > energyTransfers = { 1., 2., 3., 4. };
      std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedScatteringKernel( 293.6,
                                                 std::move( energyTransfers ),
                                                 std::move( functions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      const std::vector< double > energyTransfers = { 1., 2., 3., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } },
        { { 0., 4. }, { 0.1, 0.9 } }
      };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedScatteringKernel( 293.6,
                                                 std::move( energyTransfers ),
                                                 std::move( functions ),
                                                 std::move( boundaries ),
                                                 std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x energyTransfers is not sorted" ) {

      const std::vector< double > energyTransfers = { 1., 3., 2., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } },
        { { 0., 4. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedScatteringKernel( 293.6,
                                                 std::move( energyTransfers ),
                                                 std::move( functions ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      const std::vector< double > energyTransfers = { 1., 2., 3., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 1., 4. }, { 0.49, 0.5, 0.51 } },
        { { 0., 2., 4. }, { 0.4, 0.5, 0.6 } },
        { { 0., 4. }, { 0.1, 0.9 } }
      };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedScatteringKernel( 293.6,
                                                 std::move( energyTransfers ),
                                                 std::move( functions ),
                                                 std::move( boundaries ),
                                                 std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedScatteringKernel& chunk ) {

  CHECK_THAT( 293.6, WithinRel( chunk.moderatorTemperature() ) );

  CHECK( 4 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 4 == chunk.energyTransfers().size() );
  CHECK( 4 == chunk.functions().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.energyTransfers()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.energyTransfers()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.energyTransfers()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.energyTransfers()[3] ) );
  CHECK( 2 == chunk.functions()[0].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[0].values().size() );
  CHECK( 2 == chunk.functions()[1].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[1].values().size() );
  CHECK( 2 == chunk.functions()[2].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[2].values().size() );
  CHECK( 2 == chunk.functions()[3].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[3].values().size() );
  CHECK_THAT( 0., WithinRel( chunk.functions()[0].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[0].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.functions()[1].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[1].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.functions()[2].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[2].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.functions()[3].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[3].momentumTransfers()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.functions()[0].values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.functions()[0].values()[1] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.functions()[1].values()[0] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.functions()[1].values()[1] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.functions()[2].values()[0] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.functions()[2].values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( chunk.functions()[3].values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( chunk.functions()[3].values()[1] ) );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

  // evaluate

  // values of x in the x grid
  CHECK_THAT( 0.5 , WithinRel( chunk( 1., 3. ) ) );
  CHECK_THAT( 0.49, WithinRel( chunk( 2., 3. ) ) );
  CHECK_THAT( 0.51, WithinRel( chunk( 3., 3. ) ) );
  CHECK_THAT( 0.65, WithinRel( chunk( 4., 3. ) ) );

  // values of x outside the x grid
  CHECK_THAT( 0., WithinRel( chunk( 0., 3. ) ) );
  CHECK_THAT( 0., WithinRel( chunk( 5., 3. ) ) );

  // values of x inside the x grid
  CHECK_THAT( 0.495, WithinRel( chunk( 1.5, 3. ) ) );
  CHECK_THAT( 0.5  , WithinRel( chunk( 2.5, 3. ) ) );
  CHECK_THAT( 0.58 , WithinRel( chunk( 3.5, 3. ) ) );

  // linearisation
  auto linear = chunk.linearise();

  CHECK( 4 == linear.numberPoints() );
  CHECK( 1 == linear.numberRegions() );
  CHECK( 4 == linear.energyTransfers().size() );
  CHECK( 4 == linear.functions().size() );
  CHECK( 1 == linear.boundaries().size() );
  CHECK( 1 == linear.interpolants().size() );
  CHECK_THAT( 1., WithinRel( linear.energyTransfers()[0] ) );
  CHECK_THAT( 2., WithinRel( linear.energyTransfers()[1] ) );
  CHECK_THAT( 3., WithinRel( linear.energyTransfers()[2] ) );
  CHECK_THAT( 4., WithinRel( linear.energyTransfers()[3] ) );
  CHECK( true == linear.functions()[0].isLinearised() );
  CHECK( true == linear.functions()[1].isLinearised() );
  CHECK( true == linear.functions()[2].isLinearised() );
  CHECK( true == linear.functions()[3].isLinearised() );
  CHECK( 2 == linear.functions()[0].momentumTransfers().size() );
  CHECK( 2 == linear.functions()[1].momentumTransfers().size() );
  CHECK( 2 == linear.functions()[2].momentumTransfers().size() );
  CHECK( 2 == linear.functions()[3].momentumTransfers().size() );
  CHECK( 2 == linear.functions()[0].values().size() );
  CHECK( 2 == linear.functions()[1].values().size() );
  CHECK( 2 == linear.functions()[2].values().size() );
  CHECK( 2 == linear.functions()[3].values().size() );
  CHECK_THAT( 0., WithinRel( linear.functions()[0].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.functions()[0].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.functions()[1].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.functions()[1].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.functions()[2].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.functions()[2].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( linear.functions()[3].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( linear.functions()[3].momentumTransfers()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( linear.functions()[0].values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( linear.functions()[0].values()[1] ) );
  CHECK_THAT( 0.52, WithinRel( linear.functions()[1].values()[0] ) );
  CHECK_THAT( 0.48, WithinRel( linear.functions()[1].values()[1] ) );
  CHECK_THAT( 0.48, WithinRel( linear.functions()[2].values()[0] ) );
  CHECK_THAT( 0.52, WithinRel( linear.functions()[2].values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( linear.functions()[3].values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( linear.functions()[3].values()[1] ) );
  CHECK( 3 == linear.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
}

void verifyChunkWithJump( const TabulatedScatteringKernel& chunk ) {

  CHECK_THAT( 293.6, WithinRel( chunk.moderatorTemperature() ) );

  CHECK( 5 == chunk.numberPoints() );
  CHECK( 2 == chunk.numberRegions() );
  CHECK( 5 == chunk.energyTransfers().size() );
  CHECK( 5 == chunk.functions().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.energyTransfers()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.energyTransfers()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.energyTransfers()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.energyTransfers()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.energyTransfers()[4] ) );
  CHECK( 2 == chunk.functions()[0].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[0].values().size() );
  CHECK( 2 == chunk.functions()[1].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[1].values().size() );
  CHECK( 2 == chunk.functions()[2].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[2].values().size() );
  CHECK( 2 == chunk.functions()[3].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[3].values().size() );
  CHECK( 2 == chunk.functions()[4].momentumTransfers().size() );
  CHECK( 2 == chunk.functions()[4].values().size() );
  CHECK_THAT( 0., WithinRel( chunk.functions()[0].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[0].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.functions()[1].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[1].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.functions()[2].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[2].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.functions()[3].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[3].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.functions()[4].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.functions()[4].momentumTransfers()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.functions()[0].values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.functions()[0].values()[1] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.functions()[1].values()[0] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.functions()[1].values()[1] ) );
  CHECK_THAT( 0.51, WithinRel( chunk.functions()[2].values()[0] ) );
  CHECK_THAT( 0.49, WithinRel( chunk.functions()[2].values()[1] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.functions()[3].values()[0] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.functions()[3].values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( chunk.functions()[4].values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( chunk.functions()[4].values()[1] ) );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
}