// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createInteractionType.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;
using namespace njoy::dryad;

SCENARIO( "createInteractionType" ) {

  GIVEN( "GNDS interpolation values" ) {

    WHEN( "an interpolation value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( InteractionType::Nuclear == gnds::read::createInteractionType( "nuclear" ) );
        CHECK( InteractionType::Atomic == gnds::read::createInteractionType( "atomic" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( gnds::read::createInteractionType( "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
