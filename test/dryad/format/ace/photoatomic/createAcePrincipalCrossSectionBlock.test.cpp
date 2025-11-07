// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/photoatomic/createAcePrincipalCrossSectionBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createProjectileTargetFromFile.hpp"
#include <iostream>
#include <iomanip>
// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAcePhotoelectricCrossSectionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf", false );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::photoatomic::createAcePrincipalCrossSectionBlock( photoatomic );

        CHECK( 2021 == block.numberEnergyPoints() );
        CHECK( 2021 == block.energies().size() );
        CHECK( 2021 == block.incoherent().size() );
        CHECK( 2021 == block.coherent().size() );
        CHECK( 2021 == block.photoelectric().size() );
        CHECK( 2021 == block.pairproduction().size() );

        CHECK_THAT( -1.381551055796E+01, WithinRel( block.energies().front(), 1e-12 ) );
        CHECK_THAT(  1.151292546497E+01, WithinRel( block.energies().back(), 1e-12 ) );
        CHECK_THAT( -1.616285246005E+01, WithinRel( block.incoherent().front(), 1e-12 ) );
        CHECK_THAT( -1.097982967256E+01, WithinRel( block.incoherent().back(), 1e-12 ) );
        CHECK_THAT( -1.230584436321E+01, WithinRel( block.coherent().front(), 1e-12 ) );
        CHECK_THAT( -3.530919346430E+01, WithinRel( block.coherent().back(), 1e-12 ) );
        CHECK_THAT(  0.                , WithinRel( block.photoelectric().front(), 1e-12 ) );
        CHECK_THAT( -3.249289163676E+01, WithinRel( block.photoelectric().back(), 1e-12 ) );
        CHECK_THAT(  0.                , WithinRel( block.pairproduction().front(), 1e-12 ) );
        CHECK_THAT( -3.877573270699E+00, WithinRel( block.pairproduction().back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
