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

      THEN( "a ReactionProduct can be linearised" ) {

        ReactionProduct linear = chunk.linearise();

        verifyChunk( linear );
      } // THEN

      THEN( "a ReactionProduct can be linearised inplace" ) {

        ReactionProduct copy = chunk; // we'll do this test on a copy
        verifyChunk( copy );
        copy.lineariseInplace();
        verifyChunk( copy );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with an tabulated multiplicity" ) {

    WHEN( "the data is given explicitly" ) {

      id::ParticleID id( "n" );
      TabulatedMultiplicity multiplicity( { 1., 2., 2., 3., 4. },
                                          { 4., 3., 4., 3., 2. },
                                          { 1, 4 },
                                          { InterpolationType::LinearLinear,
                                            InterpolationType::LinearLog } );

      ReactionProduct chunk( std::move( id ), std::move( multiplicity ) );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyTabulatedChunk( chunk );
      } // THEN

      THEN( "a ReactionProduct can be linearised" ) {

        ReactionProduct linear = chunk.linearise();

        verifyTabulatedLinearisedChunk( linear );
      } // THEN

      THEN( "a ReactionProduct can be linearised inplace" ) {

        ReactionProduct copy = chunk; // we'll do this test on a copy
        verifyTabulatedChunk( copy );
        copy.lineariseInplace();
        verifyTabulatedLinearisedChunk( copy );
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
  CHECK( true == chunk.isLinearised() );
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
  CHECK( false == chunk.isLinearised() );
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( false == chunk.hasDistributionData() );
}

void verifyTabulatedLinearisedChunk( const ReactionProduct& chunk ) {

  // ReactionProduct identifier
  CHECK( id::ParticleID( "n" ) == chunk.identifier() );

  // multiplicity
  CHECK( true == std::holds_alternative< TabulatedMultiplicity >( chunk.multiplicity() ) );
  auto multiplicity = std::get< TabulatedMultiplicity >( chunk.multiplicity() );
  CHECK( 12 == multiplicity.numberPoints() );
  CHECK( 2 == multiplicity.numberRegions() );
  CHECK( 12 == multiplicity.energies().size() );
  CHECK( 12 == multiplicity.values().size() );
  CHECK( 2 == multiplicity.boundaries().size() );
  CHECK( 2 == multiplicity.interpolants().size() );
  CHECK_THAT( 1.   , WithinRel( multiplicity.energies()[0] ) );
  CHECK_THAT( 2.   , WithinRel( multiplicity.energies()[1] ) );
  CHECK_THAT( 2.   , WithinRel( multiplicity.energies()[2] ) );
  CHECK_THAT( 2.125, WithinRel( multiplicity.energies()[3] ) );
  CHECK_THAT( 2.25 , WithinRel( multiplicity.energies()[4] ) );
  CHECK_THAT( 2.5  , WithinRel( multiplicity.energies()[5] ) );
  CHECK_THAT( 2.75 , WithinRel( multiplicity.energies()[6] ) );
  CHECK_THAT( 3.   , WithinRel( multiplicity.energies()[7] ) );
  CHECK_THAT( 3.25 , WithinRel( multiplicity.energies()[8] ) );
  CHECK_THAT( 3.5  , WithinRel( multiplicity.energies()[9] ) );
  CHECK_THAT( 3.75 , WithinRel( multiplicity.energies()[10] ) );
  CHECK_THAT( 4.   , WithinRel( multiplicity.energies()[11] ) );
  CHECK_THAT( 4.              , WithinRel( multiplicity.values()[0] ) );
  CHECK_THAT( 3.              , WithinRel( multiplicity.values()[1] ) );
  CHECK_THAT( 4.              , WithinRel( multiplicity.values()[2] ) );
  CHECK_THAT( 3.85048128530886, WithinRel( multiplicity.values()[3] ) );
  CHECK_THAT( 3.70951129135145, WithinRel( multiplicity.values()[4] ) );
  CHECK_THAT( 3.44966028678679, WithinRel( multiplicity.values()[5] ) );
  CHECK_THAT( 3.21459646033567, WithinRel( multiplicity.values()[6] ) );
  CHECK_THAT( 3.              , WithinRel( multiplicity.values()[7] ) );
  CHECK_THAT( 2.72176678584324, WithinRel( multiplicity.values()[8] ) );
  CHECK_THAT( 2.46416306545103, WithinRel( multiplicity.values()[9] ) );
  CHECK_THAT( 2.22433973930853, WithinRel( multiplicity.values()[10] ) );
  CHECK_THAT( 2.              , WithinRel( multiplicity.values()[11] ) );
  CHECK( 1 == multiplicity.boundaries()[0] );
  CHECK( 11 == multiplicity.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == multiplicity.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == multiplicity.interpolants()[1] );
  CHECK( true == multiplicity.isLinearised() );

  // distribution data
  CHECK( std::nullopt == chunk.averageEnergy() );

  // distribution data
  CHECK( std::nullopt == chunk.distributionData() );

  // metadata
  CHECK( true == chunk.isLinearised() );
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( false == chunk.hasDistributionData() );
}
