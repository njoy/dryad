// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/rmatrix/createBoundaryCondition.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createBoundaryCondition" ) {

  GIVEN( "dryad formalism values" ) {

    WHEN( "a formalism value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( "Given" == gnds::write::resonances::rmatrix::createBoundaryCondition( resonances::BoundaryCondition::Constant ) );
        CHECK( "EliminateShiftFunction" == gnds::write::resonances::rmatrix::createBoundaryCondition( resonances::BoundaryCondition::ShiftFactor ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
