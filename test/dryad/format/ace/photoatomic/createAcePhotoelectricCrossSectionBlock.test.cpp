// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/photoatomic/createAcePhotoelectricCrossSectionBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAcePhotoelectricCrossSectionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf", false );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::photoatomic::createAcePhotoelectricCrossSectionBlock( photoatomic );

        CHECK( 2021 == block.numberEnergyPoints() );
        CHECK( 1 == block.numberElectronSubshells() );

        CHECK_THAT(  0.                , WithinRel( block.photoelectric(1).front(), 1e-12 ) );
        CHECK_THAT( -3.249289163676E+01, WithinRel( block.photoelectric(1).back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
