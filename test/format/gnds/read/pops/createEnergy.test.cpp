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

std::string chunk();

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

        CHECK_THAT( 0., WithinRel( chunk.value.value() ) );
        CHECK( std::nullopt == chunk.uncertainty );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS energy node with an uncertainty" ) {

    pugi::xml_document document;
    document.load_string( chunk().c_str() );
    pugi::xml_node energy = document.child( "energy" );

    WHEN( "a single energy node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::pops::createEnergy( energy, "eval" );

        CHECK_THAT( 1.8361e6, WithinRel( chunk.value.value() ) );
        CHECK_THAT( 1.0e3, WithinRel( chunk.uncertainty.value() ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "<energy>"
         "  <double label=\"eval\" value=\"1.8361e6\" unit=\"eV\">"
         "    <uncertainty>\n"
         "      <standard>\n"
         "        <double value=\"1.0e3\"/>\n"
         "      </standard>\n"
         "    </uncertainty>\n"
         "  </double>\n"
         "</energy>\n";
}
