// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/external/ripl3/LevelEntry.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::external::ripl3;

SCENARIO( "LevelEntry" ) {

  GIVEN( "valid data for a LevelEntry" ) {

    // neutron
    auto neutronID = id::ParticleID::neutron();
    double neutronSpin = 0.5;
    short neutronParity = +1;

    // proton
    auto protonID = id::ParticleID::proton();
    double protonSpin = 0.5;
    short protonParity = +1;

    // U235 ground state
    id::ParticleID u235ID( "U235" );
    double u235Spin = 3.5;           // 7/2
    short u235Parity = -1;           // negative
    double u235Energy = 0.;
    double u235HalfLife = 2.221e16;  // radioactive decay half-life in seconds

    // U235 first excited state (isomeric state at 76 eV)
    id::ParticleID u235e1ID( "U235_e1" );
    double u235e1Spin = 0.5;         // 1/2
    short u235e1Parity = +1;         // positive
    double u235e1Energy = 76.0;      // 76 eV (isomeric state)
    double u235e1HalfLife = 1560.0;  // ~26 minutes in seconds

    THEN( "a LevelEntry can be constructed" ) {

      LevelEntry neutron( neutronID, std::nullopt, neutronSpin, neutronParity, std::nullopt );

      CHECK( id::ParticleID::neutron() == neutron.identifier() );
      CHECK( std::nullopt == neutron.energy() );
      CHECK_THAT( 0.5, WithinRel( neutron.spin().value() ) );
      CHECK( +1 == neutron.parity() );
      CHECK( std::nullopt == neutron.halfLife() );

      LevelEntry proton( protonID, std::nullopt, protonSpin, protonParity, std::nullopt );

      CHECK( id::ParticleID::proton() == proton.identifier() );
      CHECK( std::nullopt == proton.energy() );
      CHECK_THAT( 0.5, WithinRel( proton.spin().value() ) );
      CHECK( +1 == proton.parity() );
      CHECK( std::nullopt == proton.halfLife() );

      LevelEntry u235( u235ID, u235Energy, u235Spin, u235Parity, u235HalfLife );

      CHECK( id::ParticleID( "U235" ) == u235.identifier() );
      CHECK( 0.0 == u235.energy() );
      CHECK_THAT( 3.5, WithinRel( u235.spin().value() ) );
      CHECK( -1 == u235.parity() );
      CHECK( std::nullopt != u235.halfLife() );
      CHECK_THAT( 2.221e16, WithinRel( u235.halfLife().value() ) );

      LevelEntry u235_e1( u235e1ID, u235e1Energy, u235e1Spin, u235e1Parity, u235e1HalfLife );

      CHECK( id::ParticleID( "U235_e1" ) == u235_e1.identifier() );
      CHECK( std::nullopt != u235_e1.energy() );
      CHECK_THAT( 76.0, WithinRel( u235_e1.energy().value() ) );
      CHECK_THAT( 0.5, WithinRel( u235_e1.spin().value() ) );
      CHECK( +1 == u235_e1.parity() );
      CHECK( std::nullopt != u235_e1.halfLife() );
      CHECK_THAT( 1560.0, WithinRel( u235_e1.halfLife().value() ) );
    } // THEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of LevelEntry is given" ) {

      LevelEntry chunk( id::ParticleID( "U235_e1" ), 76.0, 0.5, +1, 1560.0 );

      THEN( "the identifier can be changed" ) {

        id::ParticleID newid( "U235" );
        id::ParticleID original( "U235_e1" );

        chunk.identifier( newid );

        CHECK( newid == chunk.identifier() );

        chunk.identifier( original );

        CHECK( original == chunk.identifier() );
      } // THEN

      THEN( "the energy can be changed" ) {

        std::optional< double > newenergy = 1e+5;
        std::optional< double > original = 76.0;

        chunk.energy( newenergy );

        CHECK( newenergy == chunk.energy() );

        chunk.energy( original );

        CHECK( original == chunk.energy() );
      } // THEN

      THEN( "the spin can be changed" ) {

        double newspin = 1.5;
        double original = 0.5;

        chunk.spin( newspin );

        CHECK_THAT( newspin, WithinRel( chunk.spin().value() ) );

        chunk.spin( original );

        CHECK_THAT( original, WithinRel( chunk.spin().value() ) );
      } // THEN

      THEN( "the parity can be changed" ) {

        short newparity = -1;
        short original = +1;

        chunk.parity( newparity );

        CHECK( newparity == chunk.parity() );

        chunk.parity( original );

        CHECK( original == chunk.parity() );
      } // THEN

      THEN( "the half life can be changed" ) {

        std::optional< double > newhalflife = 1e+10;
        std::optional< double > original = 1560.0;

        chunk.halfLife( newhalflife );

        CHECK( newhalflife == chunk.halfLife() );

        chunk.halfLife( original );

        CHECK( original == chunk.halfLife() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of LevelEntry are given" ) {

      LevelEntry left( id::ParticleID::neutron(), std::nullopt, 0.5, +1, std::nullopt );
      LevelEntry equal( id::ParticleID::neutron(), std::nullopt, 0.5, +1, std::nullopt );
      LevelEntry different( id::ParticleID( "U235_e1" ), 76.0, 0.5, +1, 1560.0 );

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
