// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/CoherentDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunkWithoutAnomolousFormFactor( const CoherentDistributionData& );
void verifyChunkWithAnomolousFormFactor( const CoherentDistributionData& );

SCENARIO( "CoherentDistributionData" ) {

  GIVEN( "valid data for coherent distribution data without the anomolous form factor" ) {

    WHEN( "the data is given explicitly" ) {

      ReferenceFrame frame = ReferenceFrame::CentreOfMass;
      TabulatedScatteringFunction scattering( { 0., 1e+6 }, { 2., 1. } );

      CoherentDistributionData chunk( std::move( frame ), std::move( scattering ) );

      THEN( "a CoherentDistributionData can be constructed and members can be tested" ) {

        verifyChunkWithoutAnomolousFormFactor( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for coherent distribution data with the anomolous form factor" ) {

    WHEN( "the data is given explicitly" ) {

      ReferenceFrame frame = ReferenceFrame::CentreOfMass;
      TabulatedScatteringFunction scattering( { 0., 1e+6 }, { 2., 1. } );
      TabulatedFormFactor real( { 1., 2e+7 }, { 1., 2. } );
      TabulatedFormFactor imaginary( { 1., 2e+7 }, { 0.5, 0.6 } );

      CoherentDistributionData chunk( std::move( frame ), std::move( scattering ),
                                      std::move( real ), std::move( imaginary ) );

      THEN( "a CoherentDistributionData can be constructed and members can be tested" ) {

        verifyChunkWithAnomolousFormFactor( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of CoherentDistributionData is given" ) {

      CoherentDistributionData chunk( ReferenceFrame::CentreOfMass,
                                      TabulatedScatteringFunction( { 0., 1e+6 }, { 2., 1. } ) );

      THEN( "the reference frame can be changed" ) {

        ReferenceFrame newframe = ReferenceFrame::Laboratory;
        ReferenceFrame original = ReferenceFrame::CentreOfMass;

        chunk.frame( newframe );

        CHECK( newframe == chunk.frame() );

        chunk.frame( original );

        verifyChunkWithoutAnomolousFormFactor( chunk );
      } // THEN

      THEN( "the scattering function can be changed" ) {

        TabulatedScatteringFunction newfunction( { 0., 1e+6 }, { 4., 2. } );
        TabulatedScatteringFunction original( { 0., 1e+6 }, { 2., 1. } );

        chunk.scatteringFunction( newfunction );

        CHECK( newfunction == chunk.scatteringFunction() );

        chunk.scatteringFunction( original );

        verifyChunkWithoutAnomolousFormFactor( chunk );
      } // THEN

      THEN( "the form factor can be changed" ) {

        std::optional< TabulatedFormFactor > newrealfactor( { { 1., 2e+7 }, { 1., 2. } } );
        std::optional< TabulatedFormFactor > newimaginaryfactor( { { 1., 2e+7 }, { 0.5, 0.6 } } );
        std::optional< TabulatedFormFactor > original = std::nullopt;

        chunk.realAnomolousFormFactor( newrealfactor );
        chunk.imaginaryAnomolousFormFactor( newimaginaryfactor );

        verifyChunkWithAnomolousFormFactor( chunk );

        chunk.realAnomolousFormFactor( original );
        chunk.imaginaryAnomolousFormFactor( original );

        verifyChunkWithoutAnomolousFormFactor( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of CoherentDistributionData are given" ) {

      CoherentDistributionData left( ReferenceFrame::CentreOfMass,
                                     TabulatedScatteringFunction( { 0., 1e+6 }, { 2., 1. } ) );
      CoherentDistributionData equal( ReferenceFrame::CentreOfMass,
                                      TabulatedScatteringFunction( { 0., 1e+6 }, { 2., 1. } ) );
      CoherentDistributionData different( ReferenceFrame::CentreOfMass,
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

void verifyChunkWithoutAnomolousFormFactor( const CoherentDistributionData& chunk ) {

  CHECK( DistributionDataType::Coherent == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );
  CHECK( false == chunk.hasAnomolousFormFactor() );

  CHECK_THAT( 0.  , WithinRel( chunk.scatteringFunction().lowerInverseLengthLimit() ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.scatteringFunction().upperInverseLengthLimit() ) );
  CHECK( 2 == chunk.scatteringFunction().inverseLengths().size() );
  CHECK( 2 == chunk.scatteringFunction().values().size() );
  CHECK( 1 == chunk.scatteringFunction().boundaries().size() );
  CHECK( 1 == chunk.scatteringFunction().interpolants().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.scatteringFunction().inverseLengths()[0] ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.scatteringFunction().inverseLengths()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.scatteringFunction().values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.scatteringFunction().values()[1] ) );
  CHECK( 1 == chunk.scatteringFunction().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.scatteringFunction().interpolants()[0] );
  CHECK( true == chunk.scatteringFunction().isLinearised() );

  CHECK( std::nullopt == chunk.realAnomolousFormFactor() );
  CHECK( std::nullopt == chunk.imaginaryAnomolousFormFactor() );
}

void verifyChunkWithAnomolousFormFactor( const CoherentDistributionData& chunk ) {

  CHECK( DistributionDataType::Coherent == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );
  CHECK( true == chunk.hasAnomolousFormFactor() );

  CHECK_THAT( 0.  , WithinRel( chunk.scatteringFunction().lowerInverseLengthLimit() ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.scatteringFunction().upperInverseLengthLimit() ) );
  CHECK( 2 == chunk.scatteringFunction().inverseLengths().size() );
  CHECK( 2 == chunk.scatteringFunction().values().size() );
  CHECK( 1 == chunk.scatteringFunction().boundaries().size() );
  CHECK( 1 == chunk.scatteringFunction().interpolants().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.scatteringFunction().inverseLengths()[0] ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.scatteringFunction().inverseLengths()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.scatteringFunction().values()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.scatteringFunction().values()[1] ) );
  CHECK( 1 == chunk.scatteringFunction().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.scatteringFunction().interpolants()[0] );
  CHECK( true == chunk.scatteringFunction().isLinearised() );

  CHECK( std::nullopt != chunk.realAnomolousFormFactor() );
  auto factor = chunk.realAnomolousFormFactor().value();
  CHECK_THAT( 1.  , WithinRel( factor.lowerEnergyLimit() ) );
  CHECK_THAT( 2e+7, WithinRel( factor.upperEnergyLimit() ) );
  CHECK( 2 == factor.energies().size() );
  CHECK( 2 == factor.values().size() );
  CHECK( 1 == factor.boundaries().size() );
  CHECK( 1 == factor.interpolants().size() );
  CHECK_THAT( 1.  , WithinRel( factor.energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( factor.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( factor.values()[0] ) );
  CHECK_THAT( 2., WithinRel( factor.values()[1] ) );
  CHECK( 1 == factor.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
  CHECK( true == factor.isLinearised() );

  CHECK( std::nullopt != chunk.imaginaryAnomolousFormFactor() );
  factor = chunk.imaginaryAnomolousFormFactor().value();
  CHECK_THAT( 1.  , WithinRel( factor.lowerEnergyLimit() ) );
  CHECK_THAT( 2e+7, WithinRel( factor.upperEnergyLimit() ) );
  CHECK( 2 == factor.energies().size() );
  CHECK( 2 == factor.values().size() );
  CHECK( 1 == factor.boundaries().size() );
  CHECK( 1 == factor.interpolants().size() );
  CHECK_THAT( 1.  , WithinRel( factor.energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( factor.energies()[1] ) );
  CHECK_THAT( 0.5, WithinRel( factor.values()[0] ) );
  CHECK_THAT( 0.6, WithinRel( factor.values()[1] ) );
  CHECK( 1 == factor.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
  CHECK( true == factor.isLinearised() );
}
