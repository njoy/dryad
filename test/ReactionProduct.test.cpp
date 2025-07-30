// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/ReactionProduct.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const ReactionProduct& );
void verifyTabulatedChunk( const ReactionProduct& );
void verifyTabulatedLinearisedChunk( const ReactionProduct& );

SCENARIO( "ReactionProduct" ) {

  GIVEN( "valid data for a ReactionProduct with an integer multiplicity" ) {

    WHEN( "the data is given explicitly" ) {

      id::ParticleID id = id::ParticleID::neutron();
      int multiplicity = 1;

      ReactionProduct chunk( std::move( id ), std::move( multiplicity ) );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
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

      ReactionProduct chunk( std::move( id ), std::move( multiplicity ) );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyTabulatedChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of Reaction is given" ) {

      ReactionProduct chunk( id::ParticleID::neutron(), 1 );

      THEN( "the product identifier can be changed" ) {

        id::ParticleID newid = id::ParticleID::proton();
        id::ParticleID original = id::ParticleID::neutron();

        chunk.identifier( newid );

        CHECK( newid == chunk.identifier() );

        chunk.identifier( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the multiplicity can be changed" ) {

        TabulatedMultiplicity newmultiplicity( { 1., 2., 2., 3., 4. },
                                               { 4., 3., 4., 3., 2. },
                                               { 1, 4 },
                                               { InterpolationType::LinearLinear,
                                                 InterpolationType::LinearLog } );
        int original = 1;

        chunk.multiplicity( newmultiplicity );

        verifyTabulatedChunk( chunk );

        chunk.multiplicity( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the distribution data can be changed" ) {

        std::optional< ReactionProduct::DistributionData > newdistribution =
            TwoBodyDistributionData( ReferenceFrame::CentreOfMass, IsotropicAngularDistributions() );
        std::optional< ReactionProduct::DistributionData > original = std::nullopt;

        chunk.distributionData( newdistribution );

        CHECK( newdistribution == chunk.distributionData() );

        chunk.distributionData( original );

        verifyChunk( chunk );
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

        verifyChunk( chunk );
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

void verifyChunk( const ReactionProduct& chunk ) {

  // ReactionProduct identifier
  CHECK( id::ParticleID( "n" ) == chunk.identifier() );

  // multiplicity
  auto multiplicity = chunk.multiplicity();
  CHECK( true == std::holds_alternative< int >( multiplicity ) );
  CHECK( 1 == std::get< int >( multiplicity ) );

  // distribution data
  CHECK( std::nullopt == chunk.averageEnergy() );

  // distribution data
  CHECK( std::nullopt == chunk.distributionData() );

  // metadata
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( false == chunk.hasDistributionData() );
}

void verifyTabulatedChunk( const ReactionProduct& chunk ) {

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

  // distribution data
  CHECK( std::nullopt == chunk.averageEnergy() );

  // distribution data
  CHECK( std::nullopt == chunk.distributionData() );

  // metadata
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( false == chunk.hasDistributionData() );
}
