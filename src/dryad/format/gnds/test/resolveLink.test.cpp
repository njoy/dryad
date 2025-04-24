// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/resolveLink.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "resolveLink" ) {

  GIVEN( "a GNDS grid xml node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node axes = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                   find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                   child( "mixed" ).child( "shortRangeSelfScalingVariance" ).
                                   child( "gridded2d" ).child( "axes" );
    pugi::xml_node target = axes.find_child_by_attribute( "grid", "index", "2" ).child( "values" );
    pugi::xml_node grid = axes.find_child_by_attribute( "grid", "index", "1" );

    WHEN( "a single GNDS link node" ) {

      pugi::xml_node link = grid.child( "link" );

      THEN( "it can be resolved" ) {

        auto chunk = format::gnds::resolveLink( link );

        CHECK( target == chunk );
        CHECK( target.name() == chunk.name() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
