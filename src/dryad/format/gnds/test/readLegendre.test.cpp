// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/readLegendre.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const std::pair< std::optional< double >, std::vector< double > >& );

SCENARIO( "readLegendre" ) {

  GIVEN( "a GNDS Legendre xml nodes" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node legendre = document.child( "reactionSuite" ).child( "reactions" ).
                                       find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                       child( "outputChannel" ).child( "products" ).
                                       find_child_by_attribute( "product", "pid", "n" ).
                                       child( "distribution" ).child( "angularTwoBody" ).
                                       child( "XYs2d" ).child( "function1ds" ).
                                       child( "Legendre" );

    WHEN( "a single GNDS legendre node with an outer domain value is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readLegendre( legendre );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readLegendre( legendre.child( "values" ) ) );    // wrong node
        CHECK_THROWS( format::gnds::readLegendre( legendre.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::pair< std::optional< double >, std::vector< double > >& chunk ) {

  // outer domain value and unit
  CHECK( 1e-5 == chunk.first );

  // values
  CHECK( 7 == chunk.second.size() );
  CHECK_THAT( 1.         , WithinRel( chunk.second[0] ) );
  CHECK_THAT( 3.93859e-18, WithinRel( chunk.second[6] ) );
}
