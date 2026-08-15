// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/createMultigroupReactions.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createMultigroupReactions" ) {

  GIVEN( "a GROUPR formatted GENDF material" ) {

    WHEN( "a single ENDF material is given" ) {

      using GTape = njoy::ENDFtk::tree::GTape;
      auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.gendf" );
      auto material = tape.materials().front();

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "U235" );

        std::vector< double > boundaries = {

          1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0,
          8.320000e+0, 2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2,
          1.235000e+3, 3.350000e+3, 9.120000e+3, 2.480000e+4, 6.760000e+4,
          1.840000e+5, 3.030000e+5, 5.000000e+5, 8.230000e+5, 1.353000e+6,
          1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6, 6.070000e+6,
          7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
          1.700000e+7
        };
        std::size_t dilution = 0;

        auto reactions = gendf::read::createMultigroupReactions( projectile, target, material, boundaries, dilution );

        CHECK( 97 == reactions.size() );

        auto reaction = reactions[0];
        neutron::u235::verifyTotalReaction( reaction, true );

        reaction = reactions[1];
        neutron::u235::verifyInelasticReaction( reaction, true );

        reaction = reactions[2];
        neutron::u235::verifyAnythingReaction( reaction );

        reaction = reactions[3];
        neutron::u235::verifyN2NReaction( reaction );

        reaction = reactions[4];
        neutron::u235::verifyN3NReaction( reaction );

        reaction = reactions[5];
        neutron::u235::verifyFissionReaction( reaction );

        reaction = reactions[6];
        neutron::u235::verifyElasticReaction( reaction, true );

        reaction = reactions[7];
        neutron::u235::verifyFirstInelasticReaction( reaction );

        reaction = reactions[47];
        neutron::u235::verifyCaptureReaction( reaction );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an ERRORR formatted GENDF material" ) {

    WHEN( "a single ENDF material is given" ) {

      using GTape = njoy::ENDFtk::tree::GTape;
      auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.gendf" );
      auto material = tape.materials().front();

      THEN( "all reactions can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "U235" );

        std::vector< double > boundaries = {

          1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0,
          8.320000e+0, 2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2,
          1.235000e+3, 3.350000e+3, 9.120000e+3, 2.480000e+4, 6.760000e+4,
          1.840000e+5, 3.030000e+5, 5.000000e+5, 8.230000e+5, 1.353000e+6,
          1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6, 6.070000e+6,
          7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
          1.700000e+7
        };
        std::size_t dilution = 0;

        auto reactions = gendf::read::createMultigroupReactions( projectile, target, material, boundaries, dilution );

        CHECK( 11 == reactions.size() );

        auto reaction = reactions[0];
        neutron::u235::verifyTotalReaction( reaction, false );

        reaction = reactions[1];
        neutron::u235::verifyInelasticReaction( reaction, false );

        reaction = reactions[2];
        neutron::u235::verifyAnythingReaction( reaction );

        reaction = reactions[3];
        neutron::u235::verifyN2NReaction( reaction );

        reaction = reactions[4];
        neutron::u235::verifyN3NReaction( reaction );

        reaction = reactions[5];
        neutron::u235::verifyFissionReaction( reaction );

        reaction = reactions[6];
        neutron::u235::verifyElasticReaction( reaction, false );

        reaction = reactions[7];
        neutron::u235::verifyFirstInelasticReaction( reaction );

        reaction = reactions[8];
        neutron::u235::verifyCaptureReaction( reaction );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
