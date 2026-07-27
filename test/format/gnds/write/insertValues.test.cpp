// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertValues.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertValues" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a values node can be inserted - list of 11 values" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertValues( parent, options, {  1.,  2.,  3.,  4.,  5.,  6.,
                                                                 7.,  8.,  9., 10., 11. } );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "a values node can be inserted - 2 lists of 6 values" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertValues( parent, options,
                                             {  1.,  2.,  3.,  4.,  5.,  6. },
                                             {  7.,  8.,  9., 10., 11., 12. } );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<values>\n"
         "  1 2 3 4 5 6\n"
         "  7 8 9 10 11\n"
         "</values>\n";
}

std::string chunk2() {

  return "<values>\n"
         "  1 7 2 8 3 9\n"
         "  4 10 5 11 6 12\n"
         "</values>\n";
}
