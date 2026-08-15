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

  GIVEN( "a GROUPR formatted GENDF material" ) {

    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.gendf" );
    auto material = tape.materials().front();

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTarget(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, ReferenceFrame::CentreOfMass, material );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyGrouprU235( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an ERRORR formatted GENDF material with cross section covariances" ) {

    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.gendf" );
    auto material = tape.materials().front();

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTarget(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, ReferenceFrame::CentreOfMass, material );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u235::verifyErrorrU235( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an ERRORR formatted GENDF material with angular distribution covariances" ) {

    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_238.angular_covariances.gendf" );
    auto material = tape.materials().front();

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = gendf::read::createMultigroupProjectileTarget(
                       id::ParticleID( "n" ), id::ParticleID( "U238" ),
                       true, ReferenceFrame::CentreOfMass, material );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        neutron::u238::verifyU238( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
