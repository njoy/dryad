// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/covariance/createCovarianceData.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "../test_verification_functions.hpp"

SCENARIO( "createCovarianceData" ) {

  using GTape = njoy::ENDFtk::tree::GTape;

  GIVEN( "an ERRORR formatted GENDF material with cross section covariances" ) {

    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.xs.gendf" );
    auto material = tape.materials().front();

    WHEN( "constructing the covariance data" ) {

      auto chunk = gendf::read::covariance::createCovarianceData(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, ReferenceFrame::Laboratory, material );

      THEN( "only cross section covariance data is present" ) {

        CHECK( true == chunk.has_value() );
        CHECK( std::nullopt != chunk->crossSection() );
        CHECK( std::nullopt == chunk->angularDistribution() );

        neutron::u235::verifyCrossSectionCovariances( chunk->crossSection().value() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an ERRORR formatted GENDF material with angular distribution covariances" ) {

    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.angular.gendf" );
    auto material = tape.materials().front();

    WHEN( "constructing the covariance data" ) {

      auto chunk = gendf::read::covariance::createCovarianceData(
                       id::ParticleID( "n" ), id::ParticleID( "U235" ),
                       true, ReferenceFrame::Laboratory, material );

      THEN( "only angular distribution covariance data is present" ) {

        CHECK( true == chunk.has_value() );
        CHECK( std::nullopt == chunk->crossSection() );
        CHECK( std::nullopt != chunk->angularDistribution() );

        neutron::u235::verifyAngularDistributionCovariances( chunk->angularDistribution().value() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
