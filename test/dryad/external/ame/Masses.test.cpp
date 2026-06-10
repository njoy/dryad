// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/external/ame/Masses.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::external::ame;

SCENARIO( "Masses" ) {

  GIVEN( "the AME data in Masses" ) {

    THEN( "predefined particles can be retrieved" ) {

      CHECK(    0 == Masses::size() );

      auto entry = Masses::entry( id::ParticleID( "H1" ) );

      CHECK( id::ParticleID( "H1" ) == entry.identifier() );
      CHECK_THAT( 7288971.064, WithinRel( entry.massExcess().value() ) );
      CHECK_THAT( 0.013, WithinRel( entry.massExcessUncertainty().value() ) );
      CHECK_THAT( 0.0, WithinRel( entry.bindingEnergy().value() ) );
      CHECK_THAT( 0.0, WithinRel( entry.bindingEnergyUncertainty().value() ) );
      CHECK( std::nullopt == entry.betaDecayEnergy() );
      CHECK( std::nullopt == entry.betaDecayEnergyUncertainty() );
      CHECK_THAT( 1.007825031898, WithinRel( entry.atomicMass().value() ) );
      CHECK_THAT( 0.000000000014, WithinRel( entry.atomicMassUncertainty().value() ) );

      entry = Masses::entry( id::ParticleID( "He3" ) );
      CHECK( id::ParticleID( "He3" ) == entry.identifier() );
      CHECK_THAT( 14931218.88, WithinRel( entry.massExcess().value() ) );
      CHECK_THAT( 0.06, WithinRel( entry.massExcessUncertainty().value() ) );
      CHECK_THAT( 2572680.44, WithinRel( entry.bindingEnergy().value() ) );
      CHECK_THAT( 0.15, WithinRel( entry.bindingEnergyUncertainty().value() ) );
      CHECK( -13736000 == entry.betaDecayEnergy() );
      CHECK(  2000000 == entry.betaDecayEnergyUncertainty() );
      CHECK_THAT( 3.01602932197, WithinRel( entry.atomicMass().value() ) );
      CHECK_THAT( 0.00000000006, WithinRel( entry.atomicMassUncertainty().value() ) );

      CHECK( 3557 == Masses::size() );
    } // THEN

    THEN( "requesting a non-existent particle throws an exception" ) {

      if ( std::getenv( "NJOY_DATAPATH" ) ) {

        id::ParticleID h1( "H1" );
        id::ParticleID h20( "H20" );

        CHECK_NOTHROW( Masses::entry( h1 ) );
        CHECK_THROWS( Masses::entry( h20 ) );
      }
    } // THEN
  } // GIVEN
} // SCENARIO
