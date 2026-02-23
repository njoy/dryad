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
      TabulatedScatteringKernel selfScatter(

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

  GIVEN( "setter functions" ) {

    WHEN( "an instance of InelasticScattering is given" ) {

      InelasticScattering chunk( 6.337872,
                                 TabulatedScatteringKernel(

                                   { 1., 2., 3., 4. },
                                   { { { 0., 4. }, { 0.5, 0.5 } },
                                     { { 0., 4. }, { 0.52, 0.48 } },
                                     { { 0., 4. }, { 0.48, 0.52 } },
                                     { { 0., 4. }, { 0.2, 0.8 } } }
                                 ) );

      THEN( "the bound xs can be changed" ) {

        double newxs = 25.;
        double original = 6.337872;

        chunk.boundCrossSection( newxs );

        CHECK( newxs == chunk.boundCrossSection() );

        chunk.boundCrossSection( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the scattering functions can be changed" ) {

        TabulatedScatteringKernel newfunctions(

          { 1., 4. },
          { { { 0., 4. }, { 0.5, 0.5 } },
            { { 0., 4. }, { 0.2, 0.8 } } }
        );
        TabulatedScatteringKernel original(

          { 1., 2., 3., 4. },
          { { { 0., 4. }, { 0.5, 0.5 } },
            { { 0., 4. }, { 0.52, 0.48 } },
            { { 0., 4. }, { 0.48, 0.52 } },
            { { 0., 4. }, { 0.2, 0.8 } } }
        );

        chunk.selfScatteringFunction( newfunctions );

        CHECK( newfunctions == chunk.selfScatteringFunction() );

        chunk.selfScatteringFunction( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of InelasticScattering are given" ) {

      InelasticScattering left( 6.337872,
                                TabulatedScatteringKernel(

                                  { 1., 2., 3., 4. },
                                  { { { 0., 4. }, { 0.5, 0.5 } },
                                    { { 0., 4. }, { 0.52, 0.48 } },
                                    { { 0., 4. }, { 0.48, 0.52 } },
                                    { { 0., 4. }, { 0.2, 0.8 } } }
                                ) );
      InelasticScattering equal( 6.337872,
                                 TabulatedScatteringKernel(

                                   { 1., 2., 3., 4. },
                                   { { { 0., 4. }, { 0.5, 0.5 } },
                                     { { 0., 4. }, { 0.52, 0.48 } },
                                     { { 0., 4. }, { 0.48, 0.52 } },
                                     { { 0., 4. }, { 0.2, 0.8 } } }
                                 ) );
      InelasticScattering different( 6.337872,
                                     TabulatedScatteringKernel(

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

  CHECK( true == chunk.isIncoherentApproximation() );

  CHECK_THAT( 6.337872, WithinRel( chunk.boundCrossSection() ) );

  CHECK( 4 == chunk.selfScatteringFunction().numberPoints() );
  CHECK( 1 == chunk.selfScatteringFunction().numberRegions() );
  CHECK( 4 == chunk.selfScatteringFunction().energyTransfers().size() );
  CHECK( 4 == chunk.selfScatteringFunction().functions().size() );
  CHECK( 1 == chunk.selfScatteringFunction().boundaries().size() );
  CHECK( 1 == chunk.selfScatteringFunction().interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.selfScatteringFunction().energyTransfers()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.selfScatteringFunction().energyTransfers()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.selfScatteringFunction().energyTransfers()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.selfScatteringFunction().energyTransfers()[3] ) );
  CHECK( 2 == chunk.selfScatteringFunction().functions()[0].momentumTransfers().size() );
  CHECK( 2 == chunk.selfScatteringFunction().functions()[0].values().size() );
  CHECK( 2 == chunk.selfScatteringFunction().functions()[1].momentumTransfers().size() );
  CHECK( 2 == chunk.selfScatteringFunction().functions()[1].values().size() );
  CHECK( 2 == chunk.selfScatteringFunction().functions()[2].momentumTransfers().size() );
  CHECK( 2 == chunk.selfScatteringFunction().functions()[2].values().size() );
  CHECK( 2 == chunk.selfScatteringFunction().functions()[3].momentumTransfers().size() );
  CHECK( 2 == chunk.selfScatteringFunction().functions()[3].values().size() );
  CHECK_THAT( 0., WithinRel( chunk.selfScatteringFunction().functions()[0].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.selfScatteringFunction().functions()[0].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.selfScatteringFunction().functions()[1].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.selfScatteringFunction().functions()[1].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.selfScatteringFunction().functions()[2].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.selfScatteringFunction().functions()[2].momentumTransfers()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.selfScatteringFunction().functions()[3].momentumTransfers()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.selfScatteringFunction().functions()[3].momentumTransfers()[1] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.selfScatteringFunction().functions()[0].values()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( chunk.selfScatteringFunction().functions()[0].values()[1] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.selfScatteringFunction().functions()[1].values()[0] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.selfScatteringFunction().functions()[1].values()[1] ) );
  CHECK_THAT( 0.48, WithinRel( chunk.selfScatteringFunction().functions()[2].values()[0] ) );
  CHECK_THAT( 0.52, WithinRel( chunk.selfScatteringFunction().functions()[2].values()[1] ) );
  CHECK_THAT( 0.2 , WithinRel( chunk.selfScatteringFunction().functions()[3].values()[0] ) );
  CHECK_THAT( 0.8 , WithinRel( chunk.selfScatteringFunction().functions()[3].values()[1] ) );
  CHECK( 3 == chunk.selfScatteringFunction().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.selfScatteringFunction().interpolants()[0] );
}
