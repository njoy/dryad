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

SCENARIO( "ReactionType" ) {

  GIVEN( "valid data for a ReactionType" ) {

    auto n = ParticleID::neutron();
    auto p = ParticleID::proton();
    auto d = ParticleID::deuteron();
    auto t = ParticleID::triton();
    auto h = ParticleID::helion();
    auto a = ParticleID::alpha();

    THEN( "a ReactionType can be created using mt numbers" ) {

      // special numbers
      ReactionType id( 1 );
      CHECK( 1 == id.number() );
      CHECK( "total" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 3 );
      CHECK( 3 == id.number() );
      CHECK( "non-elastic" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 5 );
      CHECK( 5 == id.number() );
      CHECK( "anything" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 18 );
      CHECK( 18 == id.number() );
      CHECK( "fission(t)" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 19 );
      CHECK( 19 == id.number() );
      CHECK( "fission" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 20 );
      CHECK( 20 == id.number() );
      CHECK( "fission[n]" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 21 );
      CHECK( 21 == id.number() );
      CHECK( "fission[2n]" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 38 );
      CHECK( 38 == id.number() );
      CHECK( "fission[3n]" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 27 );
      CHECK( 27 == id.number() );
      CHECK( "absorption" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 101 );
      CHECK( 101 == id.number() );
      CHECK( "disappearance" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( std::nullopt == id.level() );
      CHECK( true == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      // normal mt numbers
      id = ReactionType( 4 );
      CHECK( 10151 == id.number() );
      CHECK( "n(t)" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { n, 1 } } == id.particles() );
      CHECK( LevelID::all == id.level() );
      CHECK( false == id.isSpecial() );
      CHECK( true == id.isCompatibleWithENDF() );

      id = ReactionType( 875 );
      CHECK( 20000 == id.number() );
      CHECK( "2n(0)" == id.symbol() );
      CHECK( std::vector< std::pair< ParticleID, char > >{ { n, 2 } } == id.particles() );
      CHECK( 0 == id.level() );
      CHECK( false == id.isSpecial() );
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

  GIVEN( "invalid data for a ReactionType" ) {

    THEN( "an exception is thrown" ) {

      // illegal values
      CHECK_THROWS( ReactionType( "not a particle symbol" ) );
      CHECK_THROWS( ReactionType( -1000 ) );
      CHECK_THROWS( ReactionType( 2 ) ); // 2 has no meaning without knowing the incident particle type
    } // THEN
  } // GIVEN
} // SCENARIO
