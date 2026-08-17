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

  GIVEN( "a GENDF file and no covariance files" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTargetFromFile(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       "n-092_U_235.gendf", std::nullopt, std::nullopt );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyU235( chunk, false, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GENDF file and xs covariance file" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTargetFromFile(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       "n-092_U_235.gendf", "n-092_U_235.covariances.xs.gendf",
                       std::nullopt );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyU235( chunk, true, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GENDF file and angular covariance file" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTargetFromFile(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       "n-092_U_235.gendf", std::nullopt,
                       "n-092_U_235.covariances.angular.gendf" );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyU235( chunk, false, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GENDF file, xs and angular covariance file" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTargetFromFile(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       "n-092_U_235.gendf",
                       "n-092_U_235.covariances.xs.gendf",
                       "n-092_U_235.covariances.angular.gendf" );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyU235( chunk, true, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
