// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createInteractionType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createInteractionType" ) {

  GIVEN( "ENDF sublibrary values" ) {

    WHEN( "a single sublibrary value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( InteractionType::Nuclear == format::endf::createInteractionType( 0 ) );
        CHECK( InteractionType::Atomic == format::endf::createInteractionType( 3 ) );
        CHECK( InteractionType::Nuclear == format::endf::createInteractionType( 10 ) );
        CHECK( InteractionType::Atomic == format::endf::createInteractionType( 113 ) );
        CHECK( InteractionType::Nuclear == format::endf::createInteractionType( 10010 ) );
        CHECK( InteractionType::Nuclear == format::endf::createInteractionType( 10020 ) );
        CHECK( InteractionType::Nuclear == format::endf::createInteractionType( 10030 ) );
        CHECK( InteractionType::Nuclear == format::endf::createInteractionType( 20030 ) );
        CHECK( InteractionType::Nuclear == format::endf::createInteractionType( 20040 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported sublibrary type" ) {

        CHECK_THROWS( format::endf::createInteractionType( 1 ) );
        CHECK_THROWS( format::endf::createInteractionType( 40090 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
