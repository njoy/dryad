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
    } // THEN
  } // GIVEN

  GIVEN( "valid values for l, i, I and s quantum numbers" ) {

    THEN( "the allowed channel spin values are generated" ) {

      // i=0.0, I=0.0, 0.5, 1.0
      auto values = ChannelQuantumNumbers::allowedChannelSpinValues( 0, 0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedChannelSpinValues( 0.0, 0.5 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedChannelSpinValues( 0.0, 1.0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );

      // i=0.5, I=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedChannelSpinValues( 0.5, 0.0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedChannelSpinValues( 0.5, 0.5 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );
      CHECK_THAT( 1.0, WithinRel( values[1] ) );

      values = ChannelQuantumNumbers::allowedChannelSpinValues( 0.5, 1.0 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );

      // i=1.0, I=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedChannelSpinValues( 1.0, 0.0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedChannelSpinValues( 1.0, 0.5 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );

      values = ChannelQuantumNumbers::allowedChannelSpinValues( 1.0, 1.0 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );
      CHECK_THAT( 1.0, WithinRel( values[1] ) );
      CHECK_THAT( 2.0, WithinRel( values[2] ) );
    } // THEN

    THEN( "the allowed total angular momentum values are generated "
          "using the incident particle and target spins" ) {

      // l=0, i=0.0, I=0.0, 0.5, 1.0
      auto values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 0, 0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 0.0, 0.5 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 0.0, 1.0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );

      // l=0, i=0.5, I=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 0.5, 0.0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 0.5, 0.5 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );
      CHECK_THAT( 1.0, WithinRel( values[1] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 0.5, 1.0 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );

      // l=0, i=1.0, I=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 1.0, 0.0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 1.0, 0.5 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 1.0, 1.0 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );
      CHECK_THAT( 1.0, WithinRel( values[1] ) );
      CHECK_THAT( 2.0, WithinRel( values[2] ) );

      // l=1, i=0.0, I=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 0.0, 0.0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 0.0, 0.5 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 0.0, 1.0 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );
      CHECK_THAT( 1.0, WithinRel( values[1] ) );
      CHECK_THAT( 2.0, WithinRel( values[2] ) );

      // l=1, i=0.5, I=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 0.5, 0.0 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 0.5, 0.5 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );
      CHECK_THAT( 1.0, WithinRel( values[1] ) );
      CHECK_THAT( 2.0, WithinRel( values[2] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 0.5, 1.0 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );
      CHECK_THAT( 2.5, WithinRel( values[2] ) );

      // l=1, i=1.0, I=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 1.0, 0.0 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );
      CHECK_THAT( 1.0, WithinRel( values[1] ) );
      CHECK_THAT( 2.0, WithinRel( values[2] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 1.0, 0.5 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );
      CHECK_THAT( 2.5, WithinRel( values[2] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 1.0, 1.0 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );
      CHECK_THAT( 2.0, WithinRel( values[1] ) );
      CHECK_THAT( 3.0, WithinRel( values[2] ) );
    } // THEN

    THEN( "the allowed total angular momentum values are generated "
          "using the channel spin" ) {

      // l=0, s=0.0, 0.5, 1.0
      auto values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 0.5 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 0, 1.0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );

      // l=1, s=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 0.5 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 0.5, WithinRel( values[0] ) );
      CHECK_THAT( 1.5, WithinRel( values[1] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 1, 1.0 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 0.0, WithinRel( values[0] ) );
      CHECK_THAT( 1.0, WithinRel( values[1] ) );
      CHECK_THAT( 2.0, WithinRel( values[2] ) );

      // l=2, s=0.0, 0.5, 1.0
      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 2, 0 );
      CHECK( 1 == values.size() );
      CHECK_THAT( 2.0, WithinRel( values[0] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 2, 0.5 );
      CHECK( 2 == values.size() );
      CHECK_THAT( 1.5, WithinRel( values[0] ) );
      CHECK_THAT( 2.5, WithinRel( values[1] ) );

      values = ChannelQuantumNumbers::allowedTotalAngularMomentumValues( 2, 1.0 );
      CHECK( 3 == values.size() );
      CHECK_THAT( 1.0, WithinRel( values[0] ) );
      CHECK_THAT( 2.0, WithinRel( values[1] ) );
      CHECK_THAT( 3.0, WithinRel( values[2] ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid ChannelQuantumNumbers instances" ) {

    ChannelQuantumNumbers id1( 0, 0.5, 0.5, +1 );
    ChannelQuantumNumbers id2( 1, 0.5, 0.5, +1 );

    THEN( "instances can be compared" ) {

      CHECK( ( id1 <  id1 ) == false );
      CHECK( ( id1 <= id1 ) == true );
      CHECK( ( id1 >  id1 ) == false );
      CHECK( ( id1 >= id1 ) == true );
      CHECK( ( id1 == id1 ) == true );
      CHECK( ( id1 != id1 ) == false );
      CHECK( ( id1 <  id2 ) == true );
      CHECK( ( id1 <= id2 ) == true );
      CHECK( ( id1 >  id2 ) == false );
      CHECK( ( id1 >= id2 ) == false );
      CHECK( ( id1 == id2 ) == false );
      CHECK( ( id1 != id2 ) == true );
      CHECK( ( id2 <  id1 ) == false );
      CHECK( ( id2 <= id1 ) == false );
      CHECK( ( id2 >  id1 ) == true );
      CHECK( ( id2 >= id1 ) == true );
      CHECK( ( id2 == id1 ) == false );
      CHECK( ( id2 != id1 ) == true );
    } // THEN
  } // GIVEN
} // SCENARIO
