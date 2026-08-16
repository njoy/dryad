// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/createMultigroupProjectileTarget.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createMultigroupProjectileTarget" ) {

  using GTape = njoy::ENDFtk::tree::GTape;
  auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.gendf" );
  auto material = tape.materials().front();

  auto xs_tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.xs.gendf" );
  auto covariances_xs = xs_tape.materials().front();

  auto angular_tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.angular.gendf" );
  auto covariances_angular = angular_tape.materials().front();

  GIVEN( "a GENDF material and no covariances" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTarget(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, ReferenceFrame::CentreOfMass, material,
                       std::nullopt, std::nullopt );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyU235( chunk, false, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GENDF material and xs covariances" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTarget(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, ReferenceFrame::CentreOfMass, material,
                       covariances_xs, std::nullopt );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyU235( chunk, true, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GENDF material and angular covariances" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTarget(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, ReferenceFrame::CentreOfMass, material,
                       std::nullopt, covariances_angular );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyU235( chunk, false, true );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GENDF material, xs and angular covariances" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTarget(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, ReferenceFrame::CentreOfMass, material,
                       covariances_xs, covariances_angular );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyU235( chunk, true, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
