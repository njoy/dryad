// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/photoatomic/createAceComptonProfileBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAceComptonProfileBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();

      std::vector< TabulatedComptonProfile > profiles = {

        { id::ElectronSubshellID( "1s" ),
          {  0.00,     0.05,     0.10,     0.15,     0.20,     0.30,     0.40,
             0.50,     0.60,     0.70,     0.80,     1.00,     1.20,     1.40,
             1.60,     1.80,     2.00,     2.40,     3.00,     4.00,     5.00,
             6.00,     7.00,     8.00,    10.00,    15.00,    20.00,    30.00,
            40.00,    60.00,   100.00 },
          { 8.49E-01,  8.42E-01,  8.24E-01,  7.94E-01,  7.55E-01,  6.55E-01,  5.44E-01,
            4.35E-01,  3.37E-01,  2.57E-01,  1.92E-01,  1.06E-01,  5.84E-02,  3.27E-02,
            1.88E-02,  1.11E-02,  6.79E-03,  2.75E-03,  8.49E-04,  1.73E-04,  4.83E-05,
            1.68E-05,  6.79E-06,  3.09E-06,  8.2E-07,   7.4E-08,   1.3E-08,   1.2E-09,
            2.3E-10,   4.3E-11,   2.6E-11 },
          InterpolationType::LinearLinear,
          true }
      };

      auto incoherent_id = id::ReactionID( "g,H->scattering[incoherent]" );
      decltype(auto) photon = photoatomic.reaction( incoherent_id ).product( id::ParticleID::photon() ).distributionData().value();
      std::get< njoy::dryad::IncoherentDistributionData >( photon ).comptonProfiles( std::move( profiles ) );

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::photoatomic::createAceComptonProfileBlock( photoatomic );


      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
