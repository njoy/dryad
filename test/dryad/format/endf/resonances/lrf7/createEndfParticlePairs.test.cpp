// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

SCENARIO( "createEndfParticlePairs" ) {

  GIVEN( "valid data for a reaction" ) {

    std::string string = chunk();
    auto dryad_group = create_dryad_compound();

    WHEN( "the data is given explicitly" ) {       

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::resonances::lrf7::createEndfParticlePairs( dryad_group );

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
      " 0.000000+0 0.000000+0          3          0         36          62925 2151     \n"
      " 0.000000+0 2.000000+0 0.000000+0 2.900000+1 1.000000+0 3.000000+02925 2151     \n"
      " 9.000000+0-1.000000+0 1.000000+0 1.020000+2 0.000000+0 9.000000+02925 2151     \n"
      " 1.000000+0 2.000000+1 0.000000+0 2.900000+1 5.000000-1 1.500000+02925 2151     \n"
      " 1.800000+1 1.000000+0 1.000000+0 5.000000+1 1.000000+0 1.000000+02925 2151     \n"
      " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
      " 2.300000+1-1.000000+0 1.000000+0 1.800000+1 0.000000+0 0.000000+02925 2151     \n";
}

// if boundary is 1 or 2, clqsh, spin group boundary ? 