// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/thermal/createIncoherentElastic.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk();

SCENARIO( "createIncoherentElastic" ) {

  GIVEN( "valid data for incoherent elastic scattering" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      thermal::IncoherentElasticScattering
      incoherent( 6.337872,
                  { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                    { 2.013538, 2.677764, 3.323456, 3.972601,
                      4.623738, 5.276127, 6.583171, 7.891981 } } );

      THEN( "it can be converted to ENDF" ) {

        auto data = endf::write::thermal::createIncoherentElastic( incoherent );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 58, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 6.337872+0 0.000000+0          0          0          1          8  58 7  2     \n"
    "          8          2                                              58 7  2     \n"
    " 2.960000+2 2.013538+0 4.000000+2 2.677764+0 5.000000+2 3.323456+0  58 7  2     \n"
    " 6.000000+2 3.972601+0 7.000000+2 4.623738+0 8.000000+2 5.276127+0  58 7  2     \n"
    " 1.000000+3 6.583171+0 1.200000+3 7.891981+0                        58 7  2     \n";
}
