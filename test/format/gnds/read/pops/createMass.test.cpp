// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/pops/createMass.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk();

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

        auto chunk = gnds::read::pops::createMass( mass, "eval" );

        CHECK_THAT( 1.00866491574, WithinRel( chunk.value.value() ) );
        CHECK( std::nullopt == chunk.uncertainty );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS mass node with an uncertainty" ) {

    pugi::xml_document document;
    document.load_string( chunk().c_str() );
    pugi::xml_node mass = document.child( "mass" );

    WHEN( "a single mass node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::pops::createMass( mass, "eval" );

        CHECK_THAT( 1.008, WithinRel( chunk.value.value() ) );
        CHECK_THAT( 0.001, WithinRel( chunk.uncertainty.value() ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "<mass>"
         "  <double label=\"eval\" value=\"1.008\" unit=\"amu\">"
         "    <uncertainty>\n"
         "      <standard>\n"
         "        <double value=\"0.001\"/>\n"
         "      </standard>\n"
         "    </uncertainty>\n"
         "  </double>\n"
         "</mass>\n";
}
