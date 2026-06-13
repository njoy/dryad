// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/electroatomic/createAceBremsstrahlungBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAceBremsstrahlungBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto electroatomic = format::endf::createProjectileTargetFromFile( "e-001_H_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::electroatomic::createAceBremsstrahlungBlock( electroatomic );

        CHECK( 82 == block.numberEnergyPoints() );
        CHECK( 82 == block.energies().size() );
        CHECK( 82 == block.energyAfterBremsstrahlung().size() );

        CHECK_THAT( 1e-5, WithinRel( block.energies().front(), 1e-12 ) );
        CHECK_THAT( 1e+5, WithinRel( block.energies().back(), 1e-12 ) );
        CHECK_THAT( 2.14426e-6, WithinRel( block.energyAfterBremsstrahlung().front(), 1e-12 ) );
        CHECK_THAT( 2.66810e+3, WithinRel( block.energyAfterBremsstrahlung().back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
