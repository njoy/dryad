// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/dryad/format/gnds/readColumn.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const format::gnds::Column& );

SCENARIO( "readAxis" ) {

  GIVEN( "a GNDS axis xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node headers = document.child( "reactionSuite" ).child( "resonances" ).
                                      child( "resolved" ).child( "RMatrix" ).
                                      child( "spinGroups" ).child( "spinGroup" ).
                                      child( "resonanceParameters" ).child( "table" ).
                                      child( "columnHeaders" );

    WHEN( "a single GNDS axes node without an axis with index 1" ) {

      pugi::xml_node column = headers.child( "column" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readColumn( column );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readColumn( headers ) );                      // wrong node
        CHECK_THROWS( format::gnds::readColumn( headers.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::Column& chunk ) {

  CHECK( 0        == std::get< 0 >( chunk ) );
  CHECK( "energy" == std::get< 1 >( chunk ) );
  CHECK( "eV"     == std::get< 2 >( chunk ) );
}
