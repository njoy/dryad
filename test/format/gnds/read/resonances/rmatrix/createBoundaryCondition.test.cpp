// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/resonances/rmatrix/createBoundaryCondition.hpp"

// other includes

// convenience typedefs
using namespace njoy::format::gnds::read::resonances::rmatrix;

SCENARIO( "createBoundaryCondition" ) {

  GIVEN( "GNDS rmatrix boundary condition values" ) {

    WHEN( "an rmatrix boundary condition is given" ) {

      THEN( "it can be converted" ) {

        CHECK( BoundaryCondition::Constant == createBoundaryCondition( "Given" ) );
        CHECK( BoundaryCondition::ShiftFactor == createBoundaryCondition( "EliminateShiftFunction" ) );
        CHECK( BoundaryCondition::NegativeOrbitalMomentum == createBoundaryCondition( "NegativeOrbitalMomentum" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( createBoundaryCondition( "com" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
