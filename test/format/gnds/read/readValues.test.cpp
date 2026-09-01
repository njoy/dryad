// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readValues.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

void verifyChunk( const std::vector< double >& );
void verifyChunk( const std::vector< std::size_t >& );

SCENARIO( "readValues" ) {

  GIVEN( "a GNDS values xml node with doubles" ) {

    pugi::xml_document document;
    document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "reactions" );

    WHEN( "a single GNDS values node" ) {

      pugi::xml_node values = reactions.child( "reaction" ).child( "crossSection" ).
                                        child( "XYs1d" ).child( "values" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readValues( values );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readValues( reactions ) );                      // wrong node
        CHECK_THROWS( gnds::read::readValues( reactions.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS values xml node with integers" ) {

    pugi::xml_document document;
    document.load_file( "tsl-7Liin7LiD-mixed.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "reactions" );

    WHEN( "a single GNDS values node" ) {

      pugi::xml_node values = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "4" ).
                                        child( "doubleDifferentialCrossSection" ).
                                        child( "thermalNeutronScatteringLaw_incoherentInelastic" ).
                                        child( "scatteringAtoms" ).child( "scatteringAtom" ).
                                        child( "selfScatteringKernel" ).child( "gridded3d" ).
                                        child( "array" ).child( "values" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readValues< std::size_t >( values );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( gnds::read::readValues< std::size_t >( reactions ) );                      // wrong node
        CHECK_THROWS( gnds::read::readValues< std::size_t >( reactions.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< double >& chunk ) {

 CHECK( 202 == chunk.size() );

 CHECK_THAT( 10.       , WithinRel( chunk[0] ) );
 CHECK_THAT( 2.74896e+8, WithinRel( chunk[1] ) );
 CHECK_THAT( 1e+11     , WithinRel( chunk[200] ) );
 CHECK_THAT( 12987.1   , WithinRel( chunk[201] ) );
}

void verifyChunk( const std::vector< std::size_t >& chunk ) {

 CHECK( 437 == chunk.size() );

 CHECK( 0      == chunk[0] );
 CHECK( 44805  == chunk[1] );
 CHECK( 359755 == chunk[435] );
 CHECK( 359956 == chunk[436] );
}
