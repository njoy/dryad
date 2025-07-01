// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/ReactionID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using InteractionType = njoy::dryad::InteractionType;
using LevelID = njoy::dryad::id::LevelID;
using NewReactionID = njoy::dryad::id::NewReactionID;
using ParticleID = njoy::dryad::id::ParticleID;
using ReactionType = njoy::dryad::id::ReactionType;

SCENARIO( "ReactionID" ) {

  GIVEN( "valid data for a ReactionID" ) {

    ParticleID g = ParticleID::photon();
    ParticleID n = ParticleID::neutron();
    ParticleID p = ParticleID::proton();
    ParticleID d = ParticleID::deuteron();
    ParticleID t = ParticleID::triton();
    ParticleID h = ParticleID::helion();
    ParticleID a = ParticleID::alpha();
    ParticleID eminus = ParticleID::electron();
    ParticleID eplus = ParticleID::positron();
    ParticleID u238( 92238 );
    ParticleID u( 92000 );

    std::map< ParticleID, short > empty;

    THEN( "a ReactionID can be created using mt numbers, strings and static functions" ) {

      auto size = NewReactionID::size();

      NewReactionID id( n, u238, ReactionType( 1 ) );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.residual() );
      CHECK( ReactionType( 1 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->total" == id.symbol() );
      CHECK( id == NewReactionID( "n,U238->total" ) );

      CHECK( size + 1 == NewReactionID::size() );

      id = NewReactionID( n, u238, ReactionType::elastic( n ) );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 1 } } == id.particles() );
      CHECK( u238 == id.residual() );
      CHECK( ReactionType( 50 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->n,U238" == id.symbol() );
      CHECK( id == NewReactionID( "n,U238->n,U238" ) );

      CHECK( size + 2 == NewReactionID::size() );

      id = NewReactionID( n, u238, ReactionType( 102 ) );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( empty == id.particles() );
      CHECK( ParticleID( 92239, LevelID::all ) == id.residual() );
      CHECK( ReactionType( 102 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->g,U239[all]" == id.symbol() );
      CHECK( id == NewReactionID( "n,U238->g,U239[all]" ) );

      CHECK( size + 3 == NewReactionID::size() );

      id = NewReactionID( n, u238, ReactionType( 199 ) );
      CHECK( n == id.projectile() );
      CHECK( u238 == id.target() );
      CHECK( std::map< ParticleID, short >{ { n, 3 }, { p, 2 }, { a, 1 } } == id.particles() );
      CHECK( ParticleID( 88230, LevelID::all ) == id.residual() );
      CHECK( ReactionType( 199 ) == id.reactionType() );
      CHECK( InteractionType::Nuclear == id.interactionType() );
      CHECK( "n,U238->3n,2p,a,Ra230[all]" == id.symbol() );
      CHECK( id == NewReactionID( "n,U238->3n,2p,a,Ra230[all]" ) );

      CHECK( size + 4 == NewReactionID::size() );

      id = NewReactionID( eminus, u, ReactionType( 525 ) );
      CHECK( eminus == id.projectile() );
      CHECK( u == id.target() );
      CHECK( std::map< ParticleID, short >{ { eminus, 1 } } == id.particles() );
      CHECK( u == id.residual() );
      CHECK( ReactionType( 525 ) == id.reactionType() );
      CHECK( InteractionType::Atomic == id.interactionType() );
      CHECK( "e-,U->e-,U[large-angle-scattering]" == id.symbol() );
      CHECK( id == NewReactionID( "e-,U->e-,U[large-angle-scattering]" ) );

      CHECK( size + 5 == NewReactionID::size() );
    }
  } // GIVEN

  GIVEN( "valid ReactionID instances" ) {

    ParticleID n = ParticleID::neutron();
    ParticleID u238( 92238 );

    NewReactionID id1( n, u238, ReactionType( 102 ) );
    NewReactionID id2( n, u238, ReactionType( 199 ) );

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

      std::map< NewReactionID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ NewReactionID( n, u238, ReactionType( 102 ) ) ] == "1" );
      CHECK( map[ NewReactionID( n, u238, ReactionType( 199 ) ) ] == "2" );
    } // THEN

//    THEN( "instances can be used as keys in a std::unordered_map" ) {
//
//      std::unordered_map< NewReactionID, std::string > map{
//
//        { id1, "1" }, { id2, "2" }
//      };
//
//      CHECK( map[ id1 ] == "1" );
//      CHECK( map[ id2 ] == "2" );
//      CHECK( map[ NewReactionID( n, u238, ReactionType( 102 ) ) ] == "1" );
//      CHECK( map[ NewReactionID( n, u238, ReactionType( 199 ) ) ] == "2" );
//    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a ReactionID" ) {

    THEN( "an exception is thrown" ) {


    } // THEN
  } // GIVEN
} // SCENARIO
