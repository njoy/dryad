// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/insertHardSphereRadius.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertHardSphereRadius" ) {

  GIVEN( "a parent node and a constant radius" ) {

    gnds::write::Options options;

    THEN( "a hardSphereRadius node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::insertHardSphereRadius( parent, options, 1., 1e-5, 2e+7, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a tabulated radius" ) {

    gnds::write::Options options;

    THEN( "a hardSphereRadius node can be inserted" ) {

      resonances::TabulatedRadius radius( { 1e-5, 2e+7 }, { 2.824, 3 } );

      pugi::xml_document parent;
      auto node = gnds::write::resonances::insertHardSphereRadius( parent, options, radius, 1e-5, 2e+7, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<hardSphereRadius>\n"
         "  <constant1d label=\"eval\" value=\"1\" domainMin=\"1e-05\" domainMax=\"20000000\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "    </axes>\n"
         "  </constant1d>\n"
         "</hardSphereRadius>\n";
}

std::string chunk2() {

  return "<hardSphereRadius>\n"
         "  <XYs1d label=\"eval\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "    </axes>\n"
         "    <values>\n"
         "      1e-05 2.824 20000000 3\n"
         "    </values>\n"
         "  </XYs1d>\n"
         "</hardSphereRadius>\n";
}
