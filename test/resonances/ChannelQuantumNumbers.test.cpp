// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/ChannelQuantumNumbers.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ChannelQuantumNumbers" ) {

  GIVEN( "valid data for a ChannelQuantumNumbers" ) {

    unsigned int l = 1;
    double s = 0.5;
    double J = 1.5;
    short pi = +1;

    THEN( "a ChannelQuantumNumbers can be constructed" ) {

      ChannelQuantumNumbers numbers( l, s, J, pi );

      CHECK( 1 == numbers.orbitalAngularMomentum() );
      CHECK( 0.5 == numbers.spin() );
      CHECK( 1.5 == numbers.totalAngularMomentum() );
      CHECK( +1 == numbers.parity() );
//      CHECK( "{1,1/2,3/2+}" == numbers.toString() );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Documentation are given" ) {

      ChannelQuantumNumbers left( 1, 0.5, 1.5, +1 );
      ChannelQuantumNumbers equal( 1, 0.5, 1.5, +1 );
      ChannelQuantumNumbers different( 0, 0.5, 1.5, -1 );

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
