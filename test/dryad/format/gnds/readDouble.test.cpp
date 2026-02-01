// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/readDouble.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunkWithoutUnit( const format::gnds::Double& );
void verifyChunkWithUnit( const format::gnds::Double& );

SCENARIO( "readLegendre" ) {

  GIVEN( "a GNDS Legendre xml node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node external = document.child( "reactionSuite" ).
                                       child( "resonances" ).child( "resolved" ).
                                       child( "RMatrix" ).child( "spinGroups" ).
                                       child( "spinGroup" ).child( "channels" ).
                                       find_child_by_attribute( "channel", "label", "1" ).
                                       child( "externalRMatrix" );
    pugi::xml_node without_unit = external.find_child_by_attribute( "double", "label", "constantExternalR" );
    pugi::xml_node with_unit = external.find_child_by_attribute( "double", "label", "linearExternalR" );

    WHEN( "a single GNDS double node with and without units are given" ) {

      THEN( "it can be converted" ) {

        auto chunk_without_unit = format::gnds::readDouble( without_unit );
        auto chunk_with_unit = format::gnds::readDouble( with_unit );

        verifyChunkWithoutUnit( chunk_without_unit );
        verifyChunkWithUnit( chunk_with_unit );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readDouble( external ) );                      // wrong node
        CHECK_THROWS( format::gnds::readDouble( external.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkWithoutUnit( const format::gnds::Double& chunk ) {

  CHECK_THAT( -0.043, WithinRel( chunk.first ) );
  CHECK( std::nullopt == chunk.second );
}

void verifyChunkWithUnit( const format::gnds::Double& chunk ) {

  CHECK_THAT( 2.8e-8, WithinRel( chunk.first ) );
  CHECK( "1/eV" == chunk.second );
}