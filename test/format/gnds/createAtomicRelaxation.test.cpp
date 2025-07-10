// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createAtomicRelaxation.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const AtomicRelaxation& );

SCENARIO( "createAtomicRelaxation" ) {

  GIVEN( "a GNDS file with atomic relaxation data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "atom-008_O_000.endf.gnds.xml" );

    WHEN( "a single GNDS xml document is given" ) {

      THEN( "it can be converted" ) {

        AtomicRelaxation oxygen = format::gnds::createAtomicRelaxation( document );

        verifyChunk( oxygen );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const AtomicRelaxation& chunk ) {

  CHECK( id::ElementID( 8 ) == chunk.elementIdentifier() );

  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "K" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L1" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L2" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L3" ) ) );
  CHECK( false == chunk.hasSubshell( id::ElectronSubshellID( "M1" ) ) );

  auto shell_k = chunk.subshell( id::ElectronSubshellID( "K" ) );
  CHECK( id::ElectronSubshellID( "K" ) == shell_k.identifier() );
  CHECK_THAT( 538, WithinRel( shell_k.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( shell_k.population() ) );

  CHECK( true == shell_k.hasRadiativeTransitions() );
  CHECK( true == shell_k.hasNonRadiativeTransitions() );
  CHECK( true == shell_k.hasTransitions() );

  CHECK( 2 == shell_k.numberRadiativeTransitions() );
  CHECK( 6 == shell_k.numberNonRadiativeTransitions() );
  CHECK( 8 == shell_k.numberTransitions() );
  CHECK( 2 == shell_k.radiativeTransitions().size() );
  CHECK( 6 == shell_k.nonRadiativeTransitions().size() );

  double normalisation = 1.00000015;

  CHECK( atomic::TransitionType::Radiative == shell_k.radiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::Radiative == shell_k.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768 / normalisation, WithinRel( shell_k.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027 / normalisation, WithinRel( shell_k.radiativeTransitions()[1].probability() ) );
  CHECK( std::nullopt == shell_k.radiativeTransitions()[0].energy() );
  CHECK( std::nullopt == shell_k.radiativeTransitions()[1].energy() );

  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::NonRadiative == shell_k.nonRadiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_k.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_k.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_k.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_k.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_k.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_k.nonRadiativeTransitions()[5].emittingShell() );
  CHECK_THAT( 0.178644  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.116224  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.230418  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0110822 / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 0.291115  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 0.166809  / normalisation, WithinRel( shell_k.nonRadiativeTransitions()[5].probability() ) );
  CHECK( std::nullopt == shell_k.nonRadiativeTransitions()[0].energy() );
  CHECK( std::nullopt == shell_k.nonRadiativeTransitions()[1].energy() );
  CHECK( std::nullopt == shell_k.nonRadiativeTransitions()[2].energy() );
  CHECK( std::nullopt == shell_k.nonRadiativeTransitions()[3].energy() );
  CHECK( std::nullopt == shell_k.nonRadiativeTransitions()[4].energy() );
  CHECK( std::nullopt == shell_k.nonRadiativeTransitions()[5].energy() );

  CHECK_THAT( 0.00570795 / normalisation, WithinRel( shell_k.totalRadiativeProbability() ) );
  CHECK_THAT( 0.9942922  / normalisation, WithinRel( shell_k.totalNonRadiativeProbability() ) );

  auto shell_l1 = chunk.subshell( id::ElectronSubshellID( "L1" ) );
  CHECK( id::ElectronSubshellID( "L1" ) == shell_l1.identifier() );
  CHECK_THAT( 28.48, WithinRel( shell_l1.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( shell_l1.population() ) );

  CHECK( false == shell_l1.hasRadiativeTransitions() );
  CHECK( false == shell_l1.hasNonRadiativeTransitions() );
  CHECK( false == shell_l1.hasTransitions() );

  CHECK( 0 == shell_l1.numberRadiativeTransitions() );
  CHECK( 0 == shell_l1.numberNonRadiativeTransitions() );
  CHECK( 0 == shell_l1.numberTransitions() );
  CHECK( 0 == shell_l1.radiativeTransitions().size() );
  CHECK( 0 == shell_l1.nonRadiativeTransitions().size() );

  auto shell_l2 = chunk.subshell( id::ElectronSubshellID( "L2" ) );
  CHECK( id::ElectronSubshellID( "L2" ) == shell_l2.identifier() );
  CHECK_THAT( 13.62, WithinRel( shell_l2.bindingEnergy() ) );
  CHECK_THAT( 1.33 , WithinRel( shell_l2.population() ) );

  CHECK( false == shell_l2.hasRadiativeTransitions() );
  CHECK( false == shell_l2.hasNonRadiativeTransitions() );
  CHECK( false == shell_l2.hasTransitions() );

  CHECK( 0 == shell_l2.numberRadiativeTransitions() );
  CHECK( 0 == shell_l2.numberNonRadiativeTransitions() );
  CHECK( 0 == shell_l2.numberTransitions() );
  CHECK( 0 == shell_l2.radiativeTransitions().size() );
  CHECK( 0 == shell_l2.nonRadiativeTransitions().size() );

  auto shell_l3 = chunk.subshell( id::ElectronSubshellID( "L3" ) );
  CHECK( id::ElectronSubshellID( "L3" ) == shell_l3.identifier() );
  CHECK_THAT( 13.62, WithinRel( shell_l3.bindingEnergy() ) );
  CHECK_THAT( 2.67 , WithinRel( shell_l3.population() ) );

  CHECK( false == shell_l3.hasRadiativeTransitions() );
  CHECK( false == shell_l3.hasNonRadiativeTransitions() );
  CHECK( false == shell_l3.hasTransitions() );

  CHECK( 0 == shell_l3.numberRadiativeTransitions() );
  CHECK( 0 == shell_l3.numberNonRadiativeTransitions() );
  CHECK( 0 == shell_l3.numberTransitions() );
  CHECK( 0 == shell_l3.radiativeTransitions().size() );
  CHECK( 0 == shell_l3.nonRadiativeTransitions().size() );
}
