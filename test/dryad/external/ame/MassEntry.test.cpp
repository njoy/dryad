// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/external/ame/MassEntry.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::external::ame;

SCENARIO( "MassEntry" ) {

  GIVEN( "valid data for a MassEntry from AME 2020" ) {

    // Hydrogen-1 (AME 2020 values)
    id::ParticleID h1ID( "H1" );
    double h1MassExcess = 7288971.064;               // eV
    double h1MassExcessUncertainty = 0.013;          // eV
    double h1BindingEnergy = 0.0;                    // eV/A
    double h1BindingEnergyUncertainty = 0.0;         // eV/A
    double h1AtomicMass = 1.007825031898;            // amu
    double h1AtomicMassUncertainty = 0.000000000014; // amu

    THEN( "a MassEntry can be constructed" ) {

      MassEntry h1( h1ID, h1MassExcess, h1MassExcessUncertainty,
                    h1BindingEnergy, h1BindingEnergyUncertainty,
                    std::nullopt, std::nullopt,
                    h1AtomicMass, h1AtomicMassUncertainty );

      CHECK( id::ParticleID( "H1" ) == h1.identifier() );
      CHECK_THAT( 7288971.064, WithinRel( h1.massExcess().value() ) );
      CHECK_THAT( 0.013, WithinRel( h1.massExcessUncertainty().value() ) );
      CHECK_THAT( 0.0, WithinRel( h1.bindingEnergy().value() ) );
      CHECK_THAT( 0.0, WithinRel( h1.bindingEnergyUncertainty().value() ) );
      CHECK( std::nullopt == h1.betaDecayEnergy() );
      CHECK( std::nullopt == h1.betaDecayEnergyUncertainty() );
      CHECK_THAT( 1.007825031898, WithinRel( h1.atomicMass().value() ) );
      CHECK_THAT( 0.000000000014, WithinRel( h1.atomicMassUncertainty().value() ) );
    } // THEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of MassEntry is given" ) {

      MassEntry chunk( id::ParticleID( "H1" ), 7288971.064, 0.013,
                       0.0, 0.0, std::nullopt, std::nullopt,
                       1.007825031898, 0.000000000014 );

      THEN( "the identifier can be changed" ) {

        id::ParticleID newid( "H2" );
        id::ParticleID original( "H1" );

        chunk.identifier( newid );

        CHECK( newid == chunk.identifier() );

        chunk.identifier( original );

        CHECK( original == chunk.identifier() );
      } // THEN

      THEN( "the mass excess can be changed" ) {

        double newvalue = 13135720.0;  // H2 value
        double original = 7288971.064;

        chunk.massExcess( newvalue );

        CHECK( newvalue == chunk.massExcess().value() );

        chunk.massExcess( original );

        CHECK( original == chunk.massExcess().value() );
      } // THEN

      THEN( "the mass excess uncertainty can be changed" ) {

        std::optional< double > newuncertainty = 2.0;
        std::optional< double > original = 0.013;

        chunk.massExcessUncertainty( newuncertainty );

        CHECK( newuncertainty == chunk.massExcessUncertainty() );

        chunk.massExcessUncertainty( original );

        CHECK( original == chunk.massExcessUncertainty() );
      } // THEN

      THEN( "the binding energy can be changed" ) {

        std::optional< double > newvalue = 1112283.0;
        std::optional< double > original = 0.0;

        chunk.bindingEnergy( newvalue );

        CHECK( newvalue == chunk.bindingEnergy() );

        chunk.bindingEnergy( original );

        CHECK( original == chunk.bindingEnergy() );
      } // THEN

      THEN( "the binding energy uncertainty can be changed" ) {

        std::optional< double > newuncertainty = 0.5;
        std::optional< double > original = 0.0;

        chunk.bindingEnergyUncertainty( newuncertainty );

        CHECK( newuncertainty == chunk.bindingEnergyUncertainty() );

        chunk.bindingEnergyUncertainty( original );

        CHECK( original == chunk.bindingEnergyUncertainty() );
      } // THEN

      THEN( "the beta decay energy can be changed" ) {

        std::optional< double > newvalue = 1000000.0;
        std::optional< double > original = std::nullopt;

        chunk.betaDecayEnergy( newvalue );

        CHECK( newvalue == chunk.betaDecayEnergy() );

        chunk.betaDecayEnergy( original );

        CHECK( original == chunk.betaDecayEnergy() );
      } // THEN

      THEN( "the beta decay energy uncertainty can be changed" ) {

        std::optional< double > newuncertainty = 1000.0;
        std::optional< double > original = std::nullopt;

        chunk.betaDecayEnergyUncertainty( newuncertainty );

        CHECK( newuncertainty == chunk.betaDecayEnergyUncertainty() );

        chunk.betaDecayEnergyUncertainty( original );

        CHECK( original == chunk.betaDecayEnergyUncertainty() );
      } // THEN

      THEN( "the atomic mass can be changed" ) {

        double newmass = 1.008;
        double original = 1.007825031898;

        chunk.atomicMass( newmass );

        CHECK( newmass == chunk.atomicMass().value() );

        chunk.atomicMass( original );

        CHECK( original == chunk.atomicMass().value() );
      } // THEN

      THEN( "the atomic mass uncertainty can be changed" ) {

        std::optional< double > newuncertainty = 2.0e-10;
        std::optional< double > original = 0.000000000014;

        chunk.atomicMassUncertainty( newuncertainty );

        CHECK( newuncertainty == chunk.atomicMassUncertainty() );

        chunk.atomicMassUncertainty( original );

        CHECK( original == chunk.atomicMassUncertainty() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of MassEntry are given" ) {

      MassEntry left( id::ParticleID( "H1" ), 7288971.064, 0.013,
                      0.0, 0.0, std::nullopt, std::nullopt,
                      1.007825031898, 0.000000000014 );
      MassEntry equal( id::ParticleID( "H1" ), 7288971.064, 0.013,
                       0.0, 0.0, std::nullopt, std::nullopt,
                       1.007825031898, 0.000000000014 );
      MassEntry different( id::ParticleID( "H2" ), 13135720.0, 2.0,
                           1112283.0, 0.5, std::nullopt, std::nullopt,
                           2.01410177812, 4.0e-11 );

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