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

      THEN( "a ProjectileTarget can be linearised" ) {

        ProjectileTarget linear = chunk.linearise();

        verifyLinearisedChunk( linear );
      } // THEN

      THEN( "a ProjectileTarget can be linearised inplace" ) {

        ProjectileTarget copy = chunk; // we'll do this test on a copy
        verifyChunk( copy );
        copy.lineariseInplace();
        verifyLinearisedChunk( copy );
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
  CHECK( ReactionType::Primary == reaction.type() );
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
  CHECK( ReactionType::Primary == reaction.type() );
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

void verifyLinearisedChunk( const ProjectileTarget& chunk ) {

  // identifiers
  CHECK( id::ParticleID( "n" ) == chunk.projectileIdentifier() );
  CHECK( id::ParticleID( "Fe56" ) == chunk.targetIdentifier() );

  // resonances are not present
  CHECK( std::nullopt == chunk.resonances() );

  // reactions
  auto reaction = chunk.reactions()[0];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK_THAT( 0, WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( 0, WithinRel( reaction.reactionQValue().value() ) );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );
  CHECK( 65 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 65 == reaction.crossSection().energies().size() );
  CHECK( 65 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(    5.0000075, WithinRel( reaction.crossSection().energies()[16] ) );
  CHECK_THAT(   10.000005, WithinRel( reaction.crossSection().energies()[32] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[64] ) );
  CHECK_THAT( 1000., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT(  316.227766016838, WithinRel( reaction.crossSection().values()[16] ) );
  CHECK_THAT(  100., WithinRel( reaction.crossSection().values()[32] ) );
  CHECK_THAT(   10., WithinRel( reaction.crossSection().values()[64] ) );
  CHECK( 64 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );
  reaction = chunk.reactions()[1];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56_e1" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );
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
  CHECK( true == chunk.isLinearised() );
}
