// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/format/gnds/read/readAxis.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyChunk( const gnds::read::Axis& );

SCENARIO( "readAxis" ) {

  GIVEN( "a GNDS axis xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node axes = document.child( "reactionSuite" ).child( "reactions" ).
                                   child( "reaction" ).child( "crossSection" ).
                                   child( "XYs1d" ).child( "axes" );

    WHEN( "a single GNDS axes node without an axis with index 1" ) {

      pugi::xml_node axis = axes.child( "axis" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readAxis( axis );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readAxis( axes ) );                      // wrong node
        CHECK_THROWS( gnds::read::readAxis( axes.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const gnds::read::Axis& chunk ) {

  CHECK( 1    == chunk.first );
  CHECK( "eV"  == chunk.second );
}
