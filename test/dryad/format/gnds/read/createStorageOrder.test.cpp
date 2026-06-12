// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/createStorageOrder.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createStorageOrder" ) {

  GIVEN( "GNDS storage order values" ) {

    WHEN( "a storage order value is given" ) {

      THEN( "it can be converted" ) {

        CHECK( format::gnds::StorageOrder::RowMajor == format::gnds::createStorageOrder( "row-major" ) );
        CHECK( format::gnds::StorageOrder::ColumnMajor == format::gnds::createStorageOrder( "column-major" ) );
      } // THEN

      THEN( "an exception is thrown for an invalid or unsupported value" ) {

        CHECK_THROWS( format::gnds::createStorageOrder( "other-order" ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
