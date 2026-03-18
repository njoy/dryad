// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfResonanceParameters.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

std::string chunk();

SCENARIO( "createEndfResonanceParameters" ) {

  GIVEN( "valid data for resonance parameters" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      ResonanceTable table( { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                              id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                              id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ) },
                            { 3.811148e+3, 2.993903e+5 },
                            { { 1., 2. },
                              { 1.1, 2.1 },
                              { 1.2, 2.2 } } );

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::resonances::lrf7::createEndfResonanceParameters( table );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 2925, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    " 3.811148+3 1.000000+0 1.100000+0 1.200000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.993903+5 2.000000+0 2.100000+0 2.200000+0 0.000000+0 0.000000+02925 2151     \n";
}
