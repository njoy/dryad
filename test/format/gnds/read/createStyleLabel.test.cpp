// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createStyleLabel.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/StyleType.hpp"

// convenience typedefs
using namespace njoy::format;

SCENARIO( "createStyleLabel" ) {

  GIVEN( "GNDS data - style is evaluation" ) {

    WHEN( "a GNDS styles node is given" ) {

      pugi::xml_document document;
      document.load_file( "n-001_H_001.endf.gnds.xml" );
      pugi::xml_node styles = document.child( "reactionSuite" ).child( "styles" );

      THEN( "the style label can be created" ) {

        CHECK( "eval" == gnds::read::createStyleLabel( styles, gnds::StyleType::Evaluation ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
