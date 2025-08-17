// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/ProjectileTarget.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const ProjectileTarget&, bool );
void verifyCorrectSummation( const ProjectileTarget& );

SCENARIO( "ProjectileTarget" ) {

  id::ParticleID g = id::ParticleID::photon();
  id::ParticleID n = id::ParticleID::neutron();
  id::ParticleID fe56( 26056 );

  id::ReactionID( n, fe56, id::ReactionType( "total" ) );
  id::ReactionID( n, fe56, id::ReactionType::elastic( n ) );
  id::ReactionID( n, fe56, id::ReactionType( "2n" ) );
  id::ReactionID( n, fe56, id::ReactionType( "2n(0)" ) );
  id::ReactionID( n, fe56, id::ReactionType( "2n(1)" ) );
  id::ReactionID( n, fe56, id::ReactionType( "p" ) );
  id::ReactionID( n, fe56, id::ReactionType( "p(0)" ) );
  id::ReactionID( n, fe56, id::ReactionType( "p(1)" ) );
  id::ReactionID( n, fe56, id::ReactionType( "a" ) );

  GIVEN( "valid data for a ProjectileTarget" ) {

    WHEN( "the data is given explicitly" ) {

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

      ProjectileTarget chunk1( projectile, target, type, reactions, false );
      ProjectileTarget chunk2( std::move( projectile ), std::move( target ),
                               type, std::move( reactions ), true );

      verifyChunk( chunk1, false );
      verifyChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyChunk( chunk1, true );
      verifyChunk( chunk2, true );

      chunk1.calculateSummationCrossSections();
      chunk2.calculateSummationCrossSections();

      verifyCorrectSummation( chunk1 );
      verifyCorrectSummation( chunk2 );
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of ProjectileTarget is given" ) {

      ProjectileTarget chunk( id::ParticleID::neutron(), id::ParticleID( 26056 ),
                              InteractionType::Nuclear,
                              { Reaction( id::ReactionID( "n,Fe56->total" ),
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
                                          0, 0 ) } );

      THEN( "the projectile identifier can be changed" ) {

        id::ParticleID newprojectile = id::ParticleID::proton();
        id::ParticleID original = id::ParticleID::neutron();

        chunk.projectileIdentifier( newprojectile );

        CHECK( newprojectile == chunk.projectileIdentifier() );

        chunk.projectileIdentifier( original );

        verifyChunk( chunk, false );
      }

      THEN( "the target identifier can be changed" ) {

        id::ParticleID newtarget = id::ParticleID( 1001 );
        id::ParticleID original = id::ParticleID( 26056 );

        chunk.targetIdentifier( newtarget );

        CHECK( newtarget == chunk.targetIdentifier() );

        chunk.targetIdentifier( original );

        verifyChunk( chunk, false );
      }

      THEN( "the interaction type can be changed" ) {

        InteractionType newtype = InteractionType::Atomic;
        InteractionType original = InteractionType::Nuclear;

        chunk.interactionType( newtype );

        CHECK( newtype == chunk.interactionType() );

        chunk.interactionType( original );

        verifyChunk( chunk, false );
      }

      THEN( "the reaction data can be changed" ) {

        std::vector< Reaction > newreactions = {

          Reaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ),
                    TabulatedCrossSection( { 5., 20. }, { 0., 15. },
                                             InterpolationType::LogLog ),
                    {},
                    0, -1 )
        };
        std::vector< Reaction > original = {

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

        chunk.reactions( newreactions );

        CHECK( newreactions == chunk.reactions() );
        CHECK( 1 == chunk.reactions().size() );

        chunk.reactions( original );

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ProjectileTarget are given" ) {

      ProjectileTarget left( id::ParticleID::neutron(), id::ParticleID( 26056 ),
                             InteractionType::Nuclear,
                             { Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                         TabulatedCrossSection( { 1e-5, 20. }, { 1000., 10. },
                                                                  InterpolationType::Histogram ),
                                         {},
                                         0, 0 ),
                              Reaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ),
                                        TabulatedCrossSection( { 1., 20. }, { 0., 100. },
                                                                 InterpolationType::LinearLinear ),
                                        {},
                                        0, -1 ) } );
      ProjectileTarget equal( id::ParticleID::neutron(), id::ParticleID( 26056 ),
                              InteractionType::Nuclear,
                              { Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                          TabulatedCrossSection( { 1e-5, 20. }, { 1000., 10. },
                                                                   InterpolationType::Histogram ),
                                          {},
                                          0, 0 ),
                               Reaction( id::ReactionID( "n,Fe56->2n,Fe55_e1" ),
                                         TabulatedCrossSection( { 1., 20. }, { 0., 100. },
                                                                  InterpolationType::LinearLinear ),
                                         {},
                                         0, -1 ) } );
      ProjectileTarget different( id::ParticleID::neutron(), id::ParticleID( 26056 ),
                                  InteractionType::Nuclear,
                                  { Reaction( id::ReactionID( "n,Fe56->n,Fe56" ),
                                              TabulatedCrossSection( { 1e-5, 20. }, { 1000., 10. },
                                                                       InterpolationType::Histogram ),
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

void verifyChunk( const ProjectileTarget& chunk, bool normalise ) {

  // documentation
  CHECK( std::nullopt == chunk.documentation().awr() );
  CHECK( std::nullopt == chunk.documentation().library() );
  CHECK( std::nullopt == chunk.documentation().version() );
  CHECK( std::nullopt == chunk.documentation().description() );

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

  reaction = chunk.reactions()[1];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( true == reaction.hasProducts() );
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
  CHECK( true == reaction.crossSection().isLinearised() );
  auto product = reaction.product( id::ParticleID( "n" ) );
  CHECK( 1 == std::get< int >( product.multiplicity() ) );
  auto distribution = product.distributionData();
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
  CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[0] );
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
  CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[6];
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.identifier() );
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
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->total" ) );
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

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->n,Fe56" ) );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( true == reaction.hasProducts() );
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
  CHECK( true == reaction.crossSection().isLinearised() );
  product = reaction.product( id::ParticleID( "n" ) );
  CHECK( 1 == std::get< int >( product.multiplicity() ) );
  distribution = product.distributionData();
  CHECK( true == std::holds_alternative< TwoBodyDistributionData >( distribution.value() ) );
  data = std::get< TwoBodyDistributionData >( distribution.value() );
  CHECK( DistributionDataType::TwoBody == data.type() );
  CHECK( ReferenceFrame::CentreOfMass == data.frame() );
  CHECK( true == std::holds_alternative< LegendreAngularDistributions >( data.angle() ) );
  angle = std::get< LegendreAngularDistributions >( data.angle() );
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
  CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[0] );
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
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->p,Mn56[all]" ) );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 2 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56_e1" ) == reaction.partialReactionIdentifiers().value()[1] );
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
  CHECK( InterpolationType::Histogram == reaction.crossSection().interpolants()[0] );
  CHECK( false == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->p,Mn56" ) );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.identifier() );
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
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->p,Mn56_e1" ) );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56_e1" ) == reaction.identifier() );
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
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->a,Cr53[all]" ) );
  CHECK( id::ReactionID( "n,Fe56->a,Cr53[all]" ) == reaction.identifier() );
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
  CHECK( true == reaction.crossSection().isLinearised() );
}

