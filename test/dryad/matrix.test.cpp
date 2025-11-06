// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/matrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "matrix functions" ) {

  matrix::Matrix< double > square_symmetric( 2, 2 );
  square_symmetric(0,0) = 1.;
  square_symmetric(0,1) = 2.;
  square_symmetric(1,0) = 2.;
  square_symmetric(1,1) = 4.;

  matrix::Matrix< double > square_notsymmetric( 2, 2 );
  square_notsymmetric(0,0) = 1.;
  square_notsymmetric(0,1) = 2.;
  square_notsymmetric(1,0) = 1000.;
  square_notsymmetric(1,1) = 4.;

  matrix::Matrix< double > notsquare( 3, 2 );
  notsquare(0,0) = 1.;
  notsquare(0,1) = 2.;
  notsquare(1,0) = 2.;
  notsquare(1,1) = 4.;
  notsquare(1,0) = 3.;
  notsquare(1,1) = 6.;

  GIVEN( "isSquare" ) {

    CHECK( true == matrix::isSquare( square_symmetric ) );
    CHECK( true == matrix::isSquare( square_notsymmetric ) );
    CHECK( false == matrix::isSquare( notsquare ) );
  } // GIVEN

  GIVEN( "isSymmetric" ) {

    CHECK( true == matrix::isSymmetric( square_symmetric ) );
    CHECK( false == matrix::isSymmetric( square_notsymmetric ) );
    CHECK( false == matrix::isSymmetric( notsquare ) );
  } // GIVEN
} // SCENARIO
