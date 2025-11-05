// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/HardSpherePenetrability.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "HardSpherePenetrability" ) {

  GIVEN( "valid orbital momentum values for a HardSpherePenetrability" ) {

    HardSpherePenetrability penetrability( 0 );

    CHECK( 0 == penetrability.orbitalAngularMomentum() );
    CHECK_THAT( 0.00, WithinRel( penetrability( 0.00 ) ) );
    CHECK_THAT( 0.25, WithinRel( penetrability( 0.25 ) ) );
    CHECK_THAT( 0.50, WithinRel( penetrability( 0.50 ) ) );
    CHECK_THAT( 0.75, WithinRel( penetrability( 0.75 ) ) );
    CHECK_THAT( 1.00, WithinRel( penetrability( 1.00 ) ) );
    CHECK_THAT( 1.25, WithinRel( penetrability( 1.25 ) ) );
    CHECK_THAT( 1.50, WithinRel( penetrability( 1.50 ) ) );
    CHECK_THAT( 1.75, WithinRel( penetrability( 1.75 ) ) );
    CHECK_THAT( 2.00, WithinRel( penetrability( 2.00 ) ) );
    CHECK_THAT( 2.25, WithinRel( penetrability( 2.25 ) ) );
    CHECK_THAT( 2.50, WithinRel( penetrability( 2.50 ) ) );
    CHECK_THAT( 2.75, WithinRel( penetrability( 2.75 ) ) );
    CHECK_THAT( 3.00, WithinRel( penetrability( 3.00 ) ) );
    CHECK_THAT( 3.25, WithinRel( penetrability( 3.25 ) ) );
    CHECK_THAT( 3.50, WithinRel( penetrability( 3.50 ) ) );
    CHECK_THAT( 3.75, WithinRel( penetrability( 3.75 ) ) );
    CHECK_THAT( 4.00, WithinRel( penetrability( 4.00 ) ) );
    CHECK_THAT( 4.25, WithinRel( penetrability( 4.25 ) ) );
    CHECK_THAT( 4.50, WithinRel( penetrability( 4.50 ) ) );
    CHECK_THAT( 4.75, WithinRel( penetrability( 4.75 ) ) );
    CHECK_THAT( 5.00, WithinRel( penetrability( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 1 );

    CHECK( 1 == penetrability.orbitalAngularMomentum() );
    CHECK_THAT( 0.0                   , WithinRel( penetrability( 0.00 ) ) );
    CHECK_THAT( 0.014705882352941176  , WithinRel( penetrability( 0.25 ) ) );
    CHECK_THAT( 0.10000000000000001   , WithinRel( penetrability( 0.50 ) ) );
    CHECK_THAT( 0.27000000000000002   , WithinRel( penetrability( 0.75 ) ) );
    CHECK_THAT( 0.5                   , WithinRel( penetrability( 1.00 ) ) );
    CHECK_THAT( 0.76219512195121952   , WithinRel( penetrability( 1.25 ) ) );
    CHECK_THAT( 1.0384615384615385    , WithinRel( penetrability( 1.50 ) ) );
    CHECK_THAT( 1.3192307692307692    , WithinRel( penetrability( 1.75 ) ) );
    CHECK_THAT( 1.6000000000000001    , WithinRel( penetrability( 2.00 ) ) );
    CHECK_THAT( 1.8788659793814433    , WithinRel( penetrability( 2.25 ) ) );
    CHECK_THAT( 2.1551724137931036    , WithinRel( penetrability( 2.50 ) ) );
    CHECK_THAT( 2.4288321167883211    , WithinRel( penetrability( 2.75 ) ) );
    CHECK_THAT( 2.7000000000000002    , WithinRel( penetrability( 3.00 ) ) );
    CHECK_THAT( 2.9689189189189191    , WithinRel( penetrability( 3.25 ) ) );
    CHECK_THAT( 3.2358490566037736    , WithinRel( penetrability( 3.50 ) ) );
    CHECK_THAT( 3.5010373443983402    , WithinRel( penetrability( 3.75 ) ) );
    CHECK_THAT( 3.7647058823529411    , WithinRel( penetrability( 4.00 ) ) );
    CHECK_THAT( 4.027049180327869     , WithinRel( penetrability( 4.25 ) ) );
    CHECK_THAT( 4.2882352941176469    , WithinRel( penetrability( 4.50 ) ) );
    CHECK_THAT( 4.5484084880636608    , WithinRel( penetrability( 4.75 ) ) );
    CHECK_THAT( 4.8076923076923075    , WithinRel( penetrability( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 2 );

    CHECK( 2 == penetrability.orbitalAngularMomentum() );
    CHECK_THAT( 0.0                   , WithinRel( penetrability( 0.00 ) ) );
    CHECK_THAT( 0.00010624734381640459, WithinRel( penetrability( 0.25 ) ) );
    CHECK_THAT( 0.0031847133757961785 , WithinRel( penetrability( 0.50 ) ) );
    CHECK_THAT( 0.021565495207667731  , WithinRel( penetrability( 0.75 ) ) );
    CHECK_THAT( 0.076923076923076927  , WithinRel( penetrability( 1.00 ) ) );
    CHECK_THAT( 0.18921046258173893   , WithinRel( penetrability( 1.25 ) ) );
    CHECK_THAT( 0.36486486486486486   , WithinRel( penetrability( 1.50 ) ) );
    CHECK_THAT( 0.5954017287799348    , WithinRel( penetrability( 1.75 ) ) );
    CHECK_THAT( 0.86486486486486491   , WithinRel( penetrability( 2.00 ) ) );
    CHECK_THAT( 1.1575511644318983    , WithinRel( penetrability( 2.25 ) ) );
    CHECK_THAT( 1.4616463985032742    , WithinRel( penetrability( 2.50 ) ) );
    CHECK_THAT( 1.7695578605019118    , WithinRel( penetrability( 2.75 ) ) );
    CHECK_THAT( 2.0769230769230771    , WithinRel( penetrability( 3.00 ) ) );
    CHECK_THAT( 2.3814878004977293    , WithinRel( penetrability( 3.25 ) ) );
    CHECK_THAT( 2.6822534312160866    , WithinRel( penetrability( 3.50 ) ) );
    CHECK_THAT( 2.9789224685778843    , WithinRel( penetrability( 3.75 ) ) );
    CHECK_THAT( 3.2715654952076676    , WithinRel( penetrability( 4.00 ) ) );
    CHECK_THAT( 3.5604306047323391    , WithinRel( penetrability( 4.25 ) ) );
    CHECK_THAT( 3.8458382180539274    , WithinRel( penetrability( 4.50 ) ) );
    CHECK_THAT( 4.128125145879042     , WithinRel( penetrability( 4.75 ) ) );
    CHECK_THAT( 4.4076163610719323    , WithinRel( penetrability( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 3 );

    CHECK( 3 == penetrability.orbitalAngularMomentum() );
    CHECK_THAT( 0.0                   , WithinRel( penetrability( 0.00 ) ) );
    CHECK_THAT( 2.6789053349863964e-07, WithinRel( penetrability( 0.25 ) ) );
    CHECK_THAT( 3.3014196104324863e-05, WithinRel( penetrability( 0.50 ) ) );
    CHECK_THAT( 0.00052888173072737556, WithinRel( penetrability( 0.75 ) ) );
    CHECK_THAT( 0.0036101083032490976 , WithinRel( penetrability( 1.00 ) ) );
    CHECK_THAT( 0.015196755431928262  , WithinRel( penetrability( 1.25 ) ) );
    CHECK_THAT( 0.046427206725257929  , WithinRel( penetrability( 1.50 ) ) );
    CHECK_THAT( 0.11224672545625537   , WithinRel( penetrability( 1.75 ) ) );
    CHECK_THAT( 0.22654867256637168   , WithinRel( penetrability( 2.00 ) ) );
    CHECK_THAT( 0.39646402855156321   , WithinRel( penetrability( 2.25 ) ) );
    CHECK_THAT( 0.61979373264577553   , WithinRel( penetrability( 2.50 ) ) );
    CHECK_THAT( 0.8869711378018893    , WithinRel( penetrability( 2.75 ) ) );
    CHECK_THAT( 1.1853658536585365    , WithinRel( penetrability( 3.00 ) ) );
    CHECK_THAT( 1.503009611344865     , WithinRel( penetrability( 3.25 ) ) );
    CHECK_THAT( 1.8304779220548293    , WithinRel( penetrability( 3.50 ) ) );
    CHECK_THAT( 2.161220272993249     , WithinRel( penetrability( 3.75 ) ) );
    CHECK_THAT( 2.491105367188688     , WithinRel( penetrability( 4.00 ) ) );
    CHECK_THAT( 2.817759654775601     , WithinRel( penetrability( 4.25 ) ) );
    CHECK_THAT( 3.139976366322009     , WithinRel( penetrability( 4.50 ) ) );
    CHECK_THAT( 3.4572748731582088    , WithinRel( penetrability( 4.75 ) ) );
    CHECK_THAT( 3.7696019300361883    , WithinRel( penetrability( 5.00 ) ) );

    penetrability = HardSpherePenetrability( 4 );

    CHECK( 4 == penetrability.orbitalAngularMomentum() );
    CHECK_THAT( 0.0                   , WithinRel( penetrability( 0.00 ) ) );
    CHECK_THAT( 3.4292596900052667e-10, WithinRel( penetrability( 0.25 ) ) );
    CHECK_THAT( 1.7091673927779473e-07, WithinRel( penetrability( 0.50 ) ) );
    CHECK_THAT( 6.2803298724456102e-06, WithinRel( penetrability( 0.75 ) ) );
    CHECK_THAT( 7.8455986191746437e-05, WithinRel( penetrability( 1.00 ) ) );
    CHECK_THAT( 0.00053757409302012836, WithinRel( penetrability( 1.25 ) ) );
    CHECK_THAT( 0.002497664506668433  , WithinRel( penetrability( 1.50 ) ) );
    CHECK_THAT( 0.0088015269632856878 , WithinRel( penetrability( 1.75 ) ) );
    CHECK_THAT( 0.0251214366321574    , WithinRel( penetrability( 2.00 ) ) );
    CHECK_THAT( 0.060537968624390849  , WithinRel( penetrability( 2.25 ) ) );
    CHECK_THAT( 0.12669425695946757   , WithinRel( penetrability( 2.50 ) ) );
    CHECK_THAT( 0.23514284018438844   , WithinRel( penetrability( 2.75 ) ) );
    CHECK_THAT( 0.39377025567158802   , WithinRel( penetrability( 3.00 ) ) );
    CHECK_THAT( 0.60419326632260684   , WithinRel( penetrability( 3.25 ) ) );
    CHECK_THAT( 0.86157462719357891   , WithinRel( penetrability( 3.50 ) ) );
    CHECK_THAT( 1.1566720140320819    , WithinRel( penetrability( 3.75 ) ) );
    CHECK_THAT( 1.478692020013425     , WithinRel( penetrability( 4.00 ) ) );
    CHECK_THAT( 1.8175851921669044    , WithinRel( penetrability( 4.25 ) ) );
    CHECK_THAT( 2.1652476381912984    , WithinRel( penetrability( 4.50 ) ) );
    CHECK_THAT( 2.5157918867739499    , WithinRel( penetrability( 4.75 ) ) );
    CHECK_THAT( 2.8652901048925403    , WithinRel( penetrability( 5.00 ) ) );
  } // GIVEN
} // SCENARIO
