// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/electroatomic/createPrincipalCrossSectionBlock.hpp"

// other includes
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createPrincipalCrossSectionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto electroatomic = endf::read::createProjectileTargetFromFile( "e-001_H_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::electroatomic::createPrincipalCrossSectionBlock( electroatomic );

        CHECK( 349 == block.numberEnergyPoints() );
        CHECK( 1 == block.numberElectronSubshells() );
        CHECK( 349 == block.energies().size() );
        CHECK( 349 == block.elastic().size() );
        CHECK( 349 == block.bremsstrahlung().size() );
        CHECK( 349 == block.excitation().size() );
        CHECK( 349 == block.totalElectroionisation().size() );
        CHECK( 349 == block.electroionisation(1).size() );

        CHECK_THAT( 1e-5, WithinRel( block.energies().front(), 1e-12 ) );
        CHECK_THAT( 1e+5, WithinRel( block.energies().back(), 1e-12 ) );
        CHECK_THAT( 274896029.7832, WithinRel( block.total().front(), 1e-12 ) );
        CHECK_THAT( 164334.9906341, WithinRel( block.total().back(), 1e-12 ) );
        CHECK_THAT( 274896000., WithinRel( block.elastic().front(), 1e-12 ) );
        CHECK_THAT( 1.311760000000E-05, WithinRel( block.elastic().back(), 1e-12 ) );
        CHECK_THAT( 29.7832, WithinRel( block.bremsstrahlung().front(), 1e-12 ) );
        CHECK_THAT( .990621, WithinRel( block.bremsstrahlung().back(), 1e-12 ) );
        CHECK_THAT( 0., WithinRel( block.excitation().front(), 1e-12 ) );
        CHECK_THAT( 81441.6, WithinRel( block.excitation().back(), 1e-12 ) );
        CHECK_THAT( 0., WithinRel( block.totalElectroionisation().front(), 1e-12 ) );
        CHECK_THAT( 82892.4, WithinRel( block.totalElectroionisation().back(), 1e-12 ) );
        CHECK_THAT( 0., WithinRel( block.electroionisation(1).front(), 1e-12 ) );
        CHECK_THAT( 82892.4, WithinRel( block.electroionisation(1).back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
