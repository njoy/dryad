// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertTemperature.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk();

SCENARIO( "insertTemperature" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a temperature node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTemperature( parent, options, 1000, "K" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "<temperature value=\"1000\" unit=\"K\" />\n";
}
