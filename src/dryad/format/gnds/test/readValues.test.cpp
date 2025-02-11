// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/readValues.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const std::vector< double >& );

SCENARIO( "readXYs1D" ) {

  GIVEN( "a GNDS values xml nodes" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "reactions" );

    WHEN( "a single GNDS values node" ) {

      pugi::xml_node values = reactions.child( "reaction" ).child( "crossSection" ).
                                        child( "XYs1d" ).child( "values" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readValues( values );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< double >& chunk ) {

 CHECK( 202 == chunk.size() );

 CHECK_THAT( 10.       , WithinRel( chunk[0] ) );
 CHECK_THAT( 2.74896e+8, WithinRel( chunk[1] ) );
 CHECK_THAT( 1e+11     , WithinRel( chunk[200] ) );
 CHECK_THAT( 12987.1   , WithinRel( chunk[201] ) );
}
