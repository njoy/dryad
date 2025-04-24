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

  GIVEN( "a GNDS xml node with a relative link path" ) {

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

  GIVEN( "a GNDS xml node with an absolute link path" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );
    pugi::xml_node reaction = document.child( "reactionSuite" ).child( "reactions" ).child( "reaction" );
    pugi::xml_node target = reaction.child( "doubleDifferentialCrossSection" ).child( "coherentPhotonScattering" );

    WHEN( "a single GNDS link node" ) {

      pugi::xml_node link = reaction.child( "outputChannel" ).child( "products" ).
                                     find_child_by_attribute( "product", "label", "photon" ).
                                     child( "distribution" ).child( "coherentPhotonScattering" );

      THEN( "it can be resolved" ) {

        auto chunk = format::gnds::resolveLink( link );

        CHECK( target == chunk );
        CHECK( target.name() == chunk.name() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
