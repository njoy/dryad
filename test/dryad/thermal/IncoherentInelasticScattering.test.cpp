// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/thermal/IncoherentInelasticScattering.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const IncoherentInelasticScattering& );

SCENARIO( "IncoherentInelasticScattering" ) {

  GIVEN( "valid incoherent scattering data" ) {

    WHEN( "the data is given explicitly" ) {

      double lower = 1e-5;
      double upper = 10.;
      double xs = 6.337872;
      std::vector< ScatteringKernel > kernels = {

        { 293.6, 300.,
          { 0., 4. },
          { { { 0., 4. }, { 0.8, 0.2 } },
            { { 0., 4. }, { 0.2, 0.8 } } } },
        { 325, 350.,
          { 0., 5. },
          { { { 0., 5. }, { 0.9, 0.1 } },
            { { 0., 5. }, { 0.1, 0.9 } } } }
      };

      IncoherentInelasticScattering chunk( lower, upper, xs, std::move( kernels ) );

      THEN( "IncoherentInelasticScattering can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of IncoherentInelasticScattering is given" ) {

      IncoherentInelasticScattering chunk( 1e-5, 10., 6.337872,
                                           { { 293.6, 300.,
                                               { 0., 4. },
                                               { { { 0., 4. }, { 0.8, 0.2 } },
                                                 { { 0., 4. }, { 0.2, 0.8 } } } },
                                             { 325, 350.,
                                               { 0., 5. },
                                               { { { 0., 5. }, { 0.9, 0.1 } },
                                                 { { 0., 5. }, { 0.1, 0.9 } } } } } );

      THEN( "the lower energy limit can be changed" ) {

        double newlimit = 1e-4;
        double original = 1e-5;

        chunk.lowerEnergyLimit( newlimit );

        CHECK( newlimit == chunk.lowerEnergyLimit() );

        chunk.lowerEnergyLimit( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the upper energy limit can be changed" ) {

        double newlimit = 7.5;
        double original = 10.;

        chunk.upperEnergyLimit( newlimit );

        CHECK( newlimit == chunk.upperEnergyLimit() );

        chunk.upperEnergyLimit( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the bound xs can be changed" ) {

        double newxs = 25.;
        double original = 6.337872;

        chunk.boundCrossSection( newxs );

        CHECK( newxs == chunk.boundCrossSection() );

        chunk.boundCrossSection( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the scattering kernels can be changed" ) {

        std::vector< ScatteringKernel > newkernels = { { 300., 305.,
                                                         { 0., 4. },
                                                         { { { 0., 4. }, { 0.8, 0.2 } },
                                                           { { 0., 4. }, { 0.2, 0.8 } } } },
                                                       { 330, 355.,
                                                         { 0., 5. },
                                                         { { { 0., 5. }, { 0.9, 0.1 } },
                                                           { { 0., 5. }, { 0.1, 0.9 } } } } };
        std::vector< ScatteringKernel > original = { { 293.6, 300.,
                                                       { 0., 4. },
                                                       { { { 0., 4. }, { 0.8, 0.2 } },
                                                         { { 0., 4. }, { 0.2, 0.8 } } } },
                                                     { 325, 350.,
                                                       { 0., 5. },
                                                       { { { 0., 5. }, { 0.9, 0.1 } },
                                                         { { 0., 5. }, { 0.1, 0.9 } } } } };

        chunk.scatteringKernels( newkernels );

        CHECK( newkernels == chunk.scatteringKernels() );

        chunk.scatteringKernels( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of IncoherentInelasticScattering are given" ) {

      IncoherentInelasticScattering left( 1e-5, 10., 6.337872,
                                          { { 293.6, 300.,
                                              { 0., 4. },
                                              { { { 0., 4. }, { 0.8, 0.2 } },
                                                { { 0., 4. }, { 0.2, 0.8 } } } },
                                            { 325, 350.,
                                              { 0., 5. },
                                              { { { 0., 5. }, { 0.9, 0.1 } },
                                                { { 0., 5. }, { 0.1, 0.9 } } } } } );
      IncoherentInelasticScattering equal( 1e-5, 10., 6.337872,
                                           { { 293.6, 300.,
                                               { 0., 4. },
                                               { { { 0., 4. }, { 0.8, 0.2 } },
                                                 { { 0., 4. }, { 0.2, 0.8 } } } },
                                             { 325, 350.,
                                               { 0., 5. },
                                               { { { 0., 5. }, { 0.9, 0.1 } },
                                                 { { 0., 5. }, { 0.1, 0.9 } } } } } );
      IncoherentInelasticScattering different( 1e-5, 10., 6.337872,
                                               { { 293.6, 300.,
                                                   { 0., 5. },
                                                   { { { 0., 5. }, { 0.8, 0.2 } },
                                                     { { 0., 5. }, { 0.2, 0.8 } } } },
                                                 { 325, 350.,
                                                   { 0., 4. },
                                                   { { { 0., 4. }, { 0.9, 0.1 } },
                                                     { { 0., 4. }, { 0.1, 0.9 } } } } } );

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

void verifyChunk( const IncoherentInelasticScattering& chunk ) {

  CHECK_THAT( 1e-5, WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 10. , WithinRel( chunk.upperEnergyLimit() ) );

  CHECK_THAT( 6.337872, WithinRel( chunk.boundCrossSection() ) );

  CHECK( true == chunk.hasScatteringKernel( 293.6 ) );
  CHECK( true == chunk.hasScatteringKernel( 325 ) );
  CHECK( false == chunk.hasScatteringKernel( 350 ) );

  CHECK( 2 == chunk.numberModeratorTemperatures() );
  CHECK( 2 == chunk.moderatorTemperatures().size() );
  CHECK_THAT( 293.6, WithinRel( chunk.moderatorTemperatures()[0] ) );
  CHECK_THAT( 325  , WithinRel( chunk.moderatorTemperatures()[1] ) );

  decltype(auto) sab1 = chunk.scatteringKernel( 293.6 );
  CHECK_THAT( 293.6, WithinRel( sab1.moderatorTemperature() ) );
  CHECK_THAT( 300. , WithinRel( sab1.effectiveTemperature() ) );
  CHECK( true == sab1.isEnergyTransferSymmetric() );
  decltype(auto) table1 = sab1.tabulatedScatteringKernel();
  CHECK_THAT( 0., WithinRel( table1.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 4., WithinRel( table1.upperEnergyTransferLimit() ) );
  CHECK_THAT( 0., WithinRel( table1.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 4., WithinRel( table1.upperMomentumTransferLimit() ) );
  CHECK( 2 == table1.numberPoints() );
  CHECK( 1 == table1.numberRegions() );
  CHECK( 2 == table1.energyTransfers().size() );
  CHECK( 2 == table1.functions().size() );
  CHECK( 1 == table1.boundaries().size() );
  CHECK( 1 == table1.interpolants().size() );
  CHECK_THAT( 0., WithinRel( table1.energyTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( table1.energyTransfers()[1] ) );
  CHECK( 2 == table1.functions()[0].momentumTransfers().size() );
  CHECK( 2 == table1.functions()[0].values().size() );
  CHECK( 2 == table1.functions()[1].momentumTransfers().size() );
  CHECK( 2 == table1.functions()[1].values().size() );
  CHECK_THAT( 0., WithinRel( table1.functions()[0].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( table1.functions()[0].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( table1.functions()[1].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( table1.functions()[1].momentumTransfers()[1] ) );
  CHECK_THAT( 0.8 , WithinRel( table1.functions()[0].values()[0] ) );
  CHECK_THAT( 0.2 , WithinRel( table1.functions()[0].values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( table1.functions()[1].values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( table1.functions()[1].values()[1] ) );
  CHECK( 1 == table1.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == table1.interpolants()[0] );

  decltype(auto) sab2 = chunk.scatteringKernel( 325 );
  CHECK_THAT( 325, WithinRel( sab2.moderatorTemperature() ) );
  CHECK_THAT( 350, WithinRel( sab2.effectiveTemperature() ) );
  CHECK( true == sab2.isEnergyTransferSymmetric() );
  decltype(auto) table2 = sab2.tabulatedScatteringKernel();
  CHECK_THAT( 0., WithinRel( table2.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 5., WithinRel( table2.upperEnergyTransferLimit() ) );
  CHECK_THAT( 0., WithinRel( table2.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 5., WithinRel( table2.upperMomentumTransferLimit() ) );
  CHECK( 2 == table2.numberPoints() );
  CHECK( 1 == table2.numberRegions() );
  CHECK( 2 == table2.energyTransfers().size() );
  CHECK( 2 == table2.functions().size() );
  CHECK( 1 == table2.boundaries().size() );
  CHECK( 1 == table2.interpolants().size() );
  CHECK_THAT( 0., WithinRel( table2.energyTransfers()[0] ) );
  CHECK_THAT( 5., WithinRel( table2.energyTransfers()[1] ) );
  CHECK( 2 == table2.functions()[0].momentumTransfers().size() );
  CHECK( 2 == table2.functions()[0].values().size() );
  CHECK( 2 == table2.functions()[1].momentumTransfers().size() );
  CHECK( 2 == table2.functions()[1].values().size() );
  CHECK_THAT( 0., WithinRel( table2.functions()[0].momentumTransfers()[0] ) );
  CHECK_THAT( 5., WithinRel( table2.functions()[0].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( table2.functions()[1].momentumTransfers()[0] ) );
  CHECK_THAT( 5., WithinRel( table2.functions()[1].momentumTransfers()[1] ) );
  CHECK_THAT( 0.9 , WithinRel( table2.functions()[0].values()[0] ) );
  CHECK_THAT( 0.1 , WithinRel( table2.functions()[0].values()[1] ) );
  CHECK_THAT( 0.1 , WithinRel( table2.functions()[1].values()[0] ) );
  CHECK_THAT( 0.9 , WithinRel( table2.functions()[1].values()[1] ) );
  CHECK( 1 == table2.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == table2.interpolants()[0] );
}
