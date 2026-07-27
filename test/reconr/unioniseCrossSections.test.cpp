// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/reconr/unioniseCrossSections.hpp"

// other includes

// convenience typedefs
using namespace njoy::reconr;
using namespace njoy::dryad;

ProjectileTarget makeProjectiletarget();
void verifyChunk( const ProjectileTarget&, bool );

SCENARIO( "unioniseCrossSections" ) {

  GIVEN( "a ProjectileTarget instance" ) {

    ProjectileTarget pt = makeProjectiletarget();

    unioniseCrossSections( pt, false );
    verifyChunk( pt, false );

    pt = makeProjectiletarget();

    unioniseCrossSections( pt, true );
    verifyChunk( pt, true );
  } // GIVEN
} // SCENARIO

ProjectileTarget makeProjectiletarget() {

  id::ParticleID projectile( "n" );
  id::ParticleID target( "Fe56" );

  InteractionType type = InteractionType::Nuclear;

  std::vector< Reaction > reactions = {

    Reaction( id::ReactionID( "n,Fe56->total" ),
              { id::ReactionID( "n,Fe56->n,Fe56" ),
                id::ReactionID( "n,Fe56->2n,Fe55[all]" ),
                id::ReactionID( "n,Fe56->p,Mn56[all]" ),
                id::ReactionID( "n,Fe56->a,Cr53[all]" ) },
              TabulatedCrossSection( { 1e-5, 20. }, { 1000001., 1000001. },
                                       InterpolationType::Histogram ),
              {} ),
    Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
              TabulatedCrossSection( { 1e-5, 20. }, { 1e+6, 1e+6 },
                                       InterpolationType::LinearLinear ),
              { ReactionProduct( id::ParticleID( "n" ), 1,
                                 TwoBodyDistributionData ( ReferenceFrame::CentreOfMass,
                                                           LegendreAngularDistributions(
                                                             { 1e-5, 20. },
                                                             { { { 1.0 } }, { { 1.0, 0.2 } } } ) ) ) },
              0, 0 ),
    Reaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ),
              { id::ReactionID( "n,Fe56->2n,Fe55" ),
                id::ReactionID( "n,Fe56->2n,Fe55_e1" ) },
              TabulatedCrossSection( { 1., 20. }, { 0., 3. },
                                       InterpolationType::Histogram ),
              {} ),
    Reaction( id::ReactionID( "n,Fe56->2n,Fe55" ),
              TabulatedCrossSection( { 1., 20. }, { 0., 2.00001 },
                                       InterpolationType::LinearLinear ),
              {},
              0, -1 ),
    Reaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ),
              TabulatedCrossSection( { 1., 20. }, { 0., 1. },
                                       InterpolationType::LinearLinear ),
              {},
              0, -1 ),
    Reaction( id::ReactionID( "n,Fe56->p,Mn56[all]" ),
              { id::ReactionID( "n,Fe56->p,Mn56" ),
                id::ReactionID( "n,Fe56->p,Mn56_e1" ) },
              TabulatedCrossSection( { 5., 20. }, { 0., 5. },
                                       InterpolationType::Histogram ),
              {} ),
    Reaction( id::ReactionID( "n,Fe56->p,Mn56" ),
              TabulatedCrossSection( { 5., 20. }, { 0., 3.00001 },
                                       InterpolationType::LinearLinear ),
              {},
              0, -5 ),
    Reaction( id::ReactionID( "n,Fe56->p,Mn56_e1" ),
              TabulatedCrossSection( { 5., 20. }, { 0., 2. },
                                       InterpolationType::LinearLinear ),
              {},
              0, -5 ),
    Reaction( id::ReactionID( "n,Fe56->a,Cr53[all]" ),
              TabulatedCrossSection( { 1e-5, 20. }, { 1., 1. },
                                       InterpolationType::LinearLinear ),
              {},
              0, 0 )
  };

  return ProjectileTarget( std::move( projectile ), std::move( target ),
                           type, std::move( reactions ), std::nullopt );
}

void verifyChunk( const ProjectileTarget& chunk, bool exclude ) {

  // only the xs are changed, so products are not checked

  // documentation
  CHECK( std::nullopt == chunk.documentation().library() );
  CHECK( std::nullopt == chunk.documentation().version() );
  CHECK( std::nullopt == chunk.documentation().description() );

  // identifiers
  CHECK( id::ParticleID( "n" ) == chunk.projectileIdentifier() );
  CHECK( id::ParticleID( "Fe56" ) == chunk.targetIdentifier() );

  // interaction type
  CHECK( InteractionType::Nuclear == chunk.interactionType() );

  // particle database is not present
  CHECK( std::nullopt == chunk.particleData() );

  // resonances are not present
  CHECK( std::nullopt == chunk.resonances() );

  // reactions are present
  CHECK( 9 == chunk.numberReactions() );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->total" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->n,Fe56" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->p,Mn56[all]" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->p,Mn56" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->p,Mn56_e1" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->a,Cr53[all]" ) ) );
