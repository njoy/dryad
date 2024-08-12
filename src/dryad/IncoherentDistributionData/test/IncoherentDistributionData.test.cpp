// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/IncoherentDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const IncoherentDistributionData& );

SCENARIO( "IncoherentDistributionData" ) {

  GIVEN( "valid data for incoherent distribution data" ) {

    WHEN( "the data is given explicitly" ) {

      ReferenceFrame frame = ReferenceFrame::CentreOfMass;
      TabulatedScatteringFunction scattering( { 1., 1e+6 }, { 2., 1. } );

      IncoherentDistributionData chunk( std::move( frame ), std::move( scattering ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const IncoherentDistributionData& chunk ) {

  CHECK( DistributionDataType::Incoherent == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );

  CHECK_THAT( 1.  , WithinRel( chunk.scatteringFunction().lowerInverseLengthLimit() ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.scatteringFunction().upperInverseLengthLimit() ) );
  CHECK( 2 == chunk.scatteringFunction().inverseLengths().size() );
  CHECK( 2 == chunk.scatteringFunction().values().size() );
  CHECK( 1 == chunk.scatteringFunction().boundaries().size() );
  CHECK( 1 == chunk.scatteringFunction().interpolants().size() );
  CHECK_THAT( 1.  , WithinRel( chunk.scatteringFunction().inverseLengths()[0] ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.scatteringFunction().inverseLengths()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.scatteringFunction().values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.scatteringFunction().values()[1] ) );
  CHECK( 1 == chunk.scatteringFunction().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.scatteringFunction().interpolants()[0] );
  CHECK( true == chunk.scatteringFunction().isLinearised() );
}
