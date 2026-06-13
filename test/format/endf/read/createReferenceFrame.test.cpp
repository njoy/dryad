// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createReferenceFrame.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createReferenceFrame" ) {

  GIVEN( "ENDF reference frame values" ) {

    WHEN( "a single reference frame value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( ReferenceFrame::Laboratory   == endf::read::createReferenceFrame( 1 ) );
        CHECK( ReferenceFrame::CentreOfMass == endf::read::createReferenceFrame( 2 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported type" ) {

        CHECK_THROWS( endf::read::createReferenceFrame( 0 ) );
        CHECK_THROWS( endf::read::createReferenceFrame( 3 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
