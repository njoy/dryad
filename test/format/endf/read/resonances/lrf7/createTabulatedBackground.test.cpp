// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createTabulatedBackground.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const TabulatedBackground& );

SCENARIO( "createTabulatedRadius" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    // tabulated backgrounds are not used in any evaluation so we use a dummy version.

    std::string component =
    " 0.000000+0 0.000000+0          1          1          0          02625 2151     \n"
    " 0.000000+0 0.000000+0          0          0          1          22625 2151     \n"
    "          2          2                                            2625 2151     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                      2625 2151     \n"
    " 0.000000+0 0.000000+0          0          0          1          22625 2151     \n"
    "          2          2                                            2625 2151     \n"
    " 1.000000-5 2.000000+0 2.000000+7 1.000000+0                      2625 2151     \n";

    auto begin = component.begin();
    auto end = component.end();
    long lineNumber = 1;

    using TabulatedBackgroundRMatrix = njoy::ENDFtk::section::Type<2, 151>::RMatrixLimited::TabulatedBackgroundRMatrix;
    TabulatedBackgroundRMatrix background( begin, end, lineNumber, 2625, 2, 151 );

    WHEN( "a single parsed scattering radius from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::resonances::lrf7::createTabulatedBackground( background );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedBackground& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 2 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 1.  , WithinRel( chunk.values()[0].real() ) );
  CHECK_THAT( 2.  , WithinRel( chunk.values()[1].real() ) );
  CHECK_THAT( 2.  , WithinRel( chunk.values()[0].imag() ) );
  CHECK_THAT( 1.  , WithinRel( chunk.values()[1].imag() ) );
}
