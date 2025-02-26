// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/format/endf/covariance/createMatrix.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::ENDFtk;
using CovariancePairs = section::CovariancePairs;
using SquareMatrix = section::SquareMatrix;

SCENARIO( "createMatrix" ) {

  GIVEN( "an instance of CovariancePairs using LB=0/1 (diagonal elements)" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    CovariancePairs covariance = std::get< CovariancePairs >( section.reactions()[0].explicitCovariances()[0] );

    WHEN( "creating a matric from the CovariancePairs instance" ) {

      covariance::Matrix< double > chunk = format::endf::covariance::createMatrix( covariance );

      THEN( "a matrix can be created and members can be tested" ) {

        CHECK( 8 == chunk.rows() );
        CHECK( 8 == chunk.cols() );
        CHECK_THAT( 0., WithinRel( chunk(0,0) ) );
        CHECK_THAT( 0., WithinRel( chunk(0,1) ) );
        CHECK_THAT( 0., WithinRel( chunk(0,2) ) );
        CHECK_THAT( 0., WithinRel( chunk(0,3) ) );
        CHECK_THAT( 0., WithinRel( chunk(0,4) ) );
        CHECK_THAT( 0., WithinRel( chunk(0,5) ) );
        CHECK_THAT( 0., WithinRel( chunk(0,6) ) );
        CHECK_THAT( 0., WithinRel( chunk(0,7) ) );

        CHECK_THAT( 0., WithinRel( chunk(1,0) ) );
        CHECK_THAT( 4.000000e-2, WithinRel( chunk(1,1) ) );
        CHECK_THAT( 0., WithinRel( chunk(1,2) ) );
        CHECK_THAT( 0., WithinRel( chunk(1,3) ) );
        CHECK_THAT( 0., WithinRel( chunk(1,4) ) );
        CHECK_THAT( 0., WithinRel( chunk(1,5) ) );
        CHECK_THAT( 0., WithinRel( chunk(1,6) ) );
        CHECK_THAT( 0., WithinRel( chunk(1,7) ) );

        CHECK_THAT( 0., WithinRel( chunk(2,0) ) );
        CHECK_THAT( 0., WithinRel( chunk(2,1) ) );
        CHECK_THAT( 6.250000e-2, WithinRel( chunk(2,2) ) );
        CHECK_THAT( 0., WithinRel( chunk(2,3) ) );
        CHECK_THAT( 0., WithinRel( chunk(2,4) ) );
        CHECK_THAT( 0., WithinRel( chunk(2,5) ) );
        CHECK_THAT( 0., WithinRel( chunk(2,6) ) );
        CHECK_THAT( 0., WithinRel( chunk(2,7) ) );

        CHECK_THAT( 0., WithinRel( chunk(3,0) ) );
        CHECK_THAT( 0., WithinRel( chunk(3,1) ) );
        CHECK_THAT( 0., WithinRel( chunk(3,2) ) );
        CHECK_THAT( 4.000000e-2, WithinRel( chunk(3,3) ) );
        CHECK_THAT( 0., WithinRel( chunk(3,4) ) );
        CHECK_THAT( 0., WithinRel( chunk(3,5) ) );
        CHECK_THAT( 0., WithinRel( chunk(3,6) ) );
        CHECK_THAT( 0., WithinRel( chunk(3,7) ) );

        CHECK_THAT( 0., WithinRel( chunk(4,0) ) );
        CHECK_THAT( 0., WithinRel( chunk(4,1) ) );
        CHECK_THAT( 0., WithinRel( chunk(4,2) ) );
        CHECK_THAT( 0., WithinRel( chunk(4,3) ) );
        CHECK_THAT( 2.250000e-2, WithinRel( chunk(4,4) ) );
        CHECK_THAT( 0., WithinRel( chunk(4,5) ) );
        CHECK_THAT( 0., WithinRel( chunk(4,6) ) );
        CHECK_THAT( 0., WithinRel( chunk(4,7) ) );

        CHECK_THAT( 0., WithinRel( chunk(5,0) ) );
        CHECK_THAT( 0., WithinRel( chunk(5,1) ) );
        CHECK_THAT( 0., WithinRel( chunk(5,2) ) );
        CHECK_THAT( 0., WithinRel( chunk(5,3) ) );
        CHECK_THAT( 0., WithinRel( chunk(5,4) ) );
        CHECK_THAT( 4.000000e-2, WithinRel( chunk(5,5) ) );
        CHECK_THAT( 0., WithinRel( chunk(5,6) ) );
        CHECK_THAT( 0., WithinRel( chunk(5,7) ) );

        CHECK_THAT( 0., WithinRel( chunk(6,0) ) );
        CHECK_THAT( 0., WithinRel( chunk(6,1) ) );
        CHECK_THAT( 0., WithinRel( chunk(6,2) ) );
        CHECK_THAT( 0., WithinRel( chunk(6,3) ) );
        CHECK_THAT( 0., WithinRel( chunk(6,4) ) );
        CHECK_THAT( 0., WithinRel( chunk(6,5) ) );
        CHECK_THAT( 2.250000e-2, WithinRel( chunk(6,6) ) );
        CHECK_THAT( 0., WithinRel( chunk(6,7) ) );

        CHECK_THAT( 0., WithinRel( chunk(7,0) ) );
        CHECK_THAT( 0., WithinRel( chunk(7,1) ) );
        CHECK_THAT( 0., WithinRel( chunk(7,2) ) );
        CHECK_THAT( 0., WithinRel( chunk(7,3) ) );
        CHECK_THAT( 0., WithinRel( chunk(7,4) ) );
        CHECK_THAT( 0., WithinRel( chunk(7,5) ) );
        CHECK_THAT( 0., WithinRel( chunk(7,6) ) );
        CHECK_THAT( 0., WithinRel( chunk(7,7) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an instance of SquareMatrix that is symmetric" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    SquareMatrix covariance = std::get< SquareMatrix >( section.reactions()[0].explicitCovariances()[1] );

    WHEN( "constructing a diagonal CovarianceBlock from a SquareMatrix" ) {

      covariance::Matrix< double > chunk = format::endf::covariance::createMatrix( covariance );

      THEN( "a matrix can be created and members can be tested" ) {

        CHECK( 6 == chunk.rows() );
        CHECK( 6 == chunk.cols() );
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
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an instance of SquareMatrix that is asymmetric" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    SquareMatrix covariance = std::get< SquareMatrix >( section.reactions()[1].explicitCovariances()[0] );

    WHEN( "constructing a diagonal CovarianceBlock from a SquareMatrix" ) {

      covariance::Matrix< double > chunk = format::endf::covariance::createMatrix( covariance );

      THEN( "a matrix can be created and members can be tested" ) {

        CHECK( 6 == chunk.rows() );
        CHECK( 6 == chunk.cols() );
        CHECK_THAT(  0., WithinRel( chunk(0,0) ) );
        CHECK_THAT(  0., WithinRel( chunk(0,1) ) );
        CHECK_THAT(  0., WithinRel( chunk(0,2) ) );
        CHECK_THAT(  0., WithinRel( chunk(0,3) ) );
        CHECK_THAT(  0., WithinRel( chunk(0,4) ) );
        CHECK_THAT(  0., WithinRel( chunk(0,5) ) );

        CHECK_THAT(  0., WithinRel( chunk(1,0) ) );
        CHECK_THAT( -2.732300e-3, WithinRel( chunk(1,1) ) );
        CHECK_THAT( -8.431200e-4, WithinRel( chunk(1,2) ) );
        CHECK_THAT(  1.625000e-3, WithinRel( chunk(1,3) ) );
        CHECK_THAT(  2.647600e-3, WithinRel( chunk(1,4) ) );
        CHECK_THAT(  4.939500e-3, WithinRel( chunk(1,5) ) );

        CHECK_THAT(  0., WithinRel( chunk(2,0) ) );
        CHECK_THAT( -1.625700e-3, WithinRel( chunk(2,1) ) );
        CHECK_THAT( -3.558100e-4, WithinRel( chunk(2,2) ) );
        CHECK_THAT(  1.459800e-3, WithinRel( chunk(2,3) ) );
        CHECK_THAT(  2.437400e-3, WithinRel( chunk(2,4) ) );
        CHECK_THAT(  3.772000e-3, WithinRel( chunk(2,5) ) );

        CHECK_THAT(  0., WithinRel( chunk(3,0) ) );
        CHECK_THAT( -2.314700e-4, WithinRel( chunk(3,1) ) );
        CHECK_THAT(  3.051500e-4, WithinRel( chunk(3,2) ) );
        CHECK_THAT(  1.292200e-3, WithinRel( chunk(3,3) ) );
        CHECK_THAT(  2.152300e-3, WithinRel( chunk(3,4) ) );
        CHECK_THAT(  2.538300e-3, WithinRel( chunk(3,5) ) );

        CHECK_THAT(  0., WithinRel( chunk(4,0) ) );
        CHECK_THAT(  3.229600e-4, WithinRel( chunk(4,1) ) );
        CHECK_THAT(  6.356200e-4, WithinRel( chunk(4,2) ) );
        CHECK_THAT(  1.308700e-3, WithinRel( chunk(4,3) ) );
        CHECK_THAT(  1.986300e-3, WithinRel( chunk(4,4) ) );
        CHECK_THAT(  2.439300e-3, WithinRel( chunk(4,5) ) );

        CHECK_THAT(  0., WithinRel( chunk(5,0) ) );
        CHECK_THAT(  4.981700e-4, WithinRel( chunk(5,1) ) );
        CHECK_THAT(  8.811700e-4, WithinRel( chunk(5,2) ) );
        CHECK_THAT(  1.559200e-3, WithinRel( chunk(5,3) ) );
        CHECK_THAT(  2.135100e-3, WithinRel( chunk(5,4) ) );
        CHECK_THAT(  2.953900e-3, WithinRel( chunk(5,5) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
