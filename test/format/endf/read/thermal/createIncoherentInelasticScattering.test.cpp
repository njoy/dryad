// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/thermal/createIncoherentInelasticScattering.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const thermal::IncoherentInelasticScattering& );

SCENARIO( "createIncoherentInelasticScattering" ) {

  GIVEN( "ENDF MF7 MT2 scattering law components" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "tsl-ZrinZrH.endf" );
    auto section = tape.materials().front().section( 7, 4 ).parse< 7, 4 >();

    WHEN( "a single parsed incoherent inelastic thermal scattering component is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::thermal::createIncoherentInelasticScattering( 1e-5, 10., section );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const thermal::IncoherentInelasticScattering& chunk ) {

  CHECK_THAT( 1e-5, WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 10. , WithinRel( chunk.upperEnergyLimit() ) );
  CHECK_THAT( 6.2 * ( 90.436 + 1. ) * ( 90.436 + 1. ) / 90.436 / 90.436,
              WithinRel( chunk.boundCrossSection() ) );
  CHECK_THAT( 90.436, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 8 == chunk.numberModeratorTemperatures() );
  CHECK( 8 == chunk.moderatorTemperatures().size() );
  CHECK_THAT(  296, WithinRel( chunk.moderatorTemperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.moderatorTemperatures()[1] ) );
  CHECK_THAT(  500, WithinRel( chunk.moderatorTemperatures()[2] ) );
  CHECK_THAT(  600, WithinRel( chunk.moderatorTemperatures()[3] ) );
  CHECK_THAT(  700, WithinRel( chunk.moderatorTemperatures()[4] ) );
  CHECK_THAT(  800, WithinRel( chunk.moderatorTemperatures()[5] ) );
  CHECK_THAT( 1000, WithinRel( chunk.moderatorTemperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.moderatorTemperatures()[7] ) );

  double min = std::numeric_limits< double >::min();

  double factor;

  auto sab = chunk.scatteringKernel( 296 );
  factor = 293.6 / 296.;
  CHECK_THAT( 296     , WithinRel( sab.moderatorTemperature() ) );
  CHECK_THAT( 317.4163, WithinRel( sab.effectiveTemperature() ) );
  CHECK( true == sab.isEnergyTransferSymmetric() );
  auto table = sab.tabulatedScatteringKernel();
  CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 39.5344     * factor, WithinRel( table.upperEnergyTransferLimit() ) );
  CHECK_THAT( 5.569960e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 1.791430    * factor, WithinRel( table.upperMomentumTransferLimit() ) );
  CHECK_THAT( 7.242787e-3         , WithinRel( table( 5.569960e-3 * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 5.569960e-3 * factor, 39.5344 * factor ) ) );
  CHECK_THAT( 1.434476e-1         , WithinRel( table( 1.791430    * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 1.791430    * factor, 39.5344 * factor ) ) );

  sab = chunk.scatteringKernel( 400 );
  factor = 293.6 / 400.;
  CHECK_THAT( 400     , WithinRel( sab.moderatorTemperature() ) );
  CHECK_THAT( 416.3325, WithinRel( sab.effectiveTemperature() ) );
  CHECK( true == sab.isEnergyTransferSymmetric() );
  table = sab.tabulatedScatteringKernel();
  CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 39.5344     * factor, WithinRel( table.upperEnergyTransferLimit() ) );
  CHECK_THAT( 5.569960e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 1.791430    * factor, WithinRel( table.upperMomentumTransferLimit() ) );
  CHECK_THAT( 1.321421e-2         , WithinRel( table( 5.569960e-3 * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 5.569960e-3 * factor, 39.5344 * factor ) ) );
  CHECK_THAT( 1.835178e-1         , WithinRel( table( 1.791430    * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 1.791430    * factor, 39.5344 * factor ) ) );

  sab = chunk.scatteringKernel( 500 );
  factor = 293.6 / 500.;
  CHECK_THAT( 500     , WithinRel( sab.moderatorTemperature() ) );
  CHECK_THAT( 513.2826, WithinRel( sab.effectiveTemperature() ) );
  CHECK( true == sab.isEnergyTransferSymmetric() );
  table = sab.tabulatedScatteringKernel();
  CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 39.5344     * factor, WithinRel( table.upperEnergyTransferLimit() ) );
  CHECK_THAT( 5.569960e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 1.791430    * factor, WithinRel( table.upperMomentumTransferLimit() ) );
  CHECK_THAT( 2.062500e-2         , WithinRel( table( 5.569960e-3 * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 5.569960e-3 * factor, 39.5344 * factor ) ) );
  CHECK_THAT( 2.170594e-1         , WithinRel( table( 1.791430    * factor, 0.      * factor ) ) );
  CHECK_THAT( 2.13881e-24         , WithinRel( table( 1.791430    * factor, 39.5344 * factor ) , 1e-12) );

  sab = chunk.scatteringKernel( 600 );
  factor = 293.6 / 600.;
  CHECK_THAT( 600     , WithinRel( sab.moderatorTemperature() ) );
  CHECK_THAT( 611.1816, WithinRel( sab.effectiveTemperature() ) );
  CHECK( true == sab.isEnergyTransferSymmetric() );
  table = sab.tabulatedScatteringKernel();
  CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 39.5344     * factor, WithinRel( table.upperEnergyTransferLimit() ) );
  CHECK_THAT( 5.569960e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 1.791430    * factor, WithinRel( table.upperMomentumTransferLimit() ) );
  CHECK_THAT( 2.966493e-2         , WithinRel( table( 5.569960e-3 * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 5.569960e-3 * factor, 39.5344 * factor ) ) );
  CHECK_THAT( 2.470634e-1         , WithinRel( table( 1.791430    * factor, 0.      * factor ) ) );
  CHECK_THAT( 8.11991e-23         , WithinRel( table( 1.791430    * factor, 39.5344 * factor ) ) );

  sab = chunk.scatteringKernel( 700 );
  factor = 293.6 / 700.;
  CHECK_THAT( 700     , WithinRel( sab.moderatorTemperature() ) );
  CHECK_THAT( 709.6479, WithinRel( sab.effectiveTemperature() ) );
  CHECK( true == sab.isEnergyTransferSymmetric() );
  table = sab.tabulatedScatteringKernel();
  CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 39.5344     * factor, WithinRel( table.upperEnergyTransferLimit() ) );
  CHECK_THAT( 5.569960e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 1.791430    * factor, WithinRel( table.upperMomentumTransferLimit() ) );
  CHECK_THAT( 4.032669e-2         , WithinRel( table( 5.569960e-3 * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 5.569960e-3 * factor, 39.5344 * factor ) ) );
  CHECK_THAT( 2.743558e-1         , WithinRel( table( 1.791430    * factor, 0.      * factor ) ) );
  CHECK_THAT( 1.50711e-21         , WithinRel( table( 1.791430    * factor, 39.5344 * factor ) ) );

  sab = chunk.scatteringKernel( 800 );
  factor = 293.6 / 800.;
  CHECK_THAT( 800     , WithinRel( sab.moderatorTemperature() ) );
  CHECK_THAT( 808.4802, WithinRel( sab.effectiveTemperature() ) );
  CHECK( true == sab.isEnergyTransferSymmetric() );
  table = sab.tabulatedScatteringKernel();
  CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 39.5344     * factor, WithinRel( table.upperEnergyTransferLimit() ) );
  CHECK_THAT( 5.569960e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 1.791430    * factor, WithinRel( table.upperMomentumTransferLimit() ) );
  CHECK_THAT( 5.260275e-2         , WithinRel( table( 5.569960e-3 * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 5.569960e-3 * factor, 39.5344 * factor ) ) );
  CHECK_THAT( 2.995066e-1         , WithinRel( table( 1.791430    * factor, 0.      * factor ) ) );
  CHECK_THAT( 1.84277e-20         , WithinRel( table( 1.791430    * factor, 39.5344 * factor ) ) );

  sab = chunk.scatteringKernel( 1000 );
  factor = 293.6 / 1000.;
  CHECK_THAT( 1000    , WithinRel( sab.moderatorTemperature() ) );
  CHECK_THAT( 1006.822, WithinRel( sab.effectiveTemperature() ) );
  CHECK( true == sab.isEnergyTransferSymmetric() );
  table = sab.tabulatedScatteringKernel();
  CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 39.5344     * factor, WithinRel( table.upperEnergyTransferLimit() ) );
  CHECK_THAT( 5.569960e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 1.791430    * factor, WithinRel( table.upperMomentumTransferLimit() ) );
  CHECK_THAT( 8.196668e-2         , WithinRel( table( 5.569960e-3 * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 5.569960e-3 * factor, 39.5344 * factor ) ) );
  CHECK_THAT( 3.448984e-1         , WithinRel( table( 1.791430    * factor, 0.      * factor ) ) );
  CHECK_THAT( 1.23757e-18         , WithinRel( table( 1.791430    * factor, 39.5344 * factor ) ) );

  sab = chunk.scatteringKernel( 1200 );
  factor = 293.6 / 1200.;
  CHECK_THAT( 1200    , WithinRel( sab.moderatorTemperature() ) );
  CHECK_THAT( 1205.703, WithinRel( sab.effectiveTemperature() ) );
  CHECK( true == sab.isEnergyTransferSymmetric() );
  table = sab.tabulatedScatteringKernel();
  CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
  CHECK_THAT( 39.5344     * factor, WithinRel( table.upperEnergyTransferLimit() ) );
  CHECK_THAT( 5.569960e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
  CHECK_THAT( 1.791430    * factor, WithinRel( table.upperMomentumTransferLimit() ) );
  CHECK_THAT( 1.176925e-1         , WithinRel( table( 5.569960e-3 * factor, 0.      * factor ) ) );
  CHECK_THAT( min                 , WithinRel( table( 5.569960e-3 * factor, 39.5344 * factor ) ) );
  CHECK_THAT( 3.853824e-1         , WithinRel( table( 1.791430    * factor, 0.      * factor ) ) );
  CHECK_THAT( 4.06882e-17         , WithinRel( table( 1.791430    * factor, 39.5344 * factor ) ) );
}
