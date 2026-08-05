// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertQ.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();

SCENARIO( "insertQ" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a constant1d node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertQ( parent, options, -6997450, 7199290, 2e+7, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<Q>\n"
         "  <constant1d label=\"eval\" value=\"-6997450\" domainMin=\"7199290\" domainMax=\"20000000\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "    </axes>\n"
         "  </constant1d>\n"
         "</Q>\n";
}
