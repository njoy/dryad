// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/thermal/createCoherentElastic.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk();

SCENARIO( "createCoherentElastic" ) {

  GIVEN( "valid data for coherent elastic scattering" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      thermal::CoherentElasticScattering
      coherent( { { 293.6, { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                           { 3.757353e-3, 1.386287e-2, 8.406348e-2, 8.406348e-2 } },
                  {  400., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                           { 3.686081e-3, 1.346478e-2, 6.996602e-2, 6.996602e-2 } },
                  {  500., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                           { 3.605680e-3, 1.305428e-2, 5.924634e-2, 5.924634e-2 } },
                  {  600., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                           { 3.518734e-3, 1.263070e-2, 5.075797e-2, 5.075797e-2 } },
                  {  700., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                           { 3.428755e-3, 1.220544e-2, 4.402291e-2, 4.402291e-2 } },
                  {  800., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                           { 3.337757e-3, 1.178474e-2, 3.861519e-2, 3.861519e-2 } } } );

      THEN( "it can be converted to ENDF" ) {

        auto data = endf::write::thermal::createCoherentElastic( coherent );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 26, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 2.936000+2 0.000000+0          5          0          1          4  26 7  2     \n"
    "          4          1                                              26 7  2     \n"
    " 3.706719-3 3.757353-3 4.942291-3 1.386287-2 5.572434-1 8.406348-2  26 7  2     \n"
    " 5.000000+0 8.406348-2                                              26 7  2     \n"
    " 4.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.686081-3 1.346478-2 6.996602-2 6.996602-2                        26 7  2     \n"
    " 5.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.605680-3 1.305428-2 5.924634-2 5.924634-2                        26 7  2     \n"
    " 6.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.518734-3 1.263070-2 5.075797-2 5.075797-2                        26 7  2     \n"
    " 7.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.428755-3 1.220544-2 4.402291-2 4.402291-2                        26 7  2     \n"
    " 8.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.337757-3 1.178474-2 3.861519-2 3.861519-2                        26 7  2     \n";
}
