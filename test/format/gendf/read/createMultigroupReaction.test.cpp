// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/createMultigroupReaction.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createMultigroupReaction" ) {

  GIVEN( "a GROUPR formatted GENDF material" ) {

    using GTape = njoy::ENDFtk::tree::GTape;
    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.gendf" );
    auto material = tape.materials().front();

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

    id::ParticleID projectile( "n" );
    id::ParticleID target( "U235" );

    WHEN( "a summation MT number is given" ) {

      auto total = gendf::read::createMultigroupReaction( projectile, target, material, 1, boundaries, dilution );

      THEN( "a summation MultigroupReaction with partials is created" ) {

        neutron::u235::verifyTotalReaction( total );
      } // THEN
    } // WHEN

    WHEN( "a primary MT number is given" ) {

      auto elastic = gendf::read::createMultigroupReaction( projectile, target, material, 2, boundaries, dilution );
      auto n2n = gendf::read::createMultigroupReaction( projectile, target, material, 16, boundaries, dilution );
      auto capture = gendf::read::createMultigroupReaction( projectile, target, material, 102, boundaries, dilution );

      THEN( "a primary MultigroupReaction with products is created" ) {

        neutron::u235::verifyElasticReaction( elastic, false );
        neutron::u235::verifyN2NReaction( n2n );
        neutron::u235::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
