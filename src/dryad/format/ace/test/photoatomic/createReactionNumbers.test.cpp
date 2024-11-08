// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/photoatomic/createReactionNumbers.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createReactionNumbers" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::photoatomic::createReactionNumbers( table );

        CHECK( 5 == numbers.size() );

        CHECK( 501 == numbers[0] );
        CHECK( 502 == numbers[1] );
        CHECK( 504 == numbers[2] );
        CHECK( 516 == numbers[3] );
        CHECK( 522 == numbers[4] );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::photoatomic::createReactionNumbers( table );

        CHECK( 6 == numbers.size() );

        CHECK( 501 == numbers[0] );
        CHECK( 502 == numbers[1] );
        CHECK( 504 == numbers[2] );
        CHECK( 516 == numbers[3] );
        CHECK( 522 == numbers[4] );
        CHECK( 534 == numbers[5] );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reaction numbers can be derived" ) {

        auto numbers = format::ace::photoatomic::createReactionNumbers( table );

        CHECK( 6 == numbers.size() );

        CHECK( 501 == numbers[0] );
        CHECK( 502 == numbers[1] );
        CHECK( 504 == numbers[2] );
        CHECK( 516 == numbers[3] );
        CHECK( 522 == numbers[4] );
        CHECK( 534 == numbers[5] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