void verifyCorrectSummation( const ProjectileTarget& chunk ) {

  // only the xs are changed, so products are not checked

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
  CHECK_THAT( 1000001. + 3.00001 / 19. * 4., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1000009.00002, WithinRel( reaction.crossSection().values()[3] ) );
  CHECK( 3 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[1];
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( true == reaction.hasProducts() );
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
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 3.00001, WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

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
  CHECK_THAT( 5.00001, WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reactions()[6];
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.identifier() );
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
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->total" ) );
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
  CHECK_THAT( 1000001. + 3.00001 / 19. * 4., WithinRel( reaction.crossSection().values()[2] ) );
  CHECK_THAT( 1000009.00002, WithinRel( reaction.crossSection().values()[3] ) );
  CHECK( 3 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->n,Fe56" ) );
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == reaction.identifier() );
  CHECK( ReactionCategory::Primary == reaction.category() );
  CHECK( true == reaction.isPrimaryReaction() );
  CHECK( false == reaction.isSummationReaction() );
  CHECK_THAT(  0., WithinRel( reaction.massDifferenceQValue().value() ) );
  CHECK_THAT(  0., WithinRel( reaction.reactionQValue().value() ) );
  CHECK( 0 == reaction.numberPartialReactions() );
  CHECK( true == reaction.hasProducts() );
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
  CHECK_THAT( 0.     , WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 3.00001, WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

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
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->p,Mn56[all]" ) );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56[all]" ) == reaction.identifier() );
  CHECK( ReactionCategory::Summation == reaction.category() );
  CHECK( false == reaction.isPrimaryReaction() );
  CHECK( true == reaction.isSummationReaction() );
  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );
  CHECK( 2 == reaction.numberPartialReactions() );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.partialReactionIdentifiers().value()[0] );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56_e1" ) == reaction.partialReactionIdentifiers().value()[1] );
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
  CHECK_THAT( 5.00001, WithinRel( reaction.crossSection().values()[1] ) );
  CHECK( 1 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->p,Mn56" ) );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56" ) == reaction.identifier() );
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
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->p,Mn56_e1" ) );
  CHECK( id::ReactionID( "n,Fe56->p,Mn56_e1" ) == reaction.identifier() );
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
  CHECK( true == reaction.crossSection().isLinearised() );

  reaction = chunk.reaction( id::ReactionID( "n,Fe56->a,Cr53[all]" ) );
  CHECK( id::ReactionID( "n,Fe56->a,Cr53[all]" ) == reaction.identifier() );
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
  CHECK( true == reaction.crossSection().isLinearised() );
}
