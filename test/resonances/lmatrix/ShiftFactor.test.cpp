// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/lmatrix/ShiftFactor.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ShiftFactor" ) {

  GIVEN( "valid number of channels" ) {

    lmatrix::ShiftFactor lmatrix( 3 );

    CHECK( 3 == lmatrix.numberChannels() );
    CHECK( std::complex< double >(0,0) == lmatrix.matrix().diagonal()[0] );
    CHECK( std::complex< double >(0,0) == lmatrix.matrix().diagonal()[1] );
    CHECK( std::complex< double >(0,0) == lmatrix.matrix().diagonal()[2] );

    auto instance = lmatrix( { 4, 5, 6 } );
    CHECK( std::complex< double >(0,4) == lmatrix.matrix().diagonal()[0] );
    CHECK( std::complex< double >(0,5) == lmatrix.matrix().diagonal()[1] );
    CHECK( std::complex< double >(0,6) == lmatrix.matrix().diagonal()[2] );
  } // GIVEN
} // SCENARIO
