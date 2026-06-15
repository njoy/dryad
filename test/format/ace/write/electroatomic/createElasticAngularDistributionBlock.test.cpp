// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/electroatomic/createElasticAngularDistributionBlock.hpp"

// other includes
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createElasticAngularDistributionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto electroatomic = endf::read::createProjectileTargetFromFile( "e-001_H_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::electroatomic::createElasticAngularDistributionBlock( electroatomic );

        CHECK( 16 == block.numberEnergyPoints() );
        CHECK( 16 == block.energies().size() );
        CHECK( 16 == block.distributions().size() );

        CHECK_THAT( 1e-5, WithinRel( block.energies().front(), 1e-12 ) );
        CHECK_THAT( 1e+5, WithinRel( block.energies().back(), 1e-12 ) );

        CHECK_THAT( 1e-5, WithinRel( block.distributions().front().energy(), 1e-12 ) );
        CHECK( 2 == block.distributions().front().numberCosines() );
        CHECK( 2 == block.distributions().front().cosines().size() );
        CHECK( 2 == block.distributions().front().cdf().size() );
        CHECK_THAT( -1., WithinRel( block.distributions().front().cosines().front(), 1e-12 ) );
        CHECK_THAT(  .999999, WithinRel( block.distributions().front().cosines().back(), 1e-12 ) );
        CHECK_THAT( 0., WithinRel( block.distributions().front().cdf().front(), 1e-12 ) );
        CHECK_THAT( 1., WithinRel( block.distributions().front().cdf().back(), 1e-12 ) );

        CHECK_THAT( 1e+5, WithinRel( block.distributions().back().energy(), 1e-12 ) );
        CHECK( 96 == block.distributions().back().numberCosines() );
        CHECK( 96 == block.distributions().back().cosines().size() );
        CHECK( 96 == block.distributions().back().cdf().size() );
        CHECK_THAT( -1., WithinRel( block.distributions().back().cosines().front(), 1e-12 ) );
        CHECK_THAT(  .999999, WithinRel( block.distributions().back().cosines().back(), 1e-12 ) );
        CHECK_THAT( 0., WithinRel( block.distributions().back().cdf().front(), 1e-12 ) );
        CHECK_THAT( 1., WithinRel( block.distributions().back().cdf().back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
