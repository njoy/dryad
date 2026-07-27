// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createStorageOrder.hpp"

// other includes

// convenience typedefs
using namespace njoy::format;

SCENARIO( "createStorageOrder" ) {

  GIVEN( "GNDS storage order values" ) {

    WHEN( "a storage order value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( gnds::read::StorageOrder::RowMajor == gnds::read::createStorageOrder( "row-major" ) );
        CHECK( gnds::read::StorageOrder::ColumnMajor == gnds::read::createStorageOrder( "column-major" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( gnds::read::createStorageOrder( "other-order" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
