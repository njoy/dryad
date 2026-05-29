// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/format/endf/covariance/createAngularDistributionCovarianceData.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::ENDFtk;

// include common test verification functions
#include "../test_verification_functions.hpp"

SCENARIO( "createAngularDistributionCovarianceData" ) {

  GIVEN( "ENDF materials - incident neutrons" ) {

    WHEN( "a single ENDF material is given" ) {

      using Tape = njoy::ENDFtk::tree::Tape;
      auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-010_Ne_022.endf" );
      auto material = tape.materials().front();

      THEN( "all covariances can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Ne22" );
        std::optional< covariance::AngularDistributionCovarianceData > covariances =
        format::endf::covariance::createAngularDistributionCovarianceData( projectile, target, material );

        neutron::ne22::verifyAngularDistributionCovariances( covariances.value() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
