// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertPolynomial1d.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();

SCENARIO( "insertPolynomial1d" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a polynomial1d node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertPolynomial1d( parent, options, { 172790200, -0.3778921 }, 1e-5, 1.2e+6,
                                                   "incidentEnergy", "outgoingEnergy", "eV", "MeV",
                                                   "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<polynomial1d label=\"eval\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"outgoingEnergy\" unit=\"MeV\" />\n"
         "  </axes>\n"
         "  <values>\n"
         "    172790200 -0.3778921\n"
         "  </values>\n"
         "</polynomial1d>\n";
}
