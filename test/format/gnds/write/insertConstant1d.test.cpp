// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertConstant1d.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();

SCENARIO( "insertConstant1d" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a constant1d node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertConstant1d( parent, options, 4.82222, 1e-5, 1.2e+6,
                                                 "incidentEnergy", "radius", "eV", "fm",
                                                 "eval", std::nullopt );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "  </axes>\n"
         "</constant1d>\n";
}
