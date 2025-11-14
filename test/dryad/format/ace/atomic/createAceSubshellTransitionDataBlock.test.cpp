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

        CHECK( 8 == block.transitionData( 1 ).numberTransitions() );
        CHECK( 3 == block.transitionData( 1 ).primaryDesignator( 1 ) );
        CHECK( 4 == block.transitionData( 1 ).primaryDesignator( 2 ) );
        CHECK( 2 == block.transitionData( 1 ).primaryDesignator( 3 ) );
        CHECK( 2 == block.transitionData( 1 ).primaryDesignator( 4 ) );
        CHECK( 2 == block.transitionData( 1 ).primaryDesignator( 5 ) );
        CHECK( 3 == block.transitionData( 1 ).primaryDesignator( 6 ) );
        CHECK( 3 == block.transitionData( 1 ).primaryDesignator( 7 ) );
        CHECK( 4 == block.transitionData( 1 ).primaryDesignator( 8 ) );
        CHECK( 0 == block.transitionData( 1 ).secondaryDesignator( 1 ) );
        CHECK( 0 == block.transitionData( 1 ).secondaryDesignator( 2 ) );
        CHECK( 2 == block.transitionData( 1 ).secondaryDesignator( 3 ) );
        CHECK( 3 == block.transitionData( 1 ).secondaryDesignator( 4 ) );
        CHECK( 4 == block.transitionData( 1 ).secondaryDesignator( 5 ) );
        CHECK( 3 == block.transitionData( 1 ).secondaryDesignator( 6 ) );
        CHECK( 4 == block.transitionData( 1 ).secondaryDesignator( 7 ) );
        CHECK( 4 == block.transitionData( 1 ).secondaryDesignator( 8 ) );
        CHECK_THAT( 1.90767971384804E-03, WithinRel( block.transitionData( 1 ).probability( 1 ) ) );
        CHECK_THAT( 5.70794914380763E-03, WithinRel( block.transitionData( 1 ).probability( 2 ) ) );
        CHECK_THAT( 1.84351922347212E-01, WithinRel( block.transitionData( 1 ).probability( 3 ) ) );
        CHECK_THAT( 3.00575904913614E-01, WithinRel( block.transitionData( 1 ).probability( 4 ) ) );
        CHECK_THAT( 5.30993870350919E-01, WithinRel( block.transitionData( 1 ).probability( 5 ) ) );
        CHECK_THAT( 5.42076068688590E-01, WithinRel( block.transitionData( 1 ).probability( 6 ) ) );
        CHECK_THAT( 8.33191025021346E-01, WithinRel( block.transitionData( 1 ).probability( 7 ) ) );
        CHECK_THAT( 1.00000000000000E+00, WithinRel( block.transitionData( 1 ).probability( 8 ) ) );
        CHECK_THAT( 524.38e-6, WithinRel( block.transitionData( 1 ).energy( 1 ) ) );
        CHECK_THAT( 524.38e-6, WithinRel( block.transitionData( 1 ).energy( 2 ) ) );
        CHECK_THAT( 481.04e-6, WithinRel( block.transitionData( 1 ).energy( 3 ) ) );
        CHECK_THAT( 495.9e-6 , WithinRel( block.transitionData( 1 ).energy( 4 ) ) );
        CHECK_THAT( 495.9e-6 , WithinRel( block.transitionData( 1 ).energy( 5 ) ) );
        CHECK_THAT( 510.76e-6, WithinRel( block.transitionData( 1 ).energy( 6 ) ) );
        CHECK_THAT( 510.76e-6, WithinRel( block.transitionData( 1 ).energy( 7 ) ) );
        CHECK_THAT( 510.76e-6, WithinRel( block.transitionData( 1 ).energy( 8 ) ) );

        CHECK( 0 == block.transitionData( 2 ).numberTransitions() );

        CHECK( 0 == block.transitionData( 3 ).numberTransitions() );

        CHECK( 0 == block.transitionData( 4 ).numberTransitions() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
