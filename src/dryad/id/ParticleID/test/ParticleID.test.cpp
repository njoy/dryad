// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/ParticleID.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ParticleID = njoy::dryad::id::ParticleID;

SCENARIO( "ParticleID" ) {

  GIVEN( "valid data for an ParticleID" ) {

    THEN( "an ParticleID can be created" ) {

      CHECK( 127 == ParticleID::size() ); // 127 pre-registered identifiers

      ParticleID id( "g" );
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );

      id = ParticleID( "photon" );
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );

      id = ParticleID( "gamma" );
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );

      id = ParticleID( "x-ray" );
      CHECK( 0 == id.number() );
      CHECK( "g" == id.symbol() );

      id = ParticleID( "e-" );
      CHECK( 1 == id.number() );
      CHECK( "e-" == id.symbol() );

      id = ParticleID( "electron" );
      CHECK( 1 == id.number() );
      CHECK( "e-" == id.symbol() );

      id = ParticleID( "beta-" );
      CHECK( 1 == id.number() );
      CHECK( "e-" == id.symbol() );

      id = ParticleID( "e+" );
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );

      id = ParticleID( "positron" );
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );

      id = ParticleID( "beta+" );
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );

      id = ParticleID( "e-_anti" );
      CHECK( 2 == id.number() );
      CHECK( "e+" == id.symbol() );

      id = ParticleID( "n" );
      CHECK( 10 == id.number() );
      CHECK( "n" == id.symbol() );

      id = ParticleID( "neutron" );
      CHECK( 10 == id.number() );
      CHECK( "n" == id.symbol() );

      id = ParticleID( "p" );
      CHECK( 1001 == id.number() );
      CHECK( "p" == id.symbol() );

      id = ParticleID( "proton" );
      CHECK( 1001 == id.number() );
      CHECK( "p" == id.symbol() );

      id = ParticleID( "d" );
      CHECK( 1002 == id.number() );
      CHECK( "d" == id.symbol() );

      id = ParticleID( "deuteron" );
      CHECK( 1002 == id.number() );
      CHECK( "d" == id.symbol() );

      id = ParticleID( "t" );
      CHECK( 1003 == id.number() );
      CHECK( "t" == id.symbol() );

      id = ParticleID( "triton" );
      CHECK( 1003 == id.number() );
      CHECK( "t" == id.symbol() );

      id = ParticleID( "h" );
      CHECK( 2003 == id.number() );
      CHECK( "h" == id.symbol() );

      id = ParticleID( "helion" );
      CHECK( 2003 == id.number() );
      CHECK( "h" == id.symbol() );

      id = ParticleID( "a" );
      CHECK( 2004 == id.number() );
      CHECK( "a" == id.symbol() );

      id = ParticleID( "alpha" );
      CHECK( 2004 == id.number() );
      CHECK( "a" == id.symbol() );

      CHECK( 127 == ParticleID::size() ); // 127 pre-registered identifiers

      id = ParticleID( 1001, 0 );
      CHECK( 1001000 == id.number() );
      CHECK( "H1" == id.symbol() );

      CHECK( 128 == ParticleID::size() ); // registering H1

      id = ParticleID( "H1" );
      CHECK( 1001000 == id.number() );
      CHECK( "H1" == id.symbol() );

      CHECK( 128 == ParticleID::size() ); // H1 already registered

      id = ParticleID( "H1_e0" );
      CHECK( 1001000 == id.number() );
      CHECK( "H1" == id.symbol() );

      CHECK( 128 == ParticleID::size() ); // H1 already registered

      id = ParticleID( 1001, 10 );
      CHECK( 1001010 == id.number() );
      CHECK( "H1_e10" == id.symbol() );

      CHECK( 129 == ParticleID::size() ); // registering H1_e10

      id = ParticleID( "H1_e10" );
      CHECK( 1001010 == id.number() );
      CHECK( "H1_e10" == id.symbol() );

      CHECK( 129 == ParticleID::size() ); // H1_e10 already registered

      id = ParticleID( 1001, njoy::dryad::id::LevelID::continuum );
      CHECK( 1001150 == id.number() );
      CHECK( "H1[continuum]" == id.symbol() );

      CHECK( 130 == ParticleID::size() ); // registering H1[continuum]

      id = ParticleID( "H1[continuum]" );
      CHECK( 1001150 == id.number() );
      CHECK( "H1[continuum]" == id.symbol() );

      CHECK( 130 == ParticleID::size() ); // H1[continuum] already registered
    } // THEN
  } // GIVEN

  GIVEN( "valid ParticleID instances" ) {

    ParticleID id1( 1001 );
    ParticleID id2( 1001, 10 );

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

      std::map< ParticleID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ParticleID( 1001 ) ] == "1" );
      CHECK( map[ ParticleID( 1001, 10 ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< ParticleID, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ParticleID( 1001 ) ] == "1" );
      CHECK( map[ ParticleID( 1001, 10 ) ] == "2" );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for an ParticleID" ) {

    THEN( "an exception is thrown" ) {

      CHECK_THROWS( ParticleID( "not a particle symbol" ) );
      CHECK_THROWS( ParticleID( -1000 ) );
      CHECK_THROWS( ParticleID( 1000, 151 ) );
      CHECK_THROWS( ParticleID( "H1_e151" ) );
    } // THEN
  } // GIVEN
} // SCENARIO
