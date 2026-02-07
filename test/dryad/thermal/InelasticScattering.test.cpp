// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/thermal/InelasticScattering.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const InelasticScattering& );

SCENARIO( "InelasticScattering" ) {

  GIVEN( "valid self scattering scattering data" ) {

    WHEN( "the data is given explicitly" ) {

      double xs = 6.337872;
      TabulatedScatteringFunctions selfScatter(

        { 1., 2., 3., 4. },
        { { { 0., 4. }, { 0.5, 0.5 } },
          { { 0., 4. }, { 0.52, 0.48 } },
          { { 0., 4. }, { 0.48, 0.52 } },
          { { 0., 4. }, { 0.2, 0.8 } } }
      );

      InelasticScattering chunk( xs, std::move( selfScatter ) );

      THEN( "InelasticScattering can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

//  GIVEN( "setter functions" ) {
//
//    WHEN( "an instance of InelasticScattering is given" ) {
//
//      InelasticScattering chunk( 6.337872,
//                                         { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
//                                           { 2.013538, 2.677764, 3.323456, 3.972601,
//                                             4.623738, 5.276127, 6.583171, 7.891981 } } );
//
//      THEN( "the bound xs can be changed" ) {
//
//        double newxs = 25.;
//        double original = 6.337872;
//
//        chunk.boundCrossSection( newxs );
//
//        CHECK( newxs == chunk.boundCrossSection() );
//
//        chunk.boundCrossSection( original );
//
//        verifyChunk( chunk );
//      } // THEN
//
//      THEN( "the Debye-Waller data can be changed" ) {
//
//        TabulatedScatteringFunctions newintegral(
//
//          { 296, 1200 },
//          { 2.013538, 7.891981 }
//        );
//        TabulatedScatteringFunctions original(
//
//          { 296, 400, 500, 600, 700, 800, 1000, 1200 },
//          { 2.013538, 2.677764, 3.323456, 3.972601,
//            4.623738, 5.276127, 6.583171, 7.891981 }
//        );
//
//        chunk.debyeWallerIntegral( newintegral );
//
//        CHECK( newintegral == chunk.debyeWallerIntegral() );
//
//        chunk.debyeWallerIntegral( original );
//
//        verifyChunk( chunk );
//      } // THEN
//    } // WHEN
//  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of InelasticScattering are given" ) {

      double xs = 6.337872;
      TabulatedScatteringFunctions(

        { 1., 2., 3., 4. },
        { { { 0., 4. }, { 0.5, 0.5 } },
          { { 0., 4. }, { 0.52, 0.48 } },
          { { 0., 4. }, { 0.48, 0.52 } },
          { { 0., 4. }, { 0.2, 0.8 } } }
      );

      InelasticScattering left( 6.337872,
                                TabulatedScatteringFunctions(

                                  { 1., 2., 3., 4. },
                                  { { { 0., 4. }, { 0.5, 0.5 } },
                                    { { 0., 4. }, { 0.52, 0.48 } },
                                    { { 0., 4. }, { 0.48, 0.52 } },
                                    { { 0., 4. }, { 0.2, 0.8 } } }
                                ) );
      InelasticScattering equal( 6.337872,
                                 TabulatedScatteringFunctions(

                                   { 1., 2., 3., 4. },
                                   { { { 0., 4. }, { 0.5, 0.5 } },
                                     { { 0., 4. }, { 0.52, 0.48 } },
                                     { { 0., 4. }, { 0.48, 0.52 } },
                                     { { 0., 4. }, { 0.2, 0.8 } } }
                                 ) );
      InelasticScattering different( 6.337872,
                                     TabulatedScatteringFunctions(

                                       { 1., 4. },
                                       { { { 0., 4. }, { 0.5, 0.5 } },
                                         { { 0., 4. }, { 0.2, 0.8 } } }
                                     ) );

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

void verifyChunk( const InelasticScattering& chunk ) {



}
