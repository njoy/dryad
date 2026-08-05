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

    THEN( "a values node can be inserted - one list of values" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertValues( parent, options, {  1.,  2.,  3.,  4.,  5.,  6.,
                                                                 7.,  8.,  9., 10., 11., 12., 13. } );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "a values node can be inserted - 2 lists of values" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertValues( parent, options,
                                             {  1.,  2.,  3.,  4.,  5.,  6., 7.,  8.,  9., 10., 11., 12. },
                                             { 13., 14., 15., 16., 17., 18., 19, 20., 21., 22., 23., 24. } );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<values>\n"
         "  1 2 3 4 5 6 7 8 9 10 11 12\n"
         "  13\n"
         "</values>\n";
}

std::string chunk2() {

  return "<values>\n"
         "  1 13 2 14 3 15 4 16 5 17 6 18\n"
         "  7 19 8 20 9 21 10 22 11 23 12 24\n"
         "</values>\n";
}
