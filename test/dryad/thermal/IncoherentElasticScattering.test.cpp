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

      double xs = 6.337872;
      TabulatedDebyeWallerIntegral debyeWaller(

        { 296, 400, 500, 600, 700, 800, 1000, 1200 },
        { 2.013538, 2.677764, 3.323456, 3.972601,
          4.623738, 5.276127, 6.583171, 7.891981 }
      );

      IncoherentElasticScattering chunk( xs, std::move( debyeWaller ) );

      THEN( "IncoherentElasticScattering can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of IncoherentElasticScattering is given" ) {

      IncoherentElasticScattering chunk( 6.337872,
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

        TabulatedDebyeWallerIntegral newintegral(

          { 296, 1200 },
          { 2.013538, 7.891981 }
        );
        TabulatedDebyeWallerIntegral original(

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

      IncoherentElasticScattering chunk( 6.337872,
                                         { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                           { 2.013538, 2.677764, 3.323456, 3.972601,
                                             4.623738, 5.276127, 6.583171, 7.891981 } } );

      IncoherentElasticScattering left( 6.337872,
                                        { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                          { 2.013538, 2.677764, 3.323456, 3.972601,
                                            4.623738, 5.276127, 6.583171, 7.891981 } } );
      IncoherentElasticScattering equal( 6.337872,
                                         { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                                           { 2.013538, 2.677764, 3.323456, 3.972601,
                                             4.623738, 5.276127, 6.583171, 7.891981 } } );
      IncoherentElasticScattering different( 25.,
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

  CHECK( true == chunk.debyeWallerIntegral().isLinearised() );
  CHECK( 8 == chunk.debyeWallerIntegral().numberPoints() );
  CHECK( 1 == chunk.debyeWallerIntegral().numberRegions() );
  CHECK( 8 == chunk.debyeWallerIntegral().temperatures().size() );
  CHECK( 8 == chunk.debyeWallerIntegral().values().size() );
  CHECK( 1 == chunk.debyeWallerIntegral().boundaries().size() );
  CHECK( 1 == chunk.debyeWallerIntegral().interpolants().size() );
  CHECK( 7 == chunk.debyeWallerIntegral().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.debyeWallerIntegral().interpolants()[0] );
  CHECK_THAT(  296, WithinRel( chunk.debyeWallerIntegral().temperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.debyeWallerIntegral().temperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( chunk.debyeWallerIntegral().temperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.debyeWallerIntegral().temperatures()[7] ) );
  CHECK_THAT( 2.013538, WithinRel( chunk.debyeWallerIntegral().values()[0] ) );
  CHECK_THAT( 2.677764, WithinRel( chunk.debyeWallerIntegral().values()[1] ) );
  CHECK_THAT( 6.583171, WithinRel( chunk.debyeWallerIntegral().values()[6] ) );
  CHECK_THAT( 7.891981, WithinRel( chunk.debyeWallerIntegral().values()[7] ) );
}
