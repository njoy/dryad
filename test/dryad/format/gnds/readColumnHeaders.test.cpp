// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/dryad/format/gnds/readColumnHeaders.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const format::gnds::Headers& );

SCENARIO( "readColumnHeaders" ) {

  GIVEN( "a GNDS table xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node table = document.child( "reactionSuite" ).child( "resonances" ).
                                    child( "resolved" ).child( "RMatrix" ).
                                    child( "spinGroups" ).child( "spinGroup" ).
                                    child( "resonanceParameters" ).child( "table" );

    WHEN( "a single GNDS heaaders node" ) {

      pugi::xml_node headers = table.child( "columnHeaders" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readColumnHeaders( headers );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readColumnHeaders( table ) );                      // wrong node
        CHECK_THROWS( format::gnds::readColumnHeaders( table.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::Headers& chunk ) {

  CHECK( 3 == chunk.size() );
  CHECK( 0  == std::get< 0 >( chunk[0] ) );
  CHECK( 1  == std::get< 0 >( chunk[1] ) );
  CHECK( 2  == std::get< 0 >( chunk[2] ) );
  CHECK( "energy"                          == std::get< 1 >( chunk[0] ) );
  CHECK( "Al28 + photon [inclusive] width" == std::get< 1 >( chunk[1] ) );
  CHECK( "n + Al27 width"                  == std::get< 1 >( chunk[2] ) );
  CHECK( "eV" == std::get< 2 >( chunk[0] ).value() );
  CHECK( "eV" == std::get< 2 >( chunk[1] ).value() );
  CHECK( "eV" == std::get< 2 >( chunk[2] ).value() );
}
