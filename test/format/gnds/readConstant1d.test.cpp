// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/readConstant1d.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const format::gnds::RealConstant1d& );

SCENARIO( "readConstant1d" ) {

  GIVEN( "a GNDS constant1d xml node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node constant1d = document.child( "reactionSuite" ).child( "reactions" ).
                                         find_child_by_attribute( "reaction", "ENDF_MT", "102" ).
                                         child( "outputChannel" ).child( "Q" ).
                                         child( "constant1d" );

    WHEN( "a single GNDS constant1d node with an outer domain value is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readConstant1dAsDouble( constant1d );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readConstant1dAsDouble( constant1d.child( "axes" ) ) );      // wrong node
        CHECK_THROWS( format::gnds::readConstant1dAsDouble( constant1d.child( "undefined" ) ) ); // undefiend node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::RealConstant1d& chunk ) {

  CHECK( 2224648 == chunk.first );
  CHECK( "eV" == chunk.second );
}
