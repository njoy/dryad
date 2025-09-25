// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/resonances/createTabulatedRadius.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const TabulatedRadius& );

SCENARIO( "createTabulatedRadius" ) {

  GIVEN( "GNDS scattering radius node from incident neutron data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-069_Tm_168.endf.gnds.xml" );
    pugi::xml_node radius = document.child( "reactionSuite" ).child( "resonances" ).
                                     child( "resolved" ).child( "BreitWigner" ).
                                     child( "scatteringRadius" ).child( "XYs1d" );

    WHEN( "a single scattering radius node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::resonances::createTabulatedRadius( radius );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedRadius& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 50 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 50 == chunk.energies().size() );
  CHECK( 50 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 49 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 9e+3, WithinRel( chunk.energies()[24] ) );
  CHECK_THAT( 2e+5, WithinRel( chunk.energies()[49] ) );
  CHECK_THAT( 12.381, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  7.844, WithinRel( chunk.values()[24] ) );
  CHECK_THAT(  5.803, WithinRel( chunk.values()[49] ) );
}
