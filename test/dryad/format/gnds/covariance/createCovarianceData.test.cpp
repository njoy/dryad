// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/format/gnds/covariance/createCovarianceData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "../test_verification_functions.hpp"

SCENARIO( "createCovarianceData" ) {

  GIVEN( "GNDS nodes - incident neutrons - single submatrices and "
         "linear combinations" ) {

    pugi::xml_document document;
    document.load_file( "n-001_H_001.endf.gnds-covar.xml" );
    pugi::xml_node node = document.child( "covarianceSuite" );

    WHEN( "a single covarianceSections node is given" ) {

      THEN( "all covariances can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        std::optional< covariance::CovarianceData > covariances =
        format::gnds::covariance::createCovarianceData( projectile, target, node );

        neutron::h1::verifyCrossSectionCovariances( covariances.value().crossSection().value() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS nodes - incident neutrons - single and multiple submatrices, with "
         "lumped covariances" ) {

    pugi::xml_document document;
    document.load_file( "n-003_Li_007.endf.gnds-covar.xml" );
    pugi::xml_node node = document.child( "covarianceSuite" );

    WHEN( "a single covarianceSections node is given" ) {

      THEN( "all covariances can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Li7" );
        std::optional< covariance::CovarianceData > covariances =
        format::gnds::covariance::createCovarianceData( projectile, target, node );

        neutron::li7::verifyCrossSectionCovariances( covariances.value().crossSection().value() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
