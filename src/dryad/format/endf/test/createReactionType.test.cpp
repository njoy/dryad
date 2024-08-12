// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createReactionType.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createReactionType" ) {

  GIVEN( "ENDF tree materials and MT numbers" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-001_H_001.endf" );
    auto material = tape.materials().front();

    WHEN( "a single tree material and MT number is given" ) {

      THEN( "it can be converted" ) {

        CHECK( ReactionType::Summation == format::endf::createReactionType( material, 1 ) );
        CHECK( ReactionType::Primary == format::endf::createReactionType( material, 2 ) );
        CHECK( ReactionType::Summation == format::endf::createReactionType( material, 3 ) );
        CHECK( ReactionType::Summation == format::endf::createReactionType( material, 4 ) );
        CHECK( ReactionType::Primary == format::endf::createReactionType( material, 5 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported MT number" ) {

        CHECK_THROWS( format::endf::createReactionType( material, 999 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
