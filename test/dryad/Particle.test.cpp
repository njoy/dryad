// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/Particle.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

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
    double u235e1Energy = 1e+6;
    double u235e1EnergyUncertainty = 1e+3;

    THEN( "a Particle can be constructed" ) {

      Particle neutron( neutronID, neutronMass,
                        neutronSpin, neutronParity );

      CHECK( id::ParticleID::neutron() == neutron.identifier() );
      CHECK_THAT( 1.008664, WithinRel( neutron.mass() ) );
      CHECK_THAT( 0.5, WithinRel( neutron.spin().value() ) );
      CHECK( 0.0 == neutron.charge() );
      CHECK( 0 == neutron.excitedState() );
      CHECK( +1 == neutron.parity().value() );
      CHECK( std::nullopt == neutron.energy() );
      CHECK( std::nullopt == neutron.massUncertainty() );
      CHECK( std::nullopt == neutron.energyUncertainty() );

      Particle proton( protonID, protonMass,
                       protonSpin, protonParity );

      CHECK( id::ParticleID::proton() == proton.identifier() );
      CHECK_THAT( 1.007276, WithinRel( proton.mass() ) );
      CHECK_THAT( 0.5, WithinRel( proton.spin().value() ) );
      CHECK( 1 == proton.charge() );
      CHECK( 0 == proton.excitedState() );
      CHECK( +1 == proton.parity().value() );
      CHECK( std::nullopt == proton.energy() );
      CHECK( std::nullopt == proton.massUncertainty() );
      CHECK( std::nullopt == proton.energyUncertainty() );

      Particle u235( u235ID, u235Mass, u235Spin, u235Parity, 0. );

      CHECK( id::ParticleID( "U235" ) == u235.identifier() );
      CHECK_THAT( 235.0439299, WithinRel( u235.mass() ) );
      CHECK_THAT( 0., WithinRel( u235.spin().value() ) );
      CHECK( 92 == u235.charge() );
      CHECK( 0 == u235.excitedState() );
      CHECK( +1 == u235.parity().value() );
      CHECK( 0.0 == u235.energy() );
      CHECK( std::nullopt == u235.massUncertainty() );
      CHECK( std::nullopt == u235.energyUncertainty() );

      Particle u235_e1( u235e1ID, u235Mass, u235Spin, u235Parity,
                        u235e1Energy, std::nullopt, u235e1EnergyUncertainty );

      CHECK( id::ParticleID( "U235_e1" ) == u235_e1.identifier() );
      CHECK_THAT( 235.0439299, WithinRel( u235_e1.mass() ) );
      CHECK_THAT( 0., WithinRel( u235_e1.spin().value() ) );
      CHECK( 92 == u235_e1.charge() );
      CHECK( 1 == u235_e1.excitedState() );
      CHECK( +1 == u235_e1.parity().value() );
      CHECK( 1e+6 == u235_e1.energy() );
      CHECK( std::nullopt == u235_e1.massUncertainty() );
      CHECK( std::nullopt != u235_e1.energyUncertainty() );
      CHECK_THAT( 1e+3, WithinRel( u235_e1.energyUncertainty().value() ) );
    } // THEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of Particle is given" ) {

      Particle chunk( id::ParticleID( "U235_e1" ), 235.0439299, 0., +1,
                      1e+6, std::nullopt, 1e+3 );

      THEN( "the identifier can be changed" ) {

        id::ParticleID newid( "U235" );
        id::ParticleID original( "U235_e1" );

        chunk.identifier( newid );

        CHECK( newid == chunk.identifier() );

        chunk.identifier( original );

        CHECK( original == chunk.identifier() );
      } // THEN

      THEN( "the mass can be changed" ) {

        double newmass = 235;
        double original = 235.0439299;

        chunk.mass( newmass );

        CHECK( newmass == chunk.mass() );

        chunk.mass( original );

        CHECK( original == chunk.mass() );
      } // THEN

      THEN( "the mass uncertainty can be changed" ) {

        std::optional< double > newuncertainty = 1.;
        std::optional< double > original = std::nullopt;

        chunk.massUncertainty( newuncertainty );

        CHECK( newuncertainty == chunk.massUncertainty() );

        chunk.massUncertainty( original );

        CHECK( original == chunk.massUncertainty() );
      } // THEN

      THEN( "the level energy can be changed" ) {

        double newenergy = 1e+5;
        double original = 1e+6;

        chunk.energy( newenergy );

        CHECK( newenergy == chunk.energy() );

        chunk.energy( original );

        CHECK( original == chunk.energy() );
      } // THEN

      THEN( "the level energy uncertainty can be changed" ) {

        std::optional< double > newuncertainty = std::nullopt;
        std::optional< double > original = 1e+3;

        chunk.energyUncertainty( newuncertainty );

        CHECK( newuncertainty == chunk.energyUncertainty() );

        chunk.energyUncertainty( original );

        CHECK( original == chunk.energyUncertainty() );
      } // THEN

      THEN( "the spin can be changed" ) {

        double newspin = .5;
        double original = 0;

        chunk.spin( newspin );

        CHECK( newspin == chunk.spin().value() );

        chunk.spin( original );

        CHECK( original == chunk.spin().value() );
      } // THEN

      THEN( "the parity can be changed" ) {

        double newparity = -1;
        double original = +1;

        chunk.parity( newparity );

        CHECK( newparity == chunk.parity().value() );

        chunk.parity( original );

        CHECK( original == chunk.parity().value() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Particle are given" ) {

      Particle left( id::ParticleID::neutron(), 1.008664, 0.5, +1 );
      Particle equal( id::ParticleID::neutron(), 1.008664, 0.5, +1 );
      Particle different( id::ParticleID( "U235_e1" ), 235.0439299, 0., +1,
                          1e+6, std::nullopt, 1e+3 );

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
