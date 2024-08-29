// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/atomic/RadiativeTransition.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::atomic;

void verifyChunkWithoutTransitionEnergy( const RadiativeTransition& );
void verifyChunkWithTransitionEnergy( const RadiativeTransition& );

SCENARIO( "RadiativeTransition" ) {

  GIVEN( "valid data for a radiative transition" ) {

    WHEN( "the data is given explicitly for a radiative transition without "
          "a transition energy" ) {

      id::ElectronSubshellID originatingShell( "K" );
      double probability = 1e-3;

      RadiativeTransition chunk( std::move( originatingShell ), std::move( probability ) );

      THEN( "an RadiativeTransition can be constructed and members can be tested" ) {

        verifyChunkWithoutTransitionEnergy( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly for a radiative transition with "
          "a transition energy" ) {

      id::ElectronSubshellID originatingShell( "K" );
      double probability = 1e-3;
      double energy = 550.;

      RadiativeTransition chunk( std::move( originatingShell ), std::move( probability ),
                        std::move( energy ) );

      THEN( "an RadiativeTransition can be constructed and members can be tested" ) {

        verifyChunkWithTransitionEnergy( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkWithoutTransitionEnergy( const RadiativeTransition& chunk ) {

  CHECK( TransitionType::Radiative == chunk.type() );
  CHECK( id::ElectronSubshellID( "K" ) == chunk.originatingShell() );
  CHECK_THAT( 1e-3, WithinRel( chunk.probability() ) );
  CHECK( std::nullopt == chunk.energy() );
}

void verifyChunkWithTransitionEnergy( const RadiativeTransition& chunk ) {

  CHECK( TransitionType::Radiative == chunk.type() );
  CHECK( id::ElectronSubshellID( "K" ) == chunk.originatingShell() );
  CHECK_THAT( 1e-3, WithinRel( chunk.probability() ) );
  CHECK_THAT( 550., WithinRel( chunk.energy().value() ) );
}
