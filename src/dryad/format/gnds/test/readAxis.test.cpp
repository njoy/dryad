// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/format/gnds/readAxis.hpp"

// other includes
#include "pugixml.hpp"
#include <iostream>
// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const format::gnds::Axis& );

SCENARIO( "readAxes" ) {

  GIVEN( "a GNDS axis xml nodes" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node axes = document.child( "reactionSuite" ).child( "reactions" ).
                                   child( "reaction" ).child( "crossSection" ).
                                   child( "XYs1d" ).child( "axes" );

    WHEN( "a single GNDS axes node without an axis with index 2" ) {

      pugi::xml_node axis = axes.child( "axis" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readAxis( axis );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readAxis( axes ) );                      // wrong node
        CHECK_THROWS( format::gnds::readAxis( axes.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::Axis& chunk ) {

  CHECK( 1    == chunk.first );
  CHECK( "eV"  == chunk.second );
}
