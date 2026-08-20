// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createSymmetry.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "createSymmetry" ) {

  GIVEN( "GNDS symmetry values" ) {

    WHEN( "a symmetry value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( gnds::read::Symmetry::None == gnds::read::createSymmetry( "none" ) );
        CHECK( gnds::read::Symmetry::Upper == gnds::read::createSymmetry( "upper" ) );
        CHECK( gnds::read::Symmetry::Lower == gnds::read::createSymmetry( "lower" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( gnds::read::createSymmetry( "other-symmetry" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
