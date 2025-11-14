// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/electroatomic/createAceBremsstrahlungDistributionBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAceBremsstrahlungDistributionBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto electroatomic = format::endf::createProjectileTargetFromFile( "e-001_H_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::electroatomic::createAceBremsstrahlungDistributionBlock( electroatomic );

        CHECK( 10 == block.numberEnergyPoints() );
        CHECK( 10 == block.energies().size() );
        CHECK( 10 == block.distributions().size() );

        CHECK_THAT( 1e-5, WithinRel( block.energies().front(), 1e-12 ) );
        CHECK_THAT( 1e+5, WithinRel( block.energies().back(), 1e-12 ) );

        CHECK_THAT( 1e-5, WithinRel( block.distributions().front().energy(), 1e-12 ) );
        CHECK( 17 == block.distributions().front().numberOutgoingEnergies() );
        CHECK( 17 == block.distributions().front().outgoingEnergies().size() );
        CHECK( 17 == block.distributions().front().cdf().size() );
        CHECK_THAT( 1e-7, WithinRel( block.distributions().front().outgoingEnergies().front(), 1e-12 ) );
        CHECK_THAT( 1e-5, WithinRel( block.distributions().front().outgoingEnergies().back(), 1e-12 ) );
        CHECK_THAT( 0., WithinRel( block.distributions().front().cdf().front(), 1e-12 ) );
        CHECK_THAT( 1., WithinRel( block.distributions().front().cdf().back(), 1e-12 ) );

        CHECK_THAT( 1e+5, WithinRel( block.distributions().back().energy(), 1e-12 ) );
        CHECK( 111 == block.distributions().back().numberOutgoingEnergies() );
        CHECK( 111 == block.distributions().back().outgoingEnergies().size() );
        CHECK( 111 == block.distributions().back().cdf().size() );
        CHECK_THAT( 1e-7, WithinRel( block.distributions().back().outgoingEnergies().front(), 1e-12 ) );
        CHECK_THAT( 1e+5, WithinRel( block.distributions().back().outgoingEnergies().back(), 1e-12 ) );
        CHECK_THAT( 0., WithinRel( block.distributions().back().cdf().front(), 1e-12 ) );
        CHECK_THAT( 1., WithinRel( block.distributions().back().cdf().back(), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
