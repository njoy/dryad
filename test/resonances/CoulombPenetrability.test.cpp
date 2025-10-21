// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/CoulombPenetrability.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "CoulombPenetrability" ) {

  GIVEN( "valid orbital momentum values for a CoulombPenetrability" ) {

    CoulombPenetrability penetrability( 0 );

    CHECK( 0 == penetrability.orbitalAngularMomentum() );
    //! @todo test against values

    penetrability = CoulombPenetrability( 1 );

    CHECK( 1 == penetrability.orbitalAngularMomentum() );
    //! @todo test against values

    penetrability = CoulombPenetrability( 2 );

    CHECK( 2 == penetrability.orbitalAngularMomentum() );
    //! @todo test against values

    penetrability = CoulombPenetrability( 3 );

    CHECK( 3 == penetrability.orbitalAngularMomentum() );
    //! @todo test against values

    penetrability = CoulombPenetrability( 4 );

    CHECK( 4 == penetrability.orbitalAngularMomentum() );
    //! @todo test against values
  } // GIVEN
} // SCENARIO
