// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/MultigroupProjectileTarget.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

MultigroupProjectileTarget makeMultigroupProjectileTarget();
void verifyChunk( const MultigroupProjectileTarget& );
void verifyCorrectSummation( const MultigroupProjectileTarget& );

SCENARIO( "MultigroupProjectileTarget" ) {

  GIVEN( "valid data for a MultigroupProjectileTarget" ) {

    WHEN( "the data is given explicitly" ) {

      MultigroupProjectileTarget chunk = makeMultigroupProjectileTarget();

      verifyChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "calculateSummationCrossSections" ) {

    WHEN( "an instance of MultigroupProjectileTarget is given" ) {

      MultigroupProjectileTarget chunk = makeMultigroupProjectileTarget();

      THEN( "the summation cross sections can be recalculated" ) {

        chunk.calculateSummationCrossSections();

        verifyCorrectSummation( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of MultigroupProjectileTarget is given" ) {

      MultigroupProjectileTarget chunk = makeMultigroupProjectileTarget();

      THEN( "the projectile identifier can be changed" ) {

        id::ParticleID newprojectile = id::ParticleID::proton();
        id::ParticleID original = id::ParticleID::neutron();

        chunk.projectileIdentifier( newprojectile );

        CHECK( newprojectile == chunk.projectileIdentifier() );

        chunk.projectileIdentifier( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the target identifier can be changed" ) {

        id::ParticleID newtarget = id::ParticleID( "H1" );
        id::ParticleID original = id::ParticleID( "Fe56" );

        chunk.targetIdentifier( newtarget );

        CHECK( newtarget == chunk.targetIdentifier() );

        chunk.targetIdentifier( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the interaction type can be changed" ) {

        InteractionType newtype = InteractionType::Atomic;
        InteractionType original = InteractionType::Nuclear;

        chunk.interactionType( newtype );

        CHECK( newtype == chunk.interactionType() );

        chunk.interactionType( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the reaction data can be changed" ) {

        std::vector< MultigroupReaction > newreactions = {

          MultigroupReaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ),
                              MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 0., 0., 0., 1. } ),
                              {}, 0., -1. )
        };
        std::vector< MultigroupReaction > original = chunk.reactions();

        chunk.reactions( newreactions );

        CHECK( newreactions == chunk.reactions() );
        CHECK( 1 == chunk.reactions().size() );

        chunk.reactions( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of MultigroupProjectileTarget are given" ) {

      MultigroupProjectileTarget left( id::ParticleID::neutron(), id::ParticleID( "Fe56" ),
                                       InteractionType::Nuclear,
                                       { MultigroupReaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                                             MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } ),
                                                             {}, 0., 0. ) } );
      MultigroupProjectileTarget equal( id::ParticleID::neutron(), id::ParticleID( "Fe56" ),
                                        InteractionType::Nuclear,
                                        { MultigroupReaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                                              MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } ),
                                                              {}, 0., 0. ) } );
      MultigroupProjectileTarget different( id::ParticleID::neutron(), id::ParticleID( "Fe56" ),
                                            InteractionType::Nuclear,
                                            { MultigroupReaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ),
                                                                  MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 0., 0., 0., 1. } ),
                                                                  {}, 0., -1. ) } );

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

MultigroupProjectileTarget makeMultigroupProjectileTarget() {

  id::ParticleID projectile( "n" );
  id::ParticleID target( "Fe56" );

  InteractionType type = InteractionType::Nuclear;

  std::vector< MultigroupReaction > reactions = {

    MultigroupReaction( id::ReactionID( "n,Fe56->total" ),
                        { id::ReactionID( "n,Fe56->n,Fe56" ),
                          id::ReactionID( "n,Fe56->2n,Fe55[all]" ) },
                        MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 5., 4., 4., 5. } ) ),
    MultigroupReaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                        MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } ),
                        { MultigroupReactionProduct( id::ParticleID( "n" ), 1 ) },
                        0., 0. ),
    MultigroupReaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ),
                        { id::ReactionID( "n,Fe56->2n,Fe55" ),
                          id::ReactionID( "n,Fe56->2n,Fe55_e1" ) },
                        MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 1., 1., 2., 4. } ) ),
    MultigroupReaction( id::ReactionID( "n,Fe56->2n,Fe55" ),
                        MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 0., 0., 1., 2. } ),
                        {}, 0., -1. ),
    MultigroupReaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ),
                        MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 0., 0., 0., 1. } ),
                        {}, 0., -1. )
  };

  return MultigroupProjectileTarget( std::move( projectile ), std::move( target ),
                                     type, std::move( reactions ) );
}

