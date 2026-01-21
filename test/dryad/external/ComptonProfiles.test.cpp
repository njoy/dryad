// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/external/ComptonProfiles.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::external;

void verifyBiggsMendelsohnMann( const std::vector< TabulatedComptonProfile >&, bool );

SCENARIO( "ComptonProfiles" ) {

  GIVEN( "a z number" ) {

    THEN( "an RadiativeTransitionData can be constructed and members can be tested" ) {

      auto chunk1 = ComptonProfiles::biggsMendelsohnMannProfiles( 1, false );
      auto chunk2 = ComptonProfiles::biggsMendelsohnMannProfiles( 1, true );

      verifyBiggsMendelsohnMann( chunk1, false );
      verifyBiggsMendelsohnMann( chunk2, true );
    } // THEN
  } // GIVEN
} // SCENARIO

void verifyBiggsMendelsohnMann( const std::vector< TabulatedComptonProfile >& chunk,
                                bool normalise ) {

  double normalisation = normalise ? .50219407976 : 1.;

  CHECK( 1 == chunk.size() );

  CHECK( id::ElectronSubshellID( "1s" ) == chunk[0].subshellIdentifier() );

  CHECK( 31 == chunk[0].momentum().size() );
  CHECK( 31 == chunk[0].values().size() );
  CHECK(  1 == chunk[0].boundaries().size() );
  CHECK(  1 == chunk[0].interpolants().size() );

  CHECK_THAT(   0.00, WithinRel( chunk[0].momentum()[0] ) );
  CHECK_THAT(   0.05, WithinRel( chunk[0].momentum()[1] ) );
  CHECK_THAT(   0.10, WithinRel( chunk[0].momentum()[2] ) );
  CHECK_THAT(   0.15, WithinRel( chunk[0].momentum()[3] ) );
  CHECK_THAT(   0.20, WithinRel( chunk[0].momentum()[4] ) );
  CHECK_THAT(   0.30, WithinRel( chunk[0].momentum()[5] ) );
  CHECK_THAT(   0.40, WithinRel( chunk[0].momentum()[6] ) );
  CHECK_THAT(   0.50, WithinRel( chunk[0].momentum()[7] ) );
  CHECK_THAT(   0.60, WithinRel( chunk[0].momentum()[8] ) );
  CHECK_THAT(   0.70, WithinRel( chunk[0].momentum()[9] ) );
  CHECK_THAT(   0.80, WithinRel( chunk[0].momentum()[10] ) );
  CHECK_THAT(   1.00, WithinRel( chunk[0].momentum()[11] ) );
  CHECK_THAT(   1.20, WithinRel( chunk[0].momentum()[12] ) );
  CHECK_THAT(   1.40, WithinRel( chunk[0].momentum()[13] ) );
  CHECK_THAT(   1.60, WithinRel( chunk[0].momentum()[14] ) );
  CHECK_THAT(   1.80, WithinRel( chunk[0].momentum()[15] ) );
  CHECK_THAT(   2.00, WithinRel( chunk[0].momentum()[16] ) );
  CHECK_THAT(   2.40, WithinRel( chunk[0].momentum()[17] ) );
  CHECK_THAT(   3.00, WithinRel( chunk[0].momentum()[18] ) );
  CHECK_THAT(   4.00, WithinRel( chunk[0].momentum()[19] ) );
  CHECK_THAT(   5.00, WithinRel( chunk[0].momentum()[20] ) );
  CHECK_THAT(   6.00, WithinRel( chunk[0].momentum()[21] ) );
  CHECK_THAT(   7.00, WithinRel( chunk[0].momentum()[22] ) );
  CHECK_THAT(   8.00, WithinRel( chunk[0].momentum()[23] ) );
  CHECK_THAT(  10.00, WithinRel( chunk[0].momentum()[24] ) );
  CHECK_THAT(  15.00, WithinRel( chunk[0].momentum()[25] ) );
  CHECK_THAT(  20.00, WithinRel( chunk[0].momentum()[26] ) );
  CHECK_THAT(  30.00, WithinRel( chunk[0].momentum()[27] ) );
  CHECK_THAT(  40.00, WithinRel( chunk[0].momentum()[28] ) );
  CHECK_THAT(  60.00, WithinRel( chunk[0].momentum()[29] ) );
  CHECK_THAT( 100.00, WithinRel( chunk[0].momentum()[30] ) );

  CHECK_THAT( 8.49E-01 / normalisation, WithinRel( chunk[0].values()[0] ) );
  CHECK_THAT( 8.42E-01 / normalisation, WithinRel( chunk[0].values()[1] ) );
  CHECK_THAT( 8.24E-01 / normalisation, WithinRel( chunk[0].values()[2] ) );
  CHECK_THAT( 7.94E-01 / normalisation, WithinRel( chunk[0].values()[3] ) );
  CHECK_THAT( 7.55E-01 / normalisation, WithinRel( chunk[0].values()[4] ) );
  CHECK_THAT( 6.55E-01 / normalisation, WithinRel( chunk[0].values()[5] ) );
  CHECK_THAT( 5.44E-01 / normalisation, WithinRel( chunk[0].values()[6] ) );
  CHECK_THAT( 4.35E-01 / normalisation, WithinRel( chunk[0].values()[7] ) );
  CHECK_THAT( 3.37E-01 / normalisation, WithinRel( chunk[0].values()[8] ) );
  CHECK_THAT( 2.57E-01 / normalisation, WithinRel( chunk[0].values()[9] ) );
  CHECK_THAT( 1.92E-01 / normalisation, WithinRel( chunk[0].values()[10] ) );
  CHECK_THAT( 1.06E-01 / normalisation, WithinRel( chunk[0].values()[11] ) );
  CHECK_THAT( 5.84E-02 / normalisation, WithinRel( chunk[0].values()[12] ) );
  CHECK_THAT( 3.27E-02 / normalisation, WithinRel( chunk[0].values()[13] ) );
  CHECK_THAT( 1.88E-02 / normalisation, WithinRel( chunk[0].values()[14] ) );
  CHECK_THAT( 1.11E-02 / normalisation, WithinRel( chunk[0].values()[15] ) );
  CHECK_THAT( 6.79E-03 / normalisation, WithinRel( chunk[0].values()[16] ) );
  CHECK_THAT( 2.75E-03 / normalisation, WithinRel( chunk[0].values()[17] ) );
  CHECK_THAT( 8.49E-04 / normalisation, WithinRel( chunk[0].values()[18] ) );
  CHECK_THAT( 1.73E-04 / normalisation, WithinRel( chunk[0].values()[19] ) );
  CHECK_THAT( 4.83E-05 / normalisation, WithinRel( chunk[0].values()[20] ) );
  CHECK_THAT( 1.68E-05 / normalisation, WithinRel( chunk[0].values()[21] ) );
  CHECK_THAT( 6.79E-06 / normalisation, WithinRel( chunk[0].values()[22] ) );
  CHECK_THAT( 3.09E-06 / normalisation, WithinRel( chunk[0].values()[23] ) );
  CHECK_THAT( 8.20E-07 / normalisation, WithinRel( chunk[0].values()[24] ) );
  CHECK_THAT( 7.40E-08 / normalisation, WithinRel( chunk[0].values()[25] ) );
  CHECK_THAT( 1.30E-08 / normalisation, WithinRel( chunk[0].values()[26] ) );
  CHECK_THAT( 1.20E-09 / normalisation, WithinRel( chunk[0].values()[27] ) );
  CHECK_THAT( 2.30E-10 / normalisation, WithinRel( chunk[0].values()[28] ) );
  CHECK_THAT( 4.30E-11 / normalisation, WithinRel( chunk[0].values()[29] ) );
  CHECK_THAT( 2.60E-11 / normalisation, WithinRel( chunk[0].values()[30] ) );

  CHECK( 30 == chunk[0].boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk[0].interpolants()[0] );

}
