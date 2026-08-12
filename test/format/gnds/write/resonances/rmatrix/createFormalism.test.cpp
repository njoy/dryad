// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/rmatrix/createFormalism.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createFormalism" ) {

  GIVEN( "dryad formalism values" ) {

    WHEN( "a formalism value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( "ReichMoore" == gnds::write::resonances::rmatrix::createFormalism( resonances::Formalism::ReichMoore ) );
        CHECK( "FullRMatrix" == gnds::write::resonances::rmatrix::createFormalism( resonances::Formalism::GeneralRMatrix ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
