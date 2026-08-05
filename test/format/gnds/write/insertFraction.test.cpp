// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertFraction.hpp"

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
std::string chunk5();

SCENARIO( "insertFraction" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a fraction node can be inserted - no label and unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertFraction( parent, options, 1, 2, std::nullopt, std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "a fraction node can be inserted - no unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertFraction( parent, options, 1, 2, "spin", std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN

    THEN( "a fraction node can be inserted - no label" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertFraction( parent, options, 1, 2, std::nullopt, "hbar" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN

    THEN( "a fraction node can be inserted - label and unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertFraction( parent, options, 1, 2, "spin", "hbar" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk4() );
    } // THEN

    THEN( "a fraction node can be inserted - fraction logic" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertFraction( parent, options, 2, 1, std::nullopt, std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk5() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<fraction value=\"1/2\" />\n";
}

std::string chunk2() {

  return "<fraction label=\"spin\" value=\"1/2\" />\n";
}

std::string chunk3() {

  return "<fraction value=\"1/2\" unit=\"hbar\" />\n";
}

std::string chunk4() {

  return "<fraction label=\"spin\" value=\"1/2\" unit=\"hbar\" />\n";
}

std::string chunk5() {

  return "<fraction value=\"2\" />\n";
}
