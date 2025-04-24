// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/readCovarianceMatrix.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyFissionChunk( const format::gnds::CovarianceMatrix& );

SCENARIO( "readCovarianceMatrix" ) {

  GIVEN( "GNDS covariance matrix node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node sections = document.child( "covarianceSuite" ).child( "covarianceSections" );

    WHEN( "a single covarianceMatrix node is given for a diagonal matrix" ) {

      pugi::xml_node covariance = sections.find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                           child( "mixed" ).
                                           find_child_by_attribute( "covarianceMatrix", "label", "0" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readCovarianceMatrix( covariance );

        CHECK( true == std::get< 0 >( chunk ) );

        CHECK( 9 == std::get< 1 >( chunk ).size() );
        CHECK_THAT( 1e-5  , WithinRel( std::get< 1 >( chunk )[0] ) );
        CHECK_THAT( 115840, WithinRel( std::get< 1 >( chunk )[1] ) );
        CHECK_THAT( 207460, WithinRel( std::get< 1 >( chunk )[2] ) );
        CHECK_THAT( 3e5   , WithinRel( std::get< 1 >( chunk )[3] ) );
        CHECK_THAT( 4.5e5 , WithinRel( std::get< 1 >( chunk )[4] ) );
        CHECK_THAT( 6e5   , WithinRel( std::get< 1 >( chunk )[5] ) );
        CHECK_THAT( 1.1e6 , WithinRel( std::get< 1 >( chunk )[6] ) );
        CHECK_THAT( 1.5e6 , WithinRel( std::get< 1 >( chunk )[7] ) );
        CHECK_THAT( 2e7   , WithinRel( std::get< 1 >( chunk )[8] ) );

        CHECK( 9 == std::get< 2 >( chunk ).size() );
        CHECK_THAT( 1e-5  , WithinRel( std::get< 2 >( chunk )[0] ) );
        CHECK_THAT( 115840, WithinRel( std::get< 2 >( chunk )[1] ) );
        CHECK_THAT( 207460, WithinRel( std::get< 2 >( chunk )[2] ) );
        CHECK_THAT( 3e5   , WithinRel( std::get< 2 >( chunk )[3] ) );
        CHECK_THAT( 4.5e5 , WithinRel( std::get< 2 >( chunk )[4] ) );
        CHECK_THAT( 6e5   , WithinRel( std::get< 2 >( chunk )[5] ) );
        CHECK_THAT( 1.1e6 , WithinRel( std::get< 2 >( chunk )[6] ) );
        CHECK_THAT( 1.5e6 , WithinRel( std::get< 2 >( chunk )[7] ) );
        CHECK_THAT( 2e7   , WithinRel( std::get< 2 >( chunk )[8] ) );

        CHECK( 8 == std::get< 3 >( chunk ).rows() );
        CHECK( 8 == std::get< 3 >( chunk ).cols() );
        for ( unsigned int i = 0; i < std::get< 3 >( chunk ).rows(); ++i ) {

          for ( unsigned int j = 0; j < std::get< 3 >( chunk ).cols(); ++j ) {

            if ( i != j ) {

              CHECK( 0. == std::get< 3 >( chunk )(i,j) );
            }
          }
        }
        CHECK_THAT( 0     , WithinRel( std::get< 3 >( chunk )(0,0) ) );
        CHECK_THAT( 4e-2  , WithinRel( std::get< 3 >( chunk )(1,1) ) );
        CHECK_THAT( 0.0625, WithinRel( std::get< 3 >( chunk )(2,2) ) );
        CHECK_THAT( 4e-2  , WithinRel( std::get< 3 >( chunk )(3,3) ) );
        CHECK_THAT( 0.0225, WithinRel( std::get< 3 >( chunk )(4,4) ) );
        CHECK_THAT( 4e-2  , WithinRel( std::get< 3 >( chunk )(5,5) ) );
        CHECK_THAT( 0.0225, WithinRel( std::get< 3 >( chunk )(6,6) ) );
        CHECK_THAT( 0     , WithinRel( std::get< 3 >( chunk )(7,7) ) );
      } // THEN
    } // WHEN

    WHEN( "a single covarianceMatrix node is given for a lower symmetric matrix" ) {

      pugi::xml_node covariance = sections.find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                           child( "mixed" ).
                                           find_child_by_attribute( "covarianceMatrix", "label", "1" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readCovarianceMatrix( covariance );

        CHECK( true == std::get< 0 >( chunk ) );

        CHECK( 7 == std::get< 1 >( chunk ).size() );
        CHECK_THAT( 1.000000e-5, WithinRel( std::get< 1 >( chunk )[0] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( std::get< 1 >( chunk )[1] ) );
        CHECK_THAT( 3.000000e+6, WithinRel( std::get< 1 >( chunk )[2] ) );
        CHECK_THAT( 6.000000e+6, WithinRel( std::get< 1 >( chunk )[3] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( std::get< 1 >( chunk )[4] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( std::get< 1 >( chunk )[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( std::get< 1 >( chunk )[6] ) );

        CHECK( 7 == std::get< 2 >( chunk ).size() );
        CHECK_THAT( 1.000000e-5, WithinRel( std::get< 2 >( chunk )[0] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( std::get< 2 >( chunk )[1] ) );
        CHECK_THAT( 3.000000e+6, WithinRel( std::get< 2 >( chunk )[2] ) );
        CHECK_THAT( 6.000000e+6, WithinRel( std::get< 2 >( chunk )[3] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( std::get< 2 >( chunk )[4] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( std::get< 2 >( chunk )[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( std::get< 2 >( chunk )[6] ) );

        CHECK( 6 == std::get< 3 >( chunk ).rows() );
        CHECK( 6 == std::get< 3 >( chunk ).cols() );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(0,0) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(0,1) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(0,2) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(0,3) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(0,4) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(0,5) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(1,0) ) );
        CHECK_THAT( 1.251800e-2, WithinRel( std::get< 3 >( chunk )(1,1) ) );
        CHECK_THAT( 1.372900e-2, WithinRel( std::get< 3 >( chunk )(1,2) ) );
        CHECK_THAT( 3.462100e-3, WithinRel( std::get< 3 >( chunk )(1,3) ) );
        CHECK_THAT( 4.176900e-3, WithinRel( std::get< 3 >( chunk )(1,4) ) );
        CHECK_THAT( 3.404000e-3, WithinRel( std::get< 3 >( chunk )(1,5) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(2,0) ) );
        CHECK_THAT( 1.372900e-2, WithinRel( std::get< 3 >( chunk )(2,1) ) );
        CHECK_THAT( 1.557300e-2, WithinRel( std::get< 3 >( chunk )(2,2) ) );
        CHECK_THAT( 5.634300e-3, WithinRel( std::get< 3 >( chunk )(2,3) ) );
        CHECK_THAT( 5.288200e-3, WithinRel( std::get< 3 >( chunk )(2,4) ) );
        CHECK_THAT( 3.863500e-3, WithinRel( std::get< 3 >( chunk )(2,5) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(3,0) ) );
        CHECK_THAT( 3.462100e-3, WithinRel( std::get< 3 >( chunk )(3,1) ) );
        CHECK_THAT( 5.634300e-3, WithinRel( std::get< 3 >( chunk )(3,2) ) );
        CHECK_THAT( 8.970100e-3, WithinRel( std::get< 3 >( chunk )(3,3) ) );
        CHECK_THAT( 4.898600e-3, WithinRel( std::get< 3 >( chunk )(3,4) ) );
        CHECK_THAT( 1.896700e-3, WithinRel( std::get< 3 >( chunk )(3,5) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(4,0) ) );
        CHECK_THAT( 4.176900e-3, WithinRel( std::get< 3 >( chunk )(4,1) ) );
        CHECK_THAT( 5.288200e-3, WithinRel( std::get< 3 >( chunk )(4,2) ) );
        CHECK_THAT( 4.898600e-3, WithinRel( std::get< 3 >( chunk )(4,3) ) );
        CHECK_THAT( 3.694600e-3, WithinRel( std::get< 3 >( chunk )(4,4) ) );
        CHECK_THAT( 1.726800e-3, WithinRel( std::get< 3 >( chunk )(4,5) ) );
        CHECK_THAT( 0., WithinRel( std::get< 3 >( chunk )(5,0) ) );
        CHECK_THAT( 3.404000e-3, WithinRel( std::get< 3 >( chunk )(5,1) ) );
        CHECK_THAT( 3.863500e-3, WithinRel( std::get< 3 >( chunk )(5,2) ) );
        CHECK_THAT( 1.896700e-3, WithinRel( std::get< 3 >( chunk )(5,3) ) );
        CHECK_THAT( 1.726800e-3, WithinRel( std::get< 3 >( chunk )(5,4) ) );
        CHECK_THAT( 1.144800e-3, WithinRel( std::get< 3 >( chunk )(5,5) ) );
      } // THEN
    } // WHEN

    WHEN( "a single covarianceMatrix node is given using an array with only a shape" ) {

      pugi::xml_node covariance = sections.find_child_by_attribute( "covarianceSection", "label", "(z,n) vs. n + n + F18 + photon" ).
                                           child( "covarianceMatrix" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readCovarianceMatrix( covariance );

        CHECK( true == std::get< 0 >( chunk ) );

        CHECK( 7 == std::get< 1 >( chunk ).size() );
        CHECK_THAT( 1.000000e-5, WithinRel( std::get< 1 >( chunk )[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( std::get< 1 >( chunk )[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( std::get< 1 >( chunk )[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( std::get< 1 >( chunk )[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( std::get< 1 >( chunk )[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( std::get< 1 >( chunk )[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( std::get< 1 >( chunk )[6] ) );

        CHECK( 7 == std::get< 2 >( chunk ).size() );
        CHECK_THAT( 1.000000e-5, WithinRel( std::get< 2 >( chunk )[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( std::get< 2 >( chunk )[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( std::get< 2 >( chunk )[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( std::get< 2 >( chunk )[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( std::get< 2 >( chunk )[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( std::get< 2 >( chunk )[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( std::get< 2 >( chunk )[6] ) );

        CHECK( 6 == std::get< 3 >( chunk ).rows() );
        CHECK( 6 == std::get< 3 >( chunk ).cols() );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(0,0) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(0,1) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(0,2) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(0,3) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(0,4) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(0,5) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(1,0) ) );
        CHECK_THAT( -2.732300e-3, WithinRel( std::get< 3 >( chunk )(1,1) ) );
        CHECK_THAT( -8.431200e-4, WithinRel( std::get< 3 >( chunk )(1,2) ) );
        CHECK_THAT(  1.625000e-3, WithinRel( std::get< 3 >( chunk )(1,3) ) );
        CHECK_THAT(  2.647600e-3, WithinRel( std::get< 3 >( chunk )(1,4) ) );
        CHECK_THAT(  4.939500e-3, WithinRel( std::get< 3 >( chunk )(1,5) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(2,0) ) );
        CHECK_THAT( -1.625700e-3, WithinRel( std::get< 3 >( chunk )(2,1) ) );
        CHECK_THAT( -3.558100e-4, WithinRel( std::get< 3 >( chunk )(2,2) ) );
        CHECK_THAT(  1.459800e-3, WithinRel( std::get< 3 >( chunk )(2,3) ) );
        CHECK_THAT(  2.437400e-3, WithinRel( std::get< 3 >( chunk )(2,4) ) );
        CHECK_THAT(  3.772000e-3, WithinRel( std::get< 3 >( chunk )(2,5) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(3,0) ) );
        CHECK_THAT( -2.314700e-4, WithinRel( std::get< 3 >( chunk )(3,1) ) );
        CHECK_THAT(  3.051500e-4, WithinRel( std::get< 3 >( chunk )(3,2) ) );
        CHECK_THAT(  1.292200e-3, WithinRel( std::get< 3 >( chunk )(3,3) ) );
        CHECK_THAT(  2.152300e-3, WithinRel( std::get< 3 >( chunk )(3,4) ) );
        CHECK_THAT(  2.538300e-3, WithinRel( std::get< 3 >( chunk )(3,5) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(4,0) ) );
        CHECK_THAT(  3.229600e-4, WithinRel( std::get< 3 >( chunk )(4,1) ) );
        CHECK_THAT(  6.356200e-4, WithinRel( std::get< 3 >( chunk )(4,2) ) );
        CHECK_THAT(  1.308700e-3, WithinRel( std::get< 3 >( chunk )(4,3) ) );
        CHECK_THAT(  1.986300e-3, WithinRel( std::get< 3 >( chunk )(4,4) ) );
        CHECK_THAT(  2.439300e-3, WithinRel( std::get< 3 >( chunk )(4,5) ) );
        CHECK_THAT(  0., WithinRel( std::get< 3 >( chunk )(5,0) ) );
        CHECK_THAT(  4.981700e-4, WithinRel( std::get< 3 >( chunk )(5,1) ) );
        CHECK_THAT(  8.811700e-4, WithinRel( std::get< 3 >( chunk )(5,2) ) );
        CHECK_THAT(  1.559200e-3, WithinRel( std::get< 3 >( chunk )(5,3) ) );
        CHECK_THAT(  2.135100e-3, WithinRel( std::get< 3 >( chunk )(5,4) ) );
        CHECK_THAT(  2.953900e-3, WithinRel( std::get< 3 >( chunk )(5,5) ) );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readAxis( sections ) );                      // wrong node
        CHECK_THROWS( format::gnds::readAxis( sections.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
