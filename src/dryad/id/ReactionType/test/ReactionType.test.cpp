// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/ReactionType.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ReactionType = njoy::dryad::id::ReactionType;

SCENARIO( "ReactionType" ) {

  GIVEN( "valid data for a ReactionType" ) {

    THEN( "an ReactionType can be created" ) {

      ReactionType id( 1 );
      CHECK( 1 == id.number() );
      CHECK( "total" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( true == id.isCompatibleWithENDF() );


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

//  GIVEN( "invalid data for an ReactionType" ) {
//
//    THEN( "an exception is thrown" ) {
//
//      CHECK_THROWS( ReactionType( "not a particle symbol" ) );
//      CHECK_THROWS( ReactionType( -1000 ) );
//      CHECK_THROWS( ReactionType( 1000, 1 ) );
//      CHECK_THROWS( ReactionType( 1000, njoy::dryad::id::LevelID::continuum ) );
//      CHECK_THROWS( ReactionType( 1000, njoy::dryad::id::LevelID::all ) );
//      CHECK_THROWS( ReactionType( 1000, 152 ) );
//      CHECK_THROWS( ReactionType( 1001, 152 ) );
//      CHECK_THROWS( ReactionType( "H_e0" ) );
//      CHECK_THROWS( ReactionType( "H_e1" ) );
//      CHECK_THROWS( ReactionType( "H1_e152" ) );
//      CHECK_THROWS( ReactionType( 1000, 533 ) );
//      CHECK_THROWS( ReactionType( 1000, 581 ) );
//    } // THEN
//  } // GIVEN
} // SCENARIO
