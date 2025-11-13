// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/CoulombPhaseShift.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "CoulombPhaseShift" ) {

  GIVEN( "valid orbital momentum values for a CoulombPhaseShift" ) {

    CoulombPhaseShift phaseShift( 0 );

    CHECK( 0 == phaseShift.orbitalAngularMomentum() );
    phaseShift( 1., 1. );
    //! @todo test against values

    phaseShift = CoulombPhaseShift( 1 );

    CHECK( 1 == phaseShift.orbitalAngularMomentum() );
    phaseShift( 1., 1. );
    //! @todo test against values

    phaseShift = CoulombPhaseShift( 2 );

    CHECK( 2 == phaseShift.orbitalAngularMomentum() );
    phaseShift( 1., 1. );
    //! @todo test against values

    phaseShift = CoulombPhaseShift( 3 );

    CHECK( 3 == phaseShift.orbitalAngularMomentum() );
    phaseShift( 1., 1. );
    //! @todo test against values

    phaseShift = CoulombPhaseShift( 4 );

    CHECK( 4 == phaseShift.orbitalAngularMomentum() );
    phaseShift( 1., 1. );
    //! @todo test against values
  } // GIVEN
} // SCENARIO
