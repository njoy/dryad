// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/format/gnds/read/readColumn.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyChunk( const gnds::read::Column& );

SCENARIO( "readAxis" ) {

  GIVEN( "a GNDS axis xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node headers = document.child( "reactionSuite" ).child( "resonances" ).
                                      child( "resolved" ).child( "RMatrix" ).
                                      child( "spinGroups" ).child( "spinGroup" ).
                                      child( "resonanceParameters" ).child( "table" ).
                                      child( "columnHeaders" );

    WHEN( "a single GNDS column node" ) {

      pugi::xml_node column = headers.child( "column" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readColumn( column );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readColumn( headers ) );                      // wrong node
        CHECK_THROWS( gnds::read::readColumn( headers.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const gnds::read::Column& chunk ) {

  CHECK( 0        == std::get< 0 >( chunk ) );
  CHECK( "energy" == std::get< 1 >( chunk ) );
  CHECK( "eV"     == std::get< 2 >( chunk ) );
}
