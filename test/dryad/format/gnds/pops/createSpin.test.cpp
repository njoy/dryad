// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/pops/createSpin.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createSpin" ) {

  GIVEN( "GNDS spin node" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node photon = document.child( "reactionSuite" ).
                                     child( "PoPs" ).child( "baryons" ).
                                     child( "baryon" );
    pugi::xml_node spin = photon.child( "spin" );

    WHEN( "a single spin node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::pops::createSpin( spin, "eval" );

        CHECK( 0.5 == chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
