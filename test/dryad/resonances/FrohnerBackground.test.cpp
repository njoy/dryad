// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/FrohnerBackground.hpp"

// other includes
#include <iostream>
#include <iomanip>
// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "FrohnerBackground" ) {

  GIVEN( "valid data for a FrohnerBackground" ) {

    double distant_level_parameter = 1.;
    double pole_strength = 2.;
    double average_radiation_width = 3.;
    double lower_singularity = 0.;
    double upper_singularity = 9.55e5;

    THEN( "a SammyBackground can be constructed" ) {

      FrohnerBackground chunk( distant_level_parameter,
                               pole_strength,
                               average_radiation_width,
                               lower_singularity,
                               upper_singularity );

      CHECK_THAT( 1.    , WithinRel( chunk.distantLevelParameter() ) );
      CHECK_THAT( 2.    , WithinRel( chunk.poleStrength() ) );
      CHECK_THAT( 3.    , WithinRel( chunk.averageRadiationWidth() ) );
      CHECK_THAT( 0.    , WithinRel( chunk.lowerSingularity() ) );
      CHECK_THAT( 9.55e5, WithinRel( chunk.upperSingularity() ) );

      CHECK_THAT( -3.291862565897340E+00, WithinRel( chunk( 1e+5 ).real() ) );
      CHECK_THAT(  3.350877192982460E-05, WithinRel( chunk( 1e+5 ).imag() ) );
    } // THEN
  } // GIVEN
} // SCENARIO
