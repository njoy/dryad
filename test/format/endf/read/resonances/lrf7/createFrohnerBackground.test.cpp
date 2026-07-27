// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/resonances/lrf7/createFrohnerBackground.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const resonances::FrohnerBackground& );

SCENARIO( "createParticlePairs" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    // tabulated backgrounds are not used in any evaluation so we use a dummy version.

    std::string component =
    " 0.000000+0 0.000000+0          1          3          0          02625 2151     \n"
    " 0.000000+0 9.550000+5          0          0          3          02625 2151     \n"
    " 1.000000+0 2.000000+0 3.000000+0                                 2625 2151     \n";

    auto begin = component.begin();
    auto end = component.end();
    long lineNumber = 1;

    using TabulatedBackgroundRMatrix = njoy::ENDFtk::section::Type<2, 151>::RMatrixLimited::FrohnerBackgroundRMatrix;
    TabulatedBackgroundRMatrix background( begin, end, lineNumber, 2625, 2, 151 );

    WHEN( "a single parsed scattering radius from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::resonances::lrf7::createFrohnerBackground( background );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const resonances::FrohnerBackground& chunk ) {

  CHECK_THAT( 1.    , WithinRel( chunk.distantLevelParameter() ) );
  CHECK_THAT( 2.    , WithinRel( chunk.poleStrength() ) );
  CHECK_THAT( 3.    , WithinRel( chunk.averageRadiationWidth() ) );
  CHECK_THAT( 0.    , WithinRel( chunk.lowerSingularity() ) );
  CHECK_THAT( 9.55e5, WithinRel( chunk.upperSingularity() ) );

  CHECK_THAT( -3.291862565897340E+00, WithinRel( chunk( 1e+5 ).real() ) );
  CHECK_THAT(  3.350877192982460E-05, WithinRel( chunk( 1e+5 ).imag() ) );
}
