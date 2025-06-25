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

void verifyOxygenChunk( const atomic::ElectronSubshellConfiguration& );
void verifyCopperChunk( const atomic::ElectronSubshellConfiguration& );

SCENARIO( "createElectronSubshellConfiguration" ) {

  GIVEN( "a GNDS configuration xml node for a one character identifier" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "atom-008_O_000.endf.gnds.xml" );
    pugi::xml_node configuration = document.child( "PoPs" ).child( "chemicalElements" ).
                                     child( "chemicalElement" ).child( "atomic" ).
                                     child( "configurations" ).child( "configuration" );

    WHEN( "a single gnds configuration node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::atomic::createElectronSubshellConfiguration( id::ElementID( 8 ), configuration );

        verifyOxygenChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS configuration xml node for a two character identifier" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "atom-029_Cu_000.endf.gnds.xml" );
    pugi::xml_node configuration = document.child( "PoPs" ).child( "chemicalElements" ).
                                     child( "chemicalElement" ).child( "atomic" ).
                                     child( "configurations" ).child( "configuration" );

    WHEN( "a single gnds configuration node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::atomic::createElectronSubshellConfiguration( id::ElementID( 29 ), configuration );

        verifyCopperChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyOxygenChunk( const atomic::ElectronSubshellConfiguration& chunk ) {

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

void verifyCopperChunk( const atomic::ElectronSubshellConfiguration& chunk ) {

  CHECK( id::ElectronSubshellID( "1s1/2" ) == chunk.identifier() );
  CHECK_THAT( 8986, WithinRel( chunk.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( chunk.population() ) );

  CHECK( true == chunk.hasRadiativeTransitions() );
  CHECK( true == chunk.hasNonRadiativeTransitions() );
  CHECK( true == chunk.hasTransitions() );

  CHECK( 6 == chunk.numberRadiativeTransitions() );
  CHECK( 43 == chunk.numberNonRadiativeTransitions() );
  CHECK( 49 == chunk.numberTransitions() );
  CHECK( 6 == chunk.radiativeTransitions().size() );
  CHECK( 43 == chunk.nonRadiativeTransitions().size() );

  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::Radiative == chunk.radiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.radiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.radiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.radiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.radiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.radiativeTransitions()[5].originatingShell() );
  CHECK_THAT( 0.131119  , WithinRel( chunk.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.255668  , WithinRel( chunk.radiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.0158899 , WithinRel( chunk.radiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0310908 , WithinRel( chunk.radiativeTransitions()[3].probability() ) );
  CHECK_THAT( 1.79389e-5, WithinRel( chunk.radiativeTransitions()[4].probability() ) );
  CHECK_THAT( 2.59348e-5, WithinRel( chunk.radiativeTransitions()[5].probability() ) );
  CHECK( std::nullopt == chunk.radiativeTransitions()[0].energy() );
  CHECK( std::nullopt == chunk.radiativeTransitions()[1].energy() );
  CHECK( std::nullopt == chunk.radiativeTransitions()[2].energy() );
  CHECK( std::nullopt == chunk.radiativeTransitions()[3].energy() );
  CHECK( std::nullopt == chunk.radiativeTransitions()[4].energy() );
  CHECK( std::nullopt == chunk.radiativeTransitions()[5].energy() );

  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[5].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[6].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[7].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[8].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[9].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[10].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[11].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[12].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[13].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[14].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[15].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[16].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[17].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[18].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[19].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[20].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[21].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[22].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[23].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[24].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[25].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[26].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[27].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[28].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[29].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[30].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[31].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[32].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[33].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[34].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[35].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[36].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[37].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[38].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[39].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[40].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[41].type() );
  CHECK( atomic::TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[42].type() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[6].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[7].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[8].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[9].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[10].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[11].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[12].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[13].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[14].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[15].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[16].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[17].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[18].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[19].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[20].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[21].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[22].originatingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[23].originatingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[24].originatingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[25].originatingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[26].originatingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[27].originatingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[28].originatingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[29].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[30].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[31].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[32].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[33].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[34].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[35].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[36].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[37].originatingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[38].originatingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.nonRadiativeTransitions()[39].originatingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.nonRadiativeTransitions()[40].originatingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[41].originatingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[42].originatingShell() );
  CHECK( id::ElectronSubshellID( "2s1/2" ) == chunk.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[5].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.nonRadiativeTransitions()[6].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[7].emittingShell() );
  CHECK( id::ElectronSubshellID( "4s1/2" ) == chunk.nonRadiativeTransitions()[8].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p1/2" ) == chunk.nonRadiativeTransitions()[9].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[10].emittingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[11].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[12].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[13].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.nonRadiativeTransitions()[14].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[15].emittingShell() );
  CHECK( id::ElectronSubshellID( "4s1/2" ) == chunk.nonRadiativeTransitions()[16].emittingShell() );
  CHECK( id::ElectronSubshellID( "2p3/2" ) == chunk.nonRadiativeTransitions()[17].emittingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[18].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[19].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[20].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.nonRadiativeTransitions()[21].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[22].emittingShell() );
  CHECK( id::ElectronSubshellID( "4s1/2" ) == chunk.nonRadiativeTransitions()[23].emittingShell() );
  CHECK( id::ElectronSubshellID( "3s1/2" ) == chunk.nonRadiativeTransitions()[24].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[25].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[26].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.nonRadiativeTransitions()[27].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[28].emittingShell() );
  CHECK( id::ElectronSubshellID( "4s1/2" ) == chunk.nonRadiativeTransitions()[29].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p1/2" ) == chunk.nonRadiativeTransitions()[30].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[31].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.nonRadiativeTransitions()[32].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[33].emittingShell() );
  CHECK( id::ElectronSubshellID( "4s1/2" ) == chunk.nonRadiativeTransitions()[34].emittingShell() );
  CHECK( id::ElectronSubshellID( "3p3/2" ) == chunk.nonRadiativeTransitions()[35].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d3/2" ) == chunk.nonRadiativeTransitions()[36].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[37].emittingShell() );
  CHECK( id::ElectronSubshellID( "4s1/2" ) == chunk.nonRadiativeTransitions()[38].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[39].emittingShell() );
  CHECK( id::ElectronSubshellID( "4s1/2" ) == chunk.nonRadiativeTransitions()[40].emittingShell() );
  CHECK( id::ElectronSubshellID( "3d5/2" ) == chunk.nonRadiativeTransitions()[41].emittingShell() );
  CHECK( id::ElectronSubshellID( "4s1/2" ) == chunk.nonRadiativeTransitions()[42].emittingShell() );
  CHECK_THAT( 0.0388567 , WithinRel( chunk.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.0431908 , WithinRel( chunk.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.0768383 , WithinRel( chunk.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0104073 , WithinRel( chunk.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 5.57458e-3, WithinRel( chunk.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 9.82486e-3, WithinRel( chunk.nonRadiativeTransitions()[5].probability() ) );
  CHECK_THAT( 2.80672e-4, WithinRel( chunk.nonRadiativeTransitions()[6].probability() ) );
  CHECK_THAT( 3.81309e-4, WithinRel( chunk.nonRadiativeTransitions()[7].probability() ) );
  CHECK_THAT( 3.54221e-4, WithinRel( chunk.nonRadiativeTransitions()[8].probability() ) );
  CHECK_THAT( 7.65781e-3, WithinRel( chunk.nonRadiativeTransitions()[9].probability() ) );
  CHECK_THAT( 0.181191  , WithinRel( chunk.nonRadiativeTransitions()[10].probability() ) );
  CHECK_THAT( 4.90291e-3, WithinRel( chunk.nonRadiativeTransitions()[11].probability() ) );
  CHECK_THAT( 1.85044e-3, WithinRel( chunk.nonRadiativeTransitions()[12].probability() ) );
  CHECK_THAT( 0.0199826 , WithinRel( chunk.nonRadiativeTransitions()[13].probability() ) );
  CHECK_THAT( 3.89071e-4, WithinRel( chunk.nonRadiativeTransitions()[14].probability() ) );
  CHECK_THAT( 1.43235e-3, WithinRel( chunk.nonRadiativeTransitions()[15].probability() ) );
  CHECK_THAT( 1.62596e-4, WithinRel( chunk.nonRadiativeTransitions()[16].probability() ) );
  CHECK_THAT( 0.100194  , WithinRel( chunk.nonRadiativeTransitions()[17].probability() ) );
  CHECK_THAT( 8.76108e-3, WithinRel( chunk.nonRadiativeTransitions()[18].probability() ) );
  CHECK_THAT( 0.0200201 , WithinRel( chunk.nonRadiativeTransitions()[19].probability() ) );
  CHECK_THAT( 0.0224684 , WithinRel( chunk.nonRadiativeTransitions()[20].probability() ) );
  CHECK_THAT( 1.77886e-3, WithinRel( chunk.nonRadiativeTransitions()[21].probability() ) );
  CHECK_THAT( 1.73429e-3, WithinRel( chunk.nonRadiativeTransitions()[22].probability() ) );
  CHECK_THAT( 2.92272e-4, WithinRel( chunk.nonRadiativeTransitions()[23].probability() ) );
  CHECK_THAT( 7.62703e-4, WithinRel( chunk.nonRadiativeTransitions()[24].probability() ) );
  CHECK_THAT( 7.0483e-4 , WithinRel( chunk.nonRadiativeTransitions()[25].probability() ) );
  CHECK_THAT( 1.2447e-3 , WithinRel( chunk.nonRadiativeTransitions()[26].probability() ) );
  CHECK_THAT( 3.21362e-5, WithinRel( chunk.nonRadiativeTransitions()[27].probability() ) );
  CHECK_THAT( 4.49905e-5, WithinRel( chunk.nonRadiativeTransitions()[28].probability() ) );
  CHECK_THAT( 5.14183e-5, WithinRel( chunk.nonRadiativeTransitions()[29].probability() ) );
  CHECK_THAT( 1.20557e-4, WithinRel( chunk.nonRadiativeTransitions()[30].probability() ) );
  CHECK_THAT( 2.52309e-3, WithinRel( chunk.nonRadiativeTransitions()[31].probability() ) );
  CHECK_THAT( 3.72645e-5, WithinRel( chunk.nonRadiativeTransitions()[32].probability() ) );
  CHECK_THAT( 1.46859e-4, WithinRel( chunk.nonRadiativeTransitions()[33].probability() ) );
  CHECK_THAT( 2.41126e-5, WithinRel( chunk.nonRadiativeTransitions()[34].probability() ) );
  CHECK_THAT( 1.52046e-3, WithinRel( chunk.nonRadiativeTransitions()[35].probability() ) );
  CHECK_THAT( 1.96192e-4, WithinRel( chunk.nonRadiativeTransitions()[36].probability() ) );
  CHECK_THAT( 1.86855e-4, WithinRel( chunk.nonRadiativeTransitions()[37].probability() ) );
  CHECK_THAT( 4.43756e-5, WithinRel( chunk.nonRadiativeTransitions()[38].probability() ) );
  CHECK_THAT( 1.10707e-5, WithinRel( chunk.nonRadiativeTransitions()[39].probability() ) );
  CHECK_THAT( 2.21424e-6, WithinRel( chunk.nonRadiativeTransitions()[40].probability() ) );
  CHECK_THAT( 4.12417e-6, WithinRel( chunk.nonRadiativeTransitions()[41].probability() ) );
  CHECK_THAT( 4.12417e-6, WithinRel( chunk.nonRadiativeTransitions()[42].probability() ) );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[0].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[1].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[2].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[3].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[4].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[5].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[6].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[7].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[8].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[9].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[10].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[11].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[12].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[13].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[14].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[15].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[16].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[17].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[18].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[19].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[20].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[21].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[22].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[23].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[24].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[25].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[26].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[27].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[28].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[29].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[30].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[31].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[32].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[33].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[34].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[35].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[36].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[37].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[38].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[39].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[40].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[41].energy() );
  CHECK( std::nullopt == chunk.nonRadiativeTransitions()[42].energy() );

  CHECK_THAT( 0.43381157370, WithinRel( chunk.totalRadiativeProbability() ) );
  CHECK_THAT( 0.56618859798, WithinRel( chunk.totalNonRadiativeProbability() ) );
}
