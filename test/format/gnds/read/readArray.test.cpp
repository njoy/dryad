// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readArray.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyDiagonalChunk( const gnds::read::Array& );
void verifyLowerSymmetricChunk( const gnds::read::Array& );

SCENARIO( "readArray" ) {

  GIVEN( "a GNDS grid array node for a diagonal compressed array" ) {

    pugi::xml_document document;
    document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node gridded = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                      find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                      child( "mixed" ).child( "shortRangeSelfScalingVariance" ).
                                      child( "gridded2d" );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = gridded.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyDiagonalChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readArray( gridded ) );                      // wrong node
        CHECK_THROWS( gnds::read::readArray( gridded.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS grid array node for a lower diagonal symmetric array" ) {

    pugi::xml_document document;
    document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node gridded = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                      find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                      child( "mixed" ).find_child_by_attribute( "covarianceMatrix", "label", "1" ).
                                      child( "gridded2d" );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = gridded.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyLowerSymmetricChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readArray( gridded ) );                      // wrong node
        CHECK_THROWS( gnds::read::readArray( gridded.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyDiagonalChunk( const gnds::read::Array& chunk ) {

  CHECK( 12 == chunk.shape[0] );
  CHECK( 12 == chunk.shape[1] );
  CHECK( 144 == chunk.values.size() );

  for ( unsigned int i = 0; i < 12; ++i ) {

    for ( unsigned int j = 0; j < 12; ++j ) {

      if ( i != j ) {

        CHECK( 0. == chunk.values[i + j * 12] );
      }
    }
  }

  CHECK_THAT( 0        , WithinRel( chunk.values[0 + 0 * 12] ) );
  CHECK_THAT( 2.2235e-6, WithinRel( chunk.values[1 + 1 * 12] ) );
  CHECK_THAT( 5.1343e-5, WithinRel( chunk.values[2 + 2 * 12] ) );
  CHECK_THAT( 1.4699e-5, WithinRel( chunk.values[3 + 3 * 12] ) );
  CHECK_THAT( 2.5148e-6, WithinRel( chunk.values[4 + 4 * 12] ) );
  CHECK_THAT( 4.8846e-6, WithinRel( chunk.values[5 + 5 * 12] ) );
  CHECK_THAT( 2.1413e-6, WithinRel( chunk.values[6 + 6 * 12] ) );
  CHECK_THAT( 1.3654e-6, WithinRel( chunk.values[7 + 7 * 12] ) );
  CHECK_THAT( 8.5116e-7, WithinRel( chunk.values[8 + 8 * 12] ) );
  CHECK_THAT( 3.4763e-7, WithinRel( chunk.values[9 + 9 * 12] ) );
  CHECK_THAT( 2.9932e-8, WithinRel( chunk.values[10 + 10 * 12] ) );
  CHECK_THAT( 4.1382e-9, WithinRel( chunk.values[11 + 11 * 12] ) );
}

void verifyLowerSymmetricChunk( const gnds::read::Array& chunk ) {

  CHECK( 6 == chunk.shape[0] );
  CHECK( 6 == chunk.shape[1] );
  CHECK( 36 == chunk.values.size() );

  CHECK_THAT( 0., WithinRel( chunk.values[0 + 0 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 1 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 2 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 3 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 4 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[1 + 0 * 6] ) );
  CHECK_THAT( 1.251800e-2, WithinRel( chunk.values[1 + 1 * 6] ) );
  CHECK_THAT( 1.372900e-2, WithinRel( chunk.values[1 + 2 * 6] ) );
  CHECK_THAT( 3.462100e-3, WithinRel( chunk.values[1 + 3 * 6] ) );
  CHECK_THAT( 4.176900e-3, WithinRel( chunk.values[1 + 4 * 6] ) );
  CHECK_THAT( 3.404000e-3, WithinRel( chunk.values[1 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[2 + 0 * 6] ) );
  CHECK_THAT( 1.372900e-2, WithinRel( chunk.values[2 + 1 * 6] ) );
  CHECK_THAT( 1.557300e-2, WithinRel( chunk.values[2 + 2 * 6] ) );
  CHECK_THAT( 5.634300e-3, WithinRel( chunk.values[2 + 3 * 6] ) );
  CHECK_THAT( 5.288200e-3, WithinRel( chunk.values[2 + 4 * 6] ) );
  CHECK_THAT( 3.863500e-3, WithinRel( chunk.values[2 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[3 + 0 * 6] ) );
  CHECK_THAT( 3.462100e-3, WithinRel( chunk.values[3 + 1 * 6] ) );
  CHECK_THAT( 5.634300e-3, WithinRel( chunk.values[3 + 2 * 6] ) );
  CHECK_THAT( 8.970100e-3, WithinRel( chunk.values[3 + 3 * 6] ) );
  CHECK_THAT( 4.898600e-3, WithinRel( chunk.values[3 + 4 * 6] ) );
  CHECK_THAT( 1.896700e-3, WithinRel( chunk.values[3 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[4 + 0 * 6] ) );
  CHECK_THAT( 4.176900e-3, WithinRel( chunk.values[4 + 1 * 6] ) );
  CHECK_THAT( 5.288200e-3, WithinRel( chunk.values[4 + 2 * 6] ) );
  CHECK_THAT( 4.898600e-3, WithinRel( chunk.values[4 + 3 * 6] ) );
  CHECK_THAT( 3.694600e-3, WithinRel( chunk.values[4 + 4 * 6] ) );
  CHECK_THAT( 1.726800e-3, WithinRel( chunk.values[4 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[5 + 0 * 6] ) );
  CHECK_THAT( 3.404000e-3, WithinRel( chunk.values[5 + 1 * 6] ) );
  CHECK_THAT( 3.863500e-3, WithinRel( chunk.values[5 + 2 * 6] ) );
  CHECK_THAT( 1.896700e-3, WithinRel( chunk.values[5 + 3 * 6] ) );
  CHECK_THAT( 1.726800e-3, WithinRel( chunk.values[5 + 4 * 6] ) );
  CHECK_THAT( 1.144800e-3, WithinRel( chunk.values[5 + 5 * 6] ) );
}
