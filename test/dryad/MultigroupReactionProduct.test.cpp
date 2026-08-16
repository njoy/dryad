// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/MultigroupReactionProduct.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const MultigroupReactionProduct& );
void verifyMultigroupChunk( const MultigroupReactionProduct& );

SCENARIO( "MultigroupReactionProduct" ) {

  GIVEN( "valid data for a MultigroupReactionProduct with an integer multiplicity" ) {

    WHEN( "the data is given explicitly" ) {

      id::ParticleID id = id::ParticleID::neutron();
      int multiplicity = 1;
      MultigroupAverageCosine cosine( { 1., 2., 3. }, { 0.1, 0.2 } );
      MultigroupAverageEnergy energy( { 1., 2., 3. }, { 1., 2. } );

      MultigroupReactionProduct chunk( id, multiplicity, cosine, energy );

      verifyChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a MultigroupReactionProduct with a multigroup multiplicity" ) {

    WHEN( "the data is given explicitly" ) {

      id::ParticleID id = id::ParticleID::neutron();
      MultigroupMultiplicity multiplicity( { 1., 2., 3. }, { 4., 3. } );
      MultigroupAverageCosine cosine( { 1., 2., 3. }, { 0.1, 0.2 } );
      MultigroupAverageEnergy energy( { 1., 2., 3. }, { 1., 2. } );

      MultigroupReactionProduct chunk( id, multiplicity, cosine, energy );

      verifyMultigroupChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of MultigroupReactionProduct is given" ) {

      MultigroupAverageCosine cosine( { 1., 2., 3. }, { 0.1, 0.2 } );
      MultigroupAverageEnergy energy( { 1., 2., 3. }, { 1., 2. } );
      MultigroupReactionProduct chunk( id::ParticleID::neutron(), 1, cosine, energy );

      THEN( "the product identifier can be changed" ) {

        id::ParticleID newid = id::ParticleID::proton();
        id::ParticleID original = id::ParticleID::neutron();

        chunk.productIdentifier( newid );

        CHECK( newid == chunk.productIdentifier() );

        chunk.productIdentifier( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the parent identifier can be changed" ) {

        std::optional< id::ParticleID > newid = id::ParticleID::proton();
        std::optional< id::ParticleID > original = std::nullopt;

        chunk.parentIdentifier( newid );

        CHECK( newid == chunk.parentIdentifier() );

        chunk.parentIdentifier( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the chain index can be changed" ) {

        std::size_t newindex = 1;
        std::size_t original = 0;

        chunk.chainIndex( newindex );

        CHECK( newindex == chunk.chainIndex() );

        chunk.chainIndex( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the multiplicity can be changed" ) {

        MultigroupMultiplicity newmultiplicity( { 1., 2., 3. }, { 4., 3. } );
        int original = 1;

        chunk.multiplicity( newmultiplicity );

        verifyMultigroupChunk( chunk );

        chunk.multiplicity( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the average cosine data can be changed" ) {

        std::optional< MultigroupAverageCosine > newaverage =
            MultigroupAverageCosine( { 1., 2., 3., 4. }, { -1., 0., 1. } );
        std::optional< MultigroupAverageCosine > original = cosine;

        chunk.averageCosine( newaverage );

        CHECK( newaverage == chunk.averageCosine() );

        chunk.averageCosine( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the average energy data can be changed" ) {

        std::optional< MultigroupAverageEnergy > newaverage =
            MultigroupAverageEnergy( { 1., 2., 3., 4. }, { 4., 3., 2. } );
        std::optional< MultigroupAverageEnergy > original = energy;

        chunk.averageEnergy( newaverage );

        CHECK( newaverage == chunk.averageEnergy() );

        chunk.averageEnergy( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of MultigroupReactionProduct are given" ) {

      MultigroupReactionProduct left( id::ParticleID::neutron(), 1 );
      MultigroupReactionProduct equal( id::ParticleID::neutron(), 1 );
      MultigroupReactionProduct different( id::ParticleID::proton(), 1 );

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

void verifyChunk( const MultigroupReactionProduct& chunk ) {

  // MultigroupReactionProduct identifier
  CHECK( id::ParticleID( "n" ) == chunk.productIdentifier() );
  CHECK( std::nullopt == chunk.parentIdentifier() );
  CHECK( 0 == chunk.chainIndex() );

  // multiplicity
  auto multiplicity = chunk.multiplicity();
  CHECK( true == std::holds_alternative< int >( multiplicity ) );
  CHECK( 1 == std::get< int >( multiplicity ) );

  // average cosine and energy data
  CHECK( true == chunk.averageCosine().has_value() );
  CHECK( 2 == chunk.averageCosine().value().numberGroups() );
  CHECK( 3 == chunk.averageCosine().value().boundaries().size() );
  CHECK_THAT( 1., WithinRel( chunk.averageCosine().value().boundaries()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.averageCosine().value().boundaries()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.averageCosine().value().boundaries()[2] ) );
  CHECK_THAT( 0.1, WithinRel( chunk.averageCosine().value().values()[0] ) );
  CHECK_THAT( 0.2, WithinRel( chunk.averageCosine().value().values()[1] ) );

  CHECK( true == chunk.averageEnergy().has_value() );
  CHECK( 2 == chunk.averageEnergy().value().numberGroups() );
  CHECK( 3 == chunk.averageEnergy().value().boundaries().size() );
  CHECK_THAT( 1., WithinRel( chunk.averageEnergy().value().boundaries()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.averageEnergy().value().boundaries()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.averageEnergy().value().boundaries()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.averageEnergy().value().values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.averageEnergy().value().values()[1] ) );

  // metadata
  CHECK( true == chunk.hasAverageCosine() );
  CHECK( true == chunk.hasAverageEnergy() );
}

void verifyMultigroupChunk( const MultigroupReactionProduct& chunk ) {

  // MultigroupReactionProduct identifier
  CHECK( id::ParticleID( "n" ) == chunk.productIdentifier() );
  CHECK( std::nullopt == chunk.parentIdentifier() );
  CHECK( 0 == chunk.chainIndex() );

  // multiplicity
  CHECK( true == std::holds_alternative< MultigroupMultiplicity >( chunk.multiplicity() ) );
  auto multiplicity = std::get< MultigroupMultiplicity >( chunk.multiplicity() );
  CHECK( 2 == multiplicity.numberGroups() );
  CHECK_THAT( 4., WithinRel( multiplicity.values()[0] ) );
  CHECK_THAT( 3., WithinRel( multiplicity.values()[1] ) );

  // average cosine and energy data
  CHECK( true == chunk.averageCosine().has_value() );
  CHECK( 2 == chunk.averageCosine().value().numberGroups() );
  CHECK( 3 == chunk.averageCosine().value().boundaries().size() );
  CHECK_THAT( 1., WithinRel( chunk.averageCosine().value().boundaries()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.averageCosine().value().boundaries()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.averageCosine().value().boundaries()[2] ) );
  CHECK_THAT( 0.1, WithinRel( chunk.averageCosine().value().values()[0] ) );
  CHECK_THAT( 0.2, WithinRel( chunk.averageCosine().value().values()[1] ) );

  CHECK( true == chunk.averageEnergy().has_value() );
  CHECK( 2 == chunk.averageEnergy().value().numberGroups() );
  CHECK( 3 == chunk.averageEnergy().value().boundaries().size() );
  CHECK_THAT( 1., WithinRel( chunk.averageEnergy().value().boundaries()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.averageEnergy().value().boundaries()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.averageEnergy().value().boundaries()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.averageEnergy().value().values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.averageEnergy().value().values()[1] ) );

  // metadata
  CHECK( true == chunk.hasAverageCosine() );
  CHECK( true == chunk.hasAverageEnergy() );
}
