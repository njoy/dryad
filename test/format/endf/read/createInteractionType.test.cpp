// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createInteractionType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createInteractionType" ) {

  GIVEN( "ENDF sublibrary values" ) {

    WHEN( "a single sublibrary value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( InteractionType::Nuclear == endf::read::createInteractionType( 0 ) );
        CHECK( InteractionType::Atomic == endf::read::createInteractionType( 3 ) );
        CHECK( InteractionType::Nuclear == endf::read::createInteractionType( 10 ) );
        CHECK( InteractionType::Atomic == endf::read::createInteractionType( 113 ) );
        CHECK( InteractionType::Nuclear == endf::read::createInteractionType( 10010 ) );
        CHECK( InteractionType::Nuclear == endf::read::createInteractionType( 10020 ) );
        CHECK( InteractionType::Nuclear == endf::read::createInteractionType( 10030 ) );
        CHECK( InteractionType::Nuclear == endf::read::createInteractionType( 20030 ) );
        CHECK( InteractionType::Nuclear == endf::read::createInteractionType( 20040 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported sublibrary type" ) {

        CHECK_THROWS( endf::read::createInteractionType( 1 ) );
        CHECK_THROWS( endf::read::createInteractionType( 40090 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
