// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const IncoherentElasticScattering& );

SCENARIO( "IncoherentElasticScattering" ) {

  GIVEN( "valid incoherent scattering data" ) {

    WHEN( "the data is given explicitly" ) {

      double lower = 1e-5;
      double upper = 10.;
      double xs = 6.337872;
      DebyeWallerIntegralData debyeWaller(

        { 296, 400, 500, 600, 700, 800, 1000, 1200 },
        { 2.013538, 2.677764, 3.323456, 3.972601,
          4.623738, 5.276127, 6.583171, 7.891981 }
      );

      IncoherentElasticScattering chunk( lower, upper, xs, std::move( debyeWaller ) );

      THEN( "IncoherentElasticScattering can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "requesting cross section data" ) {

      double lower = 1e-5;
      double upper = 10.;
      double xs = 6.337872;
      DebyeWallerIntegralData debyeWaller(

        { 296, 400, 500, 600, 700, 800, 1000, 1200 },
        { 2.013538, 2.677764, 3.323456, 3.972601,
          4.623738, 5.276127, 6.583171, 7.891981 }
      );

      IncoherentElasticScattering chunk( lower, upper, xs, std::move( debyeWaller ) );

      THEN( "the proper data is returned" ) {

        auto xs = chunk.crossSection( 296. );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 10. , WithinRel( xs.upperEnergyLimit() ) );
        CHECK_THAT( 6.337872, WithinRel( xs.boundCrossSection() ) );
        CHECK_THAT( 2.013538, WithinRel( xs.debyeWallerIntegral() ) );

        xs = chunk.crossSection( 400. );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 10. , WithinRel( xs.upperEnergyLimit() ) );
        CHECK_THAT( 6.337872, WithinRel( xs.boundCrossSection() ) );
        CHECK_THAT( 2.677764, WithinRel( xs.debyeWallerIntegral() ) );

        xs = chunk.crossSection( 500. );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 10. , WithinRel( xs.upperEnergyLimit() ) );
        CHECK_THAT( 6.337872, WithinRel( xs.boundCrossSection() ) );
        CHECK_THAT( 3.323456, WithinRel( xs.debyeWallerIntegral() ) );

        xs = chunk.crossSection( 600. );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 10. , WithinRel( xs.upperEnergyLimit() ) );
        CHECK_THAT( 6.337872, WithinRel( xs.boundCrossSection() ) );
        CHECK_THAT( 3.972601, WithinRel( xs.debyeWallerIntegral() ) );

        xs = chunk.crossSection( 700. );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 10. , WithinRel( xs.upperEnergyLimit() ) );
        CHECK_THAT( 6.337872, WithinRel( xs.boundCrossSection() ) );
        CHECK_THAT( 4.623738, WithinRel( xs.debyeWallerIntegral() ) );

        xs = chunk.crossSection( 800. );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 10. , WithinRel( xs.upperEnergyLimit() ) );
        CHECK_THAT( 6.337872, WithinRel( xs.boundCrossSection() ) );
        CHECK_THAT( 5.276127, WithinRel( xs.debyeWallerIntegral() ) );

        xs = chunk.crossSection( 1000. );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 10. , WithinRel( xs.upperEnergyLimit() ) );
        CHECK_THAT( 6.337872, WithinRel( xs.boundCrossSection() ) );
        CHECK_THAT( 6.583171, WithinRel( xs.debyeWallerIntegral() ) );

        xs = chunk.crossSection( 1200. );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 10. , WithinRel( xs.upperEnergyLimit() ) );
        CHECK_THAT( 6.337872, WithinRel( xs.boundCrossSection() ) );
        CHECK_THAT( 7.891981, WithinRel( xs.debyeWallerIntegral() ) );
      } // THEN
    } // WHEN

    WHEN( "requesting angular distribution data" ) {

      double lower = 1e-5;
      double upper = 10.;
      double xs = 6.337872;
      DebyeWallerIntegralData debyeWaller(

        { 296, 400, 500, 600, 700, 800, 1000, 1200 },
        { 2.013538, 2.677764, 3.323456, 3.972601,
          4.623738, 5.276127, 6.583171, 7.891981 }
      );

      IncoherentElasticScattering chunk( lower, upper, xs, std::move( debyeWaller ) );

      THEN( "the proper data is returned" ) {

        auto distribution = chunk.angularDistribution( 1e-5, 296. );

        CHECK_THAT( 1e-5    , WithinRel( distribution.incidentEnergy() ) );
        CHECK_THAT( 2.013538, WithinRel( distribution.debyeWallerIntegral() ) );

        distribution = chunk.angularDistribution( 1e-5, 400. );

        CHECK_THAT( 1e-5    , WithinRel( distribution.incidentEnergy() ) );
        CHECK_THAT( 2.677764, WithinRel( distribution.debyeWallerIntegral() ) );

        distribution = chunk.angularDistribution( 1e-5, 500. );

        CHECK_THAT( 1e-5    , WithinRel( distribution.incidentEnergy() ) );
        CHECK_THAT( 3.323456, WithinRel( distribution.debyeWallerIntegral() ) );

        distribution = chunk.angularDistribution( 1e-5, 600. );

        CHECK_THAT( 1e-5    , WithinRel( distribution.incidentEnergy() ) );
        CHECK_THAT( 3.972601, WithinRel( distribution.debyeWallerIntegral() ) );

        distribution = chunk.angularDistribution( 1e-5, 700. );

        CHECK_THAT( 1e-5    , WithinRel( distribution.incidentEnergy() ) );
        CHECK_THAT( 4.623738, WithinRel( distribution.debyeWallerIntegral() ) );

        distribution = chunk.angularDistribution( 1e-5, 800. );

        CHECK_THAT( 1e-5    , WithinRel( distribution.incidentEnergy() ) );
        CHECK_THAT( 5.276127, WithinRel( distribution.debyeWallerIntegral() ) );

        distribution = chunk.angularDistribution( 1e-5, 1000. );

        CHECK_THAT( 1e-5    , WithinRel( distribution.incidentEnergy() ) );
        CHECK_THAT( 6.583171, WithinRel( distribution.debyeWallerIntegral() ) );

        distribution = chunk.angularDistribution( 1e-5, 1200. );

        CHECK_THAT( 1e-5    , WithinRel( distribution.incidentEnergy() ) );
        CHECK_THAT( 7.891981, WithinRel( distribution.debyeWallerIntegral() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of IncoherentElasticScattering is given" ) {

      IncoherentElasticScattering chunk( 1e-5, 10., 6.337872,
                                         { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                           { 2.013538, 2.677764, 3.323456, 3.972601,
                                             4.623738, 5.276127, 6.583171, 7.891981 } } );

      THEN( "the bound xs can be changed" ) {

        double newxs = 25.;
        double original = 6.337872;

        chunk.boundCrossSection( newxs );

        CHECK( newxs == chunk.boundCrossSection() );

        chunk.boundCrossSection( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the Debye-Waller data can be changed" ) {

        DebyeWallerIntegralData newintegral(

          { 296, 1200 },
          { 2.013538, 7.891981 }
        );
        DebyeWallerIntegralData original(

          { 296, 400, 500, 600, 700, 800, 1000, 1200 },
          { 2.013538, 2.677764, 3.323456, 3.972601,
            4.623738, 5.276127, 6.583171, 7.891981 }
        );

        chunk.debyeWallerIntegral( newintegral );

        CHECK( newintegral == chunk.debyeWallerIntegral() );

        chunk.debyeWallerIntegral( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of IncoherentElasticScattering are given" ) {

      IncoherentElasticScattering left( 1e-5, 10., 6.337872,
                                        { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                          { 2.013538, 2.677764, 3.323456, 3.972601,
                                            4.623738, 5.276127, 6.583171, 7.891981 } } );
      IncoherentElasticScattering equal( 1e-5, 10., 6.337872,
                                         { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                           { 2.013538, 2.677764, 3.323456, 3.972601,
                                             4.623738, 5.276127, 6.583171, 7.891981 } } );
      IncoherentElasticScattering different( 1e-5, 10., 25.,
                                             { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                               { 2.013538, 2.677764, 3.323456, 3.972601,
                                                 4.623738, 5.276127, 6.583171, 7.891981 } } );

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

void verifyChunk( const IncoherentElasticScattering& chunk ) {

  CHECK_THAT( 6.337872, WithinRel( chunk.boundCrossSection() ) );

  CHECK_THAT( 1e-5, WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 10. , WithinRel( chunk.upperEnergyLimit() ) );

  CHECK( 8 == chunk.numberModeratorTemperatures() );
  CHECK( 8 == chunk.moderatorTemperatures().size() );
  CHECK_THAT(  296, WithinRel( chunk.moderatorTemperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.moderatorTemperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( chunk.moderatorTemperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.moderatorTemperatures()[7] ) );

  CHECK( 8 == chunk.debyeWallerIntegral().temperatures().size() );
  CHECK( 8 == chunk.debyeWallerIntegral().values().size() );
  CHECK_THAT(  296, WithinRel( chunk.debyeWallerIntegral().temperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.debyeWallerIntegral().temperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( chunk.debyeWallerIntegral().temperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.debyeWallerIntegral().temperatures()[7] ) );
  CHECK_THAT( 2.013538, WithinRel( chunk.debyeWallerIntegral().values()[0] ) );
  CHECK_THAT( 2.677764, WithinRel( chunk.debyeWallerIntegral().values()[1] ) );
  CHECK_THAT( 6.583171, WithinRel( chunk.debyeWallerIntegral().values()[6] ) );
  CHECK_THAT( 7.891981, WithinRel( chunk.debyeWallerIntegral().values()[7] ) );
}
