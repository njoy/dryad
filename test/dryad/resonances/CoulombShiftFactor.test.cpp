// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/CoulombShiftFactor.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "CoulombShiftFactor" ) {

  GIVEN( "valid orbital momentum values for a CoulombShiftFactor" ) {

    CoulombShiftFactor shiftFactor( 0 );

    CHECK( 0 == shiftFactor.orbitalAngularMomentum() );
    shiftFactor( 1., 1. );
    //! @todo test against values

    shiftFactor = CoulombShiftFactor( 1 );

    CHECK( 1 == shiftFactor.orbitalAngularMomentum() );
    shiftFactor( 1., 1. );
    //! @todo test against values

    shiftFactor = CoulombShiftFactor( 2 );

    CHECK( 2 == shiftFactor.orbitalAngularMomentum() );
    shiftFactor( 1., 1. );
    //! @todo test against values

    shiftFactor = CoulombShiftFactor( 3 );

    CHECK( 3 == shiftFactor.orbitalAngularMomentum() );
    shiftFactor( 1., 1. );
    //! @todo test against values

    shiftFactor = CoulombShiftFactor( 4 );

    CHECK( 4 == shiftFactor.orbitalAngularMomentum() );
    shiftFactor( 1., 1. );
    //! @todo test against values
  } // GIVEN
} // SCENARIO
