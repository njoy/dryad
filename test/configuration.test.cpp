// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/configuration.hpp"

// other includes

// convenience typedefs

SCENARIO( "njoy configuration file" ) {

  if ( std::getenv( "NJOY_DATAPATH" ) ) {

    auto& config = njoy::configuration();
    CHECK( true == config.hasKey( "ripl3_levels" ) );
  }
} // SCENARIO
