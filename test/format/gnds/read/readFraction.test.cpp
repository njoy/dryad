// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/readFraction.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunkUsingNoFraction( const format::gnds::Fraction& );
void verifyChunkUsingFraction( const format::gnds::Fraction& );

SCENARIO( "readFraction" ) {

  GIVEN( "a GNDS fraction xml node" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node photon = document.child( "reactionSuite" ).
                                     child( "PoPs" ).child( "gaugeBosons" ).
                                     child( "gaugeBoson" );
    pugi::xml_node neutron = document.child( "reactionSuite" ).
                                      child( "PoPs" ).child( "baryons" ).
                                      child( "baryon" );
    pugi::xml_node without_fraction = photon.child( "spin" ).child( "fraction" );
    pugi::xml_node with_fraction = neutron.child( "spin" ).child( "fraction" );

    WHEN( "a single GNDS fraction node with and without units are given" ) {

      THEN( "it can be converted" ) {

        auto chunk_with_no_fraction = format::gnds::readFraction( without_fraction );
        auto chunk_with_fraction = format::gnds::readFraction( with_fraction );

        verifyChunkUsingNoFraction( chunk_with_no_fraction );
        verifyChunkUsingFraction( chunk_with_fraction );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readFraction( photon ) );                      // wrong node
        CHECK_THROWS( format::gnds::readFraction( photon.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkUsingNoFraction( const format::gnds::Fraction& chunk ) {

  CHECK_THAT( 1., WithinRel( chunk.first ) );
  CHECK( "hbar" == chunk.second );
}

void verifyChunkUsingFraction( const format::gnds::Fraction& chunk ) {

  CHECK( 0.5 == chunk.first );
  CHECK( "hbar" == chunk.second );
}