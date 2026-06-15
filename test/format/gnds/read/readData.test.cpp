// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readData.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyChunk( const std::vector< double >& );

SCENARIO( "readData" ) {

  GIVEN( "a GNDS table xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node table = document.child( "reactionSuite" ).child( "resonances" ).
                                    child( "resolved" ).child( "RMatrix" ).
                                    child( "spinGroups" ).child( "spinGroup" ).
                                    child( "resonanceParameters" ).child( "table" );

    WHEN( "a single GNDS data node" ) {

      pugi::xml_node data = table.child( "data" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readData( data );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readData( table ) );                      // wrong node
        CHECK_THROWS( gnds::read::readData( table.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< double >& chunk ) {

 CHECK( 30 == chunk.size() );

 CHECK_THAT( -4585600, WithinRel( chunk[0] ) );
 CHECK_THAT( 0.99675 , WithinRel( chunk[1] ) );
 CHECK_THAT( 2       , WithinRel( chunk[28] ) );
 CHECK_THAT( 37262   , WithinRel( chunk[29] ) );
}
