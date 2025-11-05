// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createQValue.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( double );

SCENARIO( "createQValue" ) {

  GIVEN( "GNDS Q value node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node q = document.child( "reactionSuite" ).child( "reactions" ).
                                find_child_by_attribute( "reaction", "ENDF_MT", "534" ).
                                child( "outputChannel" ).child( "Q" );

    WHEN( "a single Q value node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createQValue( q );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( double chunk ) {

  CHECK_THAT( -13.6, WithinRel( chunk ) );
}
