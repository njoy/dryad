// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readTable.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyChunk( const gnds::read::Table& );

SCENARIO( "readTable" ) {

  GIVEN( "a GNDS table xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node parameters = document.child( "reactionSuite" ).child( "resonances" ).
                                         child( "resolved" ).child( "RMatrix" ).
                                         child( "spinGroups" ).child( "spinGroup" ).
                                         child( "resonanceParameters" );

    WHEN( "a single GNDS table node" ) {

      pugi::xml_node table = parameters.child( "table" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readTable( table );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readTable( parameters ) );                      // wrong node
        CHECK_THROWS( gnds::read::readTable( parameters.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const gnds::read::Table& chunk ) {

  CHECK( 3 == chunk.size() );

  CHECK( "energy"                          == chunk[0].name );
  CHECK( "Al28 + photon [inclusive] width" == chunk[1].name );
  CHECK( "n + Al27 width"                  == chunk[2].name );

  CHECK( 10 == chunk[0].values.size() );
  CHECK_THAT( -4585600, WithinRel( chunk[0].values[0] ) );
  CHECK_THAT( 1.63e6  , WithinRel( chunk[0].values[9] ) );
  CHECK( 10 == chunk[1].values.size() );
  CHECK_THAT( 0.99675 , WithinRel( chunk[1].values[0] ) );
  CHECK_THAT( 2       , WithinRel( chunk[1].values[9] ) );
  CHECK( 10 == chunk[2].values.size() );
  CHECK_THAT( 3291200 , WithinRel( chunk[2].values[0] ) );
  CHECK_THAT( 37262   , WithinRel( chunk[2].values[9] ) );

  CHECK( "eV" == chunk[0].unit.value() );
  CHECK( "eV" == chunk[1].unit.value() );
  CHECK( "eV" == chunk[2].unit.value() );
}
