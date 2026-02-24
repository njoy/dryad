// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfResonanceChannels.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfParticlePairs.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include <iostream>
#include "../../test.dryadcoumpound.hpp"
// convenience typedefs
using namespace njoy;
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

std::string chunk();

//! @todo test KBK and KPS

SCENARIO( "createEndfResonanceChannels" ) {

  GIVEN( "valid data for a reaction" ) {

    std::string string = chunk();

    auto compound = create_dryad_compound();

    auto spingroup1 = create_dryad_spingroup_1();

    WHEN( "the data is given explicitly" ) {       

      THEN( "it can be converted to ENDF" ) {

        auto ppairs = format::endf::resonances::lrf7::createEndfParticlePairs( compound );

        auto data = format::endf::resonances::lrf7::createEndfResonanceChannels( spingroup1, ppairs );

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
    "-1.000000+0-1.000000+0          0          0         12          22925 2151     \n"
    " 1.000000+0 1.000000+0 2.000000+0 1.100000+1 6.100000-1 6.200000-12925 2151     \n"
    " 2.000000+0 3.000000+0 4.000000+0 1.200000+1 6.300000-1 6.400000-12925 2151     \n";
}

// if boundary is 1 or 2, clqsh, spin group boundary ? 