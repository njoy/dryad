// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/pops/createEnergy.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

SCENARIO( "createEnergy" ) {

  GIVEN( "GNDS energy node" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node photon = document.child( "reactionSuite" ).
                                     child( "PoPs" ).child( "chemicalElements" ).
                                     child( "chemicalElement" ).child( "isotopes" ).
                                     child( "isotope" ).child( "nuclides" ).
                                     child( "nuclide" ).child( "nucleus" );
    pugi::xml_node energy = photon.child( "energy" );

    WHEN( "a single energy node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::pops::createEnergy( energy, "eval" );

        CHECK_THAT( 0., WithinRel( chunk.value() ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
