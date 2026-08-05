// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/thermal/ScatteringKernel.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifySymmetricChunk( const ScatteringKernel& );
void verifyAsymmetricChunk( const ScatteringKernel& );

SCENARIO( "ScatteringKernel" ) {

  GIVEN( "a symmetric tabulated scattering kernel" ) {

    WHEN( "the data is given explicitly" ) {

      double moderatorTemperature = 293.6;
      double effectiveTemperature = 300.;
      const std::vector< double > energyTransfers = { 0., 1., 2., 3., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.8, 0.2 } },
        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      ScatteringKernel chunk( moderatorTemperature, effectiveTemperature,
                              std::move( energyTransfers ),
                              std::move( functions ),
                              interpolant );

      verifySymmetricChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "an asymmetric tabulated scattering kernel" ) {

    WHEN( "the data is given explicitly" ) {

      double moderatorTemperature = 293.6;
      double effectiveTemperature = 300.;
      const std::vector< double > energyTransfers = { -1., 1., 2., 3., 4. };
      const std::vector< TabulatedScatteringKernelFunction > functions = {

        { { 0., 4. }, { 0.8, 0.2 } },
        { { 0., 4. }, { 0.5, 0.5 } },
        { { 0., 4. }, { 0.52, 0.48 } },
        { { 0., 4. }, { 0.48, 0.52 } },
        { { 0., 4. }, { 0.2, 0.8 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      ScatteringKernel chunk( moderatorTemperature, effectiveTemperature,
                              std::move( energyTransfers ),
                              std::move( functions ),
                              interpolant );

      verifyAsymmetricChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ScatteringKernel are given" ) {

      ScatteringKernel left( 293.6, 300.,
                             { 1., 2., 3., 4. },
                             { { { 1., 3. }, { 0.5, 0.5 } },
                               { { 1., 3. }, { 0.49, 0.51 } },
                               { { 1., 3. }, { 0.4, 0.6 } },
                               { { 1., 3. }, { 0.1, 0.9 } } } );
      ScatteringKernel equal( 293.6, 300.,
                              { 1., 2., 3., 4. },
                              { { { 1., 3. }, { 0.5, 0.5 } },
                                { { 1., 3. }, { 0.49, 0.51 } },
                                { { 1., 3. }, { 0.4, 0.6 } },
                                { { 1., 3. }, { 0.1, 0.9 } } } );
      ScatteringKernel different( 293.6, 300.,
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
} // SCENARIO

void verifySymmetricChunk( const ScatteringKernel& chunk ) {

  CHECK_THAT( 293.6, WithinRel( chunk.moderatorTemperature() ) );
  CHECK_THAT( 300. , WithinRel( chunk.effectiveTemperature() ) );

  CHECK( true == chunk.isEnergyTransferSymmetric() );

  decltype(auto) sab = chunk.tabulatedScatteringKernel();
  CHECK_THAT( 0., WithinRel( sab.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 4., WithinRel( sab.upperEnergyTransferLimit() ) );
  CHECK_THAT( 0., WithinRel( sab.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 4., WithinRel( sab.upperMomentumTransferLimit() ) );

  CHECK( 5 == sab.numberPoints() );
  CHECK( 1 == sab.numberRegions() );
  CHECK( 5 == sab.energyTransfers().size() );
  CHECK( 5 == sab.functions().size() );
  CHECK( 1 == sab.boundaries().size() );
  CHECK( 1 == sab.interpolants().size() );
  CHECK_THAT( 0., WithinRel( sab.energyTransfers()[0] ) );
  CHECK_THAT( 1., WithinRel( sab.energyTransfers()[1] ) );
  CHECK_THAT( 2., WithinRel( sab.energyTransfers()[2] ) );
  CHECK_THAT( 3., WithinRel( sab.energyTransfers()[3] ) );
  CHECK_THAT( 4., WithinRel( sab.energyTransfers()[4] ) );
  CHECK( 2 == sab.functions()[0].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[0].values().size() );
  CHECK( 2 == sab.functions()[1].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[1].values().size() );
  CHECK( 2 == sab.functions()[2].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[2].values().size() );
  CHECK( 2 == sab.functions()[3].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[3].values().size() );
  CHECK( 2 == sab.functions()[4].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[4].values().size() );
  CHECK_THAT( 0., WithinRel( sab.functions()[0].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[0].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( sab.functions()[1].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[1].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( sab.functions()[2].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[2].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( sab.functions()[3].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[3].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( sab.functions()[4].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[4].momentumTransfers()[1] ) );
  CHECK_THAT( 0.8 , WithinRel( sab.functions()[0].values()[0] ) );
  CHECK_THAT( 0.2 , WithinRel( sab.functions()[0].values()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( sab.functions()[1].values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( sab.functions()[1].values()[1] ) );
  CHECK_THAT( 0.52, WithinRel( sab.functions()[2].values()[0] ) );
  CHECK_THAT( 0.48, WithinRel( sab.functions()[2].values()[1] ) );
  CHECK_THAT( 0.48, WithinRel( sab.functions()[3].values()[0] ) );
  CHECK_THAT( 0.52, WithinRel( sab.functions()[3].values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( sab.functions()[4].values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( sab.functions()[4].values()[1] ) );
  CHECK( 4 == sab.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == sab.interpolants()[0] );

  // evaluate

  // a value below lower momentum transfer value, b within domain
  CHECK_THAT( 0.52 , WithinRel( chunk( -1.,  2. ) ) );
  CHECK_THAT( 0.52 , WithinRel( chunk( -2.,  2. ) ) );
  CHECK_THAT( 0.52 , WithinRel( chunk( -1., -2. ) ) );
  CHECK_THAT( 0.52 , WithinRel( chunk( -2., -2. ) ) );

  // a and b within domain
  CHECK_THAT( 0.5  , WithinRel( chunk( 3.,  1. ) ) );
  CHECK_THAT( 0.49 , WithinRel( chunk( 3.,  2. ) ) );
  CHECK_THAT( 0.51 , WithinRel( chunk( 3.,  3. ) ) );
  CHECK_THAT( 0.65 , WithinRel( chunk( 3.,  4. ) ) );
  CHECK_THAT( 0.495, WithinRel( chunk( 3.,  1.5 ) ) );
  CHECK_THAT( 0.5  , WithinRel( chunk( 3.,  2.5 ) ) );
  CHECK_THAT( 0.58 , WithinRel( chunk( 3.,  3.5 ) ) );
  CHECK_THAT( 0.5  , WithinRel( chunk( 3., -1. ) ) );
  CHECK_THAT( 0.49 , WithinRel( chunk( 3., -2. ) ) );
  CHECK_THAT( 0.51 , WithinRel( chunk( 3., -3. ) ) );
  CHECK_THAT( 0.65 , WithinRel( chunk( 3., -4. ) ) );
  CHECK_THAT( 0.495, WithinRel( chunk( 3., -1.5 ) ) );
  CHECK_THAT( 0.5  , WithinRel( chunk( 3., -2.5 ) ) );
  CHECK_THAT( 0.58 , WithinRel( chunk( 3., -3.5 ) ) );

  // large a - sct approximation (values calculated in excel)
  CHECK_THAT( 0.0295576357155647, WithinRel( chunk( 5.,  2. ) ) );
  CHECK_THAT( 0.0295576357155647, WithinRel( chunk( 5., -2. ) ) );

  // large b - sct approximation (values calculated in excel)
  CHECK_THAT( 0.0095441910268629, WithinRel( chunk( 3.,  5. ) ) );
  CHECK_THAT( 0.0095441910268629, WithinRel( chunk( 3., -5. ) ) );
}

void verifyAsymmetricChunk( const ScatteringKernel& chunk ) {

  CHECK( false == chunk.isEnergyTransferSymmetric() );

  decltype(auto) sab = chunk.tabulatedScatteringKernel();
  CHECK_THAT( -1., WithinRel( sab.lowerEnergyTransferLimit() ) );
  CHECK_THAT(  4., WithinRel( sab.upperEnergyTransferLimit() ) );
  CHECK_THAT(  0., WithinRel( sab.lowerMomentumTransferLimit() ) );
  CHECK_THAT(  4., WithinRel( sab.upperMomentumTransferLimit() ) );

  CHECK( 5 == sab.numberPoints() );
  CHECK( 1 == sab.numberRegions() );
  CHECK( 5 == sab.energyTransfers().size() );
  CHECK( 5 == sab.functions().size() );
  CHECK( 1 == sab.boundaries().size() );
  CHECK( 1 == sab.interpolants().size() );
  CHECK_THAT( -1., WithinRel( sab.energyTransfers()[0] ) );
  CHECK_THAT(  1., WithinRel( sab.energyTransfers()[1] ) );
  CHECK_THAT(  2., WithinRel( sab.energyTransfers()[2] ) );
  CHECK_THAT(  3., WithinRel( sab.energyTransfers()[3] ) );
  CHECK_THAT(  4., WithinRel( sab.energyTransfers()[4] ) );
  CHECK( 2 == sab.functions()[0].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[0].values().size() );
  CHECK( 2 == sab.functions()[1].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[1].values().size() );
  CHECK( 2 == sab.functions()[2].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[2].values().size() );
  CHECK( 2 == sab.functions()[3].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[3].values().size() );
  CHECK( 2 == sab.functions()[4].momentumTransfers().size() );
  CHECK( 2 == sab.functions()[4].values().size() );
  CHECK_THAT( 0., WithinRel( sab.functions()[0].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[0].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( sab.functions()[1].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[1].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( sab.functions()[2].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[2].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( sab.functions()[3].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[3].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( sab.functions()[4].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( sab.functions()[4].momentumTransfers()[1] ) );
  CHECK_THAT( 0.8 , WithinRel( sab.functions()[0].values()[0] ) );
  CHECK_THAT( 0.2 , WithinRel( sab.functions()[0].values()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( sab.functions()[1].values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( sab.functions()[1].values()[1] ) );
  CHECK_THAT( 0.52, WithinRel( sab.functions()[2].values()[0] ) );
  CHECK_THAT( 0.48, WithinRel( sab.functions()[2].values()[1] ) );
  CHECK_THAT( 0.48, WithinRel( sab.functions()[3].values()[0] ) );
  CHECK_THAT( 0.52, WithinRel( sab.functions()[3].values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( sab.functions()[4].values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( sab.functions()[4].values()[1] ) );
  CHECK( 4 == sab.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == sab.interpolants()[0] );

  // evaluate

  // a value below lower momentum transfer value, b within domain
  CHECK_THAT( 0.52 , WithinRel( chunk( -1.,  2. ) ) );
  CHECK_THAT( 0.52 , WithinRel( chunk( -2.,  2. ) ) );
  CHECK_THAT( 0.80 , WithinRel( chunk( -1., -1. ) ) );
  CHECK_THAT( 0.80 , WithinRel( chunk( -2., -1. ) ) );

  // a and b within domain
  CHECK_THAT( 0.5  , WithinRel( chunk( 3.,  1. ) ) );
  CHECK_THAT( 0.49 , WithinRel( chunk( 3.,  2. ) ) );
  CHECK_THAT( 0.51 , WithinRel( chunk( 3.,  3. ) ) );
  CHECK_THAT( 0.65 , WithinRel( chunk( 3.,  4. ) ) );
  CHECK_THAT( 0.495, WithinRel( chunk( 3.,  1.5 ) ) );
  CHECK_THAT( 0.5  , WithinRel( chunk( 3.,  2.5 ) ) );
  CHECK_THAT( 0.58 , WithinRel( chunk( 3.,  3.5 ) ) );
  CHECK_THAT( 0.35 , WithinRel( chunk( 3., -1. ) ) );

  // large a - sct approximation (values calculated in excel)
  CHECK_THAT( 0.0295576357155647, WithinRel( chunk( 5.,  2. ) ) );
  CHECK_THAT( 0.0295576357155647, WithinRel( chunk( 5., -2. ) ) );

  // large b - sct approximation (values calculated in excel)
  CHECK_THAT( 0.0095441910268629, WithinRel( chunk( 3.,  5. ) ) );
  CHECK_THAT( 0.0095441910268629, WithinRel( chunk( 3., -5. ) ) );
}
