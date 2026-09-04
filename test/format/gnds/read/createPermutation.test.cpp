// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createPermutation.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "createPermutation" ) {

  GIVEN( "GNDS symmetry values" ) {

    WHEN( "a symmetry value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( gnds::read::Permutation::None == gnds::read::createPermutation( "none" ) );
        CHECK( gnds::read::Permutation::Symmetric == gnds::read::createPermutation( "+1" ) );
        CHECK( gnds::read::Permutation::AntiSymmetric == gnds::read::createPermutation( "-1" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( gnds::read::createPermutation( "other-symmetry" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
