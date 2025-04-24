// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/readArray.hpp"

// other includes
#include "pugixml.hpp"
#include <iostream>
// convenience typedefs
using namespace njoy::dryad;

void verifyDiagonalChunk( const covariance::Matrix< double >& );
void verifyLowerSymmetricChunk( const covariance::Matrix< double >& );

SCENARIO( "readArray" ) {

  GIVEN( "a GNDS grid array node for a diagonal compressed array" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node gridded = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                      find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                      child( "mixed" ).child( "shortRangeSelfScalingVariance" ).
                                      child( "gridded2d" );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = gridded.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readArray( array );

        verifyDiagonalChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readArray( gridded ) );                      // wrong node
        CHECK_THROWS( format::gnds::readArray( gridded.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS grid array node for a lower diagonal symmetric array" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node gridded = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                      find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                      child( "mixed" ).find_child_by_attribute( "covarianceMatrix", "label", "1" ).
                                      child( "gridded2d" );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = gridded.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readArray( array );

        verifyLowerSymmetricChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readArray( gridded ) );                      // wrong node
        CHECK_THROWS( format::gnds::readArray( gridded.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyDiagonalChunk( const covariance::Matrix< double >& chunk ) {

  CHECK( 12 == chunk.rows() );
  CHECK( 12 == chunk.rows() );

  for ( unsigned int i = 0; i < chunk.rows(); ++i ) {

    for ( unsigned int j = 0; j < chunk.cols(); ++j ) {

      if ( i != j ) {

        CHECK( 0. == chunk(i,j) );
      }
    }
  }

  CHECK_THAT( 0        , WithinRel( chunk(0,0) ) );
  CHECK_THAT( 2.2235e-6, WithinRel( chunk(1,1) ) );
  CHECK_THAT( 5.1343e-5, WithinRel( chunk(2,2) ) );
  CHECK_THAT( 1.4699e-5, WithinRel( chunk(3,3) ) );
  CHECK_THAT( 2.5148e-6, WithinRel( chunk(4,4) ) );
  CHECK_THAT( 4.8846e-6, WithinRel( chunk(5,5) ) );
  CHECK_THAT( 2.1413e-6, WithinRel( chunk(6,6) ) );
  CHECK_THAT( 1.3654e-6, WithinRel( chunk(7,7) ) );
  CHECK_THAT( 8.5116e-7, WithinRel( chunk(8,8) ) );
  CHECK_THAT( 3.4763e-7, WithinRel( chunk(9,9) ) );
  CHECK_THAT( 2.9932e-8, WithinRel( chunk(10,10) ) );
  CHECK_THAT( 4.1382e-9, WithinRel( chunk(11,11) ) );
}

void verifyLowerSymmetricChunk( const covariance::Matrix< double >& chunk ) {

  CHECK( 6 == chunk.rows() );
  CHECK( 6 == chunk.rows() );

  CHECK_THAT( 0., WithinRel( chunk(0,0) ) );
  CHECK_THAT( 0., WithinRel( chunk(0,1) ) );
  CHECK_THAT( 0., WithinRel( chunk(0,2) ) );
  CHECK_THAT( 0., WithinRel( chunk(0,3) ) );
  CHECK_THAT( 0., WithinRel( chunk(0,4) ) );
  CHECK_THAT( 0., WithinRel( chunk(0,5) ) );

  CHECK_THAT( 0., WithinRel( chunk(1,0) ) );
  CHECK_THAT( 1.251800e-2, WithinRel( chunk(1,1) ) );
  CHECK_THAT( 1.372900e-2, WithinRel( chunk(1,2) ) );
  CHECK_THAT( 3.462100e-3, WithinRel( chunk(1,3) ) );
  CHECK_THAT( 4.176900e-3, WithinRel( chunk(1,4) ) );
  CHECK_THAT( 3.404000e-3, WithinRel( chunk(1,5) ) );

  CHECK_THAT( 0., WithinRel( chunk(2,0) ) );
  CHECK_THAT( 1.372900e-2, WithinRel( chunk(2,1) ) );
  CHECK_THAT( 1.557300e-2, WithinRel( chunk(2,2) ) );
  CHECK_THAT( 5.634300e-3, WithinRel( chunk(2,3) ) );
  CHECK_THAT( 5.288200e-3, WithinRel( chunk(2,4) ) );
  CHECK_THAT( 3.863500e-3, WithinRel( chunk(2,5) ) );

  CHECK_THAT( 0., WithinRel( chunk(3,0) ) );
  CHECK_THAT( 3.462100e-3, WithinRel( chunk(3,1) ) );
  CHECK_THAT( 5.634300e-3, WithinRel( chunk(3,2) ) );
  CHECK_THAT( 8.970100e-3, WithinRel( chunk(3,3) ) );
  CHECK_THAT( 4.898600e-3, WithinRel( chunk(3,4) ) );
  CHECK_THAT( 1.896700e-3, WithinRel( chunk(3,5) ) );

  CHECK_THAT( 0., WithinRel( chunk(4,0) ) );
  CHECK_THAT( 4.176900e-3, WithinRel( chunk(4,1) ) );
  CHECK_THAT( 5.288200e-3, WithinRel( chunk(4,2) ) );
  CHECK_THAT( 4.898600e-3, WithinRel( chunk(4,3) ) );
  CHECK_THAT( 3.694600e-3, WithinRel( chunk(4,4) ) );
  CHECK_THAT( 1.726800e-3, WithinRel( chunk(4,5) ) );

  CHECK_THAT( 0., WithinRel( chunk(5,0) ) );
  CHECK_THAT( 3.404000e-3, WithinRel( chunk(5,1) ) );
  CHECK_THAT( 3.863500e-3, WithinRel( chunk(5,2) ) );
  CHECK_THAT( 1.896700e-3, WithinRel( chunk(5,3) ) );
  CHECK_THAT( 1.726800e-3, WithinRel( chunk(5,4) ) );
  CHECK_THAT( 1.144800e-3, WithinRel( chunk(5,5) ) );
}
