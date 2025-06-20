// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/atomic/createElectronSubshellConfiguration.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const atomic::ElectronSubshellConfiguration& );

SCENARIO( "createElectronSubshellConfiguration" ) {

  GIVEN( "a GNDS configuration xml node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "atom-008_O_000.endf.gnds.xml" );
    pugi::xml_node configuration = document.child( "PoPs" ).child( "chemicalElements" ).
                                     child( "chemicalElement" ).child( "atomic" ).
                                     child( "configurations" ).child( "configuration" );

    WHEN( "a single gnds configuration node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::atomic::createElectronSubshellConfiguration( configuration );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const atomic::ElectronSubshellConfiguration& chunk ) {

  CHECK( id::ElectronSubshellID( "1s1/2" ) == chunk.identifier() );
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

  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768, WithinRel( chunk.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027, WithinRel( chunk.radiativeTransitions()[1].probability() ) );
  CHECK( std::nullopt == chunk.radiativeTransitions()[0].energy() );
  CHECK( std::nullopt == chunk.radiativeTransitions()[1].energy() );

  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[5].emittingShell() );
  CHECK_THAT( 0.178644 , WithinRel( chunk.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.116224 , WithinRel( chunk.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.230418 , WithinRel( chunk.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0110822, WithinRel( chunk.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 0.291115 , WithinRel( chunk.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 0.166809 , WithinRel( chunk.nonRadiativeTransitions()[5].probability() ) );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[0].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[1].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[2].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[3].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[4].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[5].energy() );

  CHECK_THAT( 0.00570795, WithinRel( chunk.totalRadiativeProbability() ) );
  CHECK_THAT( 0.9942922 , WithinRel( chunk.totalNonRadiativeProbability() ) );
}
