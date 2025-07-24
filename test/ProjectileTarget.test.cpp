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

        Reaction( id::ReactionID( "n,Fe56->total" ),
                  { "n,Fe56->n,Fe56", "n,Fe56->2n,Fe55[all]",
                    "n,Fe56->3n,Fe54[all]", "n,Fe56->a,Cr52[all]" },
                  TabulatedCrossSection( { 1e-5, 20. }, { 1000001., 1000001. },
                                           InterpolationType::LogLinear ),
                  {} ),
        Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                  TabulatedCrossSection( { 1e-5, 20. }, { 1e+6, 1e+6 },
                                           InterpolationType::LinearLinear ),
                  {},
                  0, 0 ),
        Reaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ),
                  { "n,Fe56->2n,Fe55", "n,Fe56->2n,Fe55_e1" },
                  TabulatedCrossSection( { 1., 20. }, { 0., 3. },
                                           InterpolationType::LogLinear ),
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
        Reaction( id::ReactionID( "n,Fe56->3n,Fe54[all]" ),
                  { "n,Fe56->3n,Fe54", "n,Fe56->3n,Fe54_e1" },
                  TabulatedCrossSection( { 5., 20. }, { 0., 5. },
                                           InterpolationType::LogLinear ),
                  {} ),
        Reaction( id::ReactionID( "n,Fe56->3n,Fe54" ),
                  TabulatedCrossSection( { 5., 20. }, { 0., 3.00001 },
                                           InterpolationType::LinearLinear ),
                  {},
                  0, -5 ),
        Reaction( id::ReactionID( "n,Fe56->3n,Fe54_e1" ),
                  TabulatedCrossSection( { 5., 20. }, { 0., 2. },
                                           InterpolationType::LinearLinear ),
                  {},
                  0, -5 ),
        Reaction( id::ReactionID( "n,Fe56->a,Cr52[all]" ),
                  TabulatedCrossSection( { 1e-5, 20. }, { 1., 1. },
                                           InterpolationType::LinearLinear ),
                  {},
                  0, 0 )
      };

      ProjectileTarget chunk( std::move( projectile ), std::move( target ),
                              type, std::move( reactions ) );

      THEN( "a ProjectileTarget can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of ProjectileTarget is given" ) {

      ProjectileTarget chunk( id::ParticleID::neutron(), id::ParticleID( 26056 ),
                              InteractionType::Nuclear,
                              { Reaction( id::ReactionID( "n,Fe56->total" ),
                                          { "n,Fe56->n,Fe56", "n,Fe56->2n,Fe55[all]",
                                            "n,Fe56->3n,Fe54[all]", "n,Fe56->a,Cr52[all]" },
                                          TabulatedCrossSection( { 1e-5, 20. }, { 1000001., 1000001. },
                                                                   InterpolationType::LogLinear ),
                                          {} ),
                                Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                          TabulatedCrossSection( { 1e-5, 20. }, { 1e+6, 1e+6 },
                                                                   InterpolationType::LinearLinear ),
                                          {},
                                          0, 0 ),
                                Reaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ),
                                          { "n,Fe56->2n,Fe55", "n,Fe56->2n,Fe55_e1" },
                                          TabulatedCrossSection( { 1., 20. }, { 0., 3. },
                                                                   InterpolationType::LogLinear ),
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
                                Reaction( id::ReactionID( "n,Fe56->3n,Fe54[all]" ),
                                          { "n,Fe56->3n,Fe54", "n,Fe56->3n,Fe54_e1" },
                                          TabulatedCrossSection( { 5., 20. }, { 0., 5. },
                                                                   InterpolationType::LogLinear ),
                                          {} ),
                                Reaction( id::ReactionID( "n,Fe56->3n,Fe54" ),
                                          TabulatedCrossSection( { 5., 20. }, { 0., 3.00001 },
                                                                   InterpolationType::LinearLinear ),
                                          {},
                                          0, -5 ),
                                Reaction( id::ReactionID( "n,Fe56->3n,Fe54_e1" ),
                                          TabulatedCrossSection( { 5., 20. }, { 0., 2. },
                                                                   InterpolationType::LinearLinear ),
                                          {},
                                          0, -5 ),
                                Reaction( id::ReactionID( "n,Fe56->a,Cr52[all]" ),
                                          TabulatedCrossSection( { 1e-5, 20. }, { 1., 1. },
                                                                   InterpolationType::LinearLinear ),
                                          {},
                                          0, 0 ) } );

      THEN( "the reaction data can be changed" ) {

        std::vector< Reaction > newreactions = {

          Reaction( id::ReactionID( "n,Fe56->n,Fe56_e2" ),
                    TabulatedCrossSection( { 5., 20. }, { 0., 15. },
                                             InterpolationType::LogLog ),
                    {},
                    0, -1 )
        };
        std::vector< Reaction > original = {

          Reaction( id::ReactionID( "n,Fe56->total" ),
                    { "n,Fe56->n,Fe56", "n,Fe56->2n,Fe55[all]",
                      "n,Fe56->3n,Fe54[all]", "n,Fe56->a,Cr52[all]" },
                    TabulatedCrossSection( { 1e-5, 20. }, { 1000001., 1000001. },
                                             InterpolationType::LogLinear ),
                    {} ),
          Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                    TabulatedCrossSection( { 1e-5, 20. }, { 1e+6, 1e+6 },
                                             InterpolationType::LinearLinear ),
                    {},
                    0, 0 ),
          Reaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ),
                    { "n,Fe56->2n,Fe55", "n,Fe56->2n,Fe55_e1" },
                    TabulatedCrossSection( { 1., 20. }, { 0., 3. },
                                             InterpolationType::LogLinear ),
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
          Reaction( id::ReactionID( "n,Fe56->3n,Fe54[all]" ),
                    { "n,Fe56->3n,Fe54", "n,Fe56->3n,Fe54_e1" },
                    TabulatedCrossSection( { 5., 20. }, { 0., 5. },
                                             InterpolationType::LogLinear ),
                    {} ),
          Reaction( id::ReactionID( "n,Fe56->3n,Fe54" ),
                    TabulatedCrossSection( { 5., 20. }, { 0., 3.00001 },
                                             InterpolationType::LinearLinear ),
                    {},
                    0, -5 ),
          Reaction( id::ReactionID( "n,Fe56->3n,Fe54_e1" ),
                    TabulatedCrossSection( { 5., 20. }, { 0., 2. },
                                             InterpolationType::LinearLinear ),
                    {},
                    0, -5 ),
          Reaction( id::ReactionID( "n,Fe56->a,Cr52[all]" ),
                    TabulatedCrossSection( { 1e-5, 20. }, { 1., 1. },
                                             InterpolationType::LinearLinear ),
                    {},
                    0, 0 )
        };

        chunk.reactions( newreactions );

        CHECK( newreactions == chunk.reactions() );
        CHECK( 1 == chunk.reactions().size() );

        chunk.reactions( original );

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
  CHECK( 9 == chunk.numberReactions() );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->total" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->n,Fe56" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->3n,Fe54[all]" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->3n,Fe54" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->3n,Fe54_e1" ) ) );
  CHECK( true == chunk.hasReaction( id::ReactionID( "n,Fe56->a,Cr52[all]" ) ) );
  CHECK( false == chunk.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

  // reactions
  auto reaction = chunk.reactions()[0];
  CHECK( id::ReactionID( "n,Fe56->total" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 4 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54[all]" ) == reaction.partialReactionIdentifiers().value()[2] );
  CHECK( id::ReactionID( "n,Fe56->a,Cr52[all]" ) == reaction.partialReactionIdentifiers().value()[3] );
  CHECK( false == reaction.hasProducts() );
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
  CHECK( InterpolationType::LogLinear == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.isLinearised() );
  CHECK( false == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[1];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 1000000., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1000000., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
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
  CHECK( InterpolationType::LogLinear == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.isLinearised() );
  CHECK( false == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[3];
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 2.00001, WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
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
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[5];
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 2 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54_e1" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( false == reaction.hasProducts() );
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
  CHECK( InterpolationType::LogLinear == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.isLinearised() );
  CHECK( false == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[6];
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -5., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  5., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 3.00001, WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[7];
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54_e1" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -5., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  5., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 2., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[8];
  CHECK( id::ReactionID( "n,Fe56->a,Cr52[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->total" ) );
  CHECK( id::ReactionID( "n,Fe56->total" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 4 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54[all]" ) == reaction.partialReactionIdentifiers().value()[2] );
  CHECK( id::ReactionID( "n,Fe56->a,Cr52[all]" ) == reaction.partialReactionIdentifiers().value()[3] );
  CHECK( false == reaction.hasProducts() );
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
  CHECK( InterpolationType::LogLinear == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.isLinearised() );
  CHECK( false == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->n,Fe56" ) );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 1000000., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1000000., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) );
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
  CHECK( InterpolationType::LogLinear == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.isLinearised() );
  CHECK( false == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->2n,Fe55" ) );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 2.00001, WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55_e1" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -1., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->3n,Fe54[all]" ) );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 2 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54_e1" ) == reaction.partialReactionIdentifiers().value()[1] );
  CHECK( false == reaction.hasProducts() );
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
  CHECK( InterpolationType::LogLinear == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.isLinearised() );
  CHECK( false == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->3n,Fe54" ) );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -5., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  5., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 3.00001, WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->3n,Fe54_e1" ) );
  CHECK( id::ReactionID( "n,Fe56->3n,Fe54_e1" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT( -5., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  5., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT( 20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 2., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->a,Cr52[all]" ) );
  CHECK( id::ReactionID( "n,Fe56->a,Cr52[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( false == reaction.hasProducts() );
  CHECK( 2 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 2 == reaction.crossSection().energies().size() );
  CHECK( 2 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(  1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(   20., WithinRel( reaction.crossSection().energies()[1] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 1., WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.isLinearised() );
  CHECK( true == reaction.crossSection().isLinearised() );

  // metadata
  CHECK( false == chunk.isLinearised() );
}
