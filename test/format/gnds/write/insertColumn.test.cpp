// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertColumn.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertColumn" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a column node can be inserted - no unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertColumn( parent, options, 1, "energy" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "a column node can be inserted - with unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertColumn( parent, options, 1, "energy", "eV" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<column index=\"1\" name=\"energy\" />\n";
}

std::string chunk2() {

  return "<column index=\"1\" name=\"energy\" unit=\"eV\" />\n";
}
