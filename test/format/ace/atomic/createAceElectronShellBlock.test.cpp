// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/atomic/createAceElectronShellBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createAtomicRelaxationFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAceElectronShellBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto atomic = format::endf::createAtomicRelaxationFromFile( "atom-008_O_000.endf", true );
      atomic.calculateTransitionEnergies();

      THEN( "the ace block can be generated for relativistic shelld" ) {

        auto block = format::ace::atomic::createAceElectronShellBlock( true, atomic );

        CHECK( 4 == block.numberElectronShells() );

        CHECK_THAT( 2., WithinRel( block.numberElectrons()[0] ) );
        CHECK_THAT( 2., WithinRel( block.numberElectrons()[1] ) );
        CHECK_THAT( 1.33, WithinRel( block.numberElectrons()[2] ) );
        CHECK_THAT( 2.67, WithinRel( block.numberElectrons()[3] ) );
        CHECK_THAT( 538e-6, WithinRel( block.bindingEnergies()[0] ) );
        CHECK_THAT( 28.48e-6, WithinRel( block.bindingEnergies()[1] ) );
        CHECK_THAT( 13.62e-6, WithinRel( block.bindingEnergies()[2] ) );
        CHECK_THAT( 13.62e-6, WithinRel( block.bindingEnergies()[3] ) );
        CHECK_THAT( 0.25   , WithinRel( block.interactionProbabilities()[0] ) );
        CHECK_THAT( 0.5    , WithinRel( block.interactionProbabilities()[1] ) );
        CHECK_THAT( 0.66625, WithinRel( block.interactionProbabilities()[2] ) );
        CHECK_THAT( 1.     , WithinRel( block.interactionProbabilities()[3] ) );
      } // THEN

      THEN( "the ace block can be generated for non-relativistic shelld" ) {

        auto block = format::ace::atomic::createAceElectronShellBlock( false, atomic );

        CHECK( 3 == block.numberElectronShells() );

        CHECK_THAT( 2., WithinRel( block.numberElectrons()[0] ) );
        CHECK_THAT( 2., WithinRel( block.numberElectrons()[1] ) );
        CHECK_THAT( 4., WithinRel( block.numberElectrons()[2] ) );
        CHECK_THAT( 538e-6, WithinRel( block.bindingEnergies()[0] ) );
        CHECK_THAT( 28.48e-6, WithinRel( block.bindingEnergies()[1] ) );
        CHECK_THAT( 13.62e-6, WithinRel( block.bindingEnergies()[2] ) );
        CHECK_THAT( 0.25, WithinRel( block.interactionProbabilities()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( block.interactionProbabilities()[1] ) );
        CHECK_THAT( 1.  , WithinRel( block.interactionProbabilities()[2] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
