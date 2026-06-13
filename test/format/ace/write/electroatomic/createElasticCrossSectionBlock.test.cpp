// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/electroatomic/createElasticCrossSectionBlock.hpp"

// other includes
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createElasticCrossSectionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto electroatomic = endf::read::createProjectileTargetFromFile( "e-001_H_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::electroatomic::createElasticCrossSectionBlock( electroatomic );

        CHECK( 349 == block->numberEnergyPoints() );
        CHECK( 349 == block->transport().size() );
        CHECK( 349 == block->total().size() );

        CHECK_THAT( 2.748961374480E+08, WithinRel( block->transport().front(), 1e-12 ) );
        CHECK_THAT( 1.777779122262E-10, WithinRel( block->transport().back(), 1e-12 ) );
        CHECK_THAT( 274896000., WithinRel( block->total().front(), 1e-12 ) );
        CHECK_THAT( 12987.1, WithinRel( block->total().back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
