// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/endf/read/covariance/createCrossSectionCovarianceData.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;
using namespace njoy::ENDFtk;

// include common test verification functions
#include "../test_verification_functions.hpp"

SCENARIO( "createCrossSectionCovarianceData" ) {

  GIVEN( "ENDF materials - incident neutrons - single submatrices and "
         "linear combinations" ) {

    WHEN( "a single ENDF material is given" ) {

      using Tape = njoy::ENDFtk::tree::Tape;
      auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-001_H_001.endf" );
      auto material = tape.materials().front();

      THEN( "all covariances can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        std::optional< covariance::CrossSectionCovarianceData > covariances =
        endf::read::covariance::createCrossSectionCovarianceData( projectile, target, material );

        neutron::h1::verifyCrossSectionCovariances( covariances.value() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - incident neutrons - single and multiple submatrices, with "
         "lumped covariances" ) {

    WHEN( "a single ENDF material is given" ) {

      using Tape = njoy::ENDFtk::tree::Tape;
      auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-003_Li_007.endf" );
      auto material = tape.materials().front();

      THEN( "all covariances can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Li7" );
        std::optional< covariance::CrossSectionCovarianceData > covariances =
        endf::read::covariance::createCrossSectionCovarianceData( projectile, target, material );

        neutron::li7::verifyCrossSectionCovariances( covariances.value() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
