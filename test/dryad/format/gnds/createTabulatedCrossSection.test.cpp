// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createTabulatedCrossSection.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyNeutronChunk( const TabulatedCrossSection& );
void verifyElectronChunk( const TabulatedCrossSection& );

SCENARIO( "createTabulatedCrossSection" ) {

  GIVEN( "GNDS cross section node from incident neutron data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node xs = document.child( "reactionSuite" ).child( "reactions" ).
                                 find_child_by_attribute( "reaction", "ENDF_MT", "102" ).
                                 child( "crossSection" );

    WHEN( "a single cross section node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createTabulatedCrossSection( xs );

        verifyNeutronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS cross section node from electroatomic data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node xs = document.child( "reactionSuite" ).child( "reactions" ).
                                 find_child_by_attribute( "reaction", "ENDF_MT", "527" ).
                                 child( "crossSection" );

    WHEN( "a single cross section node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createTabulatedCrossSection( xs );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyNeutronChunk( const TabulatedCrossSection& chunk ) {

  CHECK( false == chunk.isLinearised() );
  CHECK( 153 == chunk.numberPoints() );
  CHECK( 2 == chunk.numberRegions() );
  CHECK( 153 == chunk.energies().size() );
  CHECK( 153 == chunk.values().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK( 32 == chunk.boundaries()[0] );
  CHECK( 152 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LogLog == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1e+4, WithinRel( chunk.energies()[32] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[152] ) );
  CHECK_THAT( 1.672869e+1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 4.950573e-4, WithinRel( chunk.values()[32] ) );
  CHECK_THAT( 2.710792e-5, WithinRel( chunk.values()[152] ) );
}

void verifyElectronChunk( const TabulatedCrossSection& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 96 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 96 == chunk.energies().size() );
  CHECK( 96 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 95 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(    10, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT(  1e+6, WithinRel( chunk.energies()[65] ) );
  CHECK_THAT( 1e+11, WithinRel( chunk.energies()[95] ) );
  CHECK_THAT(  29.7832, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 0.552449, WithinRel( chunk.values()[65] ) );
  CHECK_THAT( 0.990621, WithinRel( chunk.values()[95] ) );
}
