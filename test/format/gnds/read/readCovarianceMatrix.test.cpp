// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readCovarianceMatrix.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyFissionChunk( const gnds::read::CovarianceMatrix& );

SCENARIO( "readCovarianceMatrix" ) {

  GIVEN( "GNDS covariance matrix node" ) {

    pugi::xml_document document;
    document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node sections = document.child( "covarianceSuite" ).child( "covarianceSections" );

    WHEN( "a single covarianceMatrix node is given for a diagonal matrix" ) {

      pugi::xml_node covariance = sections.find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                           child( "mixed" ).
                                           find_child_by_attribute( "covarianceMatrix", "label", "0" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readCovarianceMatrix( covariance );

        CHECK( true == chunk.relative );

        CHECK( 9 == chunk.row_structure.size() );
        CHECK_THAT( 1e-5  , WithinRel( chunk.row_structure[0] ) );
        CHECK_THAT( 115840, WithinRel( chunk.row_structure[1] ) );
        CHECK_THAT( 207460, WithinRel( chunk.row_structure[2] ) );
        CHECK_THAT( 3e5   , WithinRel( chunk.row_structure[3] ) );
        CHECK_THAT( 4.5e5 , WithinRel( chunk.row_structure[4] ) );
        CHECK_THAT( 6e5   , WithinRel( chunk.row_structure[5] ) );
        CHECK_THAT( 1.1e6 , WithinRel( chunk.row_structure[6] ) );
        CHECK_THAT( 1.5e6 , WithinRel( chunk.row_structure[7] ) );
        CHECK_THAT( 2e7   , WithinRel( chunk.row_structure[8] ) );

        CHECK( 9 == chunk.column_structure.size() );
        CHECK_THAT( 1e-5  , WithinRel( chunk.column_structure[0] ) );
        CHECK_THAT( 115840, WithinRel( chunk.column_structure[1] ) );
        CHECK_THAT( 207460, WithinRel( chunk.column_structure[2] ) );
        CHECK_THAT( 3e5   , WithinRel( chunk.column_structure[3] ) );
        CHECK_THAT( 4.5e5 , WithinRel( chunk.column_structure[4] ) );
        CHECK_THAT( 6e5   , WithinRel( chunk.column_structure[5] ) );
        CHECK_THAT( 1.1e6 , WithinRel( chunk.column_structure[6] ) );
        CHECK_THAT( 1.5e6 , WithinRel( chunk.column_structure[7] ) );
        CHECK_THAT( 2e7   , WithinRel( chunk.column_structure[8] ) );

        CHECK( 8 == chunk.matrix.rows() );
        CHECK( 8 == chunk.matrix.cols() );
        for ( unsigned int i = 0; i < chunk.matrix.rows(); ++i ) {

          for ( unsigned int j = 0; j < chunk.matrix.cols(); ++j ) {

            if ( i != j ) {

              CHECK( 0. == chunk.matrix(i,j) );
            }
          }
        }
        CHECK_THAT( 0     , WithinRel( chunk.matrix(0,0) ) );
        CHECK_THAT( 4e-2  , WithinRel( chunk.matrix(1,1) ) );
        CHECK_THAT( 0.0625, WithinRel( chunk.matrix(2,2) ) );
        CHECK_THAT( 4e-2  , WithinRel( chunk.matrix(3,3) ) );
        CHECK_THAT( 0.0225, WithinRel( chunk.matrix(4,4) ) );
        CHECK_THAT( 4e-2  , WithinRel( chunk.matrix(5,5) ) );
        CHECK_THAT( 0.0225, WithinRel( chunk.matrix(6,6) ) );
        CHECK_THAT( 0     , WithinRel( chunk.matrix(7,7) ) );

        CHECK( "eV" == chunk.row_unit );
        CHECK( "eV" == chunk.column_unit );
        CHECK( std::nullopt == chunk.covariance_unit );
      } // THEN
    } // WHEN

    WHEN( "a single covarianceMatrix node is given for a lower symmetric matrix" ) {

      pugi::xml_node covariance = sections.find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                           child( "mixed" ).
                                           find_child_by_attribute( "covarianceMatrix", "label", "1" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readCovarianceMatrix( covariance );

        CHECK( true == chunk.relative );

        CHECK( 7 == chunk.row_structure.size() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.row_structure[0] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( chunk.row_structure[1] ) );
        CHECK_THAT( 3.000000e+6, WithinRel( chunk.row_structure[2] ) );
        CHECK_THAT( 6.000000e+6, WithinRel( chunk.row_structure[3] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( chunk.row_structure[4] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.row_structure[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.row_structure[6] ) );

        CHECK( 7 == chunk.column_structure.size() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.column_structure[0] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( chunk.column_structure[1] ) );
        CHECK_THAT( 3.000000e+6, WithinRel( chunk.column_structure[2] ) );
        CHECK_THAT( 6.000000e+6, WithinRel( chunk.column_structure[3] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( chunk.column_structure[4] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.column_structure[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.column_structure[6] ) );

        CHECK( 6 == chunk.matrix.rows() );
        CHECK( 6 == chunk.matrix.cols() );
        CHECK_THAT( 0., WithinRel( chunk.matrix(0,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(0,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(0,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(0,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(0,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(0,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(1,0) ) );
        CHECK_THAT( 1.251800e-2, WithinRel( chunk.matrix(1,1) ) );
        CHECK_THAT( 1.372900e-2, WithinRel( chunk.matrix(1,2) ) );
        CHECK_THAT( 3.462100e-3, WithinRel( chunk.matrix(1,3) ) );
        CHECK_THAT( 4.176900e-3, WithinRel( chunk.matrix(1,4) ) );
        CHECK_THAT( 3.404000e-3, WithinRel( chunk.matrix(1,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(2,0) ) );
        CHECK_THAT( 1.372900e-2, WithinRel( chunk.matrix(2,1) ) );
        CHECK_THAT( 1.557300e-2, WithinRel( chunk.matrix(2,2) ) );
        CHECK_THAT( 5.634300e-3, WithinRel( chunk.matrix(2,3) ) );
        CHECK_THAT( 5.288200e-3, WithinRel( chunk.matrix(2,4) ) );
        CHECK_THAT( 3.863500e-3, WithinRel( chunk.matrix(2,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(3,0) ) );
        CHECK_THAT( 3.462100e-3, WithinRel( chunk.matrix(3,1) ) );
        CHECK_THAT( 5.634300e-3, WithinRel( chunk.matrix(3,2) ) );
        CHECK_THAT( 8.970100e-3, WithinRel( chunk.matrix(3,3) ) );
        CHECK_THAT( 4.898600e-3, WithinRel( chunk.matrix(3,4) ) );
        CHECK_THAT( 1.896700e-3, WithinRel( chunk.matrix(3,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(4,0) ) );
        CHECK_THAT( 4.176900e-3, WithinRel( chunk.matrix(4,1) ) );
        CHECK_THAT( 5.288200e-3, WithinRel( chunk.matrix(4,2) ) );
        CHECK_THAT( 4.898600e-3, WithinRel( chunk.matrix(4,3) ) );
        CHECK_THAT( 3.694600e-3, WithinRel( chunk.matrix(4,4) ) );
        CHECK_THAT( 1.726800e-3, WithinRel( chunk.matrix(4,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.matrix(5,0) ) );
        CHECK_THAT( 3.404000e-3, WithinRel( chunk.matrix(5,1) ) );
        CHECK_THAT( 3.863500e-3, WithinRel( chunk.matrix(5,2) ) );
        CHECK_THAT( 1.896700e-3, WithinRel( chunk.matrix(5,3) ) );
        CHECK_THAT( 1.726800e-3, WithinRel( chunk.matrix(5,4) ) );
        CHECK_THAT( 1.144800e-3, WithinRel( chunk.matrix(5,5) ) );

        CHECK( "eV" == chunk.row_unit );
        CHECK( "eV" == chunk.column_unit );
        CHECK( std::nullopt == chunk.covariance_unit );
      } // THEN
    } // WHEN

    WHEN( "a single covarianceMatrix node is given using an array with only a shape" ) {

      pugi::xml_node covariance = sections.find_child_by_attribute( "covarianceSection", "label", "(z,n) vs. n + n + F18 + photon" ).
                                           child( "covarianceMatrix" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readCovarianceMatrix( covariance );

        CHECK( true == chunk.relative );

        CHECK( 7 == chunk.row_structure.size() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.row_structure[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.row_structure[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.row_structure[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.row_structure[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.row_structure[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.row_structure[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.row_structure[6] ) );

        CHECK( 7 == chunk.column_structure.size() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.column_structure[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.column_structure[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.column_structure[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.column_structure[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.column_structure[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.column_structure[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.column_structure[6] ) );

        CHECK( 6 == chunk.matrix.rows() );
        CHECK( 6 == chunk.matrix.cols() );
        CHECK_THAT(  0., WithinRel( chunk.matrix(0,0) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(0,1) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(0,2) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(0,3) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(0,4) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(0,5) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(1,0) ) );
        CHECK_THAT( -2.732300e-3, WithinRel( chunk.matrix(1,1) ) );
        CHECK_THAT( -8.431200e-4, WithinRel( chunk.matrix(1,2) ) );
        CHECK_THAT(  1.625000e-3, WithinRel( chunk.matrix(1,3) ) );
        CHECK_THAT(  2.647600e-3, WithinRel( chunk.matrix(1,4) ) );
        CHECK_THAT(  4.939500e-3, WithinRel( chunk.matrix(1,5) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(2,0) ) );
        CHECK_THAT( -1.625700e-3, WithinRel( chunk.matrix(2,1) ) );
        CHECK_THAT( -3.558100e-4, WithinRel( chunk.matrix(2,2) ) );
        CHECK_THAT(  1.459800e-3, WithinRel( chunk.matrix(2,3) ) );
        CHECK_THAT(  2.437400e-3, WithinRel( chunk.matrix(2,4) ) );
        CHECK_THAT(  3.772000e-3, WithinRel( chunk.matrix(2,5) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(3,0) ) );
        CHECK_THAT( -2.314700e-4, WithinRel( chunk.matrix(3,1) ) );
        CHECK_THAT(  3.051500e-4, WithinRel( chunk.matrix(3,2) ) );
        CHECK_THAT(  1.292200e-3, WithinRel( chunk.matrix(3,3) ) );
        CHECK_THAT(  2.152300e-3, WithinRel( chunk.matrix(3,4) ) );
        CHECK_THAT(  2.538300e-3, WithinRel( chunk.matrix(3,5) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(4,0) ) );
        CHECK_THAT(  3.229600e-4, WithinRel( chunk.matrix(4,1) ) );
        CHECK_THAT(  6.356200e-4, WithinRel( chunk.matrix(4,2) ) );
        CHECK_THAT(  1.308700e-3, WithinRel( chunk.matrix(4,3) ) );
        CHECK_THAT(  1.986300e-3, WithinRel( chunk.matrix(4,4) ) );
        CHECK_THAT(  2.439300e-3, WithinRel( chunk.matrix(4,5) ) );
        CHECK_THAT(  0., WithinRel( chunk.matrix(5,0) ) );
        CHECK_THAT(  4.981700e-4, WithinRel( chunk.matrix(5,1) ) );
        CHECK_THAT(  8.811700e-4, WithinRel( chunk.matrix(5,2) ) );
        CHECK_THAT(  1.559200e-3, WithinRel( chunk.matrix(5,3) ) );
        CHECK_THAT(  2.135100e-3, WithinRel( chunk.matrix(5,4) ) );
        CHECK_THAT(  2.953900e-3, WithinRel( chunk.matrix(5,5) ) );

        CHECK( "eV" == chunk.row_unit );
        CHECK( "eV" == chunk.column_unit );
        CHECK( std::nullopt == chunk.covariance_unit );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readAxis( sections ) );                      // wrong node
        CHECK_THROWS( gnds::read::readAxis( sections.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
