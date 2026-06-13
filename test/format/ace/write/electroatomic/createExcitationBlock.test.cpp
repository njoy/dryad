// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/electroatomic/createExcitationBlock.hpp"

// other includes
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createExcitationBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto electroatomic = endf::read::createProjectileTargetFromFile( "e-001_H_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::electroatomic::createExcitationBlock( electroatomic );

        CHECK( 170 == block.numberEnergyPoints() );
        CHECK( 170 == block.energies().size() );
        CHECK( 170 == block.excitationEnergyLoss().size() );

        CHECK_THAT( 13.6e-6, WithinRel( block.energies().front(), 1e-12 ) );
        CHECK_THAT( 1.0000E+5, WithinRel( block.energies().back(), 1e-12 ) );
        CHECK_THAT( 13.6e-6, WithinRel( block.excitationEnergyLoss().front(), 1e-12 ) );
        CHECK_THAT( 2.107769775391e-5, WithinRel( block.excitationEnergyLoss().back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
