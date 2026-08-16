// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/createMultigroupProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createMultigroupProjectileTargetFromFile" ) {

  GIVEN( "a GROUPR formatted GENDF file" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTargetFromFile(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       "n-092_U_235.gendf" );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyGrouprU235( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an ERRORR formatted GENDF file with cross section covariances" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTargetFromFile(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       "n-092_U_235.covariances.xs.gendf" );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyErrorrU235( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
