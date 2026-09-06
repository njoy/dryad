// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readGrid.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyChunk( const gnds::read::Grid&, int index );

SCENARIO( "readAxes" ) {

  GIVEN( "a GNDS grid xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node axes = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                   find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                   child( "mixed" ).child( "shortRangeSelfScalingVariance" ).
                                   child( "gridded2d" ).child( "axes" );

    WHEN( "a single GNDS grid node with a values node is used" ) {

      pugi::xml_node grid = axes.find_child_by_attribute( "grid", "index", "2" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readGrid( grid );

        verifyChunk( chunk, 2 );
      } // THEN
    } // WHEN

    WHEN( "a single GNDS grid node with a link node is used" ) {

      pugi::xml_node grid = axes.find_child_by_attribute( "grid", "index", "1" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readGrid( grid );

        verifyChunk( chunk, 1 );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readGrid( axes ) );                      // wrong node
        CHECK_THROWS( gnds::read::readGrid( axes.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const gnds::read::Grid& chunk, int index ) {

  CHECK( index == chunk.index );
  CHECK( "eV"  == chunk.unit );

  CHECK( 13 == chunk.values.size() );

  CHECK_THAT( 1e-5   , WithinRel( chunk.values[0] ) );
  CHECK_THAT( 115840 , WithinRel( chunk.values[1] ) );
  CHECK_THAT( 207460 , WithinRel( chunk.values[2] ) );
  CHECK_THAT( 3e5    , WithinRel( chunk.values[3] ) );
  CHECK_THAT( 4.5e5  , WithinRel( chunk.values[4] ) );
  CHECK_THAT( 6e5    , WithinRel( chunk.values[5] ) );
  CHECK_THAT( 1.1e6  , WithinRel( chunk.values[6] ) );
  CHECK_THAT( 1.5e6  , WithinRel( chunk.values[7] ) );
  CHECK_THAT( 3e6    , WithinRel( chunk.values[8] ) );
  CHECK_THAT( 6e6    , WithinRel( chunk.values[9] ) );
  CHECK_THAT( 1e7    , WithinRel( chunk.values[10] ) );
  CHECK_THAT( 1.4e7  , WithinRel( chunk.values[11] ) );
  CHECK_THAT( 2e7    , WithinRel( chunk.values[12] ) );
}
