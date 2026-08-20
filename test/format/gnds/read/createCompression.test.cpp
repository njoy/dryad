// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createCompression.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "createCompression" ) {

  GIVEN( "GNDS compression values" ) {

    WHEN( "a compression value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( gnds::read::Compression::None == gnds::read::createCompression( "none" ) );
        CHECK( gnds::read::Compression::Diagonal == gnds::read::createCompression( "diagonal" ) );
        CHECK( gnds::read::Compression::Flattened == gnds::read::createCompression( "flattened" ) );
        CHECK( gnds::read::Compression::Embedded == gnds::read::createCompression( "embedded" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( gnds::read::createCompression( "other-compression" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
