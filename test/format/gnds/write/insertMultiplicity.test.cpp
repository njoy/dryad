// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertMultiplicity.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();
std::string chunk3();

SCENARIO( "insertMultiplicity" ) {

  GIVEN( "a parent node and a constant multiplicity" ) {

    gnds::write::Options options;

    THEN( "a multiplicity node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertMultiplicity( parent, options, 1, 1e-5, 2e+7, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a polynomial multiplicity" ) {

    gnds::write::Options options;

    THEN( "a multiplicity node can be inserted" ) {

      PolynomialMultiplicity multiplicity( 1e-5, 2e+7, { 2.824, 1.42e-7 } );

      pugi::xml_document parent;
      auto node = gnds::write::insertMultiplicity( parent, options, multiplicity, 1e-5, 2e+7, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a tabulated multiplicity" ) {

    gnds::write::Options options;

    THEN( "a multiplicity node can be inserted" ) {

      TabulatedMultiplicity multiplicity( { 1e-5, 2e+7 }, { 2.824, 3 } );

      pugi::xml_document parent;
      auto node = gnds::write::insertMultiplicity( parent, options, multiplicity, 1e-5, 2e+7, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<multiplicity>\n"
         "  <constant1d label=\"eval\" value=\"1\" domainMin=\"1e-05\" domainMax=\"20000000\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"multiplicity\" />\n"
         "    </axes>\n"
         "  </constant1d>\n"
         "</multiplicity>\n";
}

std::string chunk2() {

  return "<multiplicity>\n"
         "  <polynomial1d label=\"eval\" domainMin=\"1e-05\" domainMax=\"20000000\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"multiplicity\" />\n"
         "    </axes>\n"
         "    <values>\n"
         "      2.824 1.42e-07\n"
         "    </values>\n"
         "  </polynomial1d>\n"
         "</multiplicity>\n";
}

std::string chunk3() {

  return "<multiplicity>\n"
         "  <XYs1d label=\"eval\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"multiplicity\" />\n"
         "    </axes>\n"
         "    <values>\n"
         "      1e-05 2.824 20000000 3\n"
         "    </values>\n"
         "  </XYs1d>\n"
         "</multiplicity>\n";
}
