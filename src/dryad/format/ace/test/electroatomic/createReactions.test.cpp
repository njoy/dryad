// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/electroatomic/createReactions.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createReactions" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::electroatomic::createReactions( table );

        CHECK( 0 == reactions.size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::electroatomic::createReactions( table );

        CHECK( 0 == reactions.size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = format::ace::electroatomic::createReactions( table );

        CHECK( 0 == reactions.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
