// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/createInteractionType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createInteractionType" ) {

  GIVEN( "dryad interpolation values" ) {

    WHEN( "an interpolation value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( "nuclear" == gnds::write::createInteractionType( InteractionType::Nuclear ) );
        CHECK( "atomic" == gnds::write::createInteractionType( InteractionType::Atomic ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
