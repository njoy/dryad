// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/external/ame/Masses.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::external::ame;

SCENARIO( "Masses" ) {

  GIVEN( "the AME data in Masses" ) {

    THEN( "predefined particles can be retrieved" ) {

      if ( std::getenv( "NJOY_DATAPATH" ) ) {

//        const auto& entry = Masses::entry( id::ParticleID( "H1" ) );

//        CHECK( id::ParticleID( "H1" ) == data.identifier() );
      }
    } // THEN

    THEN( "requesting a non-existent particle throws an exception" ) {

      if ( std::getenv( "NJOY_DATAPATH" ) ) {

        id::ParticleID h1( "H1" );
        id::ParticleID h20( "H20" );

//        CHECK_NOTHROW( Masses::entry( h1 ) );
        CHECK_THROWS( Masses::entry( h20 ) );
      }
    } // THEN
  } // GIVEN
} // SCENARIO
