// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/covariance/createScalingType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad::covariance;
using namespace njoy::dryad::format::gnds;

SCENARIO( "createScalingType" ) {

  GIVEN( "GNDS scaling type values" ) {

    WHEN( "a scaling type value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( ScalingType::Direct == covariance::createScalingType( "direct" ) );
        CHECK( ScalingType::Inverse == covariance::createScalingType( "inverse" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( covariance::createScalingType( "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
