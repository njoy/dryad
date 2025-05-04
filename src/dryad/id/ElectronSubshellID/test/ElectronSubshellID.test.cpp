// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/ElectronSubshellID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;

SCENARIO( "ElectronSubshellID" ) {

  GIVEN( "valid data for an ElectronSubshellID" ) {

    THEN( "an ElectronSubshellID can be created" ) {

      ElectronSubshellID id( ElectronSubshellID::K );
      CHECK( 534 == id.number() );
      CHECK( "1s1/2" == id.symbol() );
      CHECK( "K" == id.name() );

      id = ElectronSubshellID( "1s1/2" );
      CHECK( 534 == id.number() );
      CHECK( "K" == id.name() );

      id = ElectronSubshellID( "K" );
      CHECK( 534 == id.number() );
      CHECK( "K" == id.name() );

      id = ElectronSubshellID( ElectronSubshellID::L1 );
      CHECK( 535 == id.number() );
      CHECK( "2s1/2" == id.symbol() );
      CHECK( "L1" == id.name() );

      id = ElectronSubshellID( "2s1/2" );
      CHECK( 535 == id.number() );
      CHECK( "L1" == id.name() );

      id = ElectronSubshellID( "L1" );
      CHECK( 535 == id.number() );
      CHECK( "L1" == id.name() );
    } // THEN
  } // GIVEN

  GIVEN( "valid ElectronSubshellID instances" ) {

    ElectronSubshellID id1( ElectronSubshellID::K );
    ElectronSubshellID id2( ElectronSubshellID::L1 );

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

      std::map< ElectronSubshellID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ElectronSubshellID( ElectronSubshellID::K ) ] == "1" );
      CHECK( map[ ElectronSubshellID( ElectronSubshellID::L1 ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< ElectronSubshellID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ElectronSubshellID( ElectronSubshellID::K ) ] == "1" );
      CHECK( map[ ElectronSubshellID( ElectronSubshellID::L1 ) ] == "2" );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for an ElectronSubshellID" ) {

    THEN( "an exception is thrown" ) {

      CHECK_THROWS( ElectronSubshellID( "not an element name, symbol or alternative" ) );
      CHECK_THROWS( ElectronSubshellID( -1 ) );
      CHECK_THROWS( ElectronSubshellID( 533 ) );
      CHECK_THROWS( ElectronSubshellID( 581 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
