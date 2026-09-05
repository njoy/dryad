// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/ndi/read/createMultigroupReaction.hpp"

// other includes
#include "NDItk/MultigroupLibrary.hpp"
#include "NDItk/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

void verifyChunk( const MultigroupReaction& );

SCENARIO( "createMultigroupReaction" ) {

  GIVEN( "an NDI multigroup library file" ) {

    using Library = njoy::NDItk::MultigroupLibrary;
    auto library = njoy::NDItk::fromFile< Library >( "1001.831nm" );
    decltype(auto) table = library.tables()[0];

    std::vector< double > boundaries = {

      1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0,
      8.320000e+0, 2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2,
      1.235000e+3, 3.350000e+3, 9.120000e+3, 2.480000e+4, 6.760000e+4,
      1.840000e+5, 3.030000e+5, 5.000000e+5, 8.230000e+5, 1.353000e+6,
      1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6, 6.070000e+6,
      7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
      1.700000e+7
    };

    id::ParticleID projectile( "n" );
    id::ParticleID target( "H1" );

    WHEN( "an MT number is given" ) {

      auto elastic = ndi::read::createMultigroupReaction( projectile, target, table, 2, boundaries );

      THEN( "a MultigroupReaction is created" ) {

        neutron::h1::verifyElasticReaction( elastic );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
