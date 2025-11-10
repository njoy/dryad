// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/dryad/id/ElectronSubshellID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;

SCENARIO( "ElectronSubshellID" ) {

  GIVEN( "valid data for an ElectronSubshellID" ) {

    THEN( "an ElectronSubshellID can be created" ) {

      ElectronSubshellID id( ElectronSubshellID::K );
      CHECK( 1 == id.principalQuantumNumber() );
      CHECK( 0 == id.azimuthalQuantumNumber() );
      CHECK( 0.5 == id.totalAngularMomentum() );
      CHECK( 534 == id.mt() );
      CHECK( "1s1/2" == id.symbol() );
      CHECK( id == ElectronSubshellID( "1s1/2" ) );
      CHECK( id == ElectronSubshellID( "1s" ) );
      CHECK( id == ElectronSubshellID( "1s+" ) );
      CHECK( id == ElectronSubshellID( "K" ) );
      CHECK( true == id.isRelativistic() );
      CHECK( false == id.isNonRelativistic() );

      id = ElectronSubshellID( ElectronSubshellID::L1 );
      CHECK( 2 == id.principalQuantumNumber() );
      CHECK( 0 == id.azimuthalQuantumNumber() );
      CHECK( 0.5 == id.totalAngularMomentum() );
      CHECK( 535 == id.mt() );
      CHECK( "2s1/2" == id.symbol() );
      CHECK( id == ElectronSubshellID( "2s1/2" ) );
      CHECK( id == ElectronSubshellID( "2s" ) );
      CHECK( id == ElectronSubshellID( "2s+" ) );
      CHECK( id == ElectronSubshellID( "L1" ) );
      CHECK( true == id.isRelativistic() );
      CHECK( false == id.isNonRelativistic() );

      id = ElectronSubshellID( "2p" );
      CHECK( 2 == id.principalQuantumNumber() );
      CHECK( 1 == id.azimuthalQuantumNumber() );
      CHECK( std::nullopt == id.totalAngularMomentum() );
      CHECK( std::nullopt == id.mt() );
      CHECK( "2p" == id.symbol() );
      CHECK( false == id.isRelativistic() );
      CHECK( true == id.isNonRelativistic() );
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
      CHECK_THROWS( ElectronSubshellID( 583 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
