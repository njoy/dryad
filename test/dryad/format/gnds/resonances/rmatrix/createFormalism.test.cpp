// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/resonances/rmatrix/createFormalism.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createFormalism" ) {

  GIVEN( "GNDS rmatrix formalism values" ) {

    WHEN( "an rmatrix formalism is given" ) {

      THEN( "it can be converted" ) {

        CHECK( resonances::Formalism::ReichMoore == format::gnds::resonances::rmatrix::createFormalism( "ReichMoore" ) );
        CHECK( resonances::Formalism::GeneralRMatrix == format::gnds::resonances::rmatrix::createFormalism( "FullRMatrix" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( format::gnds::resonances::rmatrix::createFormalism( "com" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
