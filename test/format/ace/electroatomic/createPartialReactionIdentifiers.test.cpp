// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/electroatomic/createPartialReactionIdentifiers.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createPartialReactionNumbers" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      auto e = id::ParticleID::electron();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "partials can be derived" ) {

        auto partials = format::ace::electroatomic::createPartialReactionIdentifiers( e, H, table );

        CHECK( 0 == partials.size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      auto e = id::ParticleID::electron();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "partials can be derived" ) {

        auto partials = format::ace::electroatomic::createPartialReactionIdentifiers( e, H, table );

        CHECK( 6 == partials.size() );

        CHECK( 4 == partials[0].size() );
        CHECK( id::NewReactionID( "e-,H->e-,H[total-scattering]" ) == partials[0][0] );
        CHECK( id::NewReactionID( "e-,H->e-,H[bremsstrahlung]" ) == partials[0][1] );
        CHECK( id::NewReactionID( "e-,H->e-,H[excitation]" ) == partials[0][2] );
        CHECK( id::NewReactionID( "e-,H->2e-,H{1s1/2}" ) == partials[0][3] );

        CHECK( 1 == partials[1].size() );
        CHECK( id::NewReactionID( "e-,H->2e-,H{1s1/2}" ) == partials[1][0] );

        CHECK( 0 == partials[2].size() );

        CHECK( 0 == partials[3].size() );

        CHECK( 0 == partials[4].size() );

        CHECK( 0 == partials[5].size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      auto e = id::ParticleID::electron();
      auto H = id::ParticleID( "H" );
      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "partials can be derived" ) {

        auto partials = format::ace::electroatomic::createPartialReactionIdentifiers( e, H, table );

        CHECK( 8 == partials.size() );

        CHECK( 5 == partials[0].size() );
        CHECK( id::NewReactionID( "e-,H->e-,H[large-angle-scattering]" ) == partials[0][0] );
        CHECK( id::NewReactionID( "e-,H->e-,H[bremsstrahlung]" ) == partials[0][1] );
        CHECK( id::NewReactionID( "e-,H->e-,H[excitation]" ) == partials[0][2] );
        CHECK( id::NewReactionID( "e-,H->2e-,H{1s1/2}" ) == partials[0][3] );
        CHECK( id::NewReactionID( "e-,H->e-,H[deficit-scattering]" ) == partials[0][4] );

        CHECK( 1 == partials[1].size() );
        CHECK( id::NewReactionID( "e-,H->2e-,H{1s1/2}" ) == partials[1][0] );

        CHECK( 0 == partials[2].size() );

        CHECK( 2 == partials[3].size() );
        CHECK( id::NewReactionID( "e-,H->e-,H[large-angle-scattering]" ) == partials[3][0] );
        CHECK( id::NewReactionID( "e-,H->e-,H[deficit-scattering]" ) == partials[3][1] );

        CHECK( 0 == partials[4].size() );

        CHECK( 0 == partials[5].size() );

        CHECK( 0 == partials[6].size() );

        CHECK( 0 == partials[7].size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