void verifyChunk( const MultigroupProjectileTarget& chunk ) {

  // documentation
  CHECK( std::nullopt == chunk.documentation().library() );
  CHECK( std::nullopt == chunk.documentation().version() );
  CHECK( std::nullopt == chunk.documentation().description() );

  // identifiers
  CHECK( id::ParticleID( "n" ) == chunk.projectileIdentifier() );
  CHECK( id::ParticleID( "Fe56" ) == chunk.targetIdentifier() );

  // interaction type
  CHECK( InteractionType::Nuclear == chunk.interactionType() );

  // reactions are present
  CHECK( 5 == chunk.numberReactions() );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->total" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->n,Fe56" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) ) );
  CHECK( false == chunk.hasReaction( id::ReactionID( "n,Fe56->p,Mn56" ) ) );

  // reactions
  auto reaction = chunk.reactions()[0];
  CHECK( id::ReactionID( "n,Fe56->total" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 3 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.partialReactionIdentifiers().value()[2] );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 5., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 4., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 4., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 5., WithinRel( reaction.crossSection().values()[3] ) );

  reaction = chunk.reactions()[1];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT( 0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( 0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( true == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 4., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 3., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 2., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[3] ) );
  auto product = reaction.product( id::ParticleID( "n" ) );
  CHECK( 1 == std::get< int >( product.multiplicity() ) );

  reaction = chunk.reactions()[2];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 2 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 2., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 4., WithinRel( reaction.crossSection().values()[3] ) );

  reaction = chunk.reactions()[3];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT( 0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 2., WithinRel( reaction.crossSection().values()[3] ) );

  reaction = chunk.reactions()[4];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT( 0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[3] ) );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->total" ) );
  CHECK( id::ReactionID( "n,Fe56->total" ) == reaction.identifier() );
  CHECK( 3 == reaction.numberPartialReactions() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->n,Fe56" ) );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( true == reaction.hasProducts() );

  // covariance data
  CHECK( std::nullopt == chunk.covarianceData() );
}

void verifyCorrectSummation( const MultigroupProjectileTarget& chunk ) {

  // documentation
  CHECK( std::nullopt == chunk.documentation().library() );
  CHECK( std::nullopt == chunk.documentation().version() );
  CHECK( std::nullopt == chunk.documentation().description() );

  // identifiers
  CHECK( id::ParticleID( "n" ) == chunk.projectileIdentifier() );
  CHECK( id::ParticleID( "Fe56" ) == chunk.targetIdentifier() );

  // interaction type
  CHECK( InteractionType::Nuclear == chunk.interactionType() );

  // reactions are present
  CHECK( 5 == chunk.numberReactions() );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->total" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->n,Fe56" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) ) );
  CHECK( false == chunk.hasReaction( id::ReactionID( "n,Fe56->p,Mn56" ) ) );

  // reactions
  auto reaction = chunk.reactions()[0];
  CHECK( id::ReactionID( "n,Fe56->total" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 3 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.partialReactionIdentifiers().value()[2] );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 4., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 3., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 3., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 4., WithinRel( reaction.crossSection().values()[3] ) );

  reaction = chunk.reactions()[1];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT( 0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( 0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( true == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 4., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 3., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 2., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[3] ) );
  auto product = reaction.product( id::ParticleID( "n" ) );
  CHECK( 1 == std::get< int >( product.multiplicity() ) );

  reaction = chunk.reactions()[2];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 2 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 3., WithinRel( reaction.crossSection().values()[3] ) );

  reaction = chunk.reactions()[3];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT( 0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 2., WithinRel( reaction.crossSection().values()[3] ) );

  reaction = chunk.reactions()[4];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT( 0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberGroups() );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[3] ) );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->total" ) );
  CHECK( id::ReactionID( "n,Fe56->total" ) == reaction.identifier() );
  CHECK( 3 == reaction.numberPartialReactions() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->n,Fe56" ) );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( true == reaction.hasProducts() );

  // covariance data
  CHECK( std::nullopt == chunk.covarianceData() );
}
