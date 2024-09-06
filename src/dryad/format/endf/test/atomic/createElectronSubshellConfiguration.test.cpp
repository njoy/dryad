// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/atomic/createElectronSubshellConfiguration.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const atomic::ElectronSubshellConfiguration& );

SCENARIO( "createElectronSubshellConfiguration" ) {

  GIVEN( "ENDF MF28 SubshellData" ) {

    using SubshellData = njoy::ENDFtk::section::Type< 28 >::SubshellData;

    auto tape = njoy::ENDFtk::tree::fromFile( "atom-008_O_000.endf" );
    auto section = tape.materials().front().section( 28, 533 ).parse< 28 >();

    WHEN( "a single parsed MF4 LegendreCoefficients is given" ) {

      THEN( "it can be converted" ) {

        auto subshell = section.subshells()[0];
        auto chunk = format::endf::atomic::createElectronSubshellConfiguration( subshell );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const atomic::ElectronSubshellConfiguration& chunk ) {

  CHECK( id::ElectronSubshellID( "K" ) == chunk.identifier() );
  CHECK_THAT( 538, WithinRel( chunk.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( chunk.population() ) );

  CHECK( true == chunk.hasRadiativeTransitions() );
  CHECK( true == chunk.hasNonRadiativeTransitions() );
  CHECK( true == chunk.hasTransitions() );

  CHECK( 2 == chunk.numberRadiativeTransitions() );
  CHECK( 6 == chunk.numberNonRadiativeTransitions() );
  CHECK( 2 == chunk.radiativeTransitions().size() );
  CHECK( 6 == chunk.nonRadiativeTransitions().size() );

  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768, WithinRel( chunk.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027, WithinRel( chunk.radiativeTransitions()[1].probability() ) );
  CHECK_THAT( 523.09, WithinRel( chunk.radiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 523.13, WithinRel( chunk.radiativeTransitions()[1].energy().value() ) );

  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[5].type() );
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
