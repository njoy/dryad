// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/ndi/read/createMultigroupCrossSection.hpp"

// other includes
#include "NDItk/MultigroupLibrary.hpp"
#include "NDItk/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const MultigroupCrossSection& );
void verifySubrecordChunk( const MultigroupCrossSection& );

SCENARIO( "createMultigroupCrossSection" ) {

  GIVEN( "an NDI multigroup library file" ) {

    using Library = njoy::NDItk::MultigroupLibrary;
    auto library = njoy::NDItk::fromFile< Library >( "1001.831nm" );
    decltype(auto) record = library.tables()[0].totalCrossSection();
    decltype(auto) subrecord = library.tables()[0].reactionCrossSections().reaction( 2 );

    std::vector< double > boundaries = {

      1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0,
      8.320000e+0, 2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2,
      1.235000e+3, 3.350000e+3, 9.120000e+3, 2.480000e+4, 6.760000e+4,
      1.840000e+5, 3.030000e+5, 5.000000e+5, 8.230000e+5, 1.353000e+6,
      1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6, 6.070000e+6,
      7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
      1.700000e+7
    };

    WHEN( "a single total cross section record is given" ) {

      THEN( "it can be converted" ) {

      auto chunk = ndi::read::createMultigroupCrossSection( boundaries, record );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single cross section subrecord is given" ) {

      THEN( "it can be converted" ) {

      auto chunk = ndi::read::createMultigroupCrossSection( boundaries, subrecord );

        verifySubrecordChunk( chunk );
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

  CHECK_THAT( 29.32150766956950, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 21.61693393875450, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 20.89541207945840, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 20.62012802257230, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 20.51266149169490, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 20.46827473963340, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 20.44685141515090, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 20.42985288694520, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 20.40174151859570, WithinRel( chunk.values()[8] ) );
  CHECK_THAT( 20.33402388644090, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 20.15707750942530, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 19.69623198839820, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 18.56439230911150, WithinRel( chunk.values()[12] ) );
  CHECK_THAT( 16.15193306661810, WithinRel( chunk.values()[13] ) );
  CHECK_THAT( 12.24380954569480, WithinRel( chunk.values()[14] ) );
  CHECK_THAT(  8.94169268479905, WithinRel( chunk.values()[15] ) );
  CHECK_THAT(  6.92888165102905, WithinRel( chunk.values()[16] ) );
  CHECK_THAT(  5.36179172490167, WithinRel( chunk.values()[17] ) );
  CHECK_THAT(  4.14180627574431, WithinRel( chunk.values()[18] ) );
  CHECK_THAT(  3.38399872580098, WithinRel( chunk.values()[19] ) );
  CHECK_THAT(  2.94318929152132, WithinRel( chunk.values()[20] ) );
  CHECK_THAT(  2.55094838583866, WithinRel( chunk.values()[21] ) );
  CHECK_THAT(  2.19028335341669, WithinRel( chunk.values()[22] ) );
  CHECK_THAT(  1.75604860794844, WithinRel( chunk.values()[23] ) );
  CHECK_THAT(  1.29523919063075, WithinRel( chunk.values()[24] ) );
  CHECK_THAT(  1.05774431185885, WithinRel( chunk.values()[25] ) );
  CHECK_THAT(  0.86073908041403, WithinRel( chunk.values()[26] ) );
  CHECK_THAT(  0.74390350182312, WithinRel( chunk.values()[27] ) );
  CHECK_THAT(  0.68465344564727, WithinRel( chunk.values()[28] ) );
  CHECK_THAT(  0.61438017081722, WithinRel( chunk.values()[29] ) );
}

void verifySubrecordChunk( const MultigroupCrossSection& chunk ) {

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

  CHECK_THAT( 29.02387193247870, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 21.51024435650740, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 20.83073697603060, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 20.58091403055380, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 20.48885439312890, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 20.45383300294320, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 20.43809211539920, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 20.42454178467770, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 20.39852384311520, WithinRel( chunk.values()[8] ) );
  CHECK_THAT( 20.33208244565180, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 20.15591085157790, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 19.69553919314670, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 18.56399610527600, WithinRel( chunk.values()[12] ) );
  CHECK_THAT( 16.15172519963870, WithinRel( chunk.values()[13] ) );
  CHECK_THAT( 12.24371078269810, WithinRel( chunk.values()[14] ) );
  CHECK_THAT(  8.94163902976473, WithinRel( chunk.values()[15] ) );
  CHECK_THAT(  6.92884234312335, WithinRel( chunk.values()[16] ) );
  CHECK_THAT(  5.36175758386261, WithinRel( chunk.values()[17] ) );
  CHECK_THAT(  4.14177215022087, WithinRel( chunk.values()[18] ) );
  CHECK_THAT(  3.38396312330490, WithinRel( chunk.values()[19] ) );
  CHECK_THAT(  2.94315268770038, WithinRel( chunk.values()[20] ) );
  CHECK_THAT(  2.55091138583866, WithinRel( chunk.values()[21] ) );
  CHECK_THAT(  2.19024635341669, WithinRel( chunk.values()[22] ) );
  CHECK_THAT(  1.75601275074314, WithinRel( chunk.values()[23] ) );
  CHECK_THAT(  1.29520561542145, WithinRel( chunk.values()[24] ) );
  CHECK_THAT(  1.05771215685360, WithinRel( chunk.values()[25] ) );
  CHECK_THAT(  0.86070817430621, WithinRel( chunk.values()[26] ) );
  CHECK_THAT(  0.74387347428809, WithinRel( chunk.values()[27] ) );
  CHECK_THAT(  0.68462385383360, WithinRel( chunk.values()[28] ) );
  CHECK_THAT(  0.61435136208940, WithinRel( chunk.values()[29] ) );
}
