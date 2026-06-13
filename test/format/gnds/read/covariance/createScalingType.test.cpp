// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/covariance/createScalingType.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createScalingType" ) {

  GIVEN( "GNDS scaling type values" ) {

    WHEN( "a scaling type value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( covariance::ScalingType::Direct == gnds::read::covariance::createScalingType( "direct" ) );
        CHECK( covariance::ScalingType::Inverse == gnds::read::covariance::createScalingType( "inverse" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( gnds::read::covariance::createScalingType( "unsupported" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
