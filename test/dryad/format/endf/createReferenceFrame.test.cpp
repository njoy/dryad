// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/createReferenceFrame.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createReferenceFrame" ) {

  GIVEN( "ENDF reference frame values" ) {

    WHEN( "a single reference frame value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( ReferenceFrame::Laboratory   == format::endf::createReferenceFrame( 1 ) );
        CHECK( ReferenceFrame::CentreOfMass == format::endf::createReferenceFrame( 2 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported type" ) {

        CHECK_THROWS( format::endf::createReferenceFrame( 0 ) );
        CHECK_THROWS( format::endf::createReferenceFrame( 3 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
