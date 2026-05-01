// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/format/gendf/covariance/createCrossSectionCovarianceDataFromFile.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createCrossSectionCovarianceDataFromFile" ) {

  GIVEN( "a GENDF material" ) {

    WHEN( "constructing covariance matrices" ) {

      auto chunk = format::gendf::covariance::createCrossSectionCovarianceDataFromFile(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, "n-092_U_235.covariances.gendf" );

      THEN( "covariance matrices can be created and members can be tested" ) {

      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
