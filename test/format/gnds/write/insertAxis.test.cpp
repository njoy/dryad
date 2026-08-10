// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertAxis.hpp"

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

SCENARIO( "insertAxis" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "an axis node can be inserted - no index and unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertAxis( parent, options, "energy", std::nullopt, std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "an axis node can be inserted - no unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertAxis( parent, options, "energy", 0, std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN

    THEN( "an axis node can be inserted - no index" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertAxis( parent, options, "energy", std::nullopt, "eV" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN

    THEN( "an axis node can be inserted - index and unit" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertAxis( parent, options, "energy", 0, "eV" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk4() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<axis label=\"energy\" />\n";
}

std::string chunk2() {

  return "<axis index=\"0\" label=\"energy\" />\n";
}

std::string chunk3() {

  return "<axis label=\"energy\" unit=\"eV\" />\n";
}

std::string chunk4() {

  return "<axis index=\"0\" label=\"energy\" unit=\"eV\" />\n";
}
