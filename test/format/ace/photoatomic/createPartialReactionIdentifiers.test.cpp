// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/photoatomic/createPartialReactionNumbers.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createPartialReactionNumbers" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "reaction partials can be derived" ) {

        auto partials = format::ace::photoatomic::createPartialReactionNumbers( table );

        CHECK( 5 == partials.size() );

        CHECK( 4 == partials[0].size() );
        CHECK( 502 == partials[0][0] );
        CHECK( 504 == partials[0][1] );
        CHECK( 516 == partials[0][2] );
        CHECK( 522 == partials[0][3] );

        CHECK( 0 == partials[1].size() );

        CHECK( 0 == partials[2].size() );

        CHECK( 0 == partials[3].size() );

        CHECK( 0 == partials[4].size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reaction partials can be derived" ) {

        auto partials = format::ace::photoatomic::createPartialReactionNumbers( table );

        CHECK( 6 == partials.size() );

        CHECK( 4 == partials[0].size() );
        CHECK( 502 == partials[0][0] );
        CHECK( 504 == partials[0][1] );
        CHECK( 516 == partials[0][2] );
        CHECK( 534 == partials[0][3] );

        CHECK( 0 == partials[1].size() );

        CHECK( 0 == partials[2].size() );

        CHECK( 0 == partials[3].size() );

        CHECK( 1 == partials[4].size() );
        CHECK( 534 == partials[4][0] );

        CHECK( 0 == partials[5].size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reaction partials can be derived" ) {

        auto partials = format::ace::photoatomic::createPartialReactionNumbers( table );

        CHECK( 6 == partials.size() );

        CHECK( 4 == partials[0].size() );
        CHECK( 502 == partials[0][0] );
        CHECK( 504 == partials[0][1] );
        CHECK( 516 == partials[0][2] );
        CHECK( 534 == partials[0][3] );

        CHECK( 0 == partials[1].size() );

        CHECK( 0 == partials[2].size() );

        CHECK( 0 == partials[3].size() );

        CHECK( 1 == partials[4].size() );
        CHECK( 534 == partials[4][0] );

        CHECK( 0 == partials[5].size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
