// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/atomic/createAceSubshellTransitionDataBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createAtomicRelaxationFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAceBremsstrahlungBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto atomic = format::endf::createAtomicRelaxationFromFile( "atom-008_O_000.endf", true );
      atomic.calculateTransitionEnergies();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::atomic::createAceSubshellTransitionDataBlock( atomic );

        CHECK( 4 == block.numberElectronSubshells() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
