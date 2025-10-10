// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/HardSpherePhaseShift.hpp"

// other includes
#include <iostream>
#include <iomanip>
// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "HardSpherePhaseShift" ) {

  GIVEN( "valid orbital momentum values for a HardSpherePhaseShift" ) {

    // the resonanceReconstruction implementation was used for reference
    // results for these tests

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

    CHECK_THAT( 0.                  , WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 0.005021336873135857, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 0.03635239099919385 , WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 0.1064988912067156  , WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 0.2146018366025517  , WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 0.3539446154286561  , WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 0.5172062767526709  , WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 0.6983497874516265  , WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 0.8928512822059094  , WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 1.097428002784332   , WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 1.309710050317468   , WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 1.52797467678901    , WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 1.750954227601746   , WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 1.977702604791283   , WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 2.207503332210215   , WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 2.439806064952444   , WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 2.674182336331968   , WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 2.910294340401      , WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 3.147872619079045   , WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 3.386699899640306   , WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 3.626599233054984   , WithinRel( phaseShift( 5.00 ) ) );

    phaseShift = HardSpherePhaseShift( 2 );

    CHECK_THAT( 0.                   , WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 2.137853917755228e-05, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 0.0006532783198699432, WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 0.004580523725841723 , WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 0.01720627675267095  , WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 0.04526018905252172  , WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 0.09435235061973013  , WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 3.308892127236587    , WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 3.40564764938027     , WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 3.524250517725196    , WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 3.661888497843971    , WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 3.815629565009366    , WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 3.982793723247329    , WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 4.161085898159138    , WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 4.348604995294909    , WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 4.543801326945095    , WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 4.745419476274158    , WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 4.952442908817631    , WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 5.164046162826684    , WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 5.379555731874136    , WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 5.598418893478537    , WithinRel( phaseShift( 5.00 ) ) );

    phaseShift = HardSpherePhaseShift( 3 );

    CHECK_THAT( 0.                   , WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 3.837699555364615e-08, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 4.769980173235933e-06, WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 7.755215996840814e-05, WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 0.0005411530387301466, WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 0.002348926836898357 , WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 0.007474813726381369 , WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 3.160624544437705    , WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 3.182477608622431    , WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 3.218420012688637    , WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 3.271314587574588    , WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 3.342617955391409    , WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 3.432407775570538    , WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 3.53973720768811     , WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 3.663068957709418    , WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 3.800632363606417    , WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 3.95065736774703     , WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 4.111501502567765    , WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 4.281703910186334    , WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 4.459996675554283    , WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 4.64529434798906     , WithinRel( phaseShift( 5.00 ) ) );

    phaseShift = HardSpherePhaseShift( 4 );

    CHECK_THAT( 0.                   , WithinRel( phaseShift( 0.00 ) ) );
    CHECK_THAT( 3.816491567221192e-11, WithinRel( phaseShift( 0.25 ) ) );
    CHECK_THAT( 1.911551589239835e-08, WithinRel( phaseShift( 0.50 ) ) );
    CHECK_THAT( 7.082866317897896e-07, WithinRel( phaseShift( 0.75 ) ) );
    CHECK_THAT( 8.955111328146081e-06, WithinRel( phaseShift( 1.00 ) ) );
    CHECK_THAT( 6.235437932700094e-05, WithinRel( phaseShift( 1.25 ) ) );
    CHECK_THAT( 0.0002957831966947655, WithinRel( phaseShift( 1.50 ) ) );
    CHECK_THAT( 3.142662690676349    , WithinRel( phaseShift( 1.75 ) ) );
    CHECK_THAT( 3.144748543748008    , WithinRel( phaseShift( 2.00 ) ) );
    CHECK_THAT( 3.14951083631061     , WithinRel( phaseShift( 2.25 ) ) );
    CHECK_THAT( 3.158989783646301    , WithinRel( phaseShift( 2.50 ) ) );
    CHECK_THAT( 3.175776238185705    , WithinRel( phaseShift( 2.75 ) ) );
    CHECK_THAT( 3.202658669147476    , WithinRel( phaseShift( 3.00 ) ) );
    CHECK_THAT( 3.242149801201984    , WithinRel( phaseShift( 3.25 ) ) );
    CHECK_THAT( 3.296079710047154    , WithinRel( phaseShift( 3.50 ) ) );
    CHECK_THAT( 3.365398916971965    , WithinRel( phaseShift( 3.75 ) ) );
    CHECK_THAT( 3.450212138376298    , WithinRel( phaseShift( 4.00 ) ) );
    CHECK_THAT( 3.549963389665471    , WithinRel( phaseShift( 4.25 ) ) );
    CHECK_THAT( 3.663669055220137    , WithinRel( phaseShift( 4.50 ) ) );
    CHECK_THAT( 3.790126358933249    , WithinRel( phaseShift( 4.75 ) ) );
    CHECK_THAT( 3.928067069644957    , WithinRel( phaseShift( 5.00 ) ) );
  } // GIVEN
} // SCENARIO
