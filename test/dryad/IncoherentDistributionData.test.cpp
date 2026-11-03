// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/IncoherentDistributionData.hpp"

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

  GIVEN( "incoherent distribution data with tabulated data that is not curated" ) {

    WHEN( "the data is given explicitly" ) {

      IncoherentDistributionData chunk( ReferenceFrame::CentreOfMass,
                                        TabulatedScatteringFunction( { 1., 2., 2., 2., 1e+6 },        // <-- discontinuity with 3 points
                                                                     { 2., 1.9, 1.8, 1.7, 1. } ),
                                        std::vector< TabulatedComptonProfile >{

                                          { id::ElectronSubshellID( "1s" ),
                                            { 0., 2., 3., 3., 3., 4. }, { 0., 1., 2., 3., 1., 2. } }, // <-- discontinuity with 3 points
                                          { id::ElectronSubshellID( "2s" ),
                                            { 0., 1., 2., 2., 2., 4. }, { 0., 1., 2., 3., 1., 2. } }  // <-- discontinuity with 3 points
                                        } );

      THEN( "the tabulated data is not curated" ) {

        CHECK( false == chunk.scatteringFunction().isCurated() );
        CHECK( false == chunk.comptonProfiles()->at( 0 ).isCurated() );
        CHECK( false == chunk.comptonProfiles()->at( 1 ).isCurated() );
      } // THEN

      THEN( "the tabulated data can be curated" ) {

        chunk.curate();

        CHECK( true == chunk.scatteringFunction().isCurated() );
        CHECK( true == chunk.comptonProfiles()->at( 0 ).isCurated() );
        CHECK( true == chunk.comptonProfiles()->at( 1 ).isCurated() );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly without Compton profiles" ) {

      IncoherentDistributionData chunk( ReferenceFrame::CentreOfMass,
                                        TabulatedScatteringFunction( { 1., 2., 2., 2., 1e+6 },   // <-- discontinuity with 3 points
                                                                     { 2., 1.9, 1.8, 1.7, 1. } ) );

      THEN( "the tabulated data can be curated" ) {

        CHECK( false == chunk.scatteringFunction().isCurated() );

        chunk.curate();

        CHECK( true == chunk.scatteringFunction().isCurated() );
        CHECK( std::nullopt == chunk.comptonProfiles() );
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

      THEN( "the compton profiles can be changed" ) {

        std::optional< std::vector< TabulatedComptonProfile > >
        newprofiles( { { id::ElectronSubshellID( "1s" ), { 0, 100 }, { 1, 2 } } } );
        std::optional< std::vector< TabulatedComptonProfile > >
        original = std::nullopt;

        chunk.comptonProfiles( newprofiles );

        CHECK( newprofiles == chunk.comptonProfiles() );

        chunk.comptonProfiles( original );

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

  CHECK( std::nullopt == chunk.comptonProfiles() );
}
