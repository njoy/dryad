// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/thermal/createTabulatedEffectiveTemperature.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const TabulatedEffectiveTemperature& );

SCENARIO( "createTabulatedEffectiveTemperature" ) {

  GIVEN( "GNDS Debye-Waller node from tsl data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "tsl-ZrinZrH.endf.gnds.xml" );
    pugi::xml_node temperature = document.child( "reactionSuite" ).child( "reactions" ).
                                          find_child_by_attribute( "reaction", "ENDF_MT", "4" ).
                                          child( "doubleDifferentialCrossSection" ).
                                          child( "thermalNeutronScatteringLaw_incoherentInelastic" ).
                                          child( "scatteringAtoms" ).
                                          find_child_by_attribute( "scatteringAtom", "pid", "Zr90" ).
                                          child( "T_effective" );

    WHEN( "a single effective temperature node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::thermal::createTabulatedEffectiveTemperature( temperature );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedEffectiveTemperature& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 8 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 8 == chunk.moderatorTemperatures().size() );
  CHECK( 8 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 7 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(  296, WithinRel( chunk.moderatorTemperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.moderatorTemperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( chunk.moderatorTemperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.moderatorTemperatures()[7] ) );
  CHECK_THAT(  317.4163, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  416.3325, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 1006.822 , WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 1205.703 , WithinRel( chunk.values()[7] ) );
}
