// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/format/gendf/covariance/createCrossSectionCovarianceData.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::ENDFtk;

SCENARIO( "createCrossSectionCovarianceData" ) {

  GIVEN( "a GENDF material" ) {

    using GTape = njoy::ENDFtk::tree::GTape;
    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.gendf" );
    auto material = tape.materials().front();

    WHEN( "constructing covariance matrices" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      bool relative = true;

      auto chunk = format::gendf::covariance::createCrossSectionCovarianceData( projectile, target, relative, material );

      THEN( "covariance matrices can be created and members can be tested" ) {

      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
