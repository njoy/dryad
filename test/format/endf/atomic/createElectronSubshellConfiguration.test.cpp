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

void verifyOxygenChunk( const atomic::ElectronSubshellConfiguration& );
void verifyCopperChunk( const atomic::ElectronSubshellConfiguration& );

SCENARIO( "createElectronSubshellConfiguration" ) {

  GIVEN( "ENDF MF28 SubshellData for oxygen" ) {

    using SubshellData = njoy::ENDFtk::section::Type< 28 >::SubshellData;

    auto tape = njoy::ENDFtk::tree::fromFile( "atom-008_O_000.endf" );
    auto section = tape.materials().front().section( 28, 533 ).parse< 28 >();

    WHEN( "a single parsed MF28 SubshellData is given" ) {

      THEN( "it can be converted" ) {

        auto subshell = section.subshells()[0];
        auto chunk = format::endf::atomic::createElectronSubshellConfiguration( subshell );

        verifyOxygenChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF28 SubshellData for copper" ) {

    using SubshellData = njoy::ENDFtk::section::Type< 28 >::SubshellData;

    auto tape = njoy::ENDFtk::tree::fromFile( "atom-029_Cu_000.endf" );
    auto section = tape.materials().front().section( 28, 533 ).parse< 28 >();

    WHEN( "a single parsed MF28 SubshellData is given" ) {

      THEN( "it can be converted" ) {

        auto subshell = section.subshells()[0];
        auto chunk = format::endf::atomic::createElectronSubshellConfiguration( subshell );

        verifyCopperChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyOxygenChunk( const atomic::ElectronSubshellConfiguration& chunk ) {

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
  CHECK_THAT( 7984.67, WithinRel( chunk.radiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 8005.71, WithinRel( chunk.radiativeTransitions()[1].energy().value() ) );
  CHECK_THAT( 8862.70, WithinRel( chunk.radiativeTransitions()[2].energy().value() ) );
  CHECK_THAT( 8865.34, WithinRel( chunk.radiativeTransitions()[3].energy().value() ) );
  CHECK_THAT( 8933.11, WithinRel( chunk.radiativeTransitions()[4].energy().value() ) );
  CHECK_THAT( 8933.40, WithinRel( chunk.radiativeTransitions()[5].energy().value() ) );

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
  CHECK_THAT( 6771.00, WithinRel( chunk.nonRadiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 6898.57, WithinRel( chunk.nonRadiativeTransitions()[1].energy().value() ) );
  CHECK_THAT( 6919.61, WithinRel( chunk.nonRadiativeTransitions()[2].energy().value() ) );
  CHECK_THAT( 7735.84, WithinRel( chunk.nonRadiativeTransitions()[3].energy().value() ) );
  CHECK_THAT( 7776.60, WithinRel( chunk.nonRadiativeTransitions()[4].energy().value() ) );
  CHECK_THAT( 7779.24, WithinRel( chunk.nonRadiativeTransitions()[5].energy().value() ) );
  CHECK_THAT( 7847.01, WithinRel( chunk.nonRadiativeTransitions()[6].energy().value() ) );
  CHECK_THAT( 7847.30, WithinRel( chunk.nonRadiativeTransitions()[7].energy().value() ) );
  CHECK_THAT( 7849.99, WithinRel( chunk.nonRadiativeTransitions()[8].energy().value() ) );
  CHECK_THAT( 7026.14, WithinRel( chunk.nonRadiativeTransitions()[9].energy().value() ) );
  CHECK_THAT( 7047.18, WithinRel( chunk.nonRadiativeTransitions()[10].energy().value() ) );
  CHECK_THAT( 7863.41, WithinRel( chunk.nonRadiativeTransitions()[11].energy().value() ) );
  CHECK_THAT( 7904.17, WithinRel( chunk.nonRadiativeTransitions()[12].energy().value() ) );
  CHECK_THAT( 7906.81, WithinRel( chunk.nonRadiativeTransitions()[13].energy().value() ) );
  CHECK_THAT( 7974.58, WithinRel( chunk.nonRadiativeTransitions()[14].energy().value() ) );
  CHECK_THAT( 7974.87, WithinRel( chunk.nonRadiativeTransitions()[15].energy().value() ) );
  CHECK_THAT( 7977.56, WithinRel( chunk.nonRadiativeTransitions()[16].energy().value() ) );
  CHECK_THAT( 7068.22, WithinRel( chunk.nonRadiativeTransitions()[17].energy().value() ) );
  CHECK_THAT( 7884.45, WithinRel( chunk.nonRadiativeTransitions()[18].energy().value() ) );
  CHECK_THAT( 7925.21, WithinRel( chunk.nonRadiativeTransitions()[19].energy().value() ) );
  CHECK_THAT( 7927.85, WithinRel( chunk.nonRadiativeTransitions()[20].energy().value() ) );
  CHECK_THAT( 7995.62, WithinRel( chunk.nonRadiativeTransitions()[21].energy().value() ) );
  CHECK_THAT( 7995.91, WithinRel( chunk.nonRadiativeTransitions()[22].energy().value() ) );
  CHECK_THAT( 7998.60, WithinRel( chunk.nonRadiativeTransitions()[23].energy().value() ) );
  CHECK_THAT( 8700.68, WithinRel( chunk.nonRadiativeTransitions()[24].energy().value() ) );
  CHECK_THAT( 8741.44, WithinRel( chunk.nonRadiativeTransitions()[25].energy().value() ) );
  CHECK_THAT( 8744.08, WithinRel( chunk.nonRadiativeTransitions()[26].energy().value() ) );
  CHECK_THAT( 8811.85, WithinRel( chunk.nonRadiativeTransitions()[27].energy().value() ) );
  CHECK_THAT( 8812.14, WithinRel( chunk.nonRadiativeTransitions()[28].energy().value() ) );
  CHECK_THAT( 8814.83, WithinRel( chunk.nonRadiativeTransitions()[29].energy().value() ) );
  CHECK_THAT( 8782.20, WithinRel( chunk.nonRadiativeTransitions()[30].energy().value() ) );
  CHECK_THAT( 8784.84, WithinRel( chunk.nonRadiativeTransitions()[31].energy().value() ) );
  CHECK_THAT( 8852.61, WithinRel( chunk.nonRadiativeTransitions()[32].energy().value() ) );
  CHECK_THAT( 8852.90, WithinRel( chunk.nonRadiativeTransitions()[33].energy().value() ) );
  CHECK_THAT( 8855.59, WithinRel( chunk.nonRadiativeTransitions()[34].energy().value() ) );
  CHECK_THAT( 8787.48, WithinRel( chunk.nonRadiativeTransitions()[35].energy().value() ) );
  CHECK_THAT( 8855.25, WithinRel( chunk.nonRadiativeTransitions()[36].energy().value() ) );
  CHECK_THAT( 8855.54, WithinRel( chunk.nonRadiativeTransitions()[37].energy().value() ) );
  CHECK_THAT( 8858.23, WithinRel( chunk.nonRadiativeTransitions()[38].energy().value() ) );
  CHECK_THAT( 8923.31, WithinRel( chunk.nonRadiativeTransitions()[39].energy().value() ) );
  CHECK_THAT( 8926.00, WithinRel( chunk.nonRadiativeTransitions()[40].energy().value() ) );
  CHECK_THAT( 8923.60, WithinRel( chunk.nonRadiativeTransitions()[41].energy().value() ) );
  CHECK_THAT( 8926.29, WithinRel( chunk.nonRadiativeTransitions()[42].energy().value() ) );

  CHECK_THAT( 0.43381157370, WithinRel( chunk.totalRadiativeProbability() ) );
  CHECK_THAT( 0.56618859798, WithinRel( chunk.totalNonRadiativeProbability() ) );
}
