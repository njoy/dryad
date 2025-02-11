// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/readXYs1d.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const format::gnds::XYs1d& );
void verifyChunkWithOuterDomain( const format::gnds::XYs1d& );

SCENARIO( "readXYs1D" ) {

  GIVEN( "a GNDS xys1d xml nodes" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "reactions" );

    WHEN( "a single GNDS xys1d node without an outer domain value is given" ) {

      pugi::xml_node xys1d = reactions.child( "reaction" ).child( "crossSection" ).
                                       child( "XYs1d" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readXYs1D( xys1d );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::XYs1d& chunk ) {

  // outer domain value and unit
  CHECK( std::nullopt == std::get< 0 >( chunk ) );
  CHECK( std::nullopt == std::get< 1 >( chunk ) );

  // interpolation type
  CHECK( "" == std::get< 6 >( chunk ) );

  // x and y units
  CHECK( "eV" == std::get< 3 >( chunk ) );
  CHECK( "b"  == std::get< 5 >( chunk ) );

  // x and y values
  CHECK( 101 == std::get< 2 >( chunk ).size() );
  CHECK( 101 == std::get< 4 >( chunk ).size() );
  CHECK_THAT( 10.       , WithinRel( std::get< 2 >( chunk )[0] ) );
  CHECK_THAT( 1e+11     , WithinRel( std::get< 2 >( chunk )[100] ) );
  CHECK_THAT( 2.74896e+8, WithinRel( std::get< 4 >( chunk )[0] ) );
  CHECK_THAT( 12987.1   , WithinRel( std::get< 4 >( chunk )[100] ) );
}
