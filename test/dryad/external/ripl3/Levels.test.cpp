// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/external/ripl3/Levels.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::external::ripl3;

SCENARIO( "Levels" ) {

  GIVEN( "the Levels static repository" ) {

    THEN( "predefined particles can be retrieved" ) {

      // photon
      const auto& photon = Levels::level( id::ParticleID::photon() );

      CHECK( id::ParticleID::photon() == photon.identifier() );
      CHECK( std::nullopt == photon.energy() );
      CHECK_THAT( 1.0, WithinRel( photon.spin().value() ) );
      CHECK( -1 == photon.parity() );
      CHECK( std::nullopt == photon.halfLife() );

      // neutron
      const auto& neutron = Levels::level( id::ParticleID::neutron() );

      CHECK( id::ParticleID::neutron() == neutron.identifier() );
      CHECK( std::nullopt == neutron.energy() );
      CHECK_THAT( 0.5, WithinRel( neutron.spin().value() ) );
      CHECK( 1 == neutron.parity() );
      CHECK( std::nullopt == neutron.halfLife() );

      // proton
      const auto& proton = Levels::level( id::ParticleID::proton() );

      CHECK( id::ParticleID::proton() == proton.identifier() );
      CHECK( std::nullopt == proton.energy() );
      CHECK_THAT( 0.5, WithinRel( proton.spin().value() ) );
      CHECK( 1 == proton.parity() );
      CHECK( std::nullopt == proton.halfLife() );

      // deuteron
      const auto& deuteron = Levels::level( id::ParticleID::deuteron() );

      CHECK( id::ParticleID::deuteron() == deuteron.identifier() );
      CHECK( std::nullopt == deuteron.energy() );
      CHECK_THAT( 1.0, WithinRel( deuteron.spin().value() ) );
      CHECK( 1 == deuteron.parity() );
      CHECK( std::nullopt == deuteron.halfLife() );

      // triton
      const auto& triton = Levels::level( id::ParticleID::triton() );

      CHECK( id::ParticleID::triton() == triton.identifier() );
      CHECK( std::nullopt == triton.energy() );
      CHECK_THAT( 0.5, WithinRel( triton.spin().value() ) );
      CHECK( 1 == triton.parity() );
      CHECK( std::nullopt == triton.halfLife() );

      // helion
      const auto& helion = Levels::level( id::ParticleID::helion() );

      CHECK( id::ParticleID::helion() == helion.identifier() );
      CHECK( std::nullopt == helion.energy() );
      CHECK_THAT( 0.5, WithinRel( helion.spin().value() ) );
      CHECK( 1 == helion.parity() );
      CHECK( std::nullopt == helion.halfLife() );

      // alpha
      const auto& alpha = Levels::level( id::ParticleID::alpha() );

      CHECK( id::ParticleID::alpha() == alpha.identifier() );
      CHECK( std::nullopt == alpha.energy() );
      CHECK_THAT( 0.0, WithinRel( alpha.spin().value() ) );
      CHECK( 1 == alpha.parity() );
      CHECK( std::nullopt == alpha.halfLife() );
    } // THEN

    THEN( "requesting a non-existent particle throws an exception" ) {

      id::ParticleID u214( "U214" ); // first available is U215
      id::ParticleID u235( "U235" );

      CHECK_THROWS( Levels::level( u214 ) );
      CHECK_NOTHROW( Levels::level( u235 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
