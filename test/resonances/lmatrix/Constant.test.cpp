// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/lmatrix/Constant.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "Constant" ) {

  GIVEN( "valid number of channels" ) {

    lmatrix::Constant lmatrix( 3 );

    CHECK( 3 == lmatrix.numberChannels() );
    CHECK( 3 == lmatrix.matrix().rows() );
    CHECK( 3 == lmatrix.matrix().cols() );
    CHECK( std::complex< double >(0,0) == lmatrix.matrix().diagonal()[0] );
    CHECK( std::complex< double >(0,0) == lmatrix.matrix().diagonal()[1] );
    CHECK( std::complex< double >(0,0) == lmatrix.matrix().diagonal()[2] );

    auto instance = lmatrix( { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } );
    CHECK( std::complex< double >(-6,4) == lmatrix.matrix().diagonal()[0] );
    CHECK( std::complex< double >(-6,5) == lmatrix.matrix().diagonal()[1] );
    CHECK( std::complex< double >(-6,6) == lmatrix.matrix().diagonal()[2] );
  } // GIVEN
} // SCENARIO
