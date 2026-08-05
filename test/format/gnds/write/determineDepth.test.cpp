// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/determineDepth.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

SCENARIO( "determineDepth" ) {

  GIVEN( "xml nodes" ) {

    THEN( "the depth can be determined" ) {

      pugi::xml_document parent;

      CHECK( 0 == gnds::write::determineDepth( parent ) );

    } // THEN
  } // GIVEN
} // SCENARIO
