// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/ReactionType.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ReactionType = njoy::dryad::id::ReactionType;
using ParticleID = njoy::dryad::id::ParticleID;
using LevelID = njoy::dryad::id::LevelID;
using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;
using InteractionType = njoy::dryad::InteractionType;

SCENARIO( "ReactionType" ) {

  GIVEN( "valid data for a ReactionType" ) {

    auto n = ParticleID::neutron();
    auto p = ParticleID::proton();
    auto d = ParticleID::deuteron();
    auto t = ParticleID::triton();
    auto h = ParticleID::helion();
    auto a = ParticleID::alpha();
    auto eminus = ParticleID::electron();
    auto eplus = ParticleID::positron();

    auto nuclear = InteractionType::Nuclear;
    auto atomic = InteractionType::Atomic;

    std::vector< std::pair< ParticleID, char > > empty;

    THEN( "a ReactionType can be created using mt numbers and strings" ) {

      // special numbers
      ReactionType id( 1 );
      CHECK( 1 == id.number() );
      CHECK( 1 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "total" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "total" ) );
      CHECK( id == ReactionType( "total[nuclear]" ) );

      id = ReactionType( 3 );
      CHECK( 3 == id.number() );
      CHECK( 3 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "non-elastic" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "non-elastic" ) );

      id = ReactionType( 5 );
      CHECK( 5 == id.number() );
      CHECK( 5 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "anything" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "anything" ) );

      id = ReactionType( 18 );
      CHECK( 18 == id.number() );
      CHECK( 18 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "fission(t)" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "fission(t)" ) );

      id = ReactionType( 19 );
      CHECK( 19 == id.number() );
      CHECK( 19 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "fission" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "fission" ) );
      CHECK( id == ReactionType( "fission1" ) );

      id = ReactionType( 20 );
      CHECK( 20 == id.number() );
      CHECK( 20 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "fission[n]" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "fission[n]" ) );
      CHECK( id == ReactionType( "fission2" ) );

      id = ReactionType( 21 );
      CHECK( 21 == id.number() );
      CHECK( 21 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "fission[2n]" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "fission[2n]" ) );
      CHECK( id == ReactionType( "fission3" ) );

      id = ReactionType( 38 );
      CHECK( 38 == id.number() );
      CHECK( 38 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "fission[3n]" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "fission[3n]" ) );
      CHECK( id == ReactionType( "fission4" ) );

      id = ReactionType( 27 );
      CHECK( 27 == id.number() );
      CHECK( 27 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "absorption" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "absorption" ) );

      id = ReactionType( 101 );
      CHECK( 101 == id.number() );
      CHECK( 101 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "disappearance" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "disappearance" ) );

      // standard incident neutron and charged particle reaction types
      id = ReactionType( 4 );
      CHECK( 10151 == id.number() );
      CHECK( 4 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "n(t)" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { n, 1 } } == id.particles() );
      CHECK( LevelID::all == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "n" ) );
      CHECK( id == ReactionType( "n(t)" ) );

      id = ReactionType( 875 );
      CHECK( 20000 == id.number() );
      CHECK( 875 == id.mt() );
      CHECK( nuclear == id.type() );
      CHECK( "2n(0)" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { n, 2 } } == id.particles() );
      CHECK( 0 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "2n(0)" ) );

      // photoatomic and electroatomic reaction types
      id = ReactionType( 501 );
      CHECK( 501 == id.number() );
      CHECK( 501 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "total[atomic]" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 502 );
      CHECK( 502 == id.number() );
      CHECK( 502 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "g[coherent]" == id.symbol() );
      CHECK( empty == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "coherent" ) );

      id = ReactionType( 504 );
      CHECK( 504 == id.number() );
      CHECK( 504 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "g[incoherent]" == id.symbol() );
      CHECK( empty == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "incoherent" ) );

      id = ReactionType( "e-[deficit-scattering]" ); // no mt number for this
      CHECK( 1524 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-[deficit-scattering]" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "deficit-scattering" ) );

      id = ReactionType( 525 );
      CHECK( 1525 == id.number() );
      CHECK( 525 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-[large-angle-scattering]" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-[large-angle-scattering]" ) );
      CHECK( id == ReactionType( "large-angle-scattering" ) );

      id = ReactionType( 515 );
      CHECK( 1515 == id.number() );
      CHECK( 515 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "2e-e+[nuclear]" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 2 }, { eplus, 1 } }  == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "2e-e+[nuclear]" ) );
      CHECK( id == ReactionType( "pair-production[nuclear]" ) );

      id = ReactionType( 517 );
      CHECK( 1517 == id.number() );
      CHECK( 517 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "2e-e+[electron]" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 2 }, { eplus, 1 } }  == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "2e-e+[electron]" ) );
      CHECK( id == ReactionType( "pair-production[electron]" ) );

      id = ReactionType( 516 );
      CHECK( 1518 == id.number() );
      CHECK( 516 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "2e-e+" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 2 }, { eplus, 1 } }  == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "2e-e+" ) );
      CHECK( id == ReactionType( "pair-production" ) );

      id = ReactionType( 527 );
      CHECK( 1527 == id.number() );
      CHECK( 527 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-[bremsstrahlung]" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-[bremsstrahlung]" ) );
      CHECK( id == ReactionType( "bremsstrahlung" ) );

      id = ReactionType( 528 );
      CHECK( 1528 == id.number() );
      CHECK( 528 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-[excitation]" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-[excitation]" ) );
      CHECK( id == ReactionType( "excitation" ) );

      id = ReactionType( 534 );
      CHECK( 1534 == id.number() );
      CHECK( 534 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{1s1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::K == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{1s1/2}" ) );
      CHECK( id == ReactionType( "ionisation{1s1/2}" ) );

      id = ReactionType( 535 );
      CHECK( 1535 == id.number() );
      CHECK( 535 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{2s1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::L1 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{2s1/2}" ) );
      CHECK( id == ReactionType( "ionisation{2s1/2}" ) );

      id = ReactionType( 536 );
      CHECK( 1536 == id.number() );
      CHECK( 536 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{2p1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::L2 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{2p1/2}" ) );
      CHECK( id == ReactionType( "ionisation{2p1/2}" ) );

      id = ReactionType( 537 );
      CHECK( 1537 == id.number() );
      CHECK( 537 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{2p3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::L3 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{2p3/2}" ) );
      CHECK( id == ReactionType( "ionisation{2p3/2}" ) );

      id = ReactionType( 538 );
      CHECK( 1538 == id.number() );
      CHECK( 538 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{3s1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::M1 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{3s1/2}" ) );
      CHECK( id == ReactionType( "ionisation{3s1/2}" ) );

      id = ReactionType( 539 );
      CHECK( 1539 == id.number() );
      CHECK( 539 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{3p1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::M2 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{3p1/2}" ) );
      CHECK( id == ReactionType( "ionisation{3p1/2}" ) );

      id = ReactionType( 540 );
      CHECK( 1540 == id.number() );
      CHECK( 540 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{3p3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::M3 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{3p3/2}" ) );
      CHECK( id == ReactionType( "ionisation{3p3/2}" ) );

      id = ReactionType( 541 );
      CHECK( 1541 == id.number() );
      CHECK( 541 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{3d3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::M4 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{3d3/2}" ) );
      CHECK( id == ReactionType( "ionisation{3d3/2}" ) );

      id = ReactionType( 542 );
      CHECK( 1542 == id.number() );
      CHECK( 542 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{3d5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::M5 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{3d5/2}" ) );
      CHECK( id == ReactionType( "ionisation{3d5/2}" ) );

      id = ReactionType( 543 );
      CHECK( 1543 == id.number() );
      CHECK( 543 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{4s1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::N1 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{4s1/2}" ) );
      CHECK( id == ReactionType( "ionisation{4s1/2}" ) );

      id = ReactionType( 544 );
      CHECK( 1544 == id.number() );
      CHECK( 544 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{4p1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::N2 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{4p1/2}" ) );
      CHECK( id == ReactionType( "ionisation{4p1/2}" ) );

      id = ReactionType( 545 );
      CHECK( 1545 == id.number() );
      CHECK( 545 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{4p3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::N3 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{4p3/2}" ) );
      CHECK( id == ReactionType( "ionisation{4p3/2}" ) );

      id = ReactionType( 546 );
      CHECK( 1546 == id.number() );
      CHECK( 546 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{4d3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::N4 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{4d3/2}" ) );
      CHECK( id == ReactionType( "ionisation{4d3/2}" ) );

      id = ReactionType( 547 );
      CHECK( 1547 == id.number() );
      CHECK( 547 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{4d5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::N5 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{4d5/2}" ) );
      CHECK( id == ReactionType( "ionisation{4d5/2}" ) );

      id = ReactionType( 548 );
      CHECK( 1548 == id.number() );
      CHECK( 548 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{4f5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::N6 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{4f5/2}" ) );
      CHECK( id == ReactionType( "ionisation{4f5/2}" ) );

      id = ReactionType( 549 );
      CHECK( 1549 == id.number() );
      CHECK( 549 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{4f7/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::N7 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{4f7/2}" ) );
      CHECK( id == ReactionType( "ionisation{4f7/2}" ) );

      id = ReactionType( 550 );
      CHECK( 1550 == id.number() );
      CHECK( 550 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5s1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O1 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5s1/2}" ) );
      CHECK( id == ReactionType( "ionisation{5s1/2}" ) );

      id = ReactionType( 551 );
      CHECK( 1551 == id.number() );
      CHECK( 551 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5p1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O2 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5p1/2}" ) );
      CHECK( id == ReactionType( "ionisation{5p1/2}" ) );

      id = ReactionType( 552 );
      CHECK( 1552 == id.number() );
      CHECK( 552 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5p3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O3 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5p3/2}" ) );
      CHECK( id == ReactionType( "ionisation{5p3/2}" ) );

      id = ReactionType( 553 );
      CHECK( 1553 == id.number() );
      CHECK( 553 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5d3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O4 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5d3/2}" ) );
      CHECK( id == ReactionType( "ionisation{5d3/2}" ) );

      id = ReactionType( 554 );
      CHECK( 1554 == id.number() );
      CHECK( 554 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5d5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O5 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5d5/2}" ) );
      CHECK( id == ReactionType( "ionisation{5d5/2}" ) );

      id = ReactionType( 555 );
      CHECK( 1555 == id.number() );
      CHECK( 555 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5f5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O6 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5f5/2}" ) );
      CHECK( id == ReactionType( "ionisation{5f5/2}" ) );

      id = ReactionType( 556 );
      CHECK( 1556 == id.number() );
      CHECK( 556 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5f7/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O7 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5f7/2}" ) );
      CHECK( id == ReactionType( "ionisation{5f7/2}" ) );

      id = ReactionType( 557 );
      CHECK( 1557 == id.number() );
      CHECK( 557 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5g7/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O8 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5g7/2}" ) );
      CHECK( id == ReactionType( "ionisation{5g7/2}" ) );

      id = ReactionType( 558 );
      CHECK( 1558 == id.number() );
      CHECK( 558 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{5g9/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::O9 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{5g9/2}" ) );
      CHECK( id == ReactionType( "ionisation{5g9/2}" ) );

      id = ReactionType( 559 );
      CHECK( 1559 == id.number() );
      CHECK( 559 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6s1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P1 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6s1/2}" ) );
      CHECK( id == ReactionType( "ionisation{6s1/2}" ) );

      id = ReactionType( 560 );
      CHECK( 1560 == id.number() );
      CHECK( 560 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6p1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P2 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6p1/2}" ) );
      CHECK( id == ReactionType( "ionisation{6p1/2}" ) );

      id = ReactionType( 561 );
      CHECK( 1561 == id.number() );
      CHECK( 561 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6p3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P3 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6p3/2}" ) );
      CHECK( id == ReactionType( "ionisation{6p3/2}" ) );

      id = ReactionType( 562 );
      CHECK( 1562 == id.number() );
      CHECK( 562 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6d3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P4 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6d3/2}" ) );
      CHECK( id == ReactionType( "ionisation{6d3/2}" ) );

      id = ReactionType( 563 );
      CHECK( 1563 == id.number() );
      CHECK( 563 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6d5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P5 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6d5/2}" ) );
      CHECK( id == ReactionType( "ionisation{6d5/2}" ) );

      id = ReactionType( 564 );
      CHECK( 1564 == id.number() );
      CHECK( 564 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6f5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P6 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6f5/2}" ) );
      CHECK( id == ReactionType( "ionisation{6f5/2}" ) );

      id = ReactionType( 565 );
      CHECK( 1565 == id.number() );
      CHECK( 565 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6f7/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P7 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6f7/2}" ) );
      CHECK( id == ReactionType( "ionisation{6f7/2}" ) );

      id = ReactionType( 566 );
      CHECK( 1566 == id.number() );
      CHECK( 566 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6g7/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P8 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6g7/2}" ) );
      CHECK( id == ReactionType( "ionisation{6g7/2}" ) );

      id = ReactionType( 567 );
      CHECK( 1567 == id.number() );
      CHECK( 567 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6g9/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P9 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6g9/2}" ) );
      CHECK( id == ReactionType( "ionisation{6g9/2}" ) );

      id = ReactionType( 568 );
      CHECK( 1568 == id.number() );
      CHECK( 568 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6h9/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P10 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6h9/2}" ) );
      CHECK( id == ReactionType( "ionisation{6h9/2}" ) );

      id = ReactionType( 569 );
      CHECK( 1569 == id.number() );
      CHECK( 569 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{6h11/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::P11 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{6h11/2}" ) );
      CHECK( id == ReactionType( "ionisation{6h11/2}" ) );





      id = ReactionType( 570 );
      CHECK( 1570 == id.number() );
      CHECK( 570 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7s1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q1 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{7s1/2}" ) );
      CHECK( id == ReactionType( "ionisation{7s1/2}" ) );

      id = ReactionType( 571 );
      CHECK( 1571 == id.number() );
      CHECK( 571 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7p1/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q2 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{7p1/2}" ) );
      CHECK( id == ReactionType( "ionisation{7p1/2}" ) );

      id = ReactionType( 572 );
      CHECK( 1572 == id.number() );
      CHECK( 572 == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7p3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q3 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "e-{7p3/2}" ) );
      CHECK( id == ReactionType( "ionisation{7p3/2}" ) );

      // the next set do not have mt numbers assigned to them
      id = ReactionType( "e-{7d3/2}" );
      CHECK( 1573 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7d3/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q4 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7d3/2}" ) );

      id = ReactionType( "e-{7d5/2}" );
      CHECK( 1574 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7d5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q5 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7d5/2}" ) );

      id = ReactionType( "e-{7f5/2}" );
      CHECK( 1575 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7f5/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q6 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7f5/2}" ) );

      id = ReactionType( "e-{7f7/2}" );
      CHECK( 1576 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7f7/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q7 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7f7/2}" ) );

      id = ReactionType( "e-{7g7/2}" );
      CHECK( 1577 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7g7/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q8 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7g7/2}" ) );

      id = ReactionType( "e-{7g9/2}" );
      CHECK( 1578 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7g9/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q9 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7g9/2}" ) );

      id = ReactionType( "e-{7h9/2}" );
      CHECK( 1579 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7h9/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q10 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7h9/2}" ) );

      id = ReactionType( "e-{7h11/2}" );
      CHECK( 1580 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7h11/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q11 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7h11/2}" ) );

      id = ReactionType( "e-{7i11/2}" );
      CHECK( 1581 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7i11/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q12 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7i11/2}" ) );

      id = ReactionType( "e-{7i13/2}" );
      CHECK( 1582 == id.number() );
      CHECK( std::nullopt == id.mt() );
      CHECK( atomic == id.type() );
      CHECK( "e-{7i13/2}" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { eminus, 1 } }  == id.particles() );
      CHECK( ElectronSubshellID::Q13 == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( false == id.isCompatibleWithENDF() );
      CHECK( id == ReactionType( "ionisation{7i13/2}" ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid ReactionType instances" ) {

    ReactionType id1( 50 );
    ReactionType id2( 600 );

    THEN( "instances can be compared" ) {

      CHECK( ( id1 <  id1 ) == false );
      CHECK( ( id1 <= id1 ) == true );
      CHECK( ( id1 >  id1 ) == false );
      CHECK( ( id1 >= id1 ) == true );
      CHECK( ( id1 == id1 ) == true );
      CHECK( ( id1 != id1 ) == false );
      CHECK( ( id1 <  id2 ) == true );
      CHECK( ( id1 <= id2 ) == true );
      CHECK( ( id1 >  id2 ) == false );
      CHECK( ( id1 >= id2 ) == false );
      CHECK( ( id1 == id2 ) == false );
      CHECK( ( id1 != id2 ) == true );
      CHECK( ( id2 <  id1 ) == false );
      CHECK( ( id2 <= id1 ) == false );
      CHECK( ( id2 >  id1 ) == true );
      CHECK( ( id2 >= id1 ) == true );
      CHECK( ( id2 == id1 ) == false );
      CHECK( ( id2 != id1 ) == true );
    } // THEN

    THEN( "instances can be used as keys in a std::map" ) {

      std::map< ReactionType, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ReactionType( 50 ) ] == "1" );
      CHECK( map[ ReactionType( 600 ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< ReactionType, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ReactionType( 50 ) ] == "1" );
      CHECK( map[ ReactionType( 600 ) ] == "2" );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a ReactionType" ) {

    THEN( "an exception is thrown" ) {

      // illegal values
      CHECK_THROWS( ReactionType( "not a particle symbol" ) );
      CHECK_THROWS( ReactionType( -1000 ) );
      CHECK_THROWS( ReactionType( 2 ) ); // 2 has no meaning without knowing the incident particle type
    } // THEN
  } // GIVEN
} // SCENARIO
