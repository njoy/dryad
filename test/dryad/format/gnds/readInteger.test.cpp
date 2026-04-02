// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/readInteger.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunkWithoutUnit( const format::gnds::Integer& );
void verifyChunkWithUnit( const format::gnds::Integer& );

SCENARIO( "readInteger" ) {

  GIVEN( "a GNDS integer xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node external = document.child( "reactionSuite" ).
                                       child( "PoPs" ).child( "gaugeBosons" ).
                                       child( "gaugeBoson" );
    pugi::xml_node without_unit = external.child( "parity" ).child( "integer" );
    pugi::xml_node with_unit = external.child( "charge" ).child( "integer" );

    WHEN( "a single GNDS integer node with and without units are given" ) {

      THEN( "it can be converted" ) {

        auto chunk_without_unit = format::gnds::readInteger( without_unit );
        auto chunk_with_unit = format::gnds::readInteger( with_unit );

        verifyChunkWithoutUnit( chunk_without_unit );
        verifyChunkWithUnit( chunk_with_unit );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readInteger( external ) );                      // wrong node
        CHECK_THROWS( format::gnds::readInteger( external.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkWithoutUnit( const format::gnds::Integer& chunk ) {

  CHECK( 1 == chunk.first );
  CHECK( std::nullopt == chunk.second );
}

void verifyChunkWithUnit( const format::gnds::Integer& chunk ) {

  CHECK( 0 == chunk.first );
  CHECK( "e" == chunk.second );
}