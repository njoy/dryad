// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/CoulombPhaseShiftDifference.hpp"

// other includes
#include <iostream>
#include <iomanip>
// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "CoulombPhaseShiftDifference" ) {

  GIVEN( "valid orbital momentum values for a CoulombPhaseShiftDifference" ) {

    // reference results were generated using excel

    CoulombPhaseShiftDifference w( 0 );

    CHECK( 0 == w.orbitalAngularMomentum() );
    CHECK_THAT( 0., WithinRel( w( 0.00 ) ) );
    CHECK_THAT( 0., WithinRel( w( 0.25 ) ) );
    CHECK_THAT( 0., WithinRel( w( 0.50 ) ) );
    CHECK_THAT( 0., WithinRel( w( 0.75 ) ) );
    CHECK_THAT( 0., WithinRel( w( 1.00 ) ) );
    CHECK_THAT( 0., WithinRel( w( 1.25 ) ) );
    CHECK_THAT( 0., WithinRel( w( 1.50 ) ) );
    CHECK_THAT( 0., WithinRel( w( 1.75 ) ) );
    CHECK_THAT( 0., WithinRel( w( 2.00 ) ) );
    CHECK_THAT( 0., WithinRel( w( 2.25 ) ) );
    CHECK_THAT( 0., WithinRel( w( 2.50 ) ) );
    CHECK_THAT( 0., WithinRel( w( 2.75 ) ) );
    CHECK_THAT( 0., WithinRel( w( 3.00 ) ) );
    CHECK_THAT( 0., WithinRel( w( 3.25 ) ) );
    CHECK_THAT( 0., WithinRel( w( 3.50 ) ) );
    CHECK_THAT( 0., WithinRel( w( 3.75 ) ) );
    CHECK_THAT( 0., WithinRel( w( 4.00 ) ) );
    CHECK_THAT( 0., WithinRel( w( 4.25 ) ) );
    CHECK_THAT( 0., WithinRel( w( 4.50 ) ) );
    CHECK_THAT( 0., WithinRel( w( 4.75 ) ) );
    CHECK_THAT( 0., WithinRel( w( 5.00 ) ) );

    w = CoulombPhaseShiftDifference( 1 );

    CHECK( 1 == w.orbitalAngularMomentum() );
    CHECK_THAT( 0                , WithinRel( w( 0.00 ) ) );
    CHECK_THAT( 0.244978663126864, WithinRel( w( 0.25 ) ) );
    CHECK_THAT( 0.463647609000806, WithinRel( w( 0.50 ) ) );
    CHECK_THAT( 0.643501108793284, WithinRel( w( 0.75 ) ) );
    CHECK_THAT( 0.785398163397448, WithinRel( w( 1.00 ) ) );
    CHECK_THAT( 0.896055384571344, WithinRel( w( 1.25 ) ) );
    CHECK_THAT( 0.982793723247329, WithinRel( w( 1.50 ) ) );
    CHECK_THAT( 1.051650212548370, WithinRel( w( 1.75 ) ) );
    CHECK_THAT( 1.107148717794090, WithinRel( w( 2.00 ) ) );
    CHECK_THAT( 1.152571997215670, WithinRel( w( 2.25 ) ) );
    CHECK_THAT( 1.190289949682530, WithinRel( w( 2.50 ) ) );
    CHECK_THAT( 1.222025323210990, WithinRel( w( 2.75 ) ) );
    CHECK_THAT( 1.249045772398250, WithinRel( w( 3.00 ) ) );
    CHECK_THAT( 1.272297395208720, WithinRel( w( 3.25 ) ) );
    CHECK_THAT( 1.292496667789790, WithinRel( w( 3.50 ) ) );
    CHECK_THAT( 1.310193935047560, WithinRel( w( 3.75 ) ) );
    CHECK_THAT( 1.325817663668030, WithinRel( w( 4.00 ) ) );
    CHECK_THAT( 1.339705659599000, WithinRel( w( 4.25 ) ) );
    CHECK_THAT( 1.352127380920950, WithinRel( w( 4.50 ) ) );
    CHECK_THAT( 1.363300100359690, WithinRel( w( 4.75 ) ) );
    CHECK_THAT( 1.373400766945020, WithinRel( w( 5.00 ) ) );

    w = CoulombPhaseShiftDifference( 2 );

    CHECK( 2 == w.orbitalAngularMomentum() );
    CHECK_THAT( 0                , WithinRel( w( 0.00 ) ) );
    CHECK_THAT( 0.369333657673626, WithinRel( w( 0.25 ) ) );
    CHECK_THAT( 0.708626272127670, WithinRel( w( 0.50 ) ) );
    CHECK_THAT( 1.002271779063860, WithinRel( w( 0.75 ) ) );
    CHECK_THAT( 1.249045772398250, WithinRel( w( 1.00 ) ) );
    CHECK_THAT( 1.454654699914910, WithinRel( w( 1.25 ) ) );
    CHECK_THAT( 1.626294832040610, WithinRel( w( 1.50 ) ) );
    CHECK_THAT( 1.770480212170000, WithinRel( w( 1.75 ) ) );
    CHECK_THAT( 1.892546881191540, WithinRel( w( 2.00 ) ) );
    CHECK_THAT( 1.996725983328840, WithinRel( w( 2.25 ) ) );
    CHECK_THAT( 2.086345334253880, WithinRel( w( 2.50 ) ) );
    CHECK_THAT( 2.164025363590450, WithinRel( w( 2.75 ) ) );
    CHECK_THAT( 2.231839495645580, WithinRel( w( 3.00 ) ) );
    CHECK_THAT( 2.291438739475070, WithinRel( w( 3.25 ) ) );
    CHECK_THAT( 2.344146880338160, WithinRel( w( 3.50 ) ) );
    CHECK_THAT( 2.391032935588720, WithinRel( w( 3.75 ) ) );
    CHECK_THAT( 2.432966381462120, WithinRel( w( 4.00 ) ) );
    CHECK_THAT( 2.470659403578160, WithinRel( w( 4.25 ) ) );
    CHECK_THAT( 2.504699378136620, WithinRel( w( 4.50 ) ) );
    CHECK_THAT( 2.535573981488170, WithinRel( w( 4.75 ) ) );
    CHECK_THAT( 2.563690716627550, WithinRel( w( 5.00 ) ) );

    w = CoulombPhaseShiftDifference( 3 );

    CHECK( 3 == w.orbitalAngularMomentum() );
    CHECK_THAT( 0                , WithinRel( w( 0.00 ) ) );
    CHECK_THAT( 0.452474889562067, WithinRel( w( 0.25 ) ) );
    CHECK_THAT( 0.873774949542297, WithinRel( w( 0.50 ) ) );
    CHECK_THAT( 1.247250442190720, WithinRel( w( 0.75 ) ) );
    CHECK_THAT( 1.570796326794900, WithinRel( w( 1.00 ) ) );
    CHECK_THAT( 1.849445819614670, WithinRel( w( 1.25 ) ) );
    CHECK_THAT( 2.089942441041420, WithinRel( w( 1.50 ) ) );
    CHECK_THAT( 2.298554660596360, WithinRel( w( 1.75 ) ) );
    CHECK_THAT( 2.480549484739110, WithinRel( w( 2.00 ) ) );
    CHECK_THAT( 2.640227092122120, WithinRel( w( 2.25 ) ) );
    CHECK_THAT( 2.781083610450580, WithinRel( w( 2.50 ) ) );
    CHECK_THAT( 2.905972631596370, WithinRel( w( 2.75 ) ) );
    CHECK_THAT( 3.017237659043030, WithinRel( w( 3.00 ) ) );
    CHECK_THAT( 3.116815589995810, WithinRel( w( 3.25 ) ) );
    CHECK_THAT( 3.206316935005390, WithinRel( w( 3.50 ) ) );
    CHECK_THAT( 3.287088320160070, WithinRel( w( 3.75 ) ) );
    CHECK_THAT( 3.360261599463740, WithinRel( w( 4.00 ) ) );
    CHECK_THAT( 3.426792778450890, WithinRel( w( 4.25 ) ) );
    CHECK_THAT( 3.487493101383950, WithinRel( w( 4.50 ) ) );
    CHECK_THAT( 3.543054046791100, WithinRel( w( 4.75 ) ) );
    CHECK_THAT( 3.594067543151860, WithinRel( w( 5.00 ) ) );

    w = CoulombPhaseShiftDifference( 4 );

    CHECK( 4 == w.orbitalAngularMomentum() );
    CHECK_THAT( 0                , WithinRel( w( 0.00 ) ) );
    CHECK_THAT( 0.514893699558024, WithinRel( w( 0.25 ) ) );
    CHECK_THAT( 0.998129944089059, WithinRel( w( 0.50 ) ) );
    CHECK_THAT( 1.432598392186420, WithinRel( w( 0.75 ) ) );
    CHECK_THAT( 1.815774989921760, WithinRel( w( 1.00 ) ) );
    CHECK_THAT( 2.152330687989640, WithinRel( w( 1.25 ) ) );
    CHECK_THAT( 2.448713111311990, WithinRel( w( 1.50 ) ) );
    CHECK_THAT( 2.710965102193750, WithinRel( w( 1.75 ) ) );
    CHECK_THAT( 2.944197093739910, WithinRel( w( 2.00 ) ) );
    CHECK_THAT( 3.152616552432860, WithinRel( w( 2.25 ) ) );
    CHECK_THAT( 3.339682925794140, WithinRel( w( 2.50 ) ) );
    CHECK_THAT( 3.508259977731340, WithinRel( w( 2.75 ) ) );
    CHECK_THAT( 3.660738767836320, WithinRel( w( 3.00 ) ) );
    CHECK_THAT( 3.799132144870550, WithinRel( w( 3.25 ) ) );
    CHECK_THAT( 3.925146934627010, WithinRel( w( 3.50 ) ) );
    CHECK_THAT( 4.040239601122260, WithinRel( w( 3.75 ) ) );
    CHECK_THAT( 4.145659762861180, WithinRel( w( 4.00 ) ) );
    CHECK_THAT( 4.242484701767110, WithinRel( w( 4.25 ) ) );
    CHECK_THAT( 4.331647087497120, WithinRel( w( 4.50 ) ) );
    CHECK_THAT( 4.413957503866750, WithinRel( w( 4.75 ) ) );
    CHECK_THAT( 4.490122927723200, WithinRel( w( 5.00 ) ) );

  } // GIVEN
} // SCENARIO
