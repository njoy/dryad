// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createEndfFile3Section.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

std::string chunk();

SCENARIO( "createEndfFile3Section" ) {

  GIVEN( "valid data for a reaction" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awr = 6.955732;

      Reaction reaction( id::ReactionID( "n,Li7->3n,a,H1[all]" ),
                         TabulatedCrossSection(
                           { 12522600.0, 13000000.0, 13500000.0, 14000000.0, 14500000.0,
                             15000000.0, 15500000.0, 16000000.0, 16500000.0, 17000000.0,
                             17500000.0, 18000000.0, 18500000.0, 19000000.0, 19500000.0,
                             20000000.0 },
                           {  0.0, 1.30000E-8, 1.17531E-5, 3.90000E-5, 1.718165E-4,
                              4.38000E-4, 8.089314E-4, .001320000, .001961284, .002710000,
                              .003546398, .004500000, .005593423, .006800000, .008088879,
                              .009460000 } ),
                         {},
                         -10948600, -10948600 );

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::createEndfFile3Section( awr, reaction );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 328, 3 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 3.007000+3 6.955732+0          0          0          0          0 328 3 25     \n"
    "-1.094860+7-1.094860+7          0          0          1         16 328 3 25     \n"
    "         16          2                                             328 3 25     \n"
    " 1.252260+7 0.000000+0 1.300000+7 1.300000-8 1.350000+7 1.175310-5 328 3 25     \n"
    " 1.400000+7 3.900000-5 1.450000+7 1.718165-4 1.500000+7 4.380000-4 328 3 25     \n"
    " 1.550000+7 8.089314-4 1.600000+7 1.320000-3 1.650000+7 1.961284-3 328 3 25     \n"
    " 1.700000+7 2.710000-3 1.750000+7 3.546398-3 1.800000+7 4.500000-3 328 3 25     \n"
    " 1.850000+7 5.593423-3 1.900000+7 6.800000-3 1.950000+7 8.088879-3 328 3 25     \n"
    " 2.000000+7 9.460000-3                                             328 3 25     \n"
    "                                                                   328 3  0     \n";
}
