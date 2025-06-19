// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createTabulatedAverageEnergy.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedAverageEnergy& );

SCENARIO( "createTabulatedAverageEnergy" ) {

  GIVEN( "GNDS average energy node from electroatomic data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node average = document.child( "reactionSuite" ).child( "reactions" ).
                                      find_child_by_attribute( "reaction", "ENDF_MT", "527" ).
                                      child( "outputChannel" ).child( "products" ).
                                      find_child_by_attribute( "product", "pid", "e-" ).
                                      child( "averageProductEnergy" );

    WHEN( "a single average energy node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createTabulatedAverageEnergy( average );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedAverageEnergy& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 82 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 82 == chunk.energies().size() );
  CHECK( 82 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 81 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 10.        , WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 14.4       , WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 7.86876E+10, WithinRel( chunk.energies()[80] ) );
  CHECK_THAT(       1e+11, WithinRel( chunk.energies()[81] ) );
  CHECK_THAT(  10.         - 2.14426   , WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  14.4        - 2.87181   , WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  7.86876E+10 - 2.11850E+9, WithinRel( chunk.values()[80] ) );
  CHECK_THAT(  1e+11       - 2.66810E+9, WithinRel( chunk.values()[81] ) );
}
