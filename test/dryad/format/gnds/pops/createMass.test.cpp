// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/pops/createMass.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createMass" ) {

  GIVEN( "GNDS mass node" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node photon = document.child( "reactionSuite" ).
                                     child( "PoPs" ).child( "baryons" ).
                                     child( "baryon" );
    pugi::xml_node mass = photon.child( "mass" );

    WHEN( "a single mass node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::pops::createMass( mass, "eval" );

        CHECK_THAT( 1.00866491574, WithinRel( chunk.value() ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
