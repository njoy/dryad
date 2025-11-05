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

      THEN( "an IncoherentDistributionData can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of IncoherentDistributionData is given" ) {

      IncoherentDistributionData chunk( ReferenceFrame::CentreOfMass,
                                        TabulatedScatteringFunction( { 1., 1e+6 }, { 2., 1. } ) );

      THEN( "the reference frame can be changed" ) {

        ReferenceFrame newframe = ReferenceFrame::Laboratory;
        ReferenceFrame original = ReferenceFrame::CentreOfMass;

        chunk.frame( newframe );

        CHECK( newframe == chunk.frame() );

        chunk.frame( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the scattering function can be changed" ) {

        TabulatedScatteringFunction newfunction( { 1., 1e+6 }, { 4., 2. } );
        TabulatedScatteringFunction original( { 1., 1e+6 }, { 2., 1. } );

        chunk.scatteringFunction( newfunction );

        CHECK( newfunction == chunk.scatteringFunction() );

        chunk.scatteringFunction( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of IncoherentDistributionData are given" ) {

      IncoherentDistributionData left( ReferenceFrame::CentreOfMass,
                                       TabulatedScatteringFunction( { 0., 1e+6 }, { 2., 1. } ) );
      IncoherentDistributionData equal( ReferenceFrame::CentreOfMass,
                                        TabulatedScatteringFunction( { 0., 1e+6 }, { 2., 1. } ) );
      IncoherentDistributionData different( ReferenceFrame::CentreOfMass,
                                            TabulatedScatteringFunction( { 0., 1e+7 }, { 2., 1. } ) );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
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
