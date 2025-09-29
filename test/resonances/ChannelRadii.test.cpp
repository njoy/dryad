// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/ChannelRadii.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ChannelRadii" ) {

  GIVEN( "valid data for a ChannelRadii" ) {

    double radius = 0.1;

    double trueRadius = 0.2;
    double effectiveRadius = 0.3;

    double pRadius = 0.4;
    double sRadius = 0.5;
    double phiRadius = 0.6;

    THEN( "a ChannelRadii can be constructed using constant radii" ) {

      double energy = 1e-5;

      ChannelRadii radii1( radius );

      CHECK_THAT( 0.1, WithinRel( radii1.calculatePenetrabilityRadius( energy ) ) );
      CHECK_THAT( 0.1, WithinRel( radii1.calculateShiftFactorRadius( energy ) ) );
      CHECK_THAT( 0.1, WithinRel( radii1.calculatePhaseShiftRadius( energy ) ) );

      ChannelRadii radii2( trueRadius, effectiveRadius );

      CHECK_THAT( 0.2, WithinRel( radii2.calculatePenetrabilityRadius( energy ) ) );
      CHECK_THAT( 0.2, WithinRel( radii2.calculateShiftFactorRadius( energy ) ) );
      CHECK_THAT( 0.3, WithinRel( radii2.calculatePhaseShiftRadius( energy ) ) );

      ChannelRadii radii3( pRadius, sRadius, phiRadius );

      CHECK_THAT( 0.4, WithinRel( radii3.calculatePenetrabilityRadius( energy ) ) );
      CHECK_THAT( 0.5, WithinRel( radii3.calculateShiftFactorRadius( energy ) ) );
      CHECK_THAT( 0.6, WithinRel( radii3.calculatePhaseShiftRadius( energy ) ) );
    } // THEN
  } // GIVEN
} // SCENARIO
