// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/HardSpherePhaseShift.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "HardSpherePhaseShift" ) {

  GIVEN( "valid orbital momentum values for a HardSpherePhaseShift" ) {

    HardSpherePhaseShift phaseShift( 0 );

    CHECK_THAT( 0.00, WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 0.25, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 0.50, WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 0.75, WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 1.00, WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 1.25, WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 1.50, WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 1.75, WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 2.00, WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 2.25, WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 2.50, WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 2.75, WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 3.00, WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 3.25, WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 3.50, WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 3.75, WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 4.00, WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 4.25, WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 4.50, WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 4.75, WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 5.00, WithinRel( phaseShift( 5.00 ) ) );

    phaseShift = HardSpherePhaseShift( 1 );

    CHECK_THAT( 0.00000000e+00, WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 5.02133687e-03, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 3.63523910e-02, WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 1.06498891e-01, WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 2.14601837e-01, WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 3.53944615e-01, WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 5.17206277e-01, WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 6.98349787e-01, WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 8.92851282e-01, WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 1.09742800e+00, WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 1.30971005e+00, WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 1.52797468e+00, WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 1.75095423e+00, WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 1.97770260e+00, WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 2.20750333e+00, WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 2.43980606e+00, WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 2.67418234e+00, WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 2.91029434e+00, WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 3.14787262e+00, WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 3.38669990e+00, WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 3.62659923e+00, WithinRel( phaseShift( 5.00 ) ) );

    phaseShift = HardSpherePhaseShift( 2 );

    CHECK_THAT( 0.00000000e+00, WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 2.13785392e-05, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 6.53278320e-04, WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 4.58052373e-03, WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 1.72062768e-02, WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 4.52601891e-02, WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 9.43523506e-02, WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 3.30889213e+00, WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 3.40564765e+00, WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 3.52425052e+00, WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 3.66188850e+00, WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 3.81562957e+00, WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 3.98279372e+00, WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 4.16108590e+00, WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 4.34860500e+00, WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 4.54380133e+00, WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 4.74541948e+00, WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 4.95244291e+00, WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 5.16404616e+00, WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 5.37955573e+00, WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 5.59841889e+00, WithinRel( phaseShift( 5.00 ) ) );

    phaseShift = HardSpherePhaseShift( 3 );

    CHECK_THAT( 0.00000000e+00, WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 3.83769956e-08, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 4.76998017e-06, WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 7.75521600e-05, WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 5.41153039e-04, WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 2.34892684e-03, WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 7.47481373e-03, WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 3.16062454e+00, WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 3.18247761e+00, WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 3.21842001e+00, WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 3.27131459e+00, WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 3.34261796e+00, WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 3.43240778e+00, WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 3.53973721e+00, WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 3.66306896e+00, WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 3.80063236e+00, WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 3.95065737e+00, WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 4.11150150e+00, WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 4.28170391e+00, WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 4.45999668e+00, WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 4.64529435e+00, WithinRel( phaseShift( 5.00 ) ) );

    phaseShift = HardSpherePhaseShift( 4 );

    CHECK_THAT( 0.00000000e+00, WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 3.81649157e-11, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 1.91155158e-08, WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 7.08286632e-07, WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 8.95511133e-06, WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 6.23543793e-05, WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 2.95783197e-04, WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 3.14266269e+00, WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 3.14474854e+00, WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 3.14951084e+00, WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 3.15898978e+00, WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 3.17577624e+00, WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 3.20265867e+00, WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 3.24214980e+00, WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 3.29607971e+00, WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 3.36539892e+00, WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 3.45021214e+00, WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 3.54996339e+00, WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 3.66366906e+00, WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 3.79012636e+00, WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 3.92806707e+00, WithinRel( phaseShift( 5.00 ) ) );
  } // GIVEN
} // SCENARIO
