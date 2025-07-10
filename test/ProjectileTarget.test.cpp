// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/ProjectileTarget.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const ProjectileTarget& );
void verifyLinearisedChunk( const ProjectileTarget& );

SCENARIO( "ProjectileTarget" ) {

  GIVEN( "valid data for a ProjectileTarget" ) {

    WHEN( "the data is given explicitly" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "Fe56" );

      InteractionType type = InteractionType::Nuclear;

      std::vector< Reaction > reactions = {

        Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                  TabulatedCrossSection( { 1e-5, 20. }, { 1000., 10. },
                                           InterpolationType::LogLinear ),
                  {},
                  0, 0 ),
        Reaction( id::ReactionID( "n,Fe56->n,Fe56_e1" ),
                  TabulatedCrossSection( { 1., 20. }, { 0., 100. },
                                           InterpolationType::LinearLinear ),
                  {},
                  0, -1 )
      };

      ProjectileTarget chunk( std::move( projectile ), std::move( target ),
                              type, std::move( reactions ) );

      THEN( "a ProjectileTarget can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ProjectileTarget are given" ) {

      ProjectileTarget left( id::ParticleID::neutron(), id::ParticleID( 26056 ),
                             InteractionType::Nuclear,
                             { Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                         TabulatedCrossSection( { 1e-5, 20. }, { 1000., 10. },
                                                                  InterpolationType::LogLinear ),
                                         {},
                                         0, 0 ),
                              Reaction( id::ReactionID( "n,Fe56->n,Fe56_e1" ),
                                        TabulatedCrossSection( { 1., 20. }, { 0., 100. },
                                                                 InterpolationType::LinearLinear ),
                                        {},
                                        0, -1 ) } );
      ProjectileTarget equal( id::ParticleID::neutron(), id::ParticleID( 26056 ),
                              InteractionType::Nuclear,
                              { Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                          TabulatedCrossSection( { 1e-5, 20. }, { 1000., 10. },
                                                                   InterpolationType::LogLinear ),
                                          {},
                                          0, 0 ),
                               Reaction( id::ReactionID( "n,Fe56->n,Fe56_e1" ),
                                         TabulatedCrossSection( { 1., 20. }, { 0., 100. },
                                                                  InterpolationType::LinearLinear ),
                                         {},
                                         0, -1 ) } );
      ProjectileTarget different( id::ParticleID::neutron(), id::ParticleID( 26056 ),
                                  InteractionType::Nuclear,
                                  { Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                              TabulatedCrossSection( { 1e-5, 20. }, { 1000., 10. },
                                                                       InterpolationType::LogLinear ),
                                              {},
                                              0, 0 ) } );

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

void verifyChunk( const ProjectileTarget& chunk ) {

  // identifiers
  CHECK( id::ParticleID( "n" ) == chunk.projectileIdentifier() );
  CHECK( id::ParticleID( "Fe56" ) == chunk.targetIdentifier() );

  // interaction type
  CHECK( InteractionType::Nuclear == chunk.interactionType() );

  // resonances are not present
  CHECK( std::nullopt == chunk.resonances() );

  // reactions are present
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->n,Fe56" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->n,Fe56_e1" ) ) );
  CHECK( false == chunk.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

  // reactions
  auto reaction = chunk.reactions()[0];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK( false == reaction.hasProducts() );
  CHECK( false == reaction.isLinearised() );
  CHECK_THAT( 0, WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( 0, WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 1000., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT(   10., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LogLinear == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.crossSection().isLinearised() );
  reaction = chunk.reactions()[1];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56_e1" ) == reaction.identifier() );
  CHECK_THAT( 0, WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1, WithinRel( reaction.reactionQValue().value() ) );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(   1., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(  20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT(   0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 100., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  // reaction
  reaction = chunk.reaction( id::ReactionID( "n,Fe56->n,Fe56" ) );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK( false == reaction.hasProducts() );
  CHECK( false == reaction.isLinearised() );
  CHECK_THAT( 0, WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( 0, WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 1000., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT(   10., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LogLinear == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.crossSection().isLinearised() );
  reaction = chunk.reaction( id::ReactionID( "n,Fe56->n,Fe56_e1" ) );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56_e1" ) == reaction.identifier() );
  CHECK_THAT( 0, WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1, WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(   1., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(  20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT(   0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 100., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  // metadata
  CHECK( false == chunk.isLinearised() );
}
