// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/atomic/createElectronSubshellBlock.hpp"

// other includes
#include "njoy/format/endf/read/createAtomicRelaxationFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createElectronSubshellBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-008_O_000.endf", true );
      atomic.calculateTransitionEnergies();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::atomic::createElectronSubshellBlock( atomic );

        CHECK( 4 == block.numberElectronSubshells() );

        CHECK( 1 == block.designators()[0] );
        CHECK( 2 == block.designators()[1] );
        CHECK( 3 == block.designators()[2] );
        CHECK( 4 == block.designators()[3] );
        CHECK_THAT( 2., WithinRel( block.populations()[0] ) );
        CHECK_THAT( 2., WithinRel( block.populations()[1] ) );
        CHECK_THAT( 1.33, WithinRel( block.populations()[2] ) );
        CHECK_THAT( 2.67, WithinRel( block.populations()[3] ) );
        CHECK_THAT( 538e-6, WithinRel( block.bindingEnergies()[0] ) );
        CHECK_THAT( 28.48e-6, WithinRel( block.bindingEnergies()[1] ) );
        CHECK_THAT( 13.62e-6, WithinRel( block.bindingEnergies()[2] ) );
        CHECK_THAT( 13.62e-6, WithinRel( block.bindingEnergies()[3] ) );
        CHECK_THAT( 0.25   , WithinRel( block.vacancyProbabilities()[0] ) );
        CHECK_THAT( 0.5    , WithinRel( block.vacancyProbabilities()[1] ) );
        CHECK_THAT( 0.66625, WithinRel( block.vacancyProbabilities()[2] ) );
        CHECK_THAT( 1.     , WithinRel( block.vacancyProbabilities()[3] ) );
        CHECK( 8 == block.numberTransitions()[0] );
        CHECK( 0 == block.numberTransitions()[1] );
        CHECK( 0 == block.numberTransitions()[2] );
        CHECK( 0 == block.numberTransitions()[3] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
