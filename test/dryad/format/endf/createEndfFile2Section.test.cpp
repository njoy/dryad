// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/createEndfFile2Section.hpp"

// other includes
#include "test.dryadcoumpound.hpp"

// convenience typedefs
using namespace njoy::dryad;

std::string chunk();

SCENARIO( "createEndfFile2Section" ) {

  GIVEN( "valid data for a reaction" ) {

    std::string string = chunk();
    auto dryad_group = create_dryad_compound();

    WHEN( "the data is given explicitly" ) {       

      THEN( "it can be converted to ENDF" ) {

        ENDFtk::section::Type< 2, 151 > data = format::endf::createEndfFile2Section( 29063, 62.389, std::vector< CompoundSystem >{dryad_group} );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        
        data.print( output, 2925, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

//! @todo Left to test: multiple NER, NIS ? LFW is for URR. 
//! @todo Special Case (no RP): CONT(ZAI=ZA,ABN=1,LFW=0,NER=1), then CONT(LRU=0,LRF=0,NRO=0,NAPS=0) then CONT(SPI, AP, 0, 0, 0, 0)
//! @todo Test for KPS != 0 not implemented


// The dryad compound object has 2 spingroups.
//  - The 1st SG has 3 channels (n,n), (n,g) and (n,a).
//  - The 2nd SG has 3 channels (n,n), (n,g) and (n,f).
// The channels will be read in ascending order of occurence; thus in the ParticlePair record they will appear in this order :
// - (n,n), (n,g) (n,a) and (n,f).
// This unit test ensures that SG1 effectively reports PPI {1, 2, 3} and SG2 reports {1, 2, 4}

std::string chunk() {
  return
      " 2.906300+4 6.238900+1          0          0          1          02925 2151     \n"
      " 2.906300+4 1.000000+0          0          1          1          02925 2151     \n"
      " 1.000000-5 1.000000+5          1          7          0          02925 2151     \n"
      " 0.000000+0 0.000000+0          1          3          2          02925 2151     \n"

      " 0.000000+0 0.000000+0          4          0         48          82925 2151     \n" // -- Particle Pairs
      " 0.000000+0 2.000000+0 0.000000+0 2.900000+1 1.000000+0 3.000000+02925 2151     \n" // (n,g)
      " 8.000000+0-1.000000+0 1.000000+0 1.020000+2 1.000000+0 1.000000+02925 2151     \n" 
      " 1.000000+0 2.000000+1 0.000000+0 2.900000+1 5.000000-1 1.500000+02925 2151     \n" // (n,n)
      " 8.000000+0 1.000000+0 1.000000+0 5.000000+1 1.000000+0 1.000000+02925 2151     \n" 
      " 7.000000+0 8.000000+0 2.000000+0 2.900000+1 9.000000+0 1.000000+12925 2151     \n" // (n,a)
      " 4.500000+1 1.000000+0 1.000000+0 6.000000+2 1.000000+0 1.000000+02925 2151     \n" 
      " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n" // (n,f)
      " 2.300000+1-1.000000+0 1.000000+0 1.800000+1 0.000000+0 0.000000+02925 2151     \n" 

      "-1.000000+0-1.000000+0          0          0         18          32925 2151     \n" // AJ, PJ, KBK=0 -- 1st SG
      " 1.000000+0 1.000000+0 2.000000+0 1.100000+1 6.100000-1 6.200000-12925 2151     \n"
      " 2.000000+0 3.000000+0 4.000000+0 1.200000+1 6.300000-1 6.400000-12925 2151     \n"
      " 3.000000+0 3.000000+0 4.000000+0 4.600000+1 6.500000-1 6.600000-12925 2151     \n"
      " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
      " 1.000000+1 2.000000+0 4.000000+0 6.000000+0 0.000000+0 0.000000+02925 2151     \n"
      " 2.000000+1 3.000000+0 5.000000+0 7.000000+0 0.000000+0 0.000000+02925 2151     \n"

      "-2.000000+0-1.000000+0          1          0         18          32925 2151     \n" // AJ, PJ, KBK=1 -- 2nd SG
      " 1.000000+0 1.000000+0 2.000000+0 1.100000+1 6.100000-1 6.200000-12925 2151     \n"
      " 2.000000+0 3.000000+0 4.000000+0 1.200000+1 6.300000-1 6.400000-12925 2151     \n"
      " 4.000000+0 3.000000+0 4.000000+0 1.200000+1 6.300000-1 6.400000-12925 2151     \n"
      " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
      " 1.000000+1 2.000000+0 4.000000+0 6.000000+0 0.000000+0 0.000000+02925 2151     \n"
      " 2.000000+1 3.000000+0 5.000000+0 7.000000+0 0.000000+0 0.000000+02925 2151     \n"

      " 0.000000+0 0.000000+0          3          2          0          02925 2151     \n" // SAMMY background (LBK=2) for third channel (LCH=3)
      " 1.000000+0 2.000000+0          0          0          5          02925 2151     \n"
      " 3.000000+0 4.000000+0 5.000000+0 6.000000+0 7.000000+0           2925 2151     \n"
      "                                                                  2925 2  0     \n";
}
