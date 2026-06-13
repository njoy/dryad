// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readString.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyChunkWithUnit( const gnds::read::String& );

SCENARIO( "readString" ) {

  GIVEN( "a GNDS string xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node external = document.child( "reactionSuite" ).
                                       child( "PoPs" ).child( "gaugeBosons" ).
                                       child( "gaugeBoson" );
    pugi::xml_node with_unit = external.child( "halflife" ).child( "string" );

    WHEN( "a single GNDS string node with and without units are given" ) {

      THEN( "it can be converted" ) {

        auto chunk_with_unit = gnds::read::readString( with_unit );

        verifyChunkWithUnit( chunk_with_unit );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readString( external ) );                      // wrong node
        CHECK_THROWS( gnds::read::readString( external.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkWithUnit( const gnds::read::String& chunk ) {

  CHECK( "stable" == chunk.first );
  CHECK( "s" == chunk.second );
}