//  CHECK( false == chunk.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

  // reactions
  auto reaction = chunk.reactions()[0];
  CHECK( id::ReactionID( "n,Fe56->total" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 6 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.partialReactionIdentifiers().value()[2] );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.partialReactionIdentifiers().value()[3] );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56_e1" ) == reaction.partialReactionIdentifiers().value()[4] );
  CHECK( id::ReactionID( "n,Fe56->a,Cr53[all]" ) == reaction.partialReactionIdentifiers().value()[5] );
  CHECK( false == reaction.hasProducts() );
  if ( exclude ) {

    CHECK( 2 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 2 == reaction.crossSection().energies().size() );
    CHECK( 2 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1000001., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1000001., WithinRel( reaction.crossSection().values()[1] ) );
    CHECK( 1 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[0] );
    CHECK( false == reaction.crossSection().isLinearised() );
  }
  else {

    CHECK( 4 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 4 == reaction.crossSection().energies().size() );
    CHECK( 4 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
    CHECK_THAT( 1000001., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1000001., WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 1000001., WithinRel( reaction.crossSection().values()[2] ) );
    CHECK_THAT( 1000001., WithinRel( reaction.crossSection().values()[3] ) );
    CHECK( 3 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[0] );
    CHECK( false == reaction.crossSection().isLinearised() );
  }

  reaction = chunk.reactions()[1];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( true == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 4 == reaction.crossSection().energies().size() );
  CHECK( 4 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
  CHECK_THAT( 1000000., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1000000., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 1000000., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1000000., WithinRel( reaction.crossSection().values()[3] ) );
  CHECK( 3 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

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
  if ( exclude ) {

    CHECK( 2 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 2 == reaction.crossSection().energies().size() );
    CHECK( 2 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(  1., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 3., WithinRel( reaction.crossSection().values()[1] ) );
    CHECK( 1 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[0] );
    CHECK( false == reaction.crossSection().isLinearised() );
  }
  else {

    CHECK( 4 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 4 == reaction.crossSection().energies().size() );
    CHECK( 4 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[2] ) );
    CHECK_THAT( 3., WithinRel( reaction.crossSection().values()[3] ) );
    CHECK( 1 == reaction.crossSection().boundaries()[0] );
    CHECK( 3 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[1] );
    CHECK( false == reaction.crossSection().isLinearised() );
  }

  reaction = chunk.reactions()[3];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 4 == reaction.crossSection().energies().size() );
  CHECK( 4 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 2.00001 / 19. * 4., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 2.00001, WithinRel( reaction.crossSection().values()[3] ) );
  CHECK( 3 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[4];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 4 == reaction.crossSection().energies().size() );
  CHECK( 4 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 1. / 19. * 4., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[3] ) );
  CHECK( 3 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[5];
  CHECK( id::ReactionID( "n,Fe56->p,Mn56[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 2 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56_e1" ) == reaction.partialReactionIdentifiers().value()[1] );
  if ( exclude ) {

    CHECK( 2 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 2 == reaction.crossSection().energies().size() );
    CHECK( 2 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(  5., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 5., WithinRel( reaction.crossSection().values()[1] ) );
    CHECK( 1 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[0] );
    CHECK( false == reaction.crossSection().isLinearised() );
  }
  else {

    CHECK( false == reaction.hasProducts() );
    CHECK( 4 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 4 == reaction.crossSection().energies().size() );
    CHECK( 4 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[2] ) );
    CHECK_THAT( 5., WithinRel( reaction.crossSection().values()[3] ) );
    CHECK( 2 == reaction.crossSection().boundaries()[0] );
    CHECK( 3 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[1] );
    CHECK( false == reaction.crossSection().isLinearised() );
  }

  reaction = chunk.reactions()[6];
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -5., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 4 == reaction.crossSection().energies().size() );
  CHECK( 4 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 3.00001, WithinRel( reaction.crossSection().values()[3] ) );
  CHECK( 3 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[7];
  CHECK( id::ReactionID( "n,Fe56->p,Mn56_e1" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -5., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 4 == reaction.crossSection().energies().size() );
  CHECK( 4 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 2., WithinRel( reaction.crossSection().values()[3] ) );
  CHECK( 3 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[8];
  CHECK( id::ReactionID( "n,Fe56->a,Cr53[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 4 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 4 == reaction.crossSection().energies().size() );
  CHECK( 4 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(    1., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT(    5., WithinRel( reaction.crossSection().energies()[2] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[3] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[3] ) );
  CHECK( 3 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );
}
