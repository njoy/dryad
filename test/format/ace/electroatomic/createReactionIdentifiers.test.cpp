// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/electroatomic/createReactionIdentifiers.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createReactionTypes" ) {

  auto e = id::ParticleID::electron();

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      auto e = id::ParticleID::electron();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::electroatomic::createReactionIdentifiers( e, H, table );

        CHECK( 0 == numbers.size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      auto e = id::ParticleID::electron();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::electroatomic::createReactionIdentifiers( e, H, table );

        CHECK( 6 == numbers.size() );

        CHECK( id::ReactionID( "e-,H->total[atomic]" ) == numbers[0] );
        CHECK( id::ReactionID( "e-,H->2e-,H" ) == numbers[1] );
        CHECK( id::ReactionID( "e-,H->e-,H[total-scattering]" ) == numbers[2] );
        CHECK( id::ReactionID( "e-,H->e-,H[bremsstrahlung]" ) == numbers[3] );
        CHECK( id::ReactionID( "e-,H->e-,H[excitation]" ) == numbers[4] );
        CHECK( id::ReactionID( "e-,H->2e-,H{1s1/2}" ) == numbers[5] );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      auto e = id::ParticleID::electron();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::electroatomic::createReactionIdentifiers( e, H, table );

        CHECK( 8 == numbers.size() );

        CHECK( id::ReactionID( "e-,H->total[atomic]" ) == numbers[0] );
        CHECK( id::ReactionID( "e-,H->2e-,H" ) == numbers[1] );
        CHECK( id::ReactionID( "e-,H->e-,H[large-angle-scattering]" ) == numbers[2] );
        CHECK( id::ReactionID( "e-,H->e-,H[total-scattering]" ) == numbers[3] );
        CHECK( id::ReactionID( "e-,H->e-,H[bremsstrahlung]" ) == numbers[4] );
        CHECK( id::ReactionID( "e-,H->e-,H[excitation]" ) == numbers[5] );
        CHECK( id::ReactionID( "e-,H->2e-,H{1s1/2}" ) == numbers[6] );
        CHECK( id::ReactionID( "e-,H->e-,H[deficit-scattering]" ) == numbers[7] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
