// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/createMultigroupCrossSection.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const MultigroupCrossSection& );

SCENARIO( "createMultigroupCrossSection" ) {

  GIVEN( "a GROUPR formatted GENDF material" ) {

    using GTape = njoy::ENDFtk::tree::GTape;
    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.gendf" );
    auto section = tape.materials().front().section( 3, 1 ).parse< 3 >();

    std::vector< double > boundaries = {

      1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0,
      8.320000e+0, 2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2,
      1.235000e+3, 3.350000e+3, 9.120000e+3, 2.480000e+4, 6.760000e+4,
      1.840000e+5, 3.030000e+5, 5.000000e+5, 8.230000e+5, 1.353000e+6,
      1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6, 6.070000e+6,
      7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
      1.700000e+7
    };
    std::size_t dilution = 0;

    WHEN( "a single parsed MF3 section is given" ) {

      THEN( "it can be converted" ) {

      auto chunk = gendf::read::createMultigroupCrossSection( boundaries, section, 0 );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an ERRORR formatted GENDF material" ) {

    using GTape = njoy::ENDFtk::tree::GTape;
    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.gendf" );
    auto section = tape.materials().front().section( 3, 1 ).parse< 3 >();

    std::vector< double > boundaries = {

      1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0,
      8.320000e+0, 2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2,
      1.235000e+3, 3.350000e+3, 9.120000e+3, 2.480000e+4, 6.760000e+4,
      1.840000e+5, 3.030000e+5, 5.000000e+5, 8.230000e+5, 1.353000e+6,
      1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6, 6.070000e+6,
      7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
      1.700000e+7
    };
    std::size_t dilution = 0;

    WHEN( "a single parsed MF3 section is given" ) {

      THEN( "it can be converted" ) {

      auto chunk = gendf::read::createMultigroupCrossSection( boundaries, section, 0 );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const MultigroupCrossSection& chunk ) {

  CHECK( 31 == chunk.boundaries().size() );
  CHECK( 30 == chunk.values().size() );
  CHECK( 30 == chunk.numberGroups() );

  CHECK_THAT( 1.390e-4, WithinRel( chunk.boundaries()[0] ) );
  CHECK_THAT( 1.520e-1, WithinRel( chunk.boundaries()[1] ) );
  CHECK_THAT( 4.140e-1, WithinRel( chunk.boundaries()[2] ) );
  CHECK_THAT( 1.130e+0, WithinRel( chunk.boundaries()[3] ) );
  CHECK_THAT( 3.060e+0, WithinRel( chunk.boundaries()[4] ) );
  CHECK_THAT( 8.320e+0, WithinRel( chunk.boundaries()[5] ) );
  CHECK_THAT( 2.260e+1, WithinRel( chunk.boundaries()[6] ) );
  CHECK_THAT( 6.140e+1, WithinRel( chunk.boundaries()[7] ) );
  CHECK_THAT( 1.670e+2, WithinRel( chunk.boundaries()[8] ) );
  CHECK_THAT( 4.540e+2, WithinRel( chunk.boundaries()[9] ) );
  CHECK_THAT( 1.235e+3, WithinRel( chunk.boundaries()[10] ) );
  CHECK_THAT( 3.350e+3, WithinRel( chunk.boundaries()[11] ) );
  CHECK_THAT( 9.120e+3, WithinRel( chunk.boundaries()[12] ) );
  CHECK_THAT( 2.480e+4, WithinRel( chunk.boundaries()[13] ) );
  CHECK_THAT( 6.760e+4, WithinRel( chunk.boundaries()[14] ) );
  CHECK_THAT( 1.840e+5, WithinRel( chunk.boundaries()[15] ) );
  CHECK_THAT( 3.030e+5, WithinRel( chunk.boundaries()[16] ) );
  CHECK_THAT( 5.000e+5, WithinRel( chunk.boundaries()[17] ) );
  CHECK_THAT( 8.230e+5, WithinRel( chunk.boundaries()[18] ) );
  CHECK_THAT( 1.353e+6, WithinRel( chunk.boundaries()[19] ) );
  CHECK_THAT( 1.738e+6, WithinRel( chunk.boundaries()[20] ) );
  CHECK_THAT( 2.232e+6, WithinRel( chunk.boundaries()[21] ) );
  CHECK_THAT( 2.865e+6, WithinRel( chunk.boundaries()[22] ) );
  CHECK_THAT( 3.680e+6, WithinRel( chunk.boundaries()[23] ) );
  CHECK_THAT( 6.070e+6, WithinRel( chunk.boundaries()[24] ) );
  CHECK_THAT( 7.790e+6, WithinRel( chunk.boundaries()[25] ) );
  CHECK_THAT( 1.000e+7, WithinRel( chunk.boundaries()[26] ) );
  CHECK_THAT( 1.200e+7, WithinRel( chunk.boundaries()[27] ) );
  CHECK_THAT( 1.350e+7, WithinRel( chunk.boundaries()[28] ) );
  CHECK_THAT( 1.500e+7, WithinRel( chunk.boundaries()[29] ) );
  CHECK_THAT( 1.700e+7, WithinRel( chunk.boundaries()[30] ) );

  CHECK_THAT( 536.7046, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 220.2761, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 95.71743, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 38.79649, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 55.25322, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 112.356 , WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 84.29812, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 47.16981, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 35.49166, WithinRel( chunk.values()[8] ) );
  CHECK_THAT( 26.59377, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 20.29375, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 17.12288, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 14.96041, WithinRel( chunk.values()[12] ) );
  CHECK_THAT( 13.39889, WithinRel( chunk.values()[13] ) );
  CHECK_THAT( 11.76493, WithinRel( chunk.values()[14] ) );
  CHECK_THAT( 10.30321, WithinRel( chunk.values()[15] ) );
  CHECK_THAT( 8.994543, WithinRel( chunk.values()[16] ) );
  CHECK_THAT( 7.724532, WithinRel( chunk.values()[17] ) );
  CHECK_THAT( 6.866099, WithinRel( chunk.values()[18] ) );
  CHECK_THAT( 6.841653, WithinRel( chunk.values()[19] ) );
  CHECK_THAT( 7.226625, WithinRel( chunk.values()[20] ) );
  CHECK_THAT( 7.693402, WithinRel( chunk.values()[21] ) );
  CHECK_THAT( 7.979821, WithinRel( chunk.values()[22] ) );
  CHECK_THAT( 7.647424, WithinRel( chunk.values()[23] ) );
  CHECK_THAT( 6.661945, WithinRel( chunk.values()[24] ) );
  CHECK_THAT( 6.031144, WithinRel( chunk.values()[25] ) );
  CHECK_THAT( 5.747069, WithinRel( chunk.values()[26] ) );
  CHECK_THAT( 5.746542, WithinRel( chunk.values()[27] ) );
  CHECK_THAT( 5.827871, WithinRel( chunk.values()[28] ) );
  CHECK_THAT( 6.020082, WithinRel( chunk.values()[29] ) );
}
