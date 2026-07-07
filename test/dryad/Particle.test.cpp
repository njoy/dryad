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
    double u235Energy = 0.;

    // U235
    id::ParticleID u235e1ID( "U235_e1" );
    double u235e1Energy = 1e+6;
    double u235e1EnergyUncertainty = 1e+3;

    THEN( "a Particle can be constructed using data" ) {

      Particle particle( neutronID, neutronMass,
                         neutronSpin, neutronParity );

      CHECK( id::ParticleID::neutron() == particle.identifier() );
      CHECK_THAT( 1.008664, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( 0.0 == particle.charge() );
      CHECK( 0 == particle.excitedState() );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK( std::nullopt == particle.massUncertainty() );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle( protonID, protonMass,
                           protonSpin, protonParity );

      CHECK( id::ParticleID::proton() == particle.identifier() );
      CHECK_THAT( 1.007276, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( 1 == particle.charge() );
      CHECK( 0 == particle.excitedState() );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK( std::nullopt == particle.massUncertainty() );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle( u235ID, u235Mass, u235Spin, u235Parity, u235Energy );

      CHECK( id::ParticleID( "U235" ) == particle.identifier() );
      CHECK_THAT( 235.0439299, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0., WithinRel( particle.spin().value() ) );
      CHECK( 92 == particle.charge() );
      CHECK( 0 == particle.excitedState() );
      CHECK( +1 == particle.parity().value() );
      CHECK( 0.0 == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK( std::nullopt == particle.massUncertainty() );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle( u235e1ID, u235Mass, u235Spin, u235Parity,
                           u235e1Energy, std::nullopt, std::nullopt,
                           std::nullopt, u235e1EnergyUncertainty );

      CHECK( id::ParticleID( "U235_e1" ) == particle.identifier() );
      CHECK_THAT( 235.0439299, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0., WithinRel( particle.spin().value() ) );
      CHECK( 92 == particle.charge() );
      CHECK( 1 == particle.excitedState() );
      CHECK( +1 == particle.parity().value() );
      CHECK( 1e+6 == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK( std::nullopt == particle.massUncertainty() );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt != particle.energyUncertainty() );
      CHECK_THAT( 1e+3, WithinRel( particle.energyUncertainty().value() ) );
    } // THEN

    THEN( "a Particle can be constructed using static functions" ) {

      using namespace njoy;

      // fundamental particles

      Particle particle = Particle::photon();
      CHECK( id::ParticleID::photon() == particle.identifier() );
      CHECK_THAT( 0., WithinRel( particle.mass().value() ) );
      CHECK_THAT( 1.0, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( 0., WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::electron();
      CHECK( id::ParticleID::electron() == particle.identifier() );
      CHECK_THAT( constants::electron_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::electron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::positron();
      CHECK( id::ParticleID::positron() == particle.identifier() );
      CHECK_THAT( constants::electron_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( -1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::electron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::neutron();
      CHECK( id::ParticleID::neutron() == particle.identifier() );
      CHECK_THAT( constants::neutron_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::neutron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::proton();
      CHECK( id::ParticleID::proton() == particle.identifier() );
      CHECK_THAT( constants::proton_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::proton_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::deuteron();
      CHECK( id::ParticleID::deuteron() == particle.identifier() );
      CHECK_THAT( constants::deuteron_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 1.0, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::deuteron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::triton();
      CHECK( id::ParticleID::triton() == particle.identifier() );
      CHECK_THAT( constants::triton_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::triton_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::helion();
      CHECK( id::ParticleID::helion() == particle.identifier() );
      CHECK_THAT( constants::helion_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::helion_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::alpha();
      CHECK( id::ParticleID::alpha() == particle.identifier() );
      CHECK_THAT( constants::alpha_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.0, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::alpha_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      // default particle instances

      particle = Particle::defaultParticle( id::ParticleID::photon() );
      CHECK( id::ParticleID::photon() == particle.identifier() );
      CHECK_THAT( 0., WithinRel( particle.mass().value() ) );
      CHECK_THAT( 1.0, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( 0., WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID::electron() );
      CHECK( id::ParticleID::electron() == particle.identifier() );
      CHECK_THAT( constants::electron_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::electron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID::positron() );
      CHECK( id::ParticleID::positron() == particle.identifier() );
      CHECK_THAT( constants::electron_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( -1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::electron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID::neutron() );
      CHECK( id::ParticleID::neutron() == particle.identifier() );
      CHECK_THAT( constants::neutron_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::neutron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID::proton() );
      CHECK( id::ParticleID::proton() == particle.identifier() );
      CHECK_THAT( constants::proton_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::proton_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID::deuteron() );
      CHECK( id::ParticleID::deuteron() == particle.identifier() );
      CHECK_THAT( constants::deuteron_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 1.0, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::deuteron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID::triton() );
      CHECK( id::ParticleID::triton() == particle.identifier() );
      CHECK_THAT( constants::triton_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::triton_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID::helion() );
      CHECK( id::ParticleID::helion() == particle.identifier() );
      CHECK_THAT( constants::helion_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::helion_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID::alpha() );
      CHECK( id::ParticleID::alpha() == particle.identifier() );
      CHECK_THAT( constants::alpha_mass, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.0, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( constants::alpha_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID( "U235" ) );
      CHECK( id::ParticleID( "U235" ) == particle.identifier() );
      CHECK_THAT( 235.043928117, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 3.5, WithinRel( particle.spin().value() ) );
      CHECK( -1 == particle.parity().value() );
      CHECK_THAT( 0., WithinRel( particle.energy().value() ) );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( 1.198e-6, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID( "U235_e1" ) );
      CHECK( id::ParticleID( "U235_e1" ) == particle.identifier() );
      CHECK_THAT( 235.043928117, WithinRel( particle.mass().value() ) );
      CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
      CHECK( +1 == particle.parity().value() );
      CHECK_THAT( 76., WithinRel( particle.energy().value() ) );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK_THAT( 1.198e-6, WithinRel( particle.massUncertainty().value() ) );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID( "H" ) );
      CHECK( id::ParticleID( "H" ) == particle.identifier() );
      CHECK( std::nullopt == particle.mass() );
      CHECK( std::nullopt == particle.spin() );
      CHECK( std::nullopt == particle.parity() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK( std::nullopt == particle.massUncertainty() );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );

      particle = Particle::defaultParticle( id::ParticleID( "H{1s1/2}" ) );
      CHECK( id::ParticleID( "H" ) == particle.identifier() );
      CHECK( std::nullopt == particle.mass() );
      CHECK( std::nullopt == particle.spin() );
      CHECK( std::nullopt == particle.parity() );
      CHECK( std::nullopt == particle.energy() );
      CHECK( std::nullopt == particle.nuclearMass() );
      CHECK( std::nullopt == particle.massUncertainty() );
      CHECK( std::nullopt == particle.nuclearMassUncertainty() );
      CHECK( std::nullopt == particle.energyUncertainty() );
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

        CHECK( newmass == chunk.mass().value() );

        chunk.mass( original );

        CHECK( original == chunk.mass().value() );
      } // THEN

      THEN( "the mass uncertainty can be changed" ) {

        std::optional< double > newuncertainty = 1.;
        std::optional< double > original = std::nullopt;

        chunk.massUncertainty( newuncertainty );

        CHECK( newuncertainty == chunk.massUncertainty() );

        chunk.massUncertainty( original );

        CHECK( original == chunk.massUncertainty() );
      } // THEN

      THEN( "the nuclear mass can be changed" ) {

        std::optional< double > newmass = 235;
        std::optional< double > original = std::nullopt;

        chunk.nuclearMass( newmass );

        CHECK( newmass == chunk.nuclearMass() );

        chunk.nuclearMass( original );

        CHECK( original == chunk.nuclearMass() );
      } // THEN

      THEN( "the nuclear mass uncertainty can be changed" ) {

        std::optional< double > newuncertainty = 1.;
        std::optional< double > original = std::nullopt;

        chunk.nuclearMassUncertainty( newuncertainty );

        CHECK( newuncertainty == chunk.nuclearMassUncertainty() );

        chunk.nuclearMassUncertainty( original );

        CHECK( original == chunk.nuclearMassUncertainty() );
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
