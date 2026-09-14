// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/format/gnds/read/readAxes.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyChunk( const gnds::read::Axes& );
void verifyChunkWithIndex2( const gnds::read::Axes& );
void verifyChunkWithGrid( const gnds::read::Axes& );

SCENARIO( "readAxes" ) {

  GIVEN( "a GNDS axes xml node with axis" ) {

    pugi::xml_document document;
    document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "reactions" );

    WHEN( "a single GNDS axes node without an axis with index 2" ) {

      pugi::xml_node axes = reactions.child( "reaction" ).child( "crossSection" ).
                                      child( "XYs1d" ).child( "axes" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readAxes( axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single GNDS axes node with an axis with index 2" ) {

      pugi::xml_node axes = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                      child( "outputChannel" ).child( "products" ).
                                      child( "product" ).child( "distribution" ).
                                      child( "angularTwoBody" ).child( "XYs2d" ).child( "axes" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readAxes( axes );

        verifyChunkWithIndex2( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readAxes( reactions ) );                      // wrong node
        CHECK_THROWS( gnds::read::readAxes( reactions.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS axes xml node with grid" ) {

    pugi::xml_document document;
    document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node node = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                   find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                   child( "mixed" ).child( "shortRangeSelfScalingVariance" ).
                                   child( "gridded2d" );

    WHEN( "a single GNDS axes node" ) {

      pugi::xml_node axes = node.child( "axes" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readAxes( axes );

        verifyChunkWithGrid( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readAxes( node ) );                      // wrong node
        CHECK_THROWS( gnds::read::readAxes( node.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const gnds::read::Axes& chunk ) {

  CHECK( 2 == chunk.size() );
  CHECK( 1  == chunk[0].index.value() );
  CHECK( 0  == chunk[1].index.value() );
  CHECK( "eV" == chunk[0].unit.value() );
  CHECK( "b"  == chunk[1].unit.value() );
  CHECK( std::nullopt == chunk[0].values );
  CHECK( std::nullopt == chunk[1].values );
}

void verifyChunkWithIndex2( const gnds::read::Axes& chunk ) {

  CHECK( 3 == chunk.size() );
  CHECK( 2  == chunk[0].index.value() );
  CHECK( 1  == chunk[1].index.value() );
  CHECK( 0  == chunk[2].index.value() );
  CHECK( "eV" == chunk[0].unit.value() );
  CHECK( std::nullopt == chunk[1].unit );
  CHECK( std::nullopt == chunk[2].unit );
  CHECK( std::nullopt == chunk[0].values );
  CHECK( std::nullopt == chunk[1].values );
  CHECK( std::nullopt == chunk[2].values );
}

void verifyChunkWithGrid( const gnds::read::Axes& chunk ) {

  CHECK( 3 == chunk.size() );
}
