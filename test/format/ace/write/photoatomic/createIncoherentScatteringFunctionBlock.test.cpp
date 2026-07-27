// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/photoatomic/createIncoherentScatteringFunctionBlock.hpp"

// other includes
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createIncoherentScatteringFunctionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createIncoherentScatteringFunctionBlock( photoatomic );

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
