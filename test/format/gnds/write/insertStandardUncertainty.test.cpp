// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/format/gnds/write/insertStandardUncertainty.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk();

SCENARIO( "insertStandardUncertainty" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a standard uncertainty node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertStandardUncertainty( parent, options, 0.001 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "<uncertainty>\n"
         "  <standard>\n"
         "    <double value=\"0.001\" />\n"
         "  </standard>\n"
         "</uncertainty>\n";
}
