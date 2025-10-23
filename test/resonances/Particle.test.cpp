// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/Particle.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "Particle" ) {

  GIVEN( "valid data for a Particle" ) {

    // neutron
    auto neutronID = id::ParticleID::neutron();
    double neutronMass = 1.008664;
    double neutronSpin = 0.5;
    short neutronParity = +1;

    // proton
    auto protonID = id::ParticleID::proton();
    double protonMass = 1.007276;
    double protonSpin = 0.5;
    short protonParity = +1;

    // U235
    id::ParticleID u235ID( "U235" );
    double u235Mass = 235.0439299;
    double u235Spin = 0.0;
    short u235Parity = +1;

    // U235
    id::ParticleID u235e1ID( "U235_e1" );

    THEN( "a Particle can be constructed" ) {

      Particle neutron( neutronID, neutronMass,
                        neutronSpin, neutronParity );

      CHECK( id::ParticleID::neutron() == neutron.identifier() );
      CHECK_THAT( 1.008664, WithinRel( neutron.mass() ) );
      CHECK_THAT( 0.5, WithinRel( neutron.spin() ) );
      CHECK( 0.0 == neutron.charge() );
      CHECK( 0 == neutron.excitedState() );
      CHECK( +1 == neutron.parity() );

      Particle proton( protonID, protonMass,
                       protonSpin, protonParity );

      CHECK( id::ParticleID::proton() == proton.identifier() );
      CHECK_THAT( 1.007276, WithinRel( proton.mass() ) );
      CHECK_THAT( 0.5, WithinRel( proton.spin() ) );
      CHECK( 1 == proton.charge() );
      CHECK( 0 == proton.excitedState() );
      CHECK( +1 == proton.parity() );

      Particle u235( u235ID, u235Mass, u235Spin, u235Parity );

      CHECK( id::ParticleID( "U235" ) == u235.identifier() );
      CHECK_THAT( 235.0439299, WithinRel( u235.mass() ) );
      CHECK_THAT( 0., WithinRel( u235.spin() ) );
      CHECK( 92 == u235.charge() );
      CHECK( 0 == u235.excitedState() );
      CHECK( +1 == u235.parity() );

      Particle u235_e1( u235e1ID, u235Mass, u235Spin, u235Parity );

      CHECK( id::ParticleID( "U235_e1" ) == u235_e1.identifier() );
      CHECK_THAT( 235.0439299, WithinRel( u235_e1.mass() ) );
      CHECK_THAT( 0., WithinRel( u235_e1.spin() ) );
      CHECK( 92 == u235_e1.charge() );
      CHECK( 1 == u235_e1.excitedState() );
      CHECK( +1 == u235_e1.parity() );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Documentation are given" ) {

      Particle left( id::ParticleID::neutron(), 1.008664, 0.5, +1 );
      Particle equal( id::ParticleID::neutron(), 1.008664, 0.5, +1 );
      Particle different( id::ParticleID::proton(), 1.007276, 0.5, +1 );

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
