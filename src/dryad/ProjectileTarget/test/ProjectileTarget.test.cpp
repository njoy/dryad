// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/ProjectileTarget.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "ProjectileTarget" ) {

  GIVEN( "valid data for a ProjectileTarget" ) {

    WHEN( "the data is given explicitly" ) {


      THEN( "a ProjectileTarget can be constructed and members can be tested" ) {


      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
