// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/HardSpherePenetrabilityRatio.hpp"

// other includes
#include "njoy/dryad/resonances/HardSpherePenetrability.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "HardSpherePenetrability" ) {

  GIVEN( "valid orbital momentum values for a HardSpherePenetrability" ) {

    HardSpherePenetrability penetrability( 0 );
    HardSpherePenetrabilityRatio ratio( 0, 0 );

    CHECK( 0 == ratio.numeratorOrbitalAngularMomentum() );
    CHECK( 0 == ratio.denominatorOrbitalAngularMomentum() );

    CHECK_THAT( penetrability( 0.25 ) / 0.25, WithinRel( ratio( 0.25 ) ) );
    CHECK_THAT( penetrability( 0.50 ) / 0.50, WithinRel( ratio( 0.50 ) ) );
    CHECK_THAT( penetrability( 0.75 ) / 0.75, WithinRel( ratio( 0.75 ) ) );
    CHECK_THAT( penetrability( 1.00 ) / 1.00, WithinRel( ratio( 1.00 ) ) );
    CHECK_THAT( penetrability( 1.25 ) / 1.25, WithinRel( ratio( 1.25 ) ) );
    CHECK_THAT( penetrability( 1.50 ) / 1.50, WithinRel( ratio( 1.50 ) ) );
    CHECK_THAT( penetrability( 1.75 ) / 1.75, WithinRel( ratio( 1.75 ) ) );
    CHECK_THAT( penetrability( 2.00 ) / 2.00, WithinRel( ratio( 2.00 ) ) );
    CHECK_THAT( penetrability( 2.25 ) / 2.25, WithinRel( ratio( 2.25 ) ) );
    CHECK_THAT( penetrability( 2.50 ) / 2.50, WithinRel( ratio( 2.50 ) ) );
    CHECK_THAT( penetrability( 2.75 ) / 2.75, WithinRel( ratio( 2.75 ) ) );
    CHECK_THAT( penetrability( 3.00 ) / 3.00, WithinRel( ratio( 3.00 ) ) );
    CHECK_THAT( penetrability( 3.25 ) / 3.25, WithinRel( ratio( 3.25 ) ) );
    CHECK_THAT( penetrability( 3.50 ) / 3.50, WithinRel( ratio( 3.50 ) ) );
    CHECK_THAT( penetrability( 3.75 ) / 3.75, WithinRel( ratio( 3.75 ) ) );
    CHECK_THAT( penetrability( 4.00 ) / 4.00, WithinRel( ratio( 4.00 ) ) );
    CHECK_THAT( penetrability( 4.25 ) / 4.25, WithinRel( ratio( 4.25 ) ) );
    CHECK_THAT( penetrability( 4.50 ) / 4.50, WithinRel( ratio( 4.50 ) ) );
    CHECK_THAT( penetrability( 4.75 ) / 4.75, WithinRel( ratio( 4.75 ) ) );
    CHECK_THAT( penetrability( 5.00 ) / 5.00, WithinRel( ratio( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 1 );
    ratio = HardSpherePenetrabilityRatio( 1, 0 );

    CHECK( 1 == ratio.numeratorOrbitalAngularMomentum() );
    CHECK( 0 == ratio.denominatorOrbitalAngularMomentum() );

    CHECK_THAT( penetrability( 0.25 ) / 0.25, WithinRel( ratio( 0.25 ) ) );
    CHECK_THAT( penetrability( 0.50 ) / 0.50, WithinRel( ratio( 0.50 ) ) );
    CHECK_THAT( penetrability( 0.75 ) / 0.75, WithinRel( ratio( 0.75 ) ) );
    CHECK_THAT( penetrability( 1.00 ) / 1.00, WithinRel( ratio( 1.00 ) ) );
    CHECK_THAT( penetrability( 1.25 ) / 1.25, WithinRel( ratio( 1.25 ) ) );
    CHECK_THAT( penetrability( 1.50 ) / 1.50, WithinRel( ratio( 1.50 ) ) );
    CHECK_THAT( penetrability( 1.75 ) / 1.75, WithinRel( ratio( 1.75 ) ) );
    CHECK_THAT( penetrability( 2.00 ) / 2.00, WithinRel( ratio( 2.00 ) ) );
    CHECK_THAT( penetrability( 2.25 ) / 2.25, WithinRel( ratio( 2.25 ) ) );
    CHECK_THAT( penetrability( 2.50 ) / 2.50, WithinRel( ratio( 2.50 ) ) );
    CHECK_THAT( penetrability( 2.75 ) / 2.75, WithinRel( ratio( 2.75 ) ) );
    CHECK_THAT( penetrability( 3.00 ) / 3.00, WithinRel( ratio( 3.00 ) ) );
    CHECK_THAT( penetrability( 3.25 ) / 3.25, WithinRel( ratio( 3.25 ) ) );
    CHECK_THAT( penetrability( 3.50 ) / 3.50, WithinRel( ratio( 3.50 ) ) );
    CHECK_THAT( penetrability( 3.75 ) / 3.75, WithinRel( ratio( 3.75 ) ) );
    CHECK_THAT( penetrability( 4.00 ) / 4.00, WithinRel( ratio( 4.00 ) ) );
    CHECK_THAT( penetrability( 4.25 ) / 4.25, WithinRel( ratio( 4.25 ) ) );
    CHECK_THAT( penetrability( 4.50 ) / 4.50, WithinRel( ratio( 4.50 ) ) );
    CHECK_THAT( penetrability( 4.75 ) / 4.75, WithinRel( ratio( 4.75 ) ) );
    CHECK_THAT( penetrability( 5.00 ) / 5.00, WithinRel( ratio( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 2 );
    ratio = HardSpherePenetrabilityRatio( 2, 0 );

    CHECK( 2 == ratio.numeratorOrbitalAngularMomentum() );
    CHECK( 0 == ratio.denominatorOrbitalAngularMomentum() );

    CHECK_THAT( penetrability( 0.25 ) / 0.25, WithinRel( ratio( 0.25 ) ) );
    CHECK_THAT( penetrability( 0.50 ) / 0.50, WithinRel( ratio( 0.50 ) ) );
    CHECK_THAT( penetrability( 0.75 ) / 0.75, WithinRel( ratio( 0.75 ) ) );
    CHECK_THAT( penetrability( 1.00 ) / 1.00, WithinRel( ratio( 1.00 ) ) );
    CHECK_THAT( penetrability( 1.25 ) / 1.25, WithinRel( ratio( 1.25 ) ) );
    CHECK_THAT( penetrability( 1.50 ) / 1.50, WithinRel( ratio( 1.50 ) ) );
    CHECK_THAT( penetrability( 1.75 ) / 1.75, WithinRel( ratio( 1.75 ) ) );
    CHECK_THAT( penetrability( 2.00 ) / 2.00, WithinRel( ratio( 2.00 ) ) );
    CHECK_THAT( penetrability( 2.25 ) / 2.25, WithinRel( ratio( 2.25 ) ) );
    CHECK_THAT( penetrability( 2.50 ) / 2.50, WithinRel( ratio( 2.50 ) ) );
    CHECK_THAT( penetrability( 2.75 ) / 2.75, WithinRel( ratio( 2.75 ) ) );
    CHECK_THAT( penetrability( 3.00 ) / 3.00, WithinRel( ratio( 3.00 ) ) );
    CHECK_THAT( penetrability( 3.25 ) / 3.25, WithinRel( ratio( 3.25 ) ) );
    CHECK_THAT( penetrability( 3.50 ) / 3.50, WithinRel( ratio( 3.50 ) ) );
    CHECK_THAT( penetrability( 3.75 ) / 3.75, WithinRel( ratio( 3.75 ) ) );
    CHECK_THAT( penetrability( 4.00 ) / 4.00, WithinRel( ratio( 4.00 ) ) );
    CHECK_THAT( penetrability( 4.25 ) / 4.25, WithinRel( ratio( 4.25 ) ) );
    CHECK_THAT( penetrability( 4.50 ) / 4.50, WithinRel( ratio( 4.50 ) ) );
    CHECK_THAT( penetrability( 4.75 ) / 4.75, WithinRel( ratio( 4.75 ) ) );
    CHECK_THAT( penetrability( 5.00 ) / 5.00, WithinRel( ratio( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 3 );
    ratio = HardSpherePenetrabilityRatio( 3, 0 );

    CHECK( 3 == ratio.numeratorOrbitalAngularMomentum() );
    CHECK( 0 == ratio.denominatorOrbitalAngularMomentum() );

    CHECK_THAT( penetrability( 0.25 ) / 0.25, WithinRel( ratio( 0.25 ) ) );
    CHECK_THAT( penetrability( 0.50 ) / 0.50, WithinRel( ratio( 0.50 ) ) );
    CHECK_THAT( penetrability( 0.75 ) / 0.75, WithinRel( ratio( 0.75 ) ) );
    CHECK_THAT( penetrability( 1.00 ) / 1.00, WithinRel( ratio( 1.00 ) ) );
    CHECK_THAT( penetrability( 1.25 ) / 1.25, WithinRel( ratio( 1.25 ) ) );
    CHECK_THAT( penetrability( 1.50 ) / 1.50, WithinRel( ratio( 1.50 ) ) );
    CHECK_THAT( penetrability( 1.75 ) / 1.75, WithinRel( ratio( 1.75 ) ) );
    CHECK_THAT( penetrability( 2.00 ) / 2.00, WithinRel( ratio( 2.00 ) ) );
    CHECK_THAT( penetrability( 2.25 ) / 2.25, WithinRel( ratio( 2.25 ) ) );
    CHECK_THAT( penetrability( 2.50 ) / 2.50, WithinRel( ratio( 2.50 ) ) );
    CHECK_THAT( penetrability( 2.75 ) / 2.75, WithinRel( ratio( 2.75 ) ) );
    CHECK_THAT( penetrability( 3.00 ) / 3.00, WithinRel( ratio( 3.00 ) ) );
    CHECK_THAT( penetrability( 3.25 ) / 3.25, WithinRel( ratio( 3.25 ) ) );
    CHECK_THAT( penetrability( 3.50 ) / 3.50, WithinRel( ratio( 3.50 ) ) );
    CHECK_THAT( penetrability( 3.75 ) / 3.75, WithinRel( ratio( 3.75 ) ) );
    CHECK_THAT( penetrability( 4.00 ) / 4.00, WithinRel( ratio( 4.00 ) ) );
    CHECK_THAT( penetrability( 4.25 ) / 4.25, WithinRel( ratio( 4.25 ) ) );
    CHECK_THAT( penetrability( 4.50 ) / 4.50, WithinRel( ratio( 4.50 ) ) );
    CHECK_THAT( penetrability( 4.75 ) / 4.75, WithinRel( ratio( 4.75 ) ) );
    CHECK_THAT( penetrability( 5.00 ) / 5.00, WithinRel( ratio( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 4 );
    ratio = HardSpherePenetrabilityRatio( 4, 0 );

    CHECK( 4 == ratio.numeratorOrbitalAngularMomentum() );
    CHECK( 0 == ratio.denominatorOrbitalAngularMomentum() );

    CHECK_THAT( penetrability( 0.25 ) / 0.25, WithinRel( ratio( 0.25 ) ) );
    CHECK_THAT( penetrability( 0.50 ) / 0.50, WithinRel( ratio( 0.50 ) ) );
    CHECK_THAT( penetrability( 0.75 ) / 0.75, WithinRel( ratio( 0.75 ) ) );
    CHECK_THAT( penetrability( 1.00 ) / 1.00, WithinRel( ratio( 1.00 ) ) );
    CHECK_THAT( penetrability( 1.25 ) / 1.25, WithinRel( ratio( 1.25 ) ) );
    CHECK_THAT( penetrability( 1.50 ) / 1.50, WithinRel( ratio( 1.50 ) ) );
    CHECK_THAT( penetrability( 1.75 ) / 1.75, WithinRel( ratio( 1.75 ) ) );
    CHECK_THAT( penetrability( 2.00 ) / 2.00, WithinRel( ratio( 2.00 ) ) );
    CHECK_THAT( penetrability( 2.25 ) / 2.25, WithinRel( ratio( 2.25 ) ) );
    CHECK_THAT( penetrability( 2.50 ) / 2.50, WithinRel( ratio( 2.50 ) ) );
    CHECK_THAT( penetrability( 2.75 ) / 2.75, WithinRel( ratio( 2.75 ) ) );
    CHECK_THAT( penetrability( 3.00 ) / 3.00, WithinRel( ratio( 3.00 ) ) );
    CHECK_THAT( penetrability( 3.25 ) / 3.25, WithinRel( ratio( 3.25 ) ) );
    CHECK_THAT( penetrability( 3.50 ) / 3.50, WithinRel( ratio( 3.50 ) ) );
    CHECK_THAT( penetrability( 3.75 ) / 3.75, WithinRel( ratio( 3.75 ) ) );
    CHECK_THAT( penetrability( 4.00 ) / 4.00, WithinRel( ratio( 4.00 ) ) );
    CHECK_THAT( penetrability( 4.25 ) / 4.25, WithinRel( ratio( 4.25 ) ) );
    CHECK_THAT( penetrability( 4.50 ) / 4.50, WithinRel( ratio( 4.50 ) ) );
    CHECK_THAT( penetrability( 4.75 ) / 4.75, WithinRel( ratio( 4.75 ) ) );
    CHECK_THAT( penetrability( 5.00 ) / 5.00, WithinRel( ratio( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 5 );
    ratio = HardSpherePenetrabilityRatio( 5, 0 );

    CHECK( 5 == ratio.numeratorOrbitalAngularMomentum() );
    CHECK( 0 == ratio.denominatorOrbitalAngularMomentum() );

    CHECK_THAT( penetrability( 0.25 ) / 0.25, WithinRel( ratio( 0.25 ) ) );
    CHECK_THAT( penetrability( 0.50 ) / 0.50, WithinRel( ratio( 0.50 ) ) );
    CHECK_THAT( penetrability( 0.75 ) / 0.75, WithinRel( ratio( 0.75 ) ) );
    CHECK_THAT( penetrability( 1.00 ) / 1.00, WithinRel( ratio( 1.00 ) ) );
    CHECK_THAT( penetrability( 1.25 ) / 1.25, WithinRel( ratio( 1.25 ) ) );
    CHECK_THAT( penetrability( 1.50 ) / 1.50, WithinRel( ratio( 1.50 ) ) );
    CHECK_THAT( penetrability( 1.75 ) / 1.75, WithinRel( ratio( 1.75 ) ) );
    CHECK_THAT( penetrability( 2.00 ) / 2.00, WithinRel( ratio( 2.00 ) ) );
    CHECK_THAT( penetrability( 2.25 ) / 2.25, WithinRel( ratio( 2.25 ) ) );
    CHECK_THAT( penetrability( 2.50 ) / 2.50, WithinRel( ratio( 2.50 ) ) );
    CHECK_THAT( penetrability( 2.75 ) / 2.75, WithinRel( ratio( 2.75 ) ) );
    CHECK_THAT( penetrability( 3.00 ) / 3.00, WithinRel( ratio( 3.00 ) ) );
    CHECK_THAT( penetrability( 3.25 ) / 3.25, WithinRel( ratio( 3.25 ) ) );
    CHECK_THAT( penetrability( 3.50 ) / 3.50, WithinRel( ratio( 3.50 ) ) );
    CHECK_THAT( penetrability( 3.75 ) / 3.75, WithinRel( ratio( 3.75 ) ) );
    CHECK_THAT( penetrability( 4.00 ) / 4.00, WithinRel( ratio( 4.00 ) ) );
    CHECK_THAT( penetrability( 4.25 ) / 4.25, WithinRel( ratio( 4.25 ) ) );
    CHECK_THAT( penetrability( 4.50 ) / 4.50, WithinRel( ratio( 4.50 ) ) );
    CHECK_THAT( penetrability( 4.75 ) / 4.75, WithinRel( ratio( 4.75 ) ) );
    CHECK_THAT( penetrability( 5.00 ) / 5.00, WithinRel( ratio( 5.00 ) ) );
  } // GIVEN
} // SCENARIO
