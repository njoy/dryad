// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertDouble.hpp"

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

SCENARIO( "insertDouble" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a double node can be inserted - no label and unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertDouble( parent, options, 1000, std::nullopt, std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "a double node can be inserted - no unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertDouble( parent, options, 1000, "energy", std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN

    THEN( "a double node can be inserted - no label" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertDouble( parent, options, 1000, std::nullopt, "eV" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN

    THEN( "a double node can be inserted - label and unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertDouble( parent, options, 1000, "energy", "eV" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk4() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<double value=\"1000\" />\n";
}

std::string chunk2() {

  return "<double label=\"energy\" value=\"1000\" />\n";
}

std::string chunk3() {

  return "<double value=\"1000\" unit=\"eV\" />\n";
}

std::string chunk4() {

  return "<double label=\"energy\" value=\"1000\" unit=\"eV\" />\n";
}
