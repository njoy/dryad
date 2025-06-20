// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/format/gnds/readAxes.hpp"

// other includes
#include "pugixml.hpp"
#include <iostream>
// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const format::gnds::Axes& );
void verifyChunkWithIndex2( const format::gnds::Axes& );
void verifyChunkWithGrid( const format::gnds::Axes& );

SCENARIO( "readAxes" ) {

  GIVEN( "a GNDS axes xml node with axis" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "reactions" );

    WHEN( "a single GNDS axes node without an axis with index 2" ) {

      pugi::xml_node axes = reactions.child( "reaction" ).child( "crossSection" ).
                                      child( "XYs1d" ).child( "axes" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readAxes( axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single GNDS axes node with an axis with index 2" ) {

      pugi::xml_node axes = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                      child( "outputChannel" ).child( "products" ).
                                      child( "product" ).child( "distribution" ).
                                      child( "angularTwoBody" ).child( "XYs2d" ).child( "axes" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readAxes( axes );

        verifyChunkWithIndex2( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readAxes( reactions ) );                      // wrong node
        CHECK_THROWS( format::gnds::readAxes( reactions.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS axes xml node with grid" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node node = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                   find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                   child( "mixed" ).child( "shortRangeSelfScalingVariance" ).
                                   child( "gridded2d" );

    WHEN( "a single GNDS axes node" ) {

      pugi::xml_node axes = node.child( "axes" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readAxes( axes );

        verifyChunkWithGrid( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readAxes( node ) );                      // wrong node
        CHECK_THROWS( format::gnds::readAxes( node.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::Axes& chunk ) {

  CHECK( 2 == chunk.size() );
  CHECK( 1  == std::get< 0 >( chunk[0] ).value() );
  CHECK( 0  == std::get< 0 >( chunk[1] ).value() );
  CHECK( "eV" == std::get< 1 >( chunk[0] ).value() );
  CHECK( "b"  == std::get< 1 >( chunk[1] ).value() );
  CHECK( std::nullopt == std::get< 2 >( chunk[0] ) );
  CHECK( std::nullopt == std::get< 2 >( chunk[1] ) );
}

void verifyChunkWithIndex2( const format::gnds::Axes& chunk ) {

  CHECK( 3 == chunk.size() );
  CHECK( 2  == std::get< 0 >( chunk[0] ).value() );
  CHECK( 1  == std::get< 0 >( chunk[1] ).value() );
  CHECK( 0  == std::get< 0 >( chunk[2] ).value() );
  CHECK( "eV" == std::get< 1 >( chunk[0] ).value() );
  CHECK( ""   == std::get< 1 >( chunk[1] ).value() );
  CHECK( ""   == std::get< 1 >( chunk[2] ).value() );
  CHECK( std::nullopt == std::get< 2 >( chunk[0] ) );
  CHECK( std::nullopt == std::get< 2 >( chunk[1] ) );
  CHECK( std::nullopt == std::get< 2 >( chunk[2] ) );
}

void verifyChunkWithGrid( const format::gnds::Axes& chunk ) {

  CHECK( 3 == chunk.size() );

}
