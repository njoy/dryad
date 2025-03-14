// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/format/endf/ReactionInformation.hpp"

// other includes

// convenience typedefs
using ReactionInformation = njoy::dryad::format::endf::ReactionInformation;

SCENARIO( "ReactionInformation" ) {

  CHECK( true == ReactionInformation::hasSecondaryParticles( 2 ) );
} // SCENARIO
