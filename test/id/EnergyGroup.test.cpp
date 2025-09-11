// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/EnergyGroup.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using namespace njoy::dryad::covariance;

SCENARIO( "EnergyGroup" ) {

  GIVEN( "valid group boundaries" ) {

    double lower = 1e-5;
    double upper = 100.;

    EnergyGroup chunk( lower, upper );

    THEN( "an EnergyGroup can be constructed and members can be tested" ) {

      CHECK_THAT( 1e-5, WithinRel( chunk.lowerEnergy() ) );
      CHECK_THAT( 100., WithinRel( chunk.upperEnergy() ) );

    } // THEN
  } // GIVEN

  GIVEN( "valid EnergyGroup instances" ) {

    EnergyGroup id1( 1e-5, 100. );
    EnergyGroup id2( 1e-5, 2e+7 );

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

      std::map< EnergyGroup, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ EnergyGroup( 1e-5, 100. ) ] == "1" );
      CHECK( map[ EnergyGroup( 1e-5, 2e+7 ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< EnergyGroup, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ EnergyGroup( 1e-5, 100. ) ] == "1" );
      CHECK( map[ EnergyGroup( 1e-5, 2e+7 ) ] == "2" );
    } // THEN
  } // GIVEN
} // SCENARIO