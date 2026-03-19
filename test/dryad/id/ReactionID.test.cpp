// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/dryad/id/ReactionID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using InteractionType = njoy::dryad::InteractionType;
using LevelID = njoy::dryad::id::LevelID;
using ReactionID = njoy::dryad::id::ReactionID;
using ParticleID = njoy::dryad::id::ParticleID;
using ReactionType = njoy::dryad::id::ReactionType;

SCENARIO( "ReactionID" ) {

  GIVEN( "valid data for a ReactionID" ) {

    ParticleID n = ParticleID::neutron();
    ParticleID p = ParticleID::proton();
    ParticleID a = ParticleID::alpha();
    ParticleID eminus = ParticleID::electron();
    ParticleID u235( "U235" );
    ParticleID u238( "U238" );
    ParticleID am242( "Am242" );
    ParticleID am242m( "Am242_e2" );
    ParticleID u( "U" );

    std::map< ParticleID, short > empty;

    THEN( "a ReactionID can be created using mt numbers, strings and static functions" ) {

      auto size = ReactionID::size();

      ReactionID id( "n,U238->total" );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.residual() );
      CHECK( 1 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 1 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->total" == id.symbol() );
      CHECK( id == ReactionID( n, u238, 1 ) );
      CHECK( id == ReactionID( n, u238, "total" ) );
      CHECK( id == ReactionID( n, u238, "total[nuclear]" ) );
      CHECK( id == ReactionID( n, u238, ReactionType( 1 ) ) );

      CHECK( size + 1 == ReactionID::size() );

      id = ReactionID( "n,U238->n,U238" );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 1 } } == id.particles() );
      CHECK( u238 == id.residual() );
      CHECK( 50 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 50 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->n,U238" == id.symbol() );
      CHECK( id == ReactionID( "n,U238->n(0)" ) );
      CHECK( id == ReactionID( n, u238, 2 ) );
      CHECK( id == ReactionID( n, u238, "n(0)" ) );
      CHECK( id == ReactionID( n, u238, ReactionType::elastic( n ) ) );

      CHECK( size + 2 == ReactionID::size() );

      id = ReactionID( "n,U238->g,U239[all]" );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( empty == id.particles() );
      CHECK( ParticleID( "U239[all]" ) == id.residual() );
      CHECK( 102 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 102 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->g,U239[all]" == id.symbol() );
      CHECK( id == ReactionID( "n,U238->g(t)" ) );
      CHECK( id == ReactionID( "n,U238->g" ) );
      CHECK( id == ReactionID( "n,U238->capture" ) );
      CHECK( id == ReactionID( n, u238, 102 ) );
      CHECK( id == ReactionID( n, u238, "g(t)" ) );
      CHECK( id == ReactionID( n, u238, "g" ) );
      CHECK( id == ReactionID( n, u238, "capture" ) );
      CHECK( id == ReactionID( n, u238, ReactionType( 102 ) ) );

      CHECK( size + 3 == ReactionID::size() );

      id = ReactionID( "n,U238->3n,2p,a,Ra230[all]" );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 3 }, { p, 2 }, { a, 1 } } == id.particles() );
      CHECK( ParticleID( "Ra230[all]" ) == id.residual() );
      CHECK( 199 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 199 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->3n,2p,a,Ra230[all]" == id.symbol() );
      CHECK( id == ReactionID( "n,U238->3n2pa,Ra230[all]" ) );
      CHECK( id == ReactionID( "n,U238->3n2pa(t)" ) );
      CHECK( id == ReactionID( "n,U238->3n2pa" ) );
      CHECK( id == ReactionID( "n,U238->3n,2p,a(t)" ) );
      CHECK( id == ReactionID( "n,U238->3n,2p,a" ) );
      CHECK( id == ReactionID( n, u238, 199 ) );
      CHECK( id == ReactionID( n, u238, "3n2pa(t)" ) );
      CHECK( id == ReactionID( n, u238, "3n2pa" ) );
      CHECK( id == ReactionID( n, u238, "3n,2p,a(t)" ) );
      CHECK( id == ReactionID( n, u238, "3n,2p,a" ) );
      CHECK( id == ReactionID( n, u238, ReactionType( 199 ) ) );

      CHECK( size + 4 == ReactionID::size() );

      id = ReactionID( n, u235, 1 );
      CHECK( n == id.projectile() );
      CHECK( u235 == id.target() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.residual() );
      CHECK( 1 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 1 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U235->total" == id.symbol() );
      CHECK( id == ReactionID( "n,U235->total" ) );
      CHECK( id == ReactionID( "n,U235->total[nuclear]" ) );
      CHECK( id == ReactionID( n, u235, "total" ) );
      CHECK( id == ReactionID( n, u235, "total[nuclear]" ) );
      CHECK( id == ReactionID( n, u235, ReactionType( 1 ) ) );

      CHECK( size + 5 == ReactionID::size() );

      id = ReactionID( n, u235, 2 );
      CHECK( n == id.projectile() );
      CHECK( u235 == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 1 } } == id.particles() );
      CHECK( u235 == id.residual() );
      CHECK( 50 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 50 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U235->n,U235" == id.symbol() );
      CHECK( id == ReactionID( "n,U235->n,U235" ) );
      CHECK( id == ReactionID( "n,U235->n(0)" ) );
      CHECK( id == ReactionID( n, u235, "n(0)" ) );
      CHECK( id == ReactionID( n, u235, 50 ) );
      CHECK( id == ReactionID( n, u235, ReactionType::elastic( n ) ) );

      CHECK( size + 6 == ReactionID::size() );

      id = ReactionID( n, u235, 102 );
      CHECK( n == id.projectile() );
      CHECK( u235 == id.target() );
      CHECK( empty == id.particles() );
      CHECK( ParticleID( "U236[all]" ) == id.residual() );
      CHECK( 102 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 102 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U235->g,U236[all]" == id.symbol() );
      CHECK( id == ReactionID( "n,U235->g,U236[all]" ) );
      CHECK( id == ReactionID( "n,U235->g(t)" ) );
      CHECK( id == ReactionID( "n,U235->g" ) );
      CHECK( id == ReactionID( "n,U235->capture" ) );
      CHECK( id == ReactionID( n, u235, "g(t)" ) );
      CHECK( id == ReactionID( n, u235, "g" ) );
      CHECK( id == ReactionID( n, u235, "capture" ) );
      CHECK( id == ReactionID( n, u235, ReactionType( 102 ) ) );

      CHECK( size + 7 == ReactionID::size() );

      id = ReactionID( n, u235, 199 );
      CHECK( n == id.projectile() );
      CHECK( u235 == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 3 }, { p, 2 }, { a, 1 } } == id.particles() );
      CHECK( ParticleID( "Ra227[all]" ) == id.residual() );
      CHECK( 199 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 199 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U235->3n,2p,a,Ra227[all]" == id.symbol() );
      CHECK( id == ReactionID( "n,U235->3n,2p,a,Ra227[all]" ) );
      CHECK( id == ReactionID( "n,U235->3n2pa,Ra227[all]" ) );
      CHECK( id == ReactionID( "n,U235->3n,2p,a(t)" ) );
      CHECK( id == ReactionID( "n,U235->3n,2p,a" ) );
      CHECK( id == ReactionID( "n,U235->3n2pa(t)" ) );
      CHECK( id == ReactionID( "n,U235->3n2pa" ) );
      CHECK( id == ReactionID( n, u235, "3n,2p,a(t)" ) );
      CHECK( id == ReactionID( n, u235, "3n,2p,a" ) );
      CHECK( id == ReactionID( n, u235, "3n2pa(t)" ) );
      CHECK( id == ReactionID( n, u235, "3n2pa" ) );
      CHECK( id == ReactionID( n, u235, ReactionType( 199 ) ) );

      CHECK( size + 8 == ReactionID::size() );

      id = ReactionID( "e-,U->e-,U[large-angle-scattering]" );
      CHECK( eminus == id.projectile() );
      CHECK( u == id.target() );
      CHECK( std::map< ParticleID, short >{ { eminus, 1 } } == id.particles() );
      CHECK( u == id.residual() );
      CHECK( 525 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 525 ) == id.reactionType() );
      CHECK( InteractionType::Atomic == id.interactionType() );
      CHECK( "e-,U->e-,U[large-angle-scattering]" == id.symbol() );
      CHECK( id == ReactionID( eminus, u, 525 ) );
      CHECK( id == ReactionID( eminus, u, "large-angle-scattering" ) );
      CHECK( id == ReactionID( eminus, u, ReactionType( 525 ) ) );

      CHECK( size + 9 == ReactionID::size() );

      id = ReactionID( "e-,U->e-,U[total-scattering]" );
      CHECK( eminus == id.projectile() );
      CHECK( u == id.target() );
      CHECK( std::map< ParticleID, short >{ { eminus, 1 } } == id.particles() );
      CHECK( u == id.residual() );
      CHECK( 526 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 526 ) == id.reactionType() );
      CHECK( InteractionType::Atomic == id.interactionType() );
      CHECK( "e-,U->e-,U[total-scattering]" == id.symbol() );
      CHECK( id == ReactionID( eminus, u, 526 ) );
      CHECK( id == ReactionID( eminus, u, "total-scattering" ) );
      CHECK( id == ReactionID( eminus, u, ReactionType( 526 ) ) );

      CHECK( size + 10 == ReactionID::size() );

      id = ReactionID( "n,U238->n,U238[continuum]" );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 1 } } == id.particles() );
      CHECK( 91 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 91 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->n,U238[continuum]" == id.symbol() );
      CHECK( id == ReactionID( "n,U238->n(c)" ) );
      CHECK( id == ReactionID( n, u238, 91 ) );
      CHECK( id == ReactionID( n, u238, "n(c)" ) );
      CHECK( id == ReactionID( n, u238, ReactionType( 91 ) ) );

      CHECK( size + 11 == ReactionID::size() );

      id = ReactionID( "n,Am242_e2->n,Am242_e2" );
      CHECK( n == id.projectile() );
      CHECK( am242m == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 1 } } == id.particles() );
      CHECK( am242m == id.residual() );
      CHECK( 52 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 52 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,Am242_e2->n,Am242_e2" == id.symbol() );
      CHECK( id == ReactionID( "n,Am242_e2->n(2)" ) );
      CHECK( id == ReactionID( n, am242m, 2 ) );
      CHECK( id == ReactionID( n, am242m, 52 ) );
      CHECK( id == ReactionID( n, am242m, "n(2)" ) );
      CHECK( id == ReactionID( n, am242m, ReactionType::elastic( n, 2 ) ) );

      CHECK( size + 12 == ReactionID::size() );

      id = ReactionID( "n,Am242_e2->n,Am242" );
      CHECK( n == id.projectile() );
      CHECK( am242m == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 1 } } == id.particles() );
      CHECK( am242 == id.residual() );
      CHECK( 50 == id.mt() );
      CHECK( true == id.isCompatibleWithENDF() );
      CHECK( ReactionType( 50 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,Am242_e2->n,Am242" == id.symbol() );
      CHECK( id == ReactionID( "n,Am242_e2->n(0)" ) );
      CHECK( id == ReactionID( n, am242m, 50 ) );
      CHECK( id == ReactionID( n, am242m, "n(0)" ) );
      CHECK( id == ReactionID( n, am242m, ReactionType( 50 ) ) );

      CHECK( size + 13 == ReactionID::size() );
    }
  } // GIVEN

  GIVEN( "valid ReactionID instances" ) {

    ParticleID n = ParticleID::neutron();
    ParticleID u238( "U238" );

    ReactionID id1( n, u238, ReactionType( 102 ) );
    ReactionID id2( n, u238, ReactionType( 199 ) );

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

      std::map< ReactionID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ReactionID( n, u238, ReactionType( 102 ) ) ] == "1" );
      CHECK( map[ ReactionID( n, u238, ReactionType( 199 ) ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< ReactionID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ReactionID( n, u238, ReactionType( 102 ) ) ] == "1" );
      CHECK( map[ ReactionID( n, u238, ReactionType( 199 ) ) ] == "2" );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a ReactionID" ) {

    THEN( "an exception is thrown" ) {


    } // THEN
  } // GIVEN
} // SCENARIO
