// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertDocumentation.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunkGaugeBoson();
std::string chunkLepton();
std::string chunkBaryon();
std::string chunkNuclide();
std::string chunkNuclideWithExcitedState();

SCENARIO( "insertDocumentation" ) {

  GIVEN( "a parent node and documentation with content" ) {

    gnds::write::Options options;

    THEN( "a documentation node can be inserted" ) {

      Documentation documentation( std::nullopt, std::nullopt, "1 2 3\n4 5 6 7\n" );

      pugi::xml_document parent;
      auto node = gnds::write::insertDocumentation( parent, options, documentation );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkGaugeBoson() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunkGaugeBoson() {

  return "<documentation>\n"
         "  <body>1 2 3\n"
         "4 5 6 7\n"
         "  </body>\n"
         "</documentation>\n";
}
