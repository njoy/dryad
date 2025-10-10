// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/HardSphereShiftFactor.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "HardSphereShiftFactor" ) {

  GIVEN( "valid orbital momentum values for a HardSphereShiftFactor" ) {

    HardSphereShiftFactor shiftFactor( 0 );

    CHECK_THAT( 0., WithinRel( shiftFactor( 0.00 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 0.25 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 0.50 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 0.75 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 1.00 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 1.25 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 1.50 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 1.75 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 2.00 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 2.25 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 2.50 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 2.75 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 3.00 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 3.25 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 3.50 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 3.75 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 4.00 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 4.25 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 4.50 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 4.75 ) ) );
    CHECK_THAT( 0., WithinRel( shiftFactor( 5.00 ) ) );

    shiftFactor = HardSphereShiftFactor( 1 );

    CHECK_THAT( -1.0                 , WithinRel( shiftFactor( 0.00 ) ) );
    CHECK_THAT( -0.94117647058823528 , WithinRel( shiftFactor( 0.25 ) ) );
    CHECK_THAT( -0.80000000000000004 , WithinRel( shiftFactor( 0.50 ) ) );
    CHECK_THAT( -0.64000000000000001 , WithinRel( shiftFactor( 0.75 ) ) );
    CHECK_THAT( -0.5                 , WithinRel( shiftFactor( 1.00 ) ) );
    CHECK_THAT( -0.3902439024390244  , WithinRel( shiftFactor( 1.25 ) ) );
    CHECK_THAT( -0.30769230769230771 , WithinRel( shiftFactor( 1.50 ) ) );
    CHECK_THAT( -0.24615384615384617 , WithinRel( shiftFactor( 1.75 ) ) );
    CHECK_THAT( -0.20000000000000001 , WithinRel( shiftFactor( 2.00 ) ) );
    CHECK_THAT( -0.16494845360824742 , WithinRel( shiftFactor( 2.25 ) ) );
    CHECK_THAT( -0.13793103448275862 , WithinRel( shiftFactor( 2.50 ) ) );
    CHECK_THAT( -0.11678832116788321 , WithinRel( shiftFactor( 2.75 ) ) );
    CHECK_THAT( -0.10000000000000001 , WithinRel( shiftFactor( 3.00 ) ) );
    CHECK_THAT( -0.086486486486486491, WithinRel( shiftFactor( 3.25 ) ) );
    CHECK_THAT( -0.075471698113207544, WithinRel( shiftFactor( 3.50 ) ) );
    CHECK_THAT( -0.066390041493775934, WithinRel( shiftFactor( 3.75 ) ) );
    CHECK_THAT( -0.058823529411764705, WithinRel( shiftFactor( 4.00 ) ) );
    CHECK_THAT( -0.052459016393442623, WithinRel( shiftFactor( 4.25 ) ) );
    CHECK_THAT( -0.047058823529411764, WithinRel( shiftFactor( 4.50 ) ) );
    CHECK_THAT( -0.042440318302387266, WithinRel( shiftFactor( 4.75 ) ) );
    CHECK_THAT( -0.038461538461538464, WithinRel( shiftFactor( 5.00 ) ) );

    shiftFactor = HardSphereShiftFactor( 2 );

    CHECK_THAT( -2.0                , WithinRel( shiftFactor( 0.00 ) ) );
    CHECK_THAT( -1.9787505312367191 , WithinRel( shiftFactor( 0.25 ) ) );
    CHECK_THAT( -1.910828025477707  , WithinRel( shiftFactor( 0.50 ) ) );
    CHECK_THAT( -1.7891373801916932 , WithinRel( shiftFactor( 0.75 ) ) );
    CHECK_THAT( -1.6153846153846154 , WithinRel( shiftFactor( 1.00 ) ) );
    CHECK_THAT( -1.4066359893436668 , WithinRel( shiftFactor( 1.25 ) ) );
    CHECK_THAT( -1.1891891891891893 , WithinRel( shiftFactor( 1.50 ) ) );
    CHECK_THAT( -0.98625478248547538, WithinRel( shiftFactor( 1.75 ) ) );
    CHECK_THAT( -0.81081081081081086, WithinRel( shiftFactor( 2.00 ) ) );
    CHECK_THAT( -0.66619618913196899, WithinRel( shiftFactor( 2.25 ) ) );
    CHECK_THAT( -0.55004677268475211, WithinRel( shiftFactor( 2.50 ) ) );
    CHECK_THAT( -0.45778578648969365, WithinRel( shiftFactor( 2.75 ) ) );
    CHECK_THAT( -0.38461538461538464, WithinRel( shiftFactor( 3.00 ) ) );
    CHECK_THAT( -0.32634630679631577, WithinRel( shiftFactor( 3.25 ) ) );
    CHECK_THAT( -0.27960421321417173, WithinRel( shiftFactor( 3.50 ) ) );
    CHECK_THAT( -0.24177376076825308, WithinRel( shiftFactor( 3.75 ) ) );
    CHECK_THAT( -0.2108626198083067 , WithinRel( shiftFactor( 4.00 ) ) );
    CHECK_THAT( -0.18536164578673381, WithinRel( shiftFactor( 4.25 ) ) );
    CHECK_THAT( -0.16412661195779601, WithinRel( shiftFactor( 4.50 ) ) );
    CHECK_THAT( -0.14628583622868499, WithinRel( shiftFactor( 4.75 ) ) );
    CHECK_THAT( -0.1311706629055007 , WithinRel( shiftFactor( 5.00 ) ) );

    shiftFactor = HardSphereShiftFactor( 3 );

    CHECK_THAT( -3.0                , WithinRel( shiftFactor( 0.00 ) ) );
    CHECK_THAT( -2.9874466496002539 , WithinRel( shiftFactor( 0.25 ) ) );
    CHECK_THAT( -2.9490921096071312 , WithinRel( shiftFactor( 0.50 ) ) );
    CHECK_THAT( -2.8825490793540243 , WithinRel( shiftFactor( 0.75 ) ) );
    CHECK_THAT( -2.7833935018050542 , WithinRel( shiftFactor( 1.00 ) ) );
    CHECK_THAT( -2.6460736446925637 , WithinRel( shiftFactor( 1.25 ) ) );
    CHECK_THAT( -2.4669468857470385 , WithinRel( shiftFactor( 1.50 ) ) );
    CHECK_THAT( -2.2485005928934565 , WithinRel( shiftFactor( 1.75 ) ) );
    CHECK_THAT( -2.0017699115044247 , WithinRel( shiftFactor( 2.00 ) ) );
    CHECK_THAT( -1.7443190804295865 , WithinRel( shiftFactor( 2.25 ) ) );
    CHECK_THAT( -1.4946449821499406 , WithinRel( shiftFactor( 2.50 ) ) );
    CHECK_THAT( -1.2668234468196127 , WithinRel( shiftFactor( 2.75 ) ) );
    CHECK_THAT( -1.0682926829268293 , WithinRel( shiftFactor( 3.00 ) ) );
    CHECK_THAT( -0.90066929222502901, WithinRel( shiftFactor( 3.25 ) ) );
    CHECK_THAT( -0.76186581196961145, WithinRel( shiftFactor( 3.50 ) ) );
    CHECK_THAT( -0.64808005373345023, WithinRel( shiftFactor( 3.75 ) ) );
    CHECK_THAT( -0.55511631442907106, WithinRel( shiftFactor( 4.00 ) ) );
    CHECK_THAT( -0.47907359311045444, WithinRel( shiftFactor( 4.25 ) ) );
    CHECK_THAT( -0.4166144756277696 , WithinRel( shiftFactor( 4.50 ) ) );
    CHECK_THAT( -0.36500842852942922, WithinRel( shiftFactor( 4.75 ) ) );
    CHECK_THAT( -0.32207478890229191, WithinRel( shiftFactor( 5.00 ) ) );

    shiftFactor = HardSphereShiftFactor( 4 );

    CHECK_THAT( -4.0                , WithinRel( shiftFactor( 0.00 ) ) );
    CHECK_THAT( -3.99105538787855   , WithinRel( shiftFactor( 0.25 ) ) );
    CHECK_THAT( -3.9640240773828954 , WithinRel( shiftFactor( 0.50 ) ) );
    CHECK_THAT( -3.9182715604069123 , WithinRel( shiftFactor( 0.75 ) ) );
    CHECK_THAT( -3.8525812019457084 , WithinRel( shiftFactor( 1.00 ) ) );
    CHECK_THAT( -3.7649000125260783 , WithinRel( shiftFactor( 1.25 ) ) );
    CHECK_THAT( -3.6520948632851313 , WithinRel( shiftFactor( 1.50 ) ) );
    CHECK_THAT( -3.5100405270183899 , WithinRel( shiftFactor( 1.75 ) ) );
    CHECK_THAT( -3.3344781904715175 , WithinRel( shiftFactor( 2.00 ) ) );
    CHECK_THAT( -3.1228727369542217 , WithinRel( shiftFactor( 2.25 ) ) );
    CHECK_THAT( -2.8768199376623715 , WithinRel( shiftFactor( 2.50 ) ) );
    CHECK_THAT( -2.6037247760912927 , WithinRel( shiftFactor( 2.75 ) ) );
    CHECK_THAT( -2.3163485776017283 , WithinRel( shiftFactor( 3.00 ) ) );
    CHECK_THAT( -2.0299850616477868 , WithinRel( shiftFactor( 3.25 ) ) );
    CHECK_THAT( -1.7586712670710503 , WithinRel( shiftFactor( 3.50 ) ) );
    CHECK_THAT( -1.5123756776128434 , WithinRel( shiftFactor( 3.75 ) ) );
    CHECK_THAT( -1.2961343855235474 , WithinRel( shiftFactor( 4.00 ) ) );
    CHECK_THAT( -1.1107905446564041 , WithinRel( shiftFactor( 4.25 ) ) );
    CHECK_THAT( -0.95441527371871204, WithinRel( shiftFactor( 4.50 ) ) );
    CHECK_THAT( -0.82366800642532489, WithinRel( shiftFactor( 4.75 ) ) );
    CHECK_THAT( -0.71477297733440914, WithinRel( shiftFactor( 5.00 ) ) );
  } // GIVEN
} // SCENARIO
