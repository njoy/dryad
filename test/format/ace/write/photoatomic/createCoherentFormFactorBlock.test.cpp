// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/photoatomic/createCoherentFormFactorBlock.hpp"

// other includes
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createCoherentScatteringFunctionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createCoherentFormFactorBlock( photoatomic );

        CHECK( 1253 == block.numberValues() );
        CHECK( 1253 == block.momentum().size() );
        CHECK( 1253 == block.integratedFormFactors().size() );
        CHECK( 1253 == block.formFactors().size() );

        CHECK_THAT(  0.  , WithinRel( block.momentum().front(), 1e-12 ) );
        CHECK_THAT(  1e+9, WithinRel( block.momentum().back(), 1e-12 ) );
        CHECK_THAT(  0., WithinRel( block.integratedFormFactors().front(), 1e-12 ) );
        CHECK_THAT(  3.016705076613E-02, WithinRel( block.integratedFormFactors().back(), 1e-12 ) );
        CHECK_THAT(  1., WithinRel( block.formFactors().front(), 1e-12 ) );
        CHECK_THAT(  8.1829E-39, WithinRel( block.formFactors().back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
