// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/toString.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

SCENARIO( "toString" ) {

  gnds::write::Options options;

  GIVEN( "single values" ) {

    THEN( "a double node can be converted to a string" ) {

      CHECK( "1000" == gnds::write::toString( options, 1000 ) );
      CHECK( "1000" == gnds::write::toString( options, 1000. ) );

      CHECK( "123"             == gnds::write::toString( options, 123 ) );
      CHECK( "1234567"         == gnds::write::toString( options, 1234567 ) );
      CHECK( "1234567890"      == gnds::write::toString( options, 1234567890 ) );

      CHECK( "1.123"           == gnds::write::toString( options, 1.123 ) );
      CHECK( "1.123456789"     == gnds::write::toString( options, 1.123456789 ) );
      CHECK( "1123456789"      == gnds::write::toString( options, 1123456789. ) );
      CHECK( "123.1234568"     == gnds::write::toString( options, 123.123456789 ) );
      CHECK( "1e-05"           == gnds::write::toString( options, 1e-5 ) );
      CHECK( "20000000"        == gnds::write::toString( options, 2.e+7 ) );
      CHECK( "21200000"        == gnds::write::toString( options, 2.1200000005e+7 ) );
      CHECK( "21200000.01"     == gnds::write::toString( options, 2.12000000051e+7 ) );
      CHECK( "21200000.01"     == gnds::write::toString( options, 2.1200000006e+7 ) );
      CHECK( "2000000000"      == gnds::write::toString( options, 2.e+9 ) );
      CHECK( "2120000000"      == gnds::write::toString( options, 2.1200000005e+9 ) );
      CHECK( "2120000001"      == gnds::write::toString( options, 2.12000000051e+9 ) );
      CHECK( "2120000001"      == gnds::write::toString( options, 2.1200000006e+9 ) );
      CHECK( "2e+11"           == gnds::write::toString( options, 2.e+11 ) );
      CHECK( "2.120000000e+11" == gnds::write::toString( options, 2.1200000005e+11 ) );
      CHECK( "2.120000001e+11" == gnds::write::toString( options, 2.12000000051e+11 ) );
      CHECK( "2.120000001e+11" == gnds::write::toString( options, 2.1200000006e+11 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
