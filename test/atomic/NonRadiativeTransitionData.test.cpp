// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/atomic/NonRadiativeTransitionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::atomic;

void verifyChunkWithoutTransitionEnergy( const NonRadiativeTransitionData& );
void verifyChunkWithTransitionEnergy( const NonRadiativeTransitionData& );

SCENARIO( "NonRadiativeTransitionData" ) {

  GIVEN( "valid data for a non-radiative transition" ) {

    WHEN( "the data is given explicitly for a non-radiative transition without "
          "a transition energy" ) {

      id::ElectronSubshellID originatingShell( "K" );
      id::ElectronSubshellID emittingShell( "L1" );
      double probability = 1e-3;

      NonRadiativeTransitionData chunk( std::move( originatingShell ), std::move( emittingShell ),
                                        std::move( probability ) );

      THEN( "an NonRadiativeTransitionData can be constructed and members can be tested" ) {

        verifyChunkWithoutTransitionEnergy( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly for a radiative transition with "
          "a transition energy" ) {

      id::ElectronSubshellID originatingShell( "K" );
      id::ElectronSubshellID emittingShell( "L1" );
      double probability = 1e-3;
      double energy = 550.;

      NonRadiativeTransitionData chunk( std::move( originatingShell ), std::move( emittingShell ),
                                        std::move( probability ), std::move( energy ) );

      THEN( "an NonRadiativeTransitionData can be constructed and members can be tested" ) {

        verifyChunkWithTransitionEnergy( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of NonRadiativeTransitionData are given" ) {

      id::ElectronSubshellID k_shell( id::ElectronSubshellID::K );
      id::ElectronSubshellID l1_shell( id::ElectronSubshellID::L1 );

      NonRadiativeTransitionData left( k_shell, l1_shell, 1e-3 );
      NonRadiativeTransitionData equal( k_shell, l1_shell, 1e-3 );
      NonRadiativeTransitionData different( k_shell, l1_shell, 1e-3, 550. );

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

void verifyChunkWithoutTransitionEnergy( const NonRadiativeTransitionData& chunk ) {

  CHECK( TransitionType::NonRadiative == chunk.type() );
  CHECK( id::ElectronSubshellID( "K" ) == chunk.originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" )== chunk.emittingShell() );
  CHECK_THAT( 1e-3, WithinRel( chunk.probability() ) );
  CHECK( std::nullopt == chunk.energy() );
}

void verifyChunkWithTransitionEnergy( const NonRadiativeTransitionData& chunk ) {

  CHECK( TransitionType::NonRadiative == chunk.type() );
  CHECK( id::ElectronSubshellID( "K" ) == chunk.originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" )== chunk.emittingShell() );
  CHECK_THAT( 1e-3, WithinRel( chunk.probability() ) );
  CHECK_THAT( 550., WithinRel( chunk.energy().value() ) );
}
