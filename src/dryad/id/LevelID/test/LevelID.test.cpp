// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/LevelID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using LevelID = njoy::dryad::id::LevelID;

SCENARIO( "LevelID" ) {

  GIVEN( "valid data for an LevelID" ) {

    THEN( "an LevelID can be created" ) {

      LevelID id( 0 );
      CHECK( 0 == id.number() );
      CHECK( "" == id.symbol() );

      id = LevelID( "" );
      CHECK( 0 == id.number() );
      CHECK( "" == id.symbol() );

      id = LevelID( "_e0" );
      CHECK( 0 == id.number() );
      CHECK( "" == id.symbol() );

      id = LevelID( 1 );
      CHECK( 1 == id.number() );
      CHECK( "_e1" == id.symbol() );

      id = LevelID( "_e1" );
      CHECK( 1 == id.number() );
      CHECK( "_e1" == id.symbol() );

      auto continuum = njoy::dryad::id::LevelID::continuum;

      id = LevelID( continuum );
      CHECK( continuum == id.number() );
      CHECK( "[continuum]" == id.symbol() );

      id = LevelID( "[continuum]" );
      CHECK( continuum == id.number() );
      CHECK( "[continuum]" == id.symbol() );
    } // THEN
  } // GIVEN

  GIVEN( "valid LevelID instances" ) {

    LevelID id1( 1 );
    LevelID id2( 2 );

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

      std::map< LevelID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ LevelID( 1 ) ] == "1" );
      CHECK( map[ LevelID( 2 ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< LevelID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ LevelID( 1 ) ] == "1" );
      CHECK( map[ LevelID( 2 ) ] == "2" );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for an LevelID" ) {

    THEN( "an exception is thrown" ) {

      CHECK_THROWS( LevelID( "not an level symbol" ) );
      CHECK_THROWS( LevelID( -1 ) );
      CHECK_THROWS( LevelID( 151 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
