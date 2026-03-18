// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/thermal/createDebyeWallerIntegralData.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const DebyeWallerIntegralData& );

SCENARIO( "createDebyeWallerIntegralData" ) {

  GIVEN( "GNDS Debye-Waller node from tsl data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "tsl-ZrinZrH.endf.gnds.xml" );
    pugi::xml_node debyewaller = document.child( "reactionSuite" ).child( "reactions" ).
                                          find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                          child( "doubleDifferentialCrossSection" ).
                                          child( "thermalNeutronScatteringLaw_incoherentElastic" ).
                                          child( "DebyeWallerIntegral" );

    WHEN( "a single Debye-Waller integral node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::thermal::createDebyeWallerIntegralData( debyewaller );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const DebyeWallerIntegralData& chunk ) {

  CHECK( 8 == chunk.temperatures().size() );
  CHECK( 8 == chunk.values().size() );
  CHECK_THAT(  296, WithinRel( chunk.temperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.temperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( chunk.temperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.temperatures()[7] ) );
  CHECK_THAT( 2.013538, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 2.677764, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 6.583171, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 7.891981, WithinRel( chunk.values()[7] ) );
}
