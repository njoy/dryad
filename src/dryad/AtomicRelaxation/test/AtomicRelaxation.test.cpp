// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/AtomicRelaxation.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const AtomicRelaxation& );

SCENARIO( "AtomicRelaxation" ) {

  GIVEN( "valid data for a AtomicRelaxation" ) {

    WHEN( "the data is given explicitly" ) {

      id::ElementID element( 1 );
      std::vector< atomic::ElectronSubshellConfiguration > subshells = {

        atomic::ElectronSubshellConfiguration(

          "K", 538, 2,
          { atomic::RadiativeTransitionData( "L2", 0.00190768, 523.09 ),
            atomic::RadiativeTransitionData( "L3", 0.00380027, 523.13 ) },
          { atomic::NonRadiativeTransitionData( "L1", "L1", 0.178644, 478.82 ),
            atomic::NonRadiativeTransitionData( "L1", "L2", 0.116224, 493.86 ),
            atomic::NonRadiativeTransitionData( "L1", "L3", 0.230418, 493.9 ),
            atomic::NonRadiativeTransitionData( "L2", "L2", 0.0110822, 508.9 ),
            atomic::NonRadiativeTransitionData( "L2", "L3", 0.291115, 508.94 ),
            atomic::NonRadiativeTransitionData( "L3", "L3", 0.166809, 508.98 ) }
        ),
        atomic::ElectronSubshellConfiguration( "L1", 28.48, 2 ),
        atomic::ElectronSubshellConfiguration( "L2", 13.62, 1.33 ),
        atomic::ElectronSubshellConfiguration( "L3", 13.62, 2.67 )
      };

      AtomicRelaxation chunk( std::move( element ), std::move( subshells ) );

      THEN( "a AtomicRelaxation can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const AtomicRelaxation& chunk ) {

  // identifiers
  CHECK( id::ElementID( 1 ) == chunk.elementIdentifier() );

  // subshell configuration data
  CHECK( 4 == chunk.subshells().size() );

  auto k_shell = chunk.subshells()[0];
  CHECK( id::ElectronSubshellID( "K" ) == k_shell.identifier() );
  CHECK_THAT( 538, WithinRel( k_shell.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( k_shell.population() ) );
  CHECK( true == k_shell.hasRadiativeTransitions() );
  CHECK( true == k_shell.hasNonRadiativeTransitions() );
  CHECK( true == k_shell.hasTransitions() );
  CHECK( 2 == k_shell.numberRadiativeTransitions() );
  CHECK( 6 == k_shell.numberNonRadiativeTransitions() );
  CHECK( 2 == k_shell.radiativeTransitions().size() );
  CHECK( 6 == k_shell.nonRadiativeTransitions().size() );
  CHECK( atomic::TransitionType::Radiative == k_shell.radiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::Radiative == k_shell.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768, WithinRel( k_shell.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027, WithinRel( k_shell.radiativeTransitions()[1].probability() ) );
  CHECK_THAT( 523.09, WithinRel( k_shell.radiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 523.13, WithinRel( k_shell.radiativeTransitions()[1].energy().value() ) );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[5].emittingShell() );
  CHECK_THAT( 0.178644 , WithinRel( k_shell.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.116224 , WithinRel( k_shell.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.230418 , WithinRel( k_shell.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0110822, WithinRel( k_shell.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 0.291115 , WithinRel( k_shell.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 0.166809 , WithinRel( k_shell.nonRadiativeTransitions()[5].probability() ) );
  CHECK_THAT( 478.82, WithinRel( k_shell.nonRadiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 493.86, WithinRel( k_shell.nonRadiativeTransitions()[1].energy().value() ) );
  CHECK_THAT( 493.9 , WithinRel( k_shell.nonRadiativeTransitions()[2].energy().value() ) );
  CHECK_THAT( 508.9 , WithinRel( k_shell.nonRadiativeTransitions()[3].energy().value() ) );
  CHECK_THAT( 508.94, WithinRel( k_shell.nonRadiativeTransitions()[4].energy().value() ) );
  CHECK_THAT( 508.98, WithinRel( k_shell.nonRadiativeTransitions()[5].energy().value() ) );
  CHECK_THAT( 0.00570795, WithinRel( k_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0.9942922 , WithinRel( k_shell.totalNonRadiativeProbability() ) );

  auto l1_shell = chunk.subshells()[1];
  CHECK( id::ElectronSubshellID( "L1" ) == l1_shell.identifier() );
  CHECK_THAT( 28.48, WithinRel( l1_shell.bindingEnergy() ) );
  CHECK_THAT( 2.   , WithinRel( l1_shell.population() ) );
  CHECK( false == l1_shell.hasRadiativeTransitions() );
  CHECK( false == l1_shell.hasNonRadiativeTransitions() );
  CHECK( false == l1_shell.hasTransitions() );
  CHECK( 0 == l1_shell.numberRadiativeTransitions() );
  CHECK( 0 == l1_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l1_shell.radiativeTransitions().size() );
  CHECK( 0 == l1_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l1_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l1_shell.totalNonRadiativeProbability() ) );

  auto l2_shell = chunk.subshells()[2];
  CHECK( id::ElectronSubshellID( "L2" ) == l2_shell.identifier() );
  CHECK_THAT( 13.62, WithinRel( l2_shell.bindingEnergy() ) );
  CHECK_THAT( 1.33 , WithinRel( l2_shell.population() ) );
  CHECK( false == l2_shell.hasRadiativeTransitions() );
  CHECK( false == l2_shell.hasNonRadiativeTransitions() );
  CHECK( false == l2_shell.hasTransitions() );
  CHECK( 0 == l2_shell.numberRadiativeTransitions() );
  CHECK( 0 == l2_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l2_shell.radiativeTransitions().size() );
  CHECK( 0 == l2_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l2_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l2_shell.totalNonRadiativeProbability() ) );

  auto l3_shell = chunk.subshells()[3];
  CHECK( id::ElectronSubshellID( "L3" ) == l3_shell.identifier() );
  CHECK_THAT( 13.62, WithinRel( l3_shell.bindingEnergy() ) );
  CHECK_THAT( 2.67 , WithinRel( l3_shell.population() ) );
  CHECK( false == l3_shell.hasRadiativeTransitions() );
  CHECK( false == l3_shell.hasNonRadiativeTransitions() );
  CHECK( false == l3_shell.hasTransitions() );
  CHECK( 0 == l3_shell.numberRadiativeTransitions() );
  CHECK( 0 == l3_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l3_shell.radiativeTransitions().size() );
  CHECK( 0 == l3_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l3_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l3_shell.totalNonRadiativeProbability() ) );
}
