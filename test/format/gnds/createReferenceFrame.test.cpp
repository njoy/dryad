// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createReferenceFrame.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createReferenceFrame" ) {

  GIVEN( "GNDS product frame values" ) {

    WHEN( "a product frame value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( ReferenceFrame::Laboratory == format::gnds::createReferenceFrame( "lab" ) );
        CHECK( ReferenceFrame::CentreOfMass == format::gnds::createReferenceFrame( "centerOfMass" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( format::gnds::createReferenceFrame( "com" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
