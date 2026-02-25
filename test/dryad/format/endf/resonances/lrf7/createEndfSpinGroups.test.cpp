// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfSpinGroups.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfParticlePairs.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include <iostream>
#include "../../test.dryadcoumpound.hpp"

// convenience typedefs
using namespace njoy;
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

using ENDFtkSpinGroup = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SpinGroup;

std::string chunk();

//! @todo add a fourth PP to check PPI numbering (right now always CAPT + ELAST + FISSION)

SCENARIO( "createEndfParticlePairs" ) {

  GIVEN( "valid data for a reaction" ) {

    std::string string = chunk();
    auto compound = create_dryad_compound();

    WHEN( "the data is given explicitly" ) {       

      THEN( "it can be converted to ENDF" ) {

        auto ppairs = format::endf::resonances::lrf7::createEndfParticlePairs( compound );

        std::vector< ENDFtkSpinGroup > data = format::endf::resonances::lrf7::createEndfSpinGroups( compound.spinGroups(), ppairs );

        std::string buffer;
        auto output = std::back_inserter( buffer );

        for ( const auto& it : data ) {
          
          it.print( output, 2925, 2, 151 );
        }

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
      "-1.000000+0-1.000000+0          0          0         12          22925 2151     \n"
      " 1.000000+0 1.000000+0 2.000000+0 1.100000+1 6.100000-1 6.200000-12925 2151     \n"
      " 2.000000+0 3.000000+0 4.000000+0 1.200000+1 6.300000-1 6.400000-12925 2151     \n"
      " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
      " 1.000000+1 2.000000+0 4.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
      " 2.000000+1 3.000000+0 5.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
      "-2.000000+0-1.000000+0          0          0         18          32925 2151     \n"
      " 1.000000+0 1.000000+0 2.000000+0 1.100000+1 6.100000-1 6.200000-12925 2151     \n"
      " 2.000000+0 3.000000+0 4.000000+0 1.200000+1 6.300000-1 6.400000-12925 2151     \n"
      " 3.000000+0 3.000000+0 4.000000+0 1.200000+1 6.300000-1 6.400000-12925 2151     \n"
      " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
      " 1.000000+1 2.000000+0 4.000000+0 6.000000+0 0.000000+0 0.000000+02925 2151     \n"
      " 2.000000+1 3.000000+0 5.000000+0 7.000000+0 0.000000+0 0.000000+02925 2151     \n";
}

