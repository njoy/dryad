// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createIncoherentDistributionData.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const IncoherentDistributionData& );

SCENARIO( "createIncoherentDistributionData" ) {

  GIVEN( "GNDS incoherent distribution data node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "504" ).
                                   child( "doubleDifferentialCrossSection" );

    pugi::xml_node incoherent = node.child( "incoherentPhotonScattering" );

    WHEN( "a single incoherent data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createIncoherentDistributionData( incoherent );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const IncoherentDistributionData& chunk ) {

  CHECK( DistributionDataType::Incoherent == chunk.type() );
  CHECK( ReferenceFrame::Laboratory == chunk.frame() );

  CHECK_THAT( 0.  , WithinRel( chunk.scatteringFunction().lowerInverseLengthLimit() ) );
  CHECK_THAT( 1e+9, WithinRel( chunk.scatteringFunction().upperInverseLengthLimit() ) );
  CHECK( 398 == chunk.scatteringFunction().inverseLengths().size() );
  CHECK( 398 == chunk.scatteringFunction().values().size() );
  CHECK( 1 == chunk.scatteringFunction().boundaries().size() );
  CHECK( 1 == chunk.scatteringFunction().interpolants().size() );
  CHECK_THAT( 0.       , WithinRel( chunk.scatteringFunction().inverseLengths()[0] ) );
  CHECK_THAT( 1e-7     , WithinRel( chunk.scatteringFunction().inverseLengths()[1] ) );
  CHECK_THAT( 512000000, WithinRel( chunk.scatteringFunction().inverseLengths()[396] ) );
  CHECK_THAT( 1e+9     , WithinRel( chunk.scatteringFunction().inverseLengths()[397] ) );
  CHECK_THAT( 0.        , WithinRel( chunk.scatteringFunction().values()[0] ) );
  CHECK_THAT( 4.4097E-13, WithinRel( chunk.scatteringFunction().values()[1] ) );
  CHECK_THAT( 1.        , WithinRel( chunk.scatteringFunction().values()[396] ) );
  CHECK_THAT( 1.        , WithinRel( chunk.scatteringFunction().values()[397] ) );
  CHECK( 397 == chunk.scatteringFunction().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.scatteringFunction().interpolants()[0] );
  CHECK( true == chunk.scatteringFunction().isLinearised() );
}
