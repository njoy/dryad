// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createTabulatedScatteringFunctionFromNodes.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedScatteringFunction& );

SCENARIO( "createTabulatedScatteringFunctionFromNodes" ) {

  GIVEN( "GNDS scattering function node from photoatomic data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "504" ).
                                   child( "doubleDifferentialCrossSection" ).
                                   child( "incoherentPhotonScattering" ).
                                   child( "scatteringFactor" ).
                                   first_child();

    WHEN( "a single scattering function node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createTabulatedScatteringFunctionFromNodes( node );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedScatteringFunction& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 398 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 398 == chunk.inverseLengths().size() );
  CHECK( 398 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 397 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 0.       , WithinRel( chunk.inverseLengths()[0] ) );
  CHECK_THAT( 1e-7     , WithinRel( chunk.inverseLengths()[1] ) );
  CHECK_THAT( 512000000, WithinRel( chunk.inverseLengths()[396] ) );
  CHECK_THAT( 1e+9     , WithinRel( chunk.inverseLengths()[397] ) );
  CHECK_THAT( 0.        , WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 4.4097E-13, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 1.        , WithinRel( chunk.values()[396] ) );
  CHECK_THAT( 1.        , WithinRel( chunk.values()[397] ) );
}
