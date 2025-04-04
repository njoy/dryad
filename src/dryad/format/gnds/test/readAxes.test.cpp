// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/format/gnds/readAxes.hpp"

// other includes
#include "pugixml.hpp"
#include <iostream>
// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const std::vector< std::string >& );
void verifyChunkWithIndex2( const std::vector< std::string >& );

SCENARIO( "readAxes" ) {

  GIVEN( "a GNDS axes xml node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "reactions" );

    WHEN( "a single GNDS axes node without an axis with index 2" ) {

      pugi::xml_node axes = reactions.child( "reaction" ).child( "crossSection" ).
                                      child( "XYs1d" ).child( "axes" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readAxes( axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single GNDS axes node with an axis with index 2" ) {

      pugi::xml_node axes = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                      child( "outputChannel" ).child( "products" ).
                                      child( "product" ).child( "distribution" ).
                                      child( "angularTwoBody" ).child( "XYs2d" ).child( "axes" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readAxes( axes );

        verifyChunkWithIndex2( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readAxes( reactions ) );                      // wrong node
        CHECK_THROWS( format::gnds::readAxes( reactions.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< std::string >& chunk ) {

  CHECK( 2 == chunk.size() );
  CHECK( "eV" == chunk[0] );
  CHECK( "b"  == chunk[1] );
}

void verifyChunkWithIndex2( const std::vector< std::string >& chunk ) {

  CHECK( 3 == chunk.size() );
  CHECK( "eV" == chunk[0] );
  CHECK( ""   == chunk[1] );
  CHECK( ""   == chunk[2] );
}
