// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertAxes.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertAxes" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "an axes node can be inserted - x and y" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertAxes( parent, options, "incidentEnergy", "crossSection", "eV", "b" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "an axes node can be inserted - x, y and z" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertAxes( parent, options,
                                           "incidentEnergy", "outgoingEnergy", "probability",
                                           "eV", "MeV", "1/eV" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<axes>\n"
         "  <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "  <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "</axes>\n";
}

std::string chunk2() {

  return "<axes>\n"
         "  <axis index=\"2\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "  <axis index=\"1\" label=\"outgoingEnergy\" unit=\"MeV\" />\n"
         "  <axis index=\"0\" label=\"probability\" unit=\"1/eV\" />\n"
         "</axes>\n";
}
