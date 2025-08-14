// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/ReactionProduct.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const ReactionProduct&, bool );
void verifyTabulatedChunk( const ReactionProduct&, bool );

SCENARIO( "ReactionProduct" ) {

  GIVEN( "valid data for a ReactionProduct with an integer multiplicity" ) {

    WHEN( "the data is given explicitly" ) {

      id::ParticleID id = id::ParticleID::neutron();
      int multiplicity = 1;
      TwoBodyDistributionData distribution( ReferenceFrame::CentreOfMass,
                                            LegendreAngularDistributions(
                                              { 1e-5, 20. },
                                              { { { 1.0 } }, { { 1.0, 0.2 } } } ) );

      ReactionProduct chunk1( id, multiplicity,
                              distribution, std::nullopt, false );
      ReactionProduct chunk2( std::move( id ), std::move( multiplicity ),
                              std::move( distribution ), std::nullopt, true );

      verifyChunk( chunk1, false );
      verifyChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyChunk( chunk1, true );
      verifyChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with an tabulated multiplicity" ) {

    WHEN( "the data is given explicitly" ) {

      id::ParticleID id = id::ParticleID::neutron();
      TabulatedMultiplicity multiplicity( { 1., 2., 2., 3., 4. },
                                          { 4., 3., 4., 3., 2. },
                                          { 1, 4 },
                                          { InterpolationType::LinearLinear,
                                            InterpolationType::LinearLog } );
      TwoBodyDistributionData distribution( ReferenceFrame::CentreOfMass,
                                            LegendreAngularDistributions(
                                              { 1e-5, 20. },
                                              { { { 1.0 } }, { { 1.0, 0.2 } } } ) );

      ReactionProduct chunk1( id, multiplicity, distribution, std::nullopt, false );
      ReactionProduct chunk2( std::move( id ), std::move( multiplicity ), std::move( distribution ),
                              std::nullopt, true );

      verifyTabulatedChunk( chunk1, false );
      verifyTabulatedChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyTabulatedChunk( chunk1, true );
      verifyTabulatedChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of Reaction is given" ) {

      ReactionProduct chunk( id::ParticleID::neutron(), 1,
                             TwoBodyDistributionData ( ReferenceFrame::CentreOfMass,
                                                       LegendreAngularDistributions(
                                                         { 1e-5, 20. },
                                                         { { { 1.0 } }, { { 1.0, 0.2 } } } ) ) );

      THEN( "the product identifier can be changed" ) {

        id::ParticleID newid = id::ParticleID::proton();
        id::ParticleID original = id::ParticleID::neutron();

        chunk.identifier( newid );

        CHECK( newid == chunk.identifier() );

        chunk.identifier( original );

        verifyChunk( chunk, false );
      } // THEN

      THEN( "the multiplicity can be changed" ) {

        TabulatedMultiplicity newmultiplicity( { 1., 2., 2., 3., 4. },
                                               { 4., 3., 4., 3., 2. },
                                               { 1, 4 },
                                               { InterpolationType::LinearLinear,
                                                 InterpolationType::LinearLog } );
        int original = 1;

        chunk.multiplicity( newmultiplicity );

        verifyTabulatedChunk( chunk, false );

        chunk.multiplicity( original );

        verifyChunk( chunk, false );
      } // THEN

      THEN( "the distribution data can be changed" ) {

        std::optional< ReactionProduct::DistributionData > newdistribution =
            TwoBodyDistributionData( ReferenceFrame::CentreOfMass, IsotropicAngularDistributions() );
        std::optional< ReactionProduct::DistributionData > original =
            TwoBodyDistributionData( ReferenceFrame::CentreOfMass,
                                     LegendreAngularDistributions(
                                       { 1e-5, 20. },
                                       { { { 1.0 } }, { { 1.0, 0.2 } } } ) );

        chunk.distributionData( newdistribution );

        CHECK( newdistribution == chunk.distributionData() );

        chunk.distributionData( original );

        verifyChunk( chunk, false );
      } // THEN

      THEN( "the average energy data can be changed" ) {

        std::optional< TabulatedAverageEnergy > newaverage =
            TabulatedAverageEnergy( { 1., 2., 2., 3., 4. },
                                    { 4., 3., 4., 3., 2. },
                                    { 1, 4 },
                                    { InterpolationType::LinearLinear,
                                      InterpolationType::LinearLog } );
        std::optional< TabulatedAverageEnergy > original = std::nullopt;

        chunk.averageEnergy( newaverage );

        CHECK( newaverage == chunk.averageEnergy() );

        chunk.averageEnergy( original );

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ReactionProduct are given" ) {

      ReactionProduct left( id::ParticleID::neutron(), 1 );
      ReactionProduct equal( id::ParticleID::neutron(), 1 );
      ReactionProduct different( id::ParticleID::proton(), 1,
                                 TwoBodyDistributionData( ReferenceFrame::CentreOfMass,
                                                          IsotropicAngularDistributions() ) );

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

void verifyChunk( const ReactionProduct& chunk, bool normalise ) {

  // ReactionProduct identifier
  CHECK( id::ParticleID( "n" ) == chunk.identifier() );

  // multiplicity
  auto multiplicity = chunk.multiplicity();
  CHECK( true == std::holds_alternative< int >( multiplicity ) );
  CHECK( 1 == std::get< int >( multiplicity ) );

  // average energy data
  CHECK( std::nullopt == chunk.averageEnergy() );

  // distribution data
  auto distribution = chunk.distributionData();
  CHECK( true == std::holds_alternative< TwoBodyDistributionData >( distribution.value() ) );

  double normalisation = normalise ? 2. : 1.;

  auto data = std::get< TwoBodyDistributionData >( distribution.value() );
  CHECK( DistributionDataType::TwoBody == data.type() );
  CHECK( ReferenceFrame::CentreOfMass == data.frame() );
  CHECK( true == std::holds_alternative< LegendreAngularDistributions >( data.angle() ) );
  LegendreAngularDistributions angle = std::get< LegendreAngularDistributions >( data.angle() );
  CHECK( 2 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 2 == angle.grid().size() );
  CHECK( 2 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( angle.grid()[0] ) );
  CHECK_THAT( 20. , WithinRel( angle.grid()[1] ) );
  CHECK( 1 == angle.distributions()[0].pdf().coefficients().size() );
  CHECK( 2 == angle.distributions()[1].pdf().coefficients().size() );
  CHECK_THAT( 1.  / normalisation, WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
  CHECK_THAT( 1.  / normalisation, WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.2 / normalisation, WithinRel( angle.distributions()[1].pdf().coefficients()[1] ) );
  CHECK( 2 == angle.distributions()[0].cdf().coefficients().size() );
  CHECK( 3 == angle.distributions()[1].cdf().coefficients().size() );
  CHECK_THAT( 1.                 / normalisation, WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.                 / normalisation, WithinRel( angle.distributions()[0].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.9333333333333333 / normalisation, WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( angle.distributions()[1].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.0666666666666666 / normalisation, WithinRel( angle.distributions()[1].cdf().coefficients()[2] ) );
  CHECK( 1 == angle.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );

  // metadata
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( true == chunk.hasDistributionData() );
}

void verifyTabulatedChunk( const ReactionProduct& chunk, bool normalise ) {

  // ReactionProduct identifier
  CHECK( id::ParticleID( "n" ) == chunk.identifier() );

  // multiplicity
  CHECK( true == std::holds_alternative< TabulatedMultiplicity >( chunk.multiplicity() ) );
  auto multiplicity = std::get< TabulatedMultiplicity >( chunk.multiplicity() );
  CHECK( 5 == multiplicity.numberPoints() );
  CHECK( 2 == multiplicity.numberRegions() );
  CHECK( 5 == multiplicity.energies().size() );
  CHECK( 5 == multiplicity.values().size() );
  CHECK( 2 == multiplicity.boundaries().size() );
  CHECK( 2 == multiplicity.interpolants().size() );
  CHECK_THAT( 1., WithinRel( multiplicity.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( multiplicity.energies()[1] ) );
  CHECK_THAT( 2., WithinRel( multiplicity.energies()[2] ) );
  CHECK_THAT( 3., WithinRel( multiplicity.energies()[3] ) );
  CHECK_THAT( 4., WithinRel( multiplicity.energies()[4] ) );
  CHECK_THAT( 4., WithinRel( multiplicity.values()[0] ) );
  CHECK_THAT( 3., WithinRel( multiplicity.values()[1] ) );
  CHECK_THAT( 4., WithinRel( multiplicity.values()[2] ) );
  CHECK_THAT( 3., WithinRel( multiplicity.values()[3] ) );
  CHECK_THAT( 2., WithinRel( multiplicity.values()[4] ) );
  CHECK( 1 == multiplicity.boundaries()[0] );
  CHECK( 4 == multiplicity.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == multiplicity.interpolants()[0] );
  CHECK( InterpolationType::LinearLog == multiplicity.interpolants()[1] );
  CHECK( false == multiplicity.isLinearised() );

  // average energy data
  CHECK( std::nullopt == chunk.averageEnergy() );

  // distribution data
  // distribution data
  auto distribution = chunk.distributionData();
  CHECK( true == std::holds_alternative< TwoBodyDistributionData >( distribution.value() ) );

  double normalisation = normalise ? 2. : 1.;

  auto data = std::get< TwoBodyDistributionData >( distribution.value() );
  CHECK( DistributionDataType::TwoBody == data.type() );
  CHECK( ReferenceFrame::CentreOfMass == data.frame() );
  CHECK( true == std::holds_alternative< LegendreAngularDistributions >( data.angle() ) );
  LegendreAngularDistributions angle = std::get< LegendreAngularDistributions >( data.angle() );
  CHECK( 2 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 2 == angle.grid().size() );
  CHECK( 2 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( angle.grid()[0] ) );
  CHECK_THAT( 20. , WithinRel( angle.grid()[1] ) );
  CHECK( 1 == angle.distributions()[0].pdf().coefficients().size() );
  CHECK( 2 == angle.distributions()[1].pdf().coefficients().size() );
  CHECK_THAT( 1.  / normalisation, WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
  CHECK_THAT( 1.  / normalisation, WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.2 / normalisation, WithinRel( angle.distributions()[1].pdf().coefficients()[1] ) );
  CHECK( 2 == angle.distributions()[0].cdf().coefficients().size() );
  CHECK( 3 == angle.distributions()[1].cdf().coefficients().size() );
  CHECK_THAT( 1.                 / normalisation, WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.                 / normalisation, WithinRel( angle.distributions()[0].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.9333333333333333 / normalisation, WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
  CHECK_THAT( 1.0                / normalisation, WithinRel( angle.distributions()[1].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.0666666666666666 / normalisation, WithinRel( angle.distributions()[1].cdf().coefficients()[2] ) );
  CHECK( 1 == angle.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );

  // metadata
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( true == chunk.hasDistributionData() );
}
