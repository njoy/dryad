// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/ThermalScattering.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const ThermalScattering& );

SCENARIO( "ThermalScattering" ) {

  GIVEN( "valid data for a ThermalScattering" ) {

    WHEN( "the data is given explicitly" ) {

      IncoherentElasticScattering
      incoherent( 6.337872,
                  { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                    { 2.013538, 2.677764, 3.323456, 3.972601,
                      4.623738, 5.276127, 6.583171, 7.891981 } } );

      ThermalScattering chunk( std::nullopt, std::move( incoherent ) );

      verifyChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of ThermalScattering is given" ) {

      ThermalScattering chunk( std::nullopt,
                               IncoherentElasticScattering(
                                 6.337872,
                                 { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                   { 2.013538, 2.677764, 3.323456, 3.972601,
                                     4.623738, 5.276127, 6.583171, 7.891981 } } ) );

      THEN( "the projectile identifier can be changed" ) {

        IncoherentElasticScattering newincoherent( 25.,
                                                   { { 296, 1200 },
                                                     { 2.013538, 7.891981 } } );
        IncoherentElasticScattering original( 6.337872,
                                              { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                                { 2.013538, 2.677764, 3.323456, 3.972601,
                                                  4.623738, 5.276127, 6.583171, 7.891981 } } );

        chunk.incoherentElasticScattering( newincoherent );

        CHECK( newincoherent == chunk.incoherentElasticScattering() );

        chunk.incoherentElasticScattering( original );

        verifyChunk( chunk );
      }
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ThermalScattering are given" ) {

      ThermalScattering left( std::nullopt,
                              IncoherentElasticScattering(
                                6.337872,
                                { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                  { 2.013538, 2.677764, 3.323456, 3.972601,
                                    4.623738, 5.276127, 6.583171, 7.891981 } } ) );
      ThermalScattering equal( std::nullopt,
                               IncoherentElasticScattering(
                                 6.337872,
                                 { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                   { 2.013538, 2.677764, 3.323456, 3.972601,
                                     4.623738, 5.276127, 6.583171, 7.891981 } } ) );
      ThermalScattering different( std::nullopt,
                                   IncoherentElasticScattering(
                                     25.,
                                     { { 296, 1200 },
                                       { 2.013538, 7.891981 } } ) );

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

void verifyChunk( const ThermalScattering& chunk ) {

  // documentation
  CHECK( std::nullopt == chunk.documentation().awr() );
  CHECK( std::nullopt == chunk.documentation().library() );
  CHECK( std::nullopt == chunk.documentation().version() );
  CHECK( std::nullopt == chunk.documentation().description() );

  // content
  CHECK( false == chunk.hasCoherentElasticScattering() );
  CHECK( true == chunk.hasIncoherentElasticScattering() );
  CHECK( true == chunk.hasElasticScattering() );
  CHECK( false == chunk.hasInelasticScattering() );

  // coherent elastic
  CHECK( std::nullopt == chunk.coherentElasticScattering() );

  // incoherent elastic
  CHECK( std::nullopt != chunk.incoherentElasticScattering() );
  auto incoherent = chunk.incoherentElasticScattering().value();
  CHECK_THAT( 6.337872, WithinRel( incoherent.boundCrossSection() ) );
  CHECK( 8 == incoherent.debyeWallerIntegral().temperatures().size() );
  CHECK( 8 == incoherent.debyeWallerIntegral().values().size() );
  CHECK_THAT(  296, WithinRel( incoherent.debyeWallerIntegral().temperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( incoherent.debyeWallerIntegral().temperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( incoherent.debyeWallerIntegral().temperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( incoherent.debyeWallerIntegral().temperatures()[7] ) );
  CHECK_THAT( 2.013538, WithinRel( incoherent.debyeWallerIntegral().values()[0] ) );
  CHECK_THAT( 2.677764, WithinRel( incoherent.debyeWallerIntegral().values()[1] ) );
  CHECK_THAT( 6.583171, WithinRel( incoherent.debyeWallerIntegral().values()[6] ) );
  CHECK_THAT( 7.891981, WithinRel( incoherent.debyeWallerIntegral().values()[7] ) );
}
