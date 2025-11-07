// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/photoatomic/createAceIncoherentScatteringFunctionBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAceIncoherentScatteringFunctionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf", false );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::photoatomic::createAceIncoherentScatteringFunctionBlock( photoatomic );

        CHECK( 398 == block.numberValues() );
        CHECK( 398 == block.momentum().size() );
        CHECK( 398 == block.values().size() );

        CHECK_THAT(  0.  , WithinRel( block.momentum().front(), 1e-12 ) );
        CHECK_THAT(  1e+9, WithinRel( block.momentum().back(), 1e-12 ) );
        CHECK_THAT(  0., WithinRel( block.values().front(), 1e-12 ) );
        CHECK_THAT(  1., WithinRel( block.values().back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
