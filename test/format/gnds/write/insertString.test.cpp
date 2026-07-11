// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertString.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();
std::string chunk2();
std::string chunk3();
std::string chunk4();

SCENARIO( "insertString" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a string node can be inserted - no label and unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertString( parent, options, "a", std::nullopt, std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "a string node can be inserted - no unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertString( parent, options, "a", "b", std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN

    THEN( "a string node can be inserted - no label" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertString( parent, options, "a", std::nullopt, "c" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN

    THEN( "a string node can be inserted - label and unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertString( parent, options, "a", "b", "c" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk4() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<string value=\"a\" />\n";
}

std::string chunk2() {

  return "<string label=\"b\" value=\"a\" />\n";
}

std::string chunk3() {

  return "<string value=\"a\" unit=\"c\" />\n";
}

std::string chunk4() {

  return "<string label=\"b\" value=\"a\" unit=\"c\" />\n";
}
