// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/atomic/ElectronSubshellConfiguration.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::atomic;

void verifyChunkWithoutTransitions( const ElectronSubshellConfiguration& );
void verifyChunkWithTransitions( const ElectronSubshellConfiguration& );

SCENARIO( "ElectronSubshellConfiguration" ) {

  GIVEN( "valid data for a subshell configuration with transitions" ) {

    WHEN( "the data is given explicitly" ) {

      id::ElectronSubshellID id( "K" );
      double energy = 538;
      double population = 2.;

      ElectronSubshellConfiguration chunk( std::move( id ), std::move( energy ),
                                           std::move( population ) );

      THEN( "an ElectronSubshellConfiguration can be constructed and members "
            "can be tested" ) {

        verifyChunkWithoutTransitions( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a subshell configuration with transitions" ) {

    WHEN( "the data is given explicitly" ) {

      id::ElectronSubshellID id( "K" );
      double energy = 538;
      double population = 2.;
      std::vector< RadiativeTransitionData > radiative = {

        RadiativeTransitionData( "L2", 0.00190768, 523.09 ),
        RadiativeTransitionData( "L3", 0.00380027, 523.13 )
      };
      std::vector< NonRadiativeTransitionData > nonradiative = {

        NonRadiativeTransitionData( "L1", "L1", 0.178644, 478.82 ),
        NonRadiativeTransitionData( "L1", "L2", 0.116224, 493.86 ),
        NonRadiativeTransitionData( "L1", "L3", 0.230418, 493.9 ),
        NonRadiativeTransitionData( "L2", "L2", 0.0110822, 508.9 ),
        NonRadiativeTransitionData( "L2", "L3", 0.291115, 508.94 ),
        NonRadiativeTransitionData( "L3", "L3", 0.166809, 508.98 )
      };

      ElectronSubshellConfiguration chunk( std::move( id ), std::move( energy ),
                                           std::move( population ),
                                           std::move( radiative ),
                                           std::move( nonradiative ) );

      THEN( "an ElectronSubshellConfiguration can be constructed and members "
            "can be tested" ) {

        verifyChunkWithTransitions( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkWithoutTransitions( const ElectronSubshellConfiguration& chunk ) {

  CHECK( id::ElectronSubshellID( "K" ) == chunk.identifier() );
  CHECK_THAT( 538, WithinRel( chunk.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( chunk.population() ) );

  CHECK( false == chunk.hasRadiativeTransitions() );
  CHECK( false == chunk.hasNonRadiativeTransitions() );
  CHECK( false == chunk.hasTransitions() );

  CHECK( 0 == chunk.numberRadiativeTransitions() );
  CHECK( 0 == chunk.numberNonRadiativeTransitions() );
  CHECK( 0 == chunk.numberTransitions() );
  CHECK( 0 == chunk.radiativeTransitions().size() );
  CHECK( 0 == chunk.nonRadiativeTransitions().size() );

  CHECK_THAT( 0., WithinRel( chunk.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( chunk.totalNonRadiativeProbability() ) );
}

void verifyChunkWithTransitions( const ElectronSubshellConfiguration& chunk ) {

  CHECK( id::ElectronSubshellID( "K" ) == chunk.identifier() );
  CHECK_THAT( 538, WithinRel( chunk.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( chunk.population() ) );

  CHECK( true == chunk.hasRadiativeTransitions() );
  CHECK( true == chunk.hasNonRadiativeTransitions() );
  CHECK( true == chunk.hasTransitions() );

  CHECK( 2 == chunk.numberRadiativeTransitions() );
  CHECK( 6 == chunk.numberNonRadiativeTransitions() );
  CHECK( 8 == chunk.numberTransitions() );
  CHECK( 2 == chunk.radiativeTransitions().size() );
  CHECK( 6 == chunk.nonRadiativeTransitions().size() );

  CHECK( TransitionType::Radiative == chunk.radiativeTransitions()[0].type() );
  CHECK( TransitionType::Radiative == chunk.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768, WithinRel( chunk.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027, WithinRel( chunk.radiativeTransitions()[1].probability() ) );
  CHECK_THAT( 523.09, WithinRel( chunk.radiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 523.13, WithinRel( chunk.radiativeTransitions()[1].energy().value() ) );

  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[0].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[1].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[2].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[3].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[4].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "L1" ) == chunk.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == chunk.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == chunk.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == chunk.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.nonRadiativeTransitions()[5].emittingShell() );
  CHECK_THAT( 0.178644 , WithinRel( chunk.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.116224 , WithinRel( chunk.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.230418 , WithinRel( chunk.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0110822, WithinRel( chunk.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 0.291115 , WithinRel( chunk.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 0.166809 , WithinRel( chunk.nonRadiativeTransitions()[5].probability() ) );
  CHECK_THAT( 478.82, WithinRel( chunk.nonRadiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 493.86, WithinRel( chunk.nonRadiativeTransitions()[1].energy().value() ) );
  CHECK_THAT( 493.9 , WithinRel( chunk.nonRadiativeTransitions()[2].energy().value() ) );
  CHECK_THAT( 508.9 , WithinRel( chunk.nonRadiativeTransitions()[3].energy().value() ) );
  CHECK_THAT( 508.94, WithinRel( chunk.nonRadiativeTransitions()[4].energy().value() ) );
  CHECK_THAT( 508.98, WithinRel( chunk.nonRadiativeTransitions()[5].energy().value() ) );

  CHECK_THAT( 0.00570795, WithinRel( chunk.totalRadiativeProbability() ) );
  CHECK_THAT( 0.9942922 , WithinRel( chunk.totalNonRadiativeProbability() ) );
}
