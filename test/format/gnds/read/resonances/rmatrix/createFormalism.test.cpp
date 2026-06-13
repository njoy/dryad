// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/resonances/rmatrix/createFormalism.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createFormalism" ) {

  GIVEN( "GNDS rmatrix formalism values" ) {

    WHEN( "an rmatrix formalism is given" ) {

      THEN( "it can be converted" ) {

        CHECK( resonances::Formalism::ReichMoore == gnds::read::resonances::rmatrix::createFormalism( "ReichMoore" ) );
        CHECK( resonances::Formalism::GeneralRMatrix == gnds::read::resonances::rmatrix::createFormalism( "FullRMatrix" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( gnds::read::resonances::rmatrix::createFormalism( "com" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
