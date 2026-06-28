// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/utility/find_closest.hpp"

// other includes

// convenience typedefs
using namespace njoy::utility;

SCENARIO( "find_closest" ) {

  GIVEN( "a sequence of values" ) {

    std::vector< double > values = { 100., 200., 300., 400., 500. };

    CHECK( std::next( values.begin(), 2 ) == find_closest( values.begin(), values.end(), 302., 5. ) );
    CHECK( std::next( values.begin(), 2 ) == find_closest( values.begin(), values.end(), 302., 2. ) );
    CHECK( values.end() == find_closest( values.begin(), values.end(), 302., 1. ) );

  } // GIVEN
} // SCENARIO
