// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/photoatomic/createReactionIdentifiers.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createReactionNumbers" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      auto g = id::ParticleID::photon();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::photoatomic::createReactionIdentifiers( g, H, table );

        CHECK( 5 == numbers.size() );

        CHECK( id::ReactionID( "g,H->total[atomic]" ) == numbers[0] );
        CHECK( id::ReactionID( "g,H->g,H[coherent]" ) == numbers[1] );
        CHECK( id::ReactionID( "g,H->g,H[incoherent]" ) == numbers[2] );
        CHECK( id::ReactionID( "g,H->pair-production" ) == numbers[3] );
        CHECK( id::ReactionID( "g,H->e-,H" ) == numbers[4] );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      auto g = id::ParticleID::photon();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::photoatomic::createReactionIdentifiers( g, H, table );

        CHECK( 6 == numbers.size() );

        CHECK( id::ReactionID( "g,H->total[atomic]" ) == numbers[0] );
        CHECK( id::ReactionID( "g,H->g,H[coherent]" ) == numbers[1] );
        CHECK( id::ReactionID( "g,H->g,H[incoherent]" ) == numbers[2] );
        CHECK( id::ReactionID( "g,H->pair-production" ) == numbers[3] );
        CHECK( id::ReactionID( "g,H->e-,H" ) == numbers[4] );
        CHECK( id::ReactionID( "g,H->e-,H{1s1/2}" ) == numbers[5] );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      auto g = id::ParticleID::photon();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::photoatomic::createReactionIdentifiers( g, H, table );

        CHECK( 6 == numbers.size() );

        CHECK( id::ReactionID( "g,H->total[atomic]" ) == numbers[0] );
        CHECK( id::ReactionID( "g,H->g,H[coherent]" ) == numbers[1] );
        CHECK( id::ReactionID( "g,H->g,H[incoherent]" ) == numbers[2] );
        CHECK( id::ReactionID( "g,H->pair-production" ) == numbers[3] );
        CHECK( id::ReactionID( "g,H->e-,H" ) == numbers[4] );
        CHECK( id::ReactionID( "g,H->e-,H{1s1/2}" ) == numbers[5] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
