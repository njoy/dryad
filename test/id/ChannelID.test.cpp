// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/ChannelID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ChannelID = njoy::dryad::id::ChannelID;
using ReactionID = njoy::dryad::id::ReactionID;
using ChannelQuantumNumbers = njoy::dryad::resonances::ChannelQuantumNumbers;

SCENARIO( "ChannelID" ) {

  GIVEN( "valid data for a ChannelID" ) {

    ReactionID elastic( "n,U235->n,U235" );
    ReactionID fission( "n,U235->fission(t)" );
    ChannelQuantumNumbers numbers( 0, 0.5, 0.5, +1 );

    THEN( "a ChannelID can be created" ) {

      auto size = ChannelID::size();

      ChannelID id( "n,U235->n,U235{0,1/2,1/2+}" );
      CHECK( elastic == id.reaction() );
      CHECK( numbers == id.quantumNumbers() );
      CHECK( std::nullopt == id.partial() );
      CHECK( "n,U235->n,U235{0,1/2,1/2+}" == id.symbol() );
      CHECK( id == ChannelID( elastic, numbers ) );

      CHECK( size + 1 == ChannelID::size() );

      id = ChannelID( "n,U235->fission(t){0,1/2,1/2+}[0]" );
      CHECK( fission == id.reaction() );
      CHECK( numbers == id.quantumNumbers() );
      CHECK( 0 == id.partial() );
      CHECK( "n,U235->fission(t){0,1/2,1/2+}[0]" == id.symbol() );
      CHECK( id == ChannelID( fission, numbers, 0 ) );

      CHECK( size + 2 == ChannelID::size() );

      id = ChannelID( "n,U235->fission(t){0,1/2,1/2+}[1]" );
      CHECK( fission == id.reaction() );
      CHECK( numbers == id.quantumNumbers() );
      CHECK( 1 == id.partial() );
      CHECK( "n,U235->fission(t){0,1/2,1/2+}[1]" == id.symbol() );
      CHECK( id == ChannelID( fission, numbers, 1 ) );

      CHECK( size + 3 == ChannelID::size() );
    }
  } // GIVEN

  GIVEN( "valid ReactionID instances" ) {

    ChannelID id1( "n,U235->fission(t){0,1/2,1/2+}[1]" );
    ChannelID id2( "n,U235->n,U235{0,1/2,1/2+}" );

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

      std::map< ChannelID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ChannelID( "n,U235->fission(t){0,1/2,1/2+}[1]" ) ] == "1" );
      CHECK( map[ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< ChannelID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ChannelID( "n,U235->fission(t){0,1/2,1/2+}[1]" ) ] == "1" );
      CHECK( map[ ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ] == "2" );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a ReactionID" ) {

    THEN( "an exception is thrown" ) {


    } // THEN
  } // GIVEN
} // SCENARIO
