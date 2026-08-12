// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertData.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();

SCENARIO( "insertData" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a values node can be inserted - one list of values" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertData( parent, options,
                                           { { 1., 2., 3. }, { 4., 5., 6. },
                                             { 7., 8., 9. }, { 10., 11., 12. } } );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<data>\n"
         "  1 4 7 10\n"
         "  2 5 8 11\n"
         "  3 6 9 12\n"
         "</data>\n";
}
