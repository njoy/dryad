// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertTable.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();

SCENARIO( "insertTable" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a columnHeaders node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTable( parent, options,
                                            { "energy", "width" },
                                            { "eV", "eV^1/2" },
                                            { { 1., 2., 3. }, { 4., 5., 6. } } );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<table rows=\"3\" columns=\"2\">\n"
         "  <columnHeaders>\n"
         "    <column index=\"0\" name=\"energy\" unit=\"eV\" />\n"
         "    <column index=\"1\" name=\"width\" unit=\"eV^1/2\" />\n"
         "  </columnHeaders>\n"
         "  <data>\n"
         "    1 4\n"
         "    2 5\n"
         "    3 6\n"
         "  </data>\n"
         "</table>\n";
}
