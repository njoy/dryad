// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/Reaction.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const Reaction& );
void verifySummationChunk( const Reaction& );

SCENARIO( "Reaction" ) {

  GIVEN( "valid data for a primary reaction" ) {

    WHEN( "the data is given explicitly" ) {

      id::ReactionID id( "n,Fe56->n,Fe56_e1" );
      TabulatedCrossSection xs( { 1., 2., 2., 3., 4. },
                                { 4., 3., 4., 3., 2. },
                                { 1, 4 },
                                { InterpolationType::LinearLinear,
                                  InterpolationType::LinearLog } );
      double mass_q = 0;
      double reaction_q = -1;
      std::vector< ReactionProduct > products = {

        ReactionProduct( id::ParticleID( "n" ), 1 ),
        ReactionProduct( id::ParticleID( "g" ), 2 ),
        ReactionProduct( id::ParticleID( "g" ), 3 )
      };

      Reaction chunk( std::move( id ), std::move( xs ),
                      std::move( products ), mass_q, reaction_q );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a summation reaction" ) {

    WHEN( "the data is given explicitly" ) {

      id::ReactionID id( "n,Fe56->total" );
      std::vector< id::ReactionID > partials = { "n,Fe56->elastic", "n,Fe56->2n,Fe55" };
      TabulatedCrossSection xs( { 1., 2., 2., 3., 4. },
                                { 4., 3., 4., 3., 2. },
                                { 1, 4 },
                                { InterpolationType::LinearLinear,
                                  InterpolationType::LinearLog } );

      Reaction chunk( std::move( id ), std::move( partials ), std::move( xs ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifySummationChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of Reaction is given" ) {

      Reaction chunk( id::ReactionID( "n,Fe56->n,Fe56_e1" ),
                      TabulatedCrossSection( { 1., 2., 2., 3., 4. },
                                             { 4., 3., 4., 3., 2. },
                                             { 1, 4 },
                                             { InterpolationType::LinearLinear,
                                               InterpolationType::LinearLog } ),
                      { ReactionProduct( id::ParticleID( "n" ), 1 ),
                        ReactionProduct( id::ParticleID( "g" ), 2 ),
                        ReactionProduct( id::ParticleID( "g" ), 3 ) },
                      0, -1 );

      THEN( "the reaction identifier can be changed" ) {

        id::ReactionID newid( "n,Fe56->n,Fe56_e40" );
        id::ReactionID original( "n,Fe56->n,Fe56_e1" );

        chunk.identifier( newid );

        CHECK( newid == chunk.identifier() );

        chunk.identifier( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the partial reaction identifiers can be changed" ) {

        std::optional< std::vector< id::ReactionID > > newpartials( { "n,Fe56->elastic", "n,Fe56->2n,Fe55" } );
        std::optional< std::vector< id::ReactionID > > original( std::nullopt );

        chunk.partialReactionIdentifiers( newpartials );

        CHECK( newpartials == chunk.partialReactionIdentifiers() );
        CHECK( ReactionCategory::Summation == chunk.category() );
        CHECK( false == chunk.isPrimaryReaction() );
        CHECK( true == chunk.isSummationReaction() );

        chunk.partialReactionIdentifiers( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the q values can be changed" ) {

        std::optional< double > newmassq = 2;
        std::optional< double > originalmassq = 0;
        std::optional< double > newreactionq = -2;
        std::optional< double > originalreactionq = -1;

        chunk.massDifferenceQValue( newmassq );
        chunk.reactionQValue( newreactionq );

        CHECK( newmassq == chunk.massDifferenceQValue() );
        CHECK( newreactionq == chunk.reactionQValue() );

        chunk.massDifferenceQValue( originalmassq );
        chunk.reactionQValue( originalreactionq );

        verifyChunk( chunk );
      } // THEN

      THEN( "the cross section can be changed" ) {

        TabulatedCrossSection newxs( { 1., 4. }, { 1., 4. } );
        TabulatedCrossSection original( { 1., 2., 2., 3., 4. },
                                        { 4., 3., 4., 3., 2. },
                                        { 1, 4 },
                                        { InterpolationType::LinearLinear,
                                          InterpolationType::LinearLog } );

        chunk.crossSection( newxs );

        CHECK( newxs == chunk.crossSection() );
        CHECK( true == chunk.isLinearised() );

        chunk.crossSection( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the products can be changed" ) {

        std::vector< ReactionProduct > newproducts = { ReactionProduct( id::ParticleID( "n" ), 1 ) };
        std::vector< ReactionProduct > original = { ReactionProduct( id::ParticleID( "n" ), 1 ),
                                                    ReactionProduct( id::ParticleID( "g" ), 2 ),
                                                    ReactionProduct( id::ParticleID( "g" ), 3 ) };

        chunk.products( newproducts );

        CHECK( newproducts == chunk.products() );
        CHECK( 1 == chunk.numberProducts() );

        chunk.products( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Reaction are given" ) {

      Reaction left( id::ReactionID( "n,Fe56->n,Fe56_e1" ),
                     TabulatedCrossSection( { 1., 2., 2., 3., 4. },
                                            { 4., 3., 4., 3., 2. },
                                            { 1, 4 },
                                            { InterpolationType::LinearLinear,
                                              InterpolationType::LinearLog } ),
                     { ReactionProduct( id::ParticleID( "n" ), 1 ),
                       ReactionProduct( id::ParticleID( "g" ), 2 ),
                       ReactionProduct( id::ParticleID( "g" ), 3 ) },
                     0, -1 );
      Reaction equal( id::ReactionID( "n,Fe56->n,Fe56_e1" ),
                      TabulatedCrossSection( { 1., 2., 2., 3., 4. },
                                             { 4., 3., 4., 3., 2. },
                                             { 1, 4 },
                                             { InterpolationType::LinearLinear,
                                               InterpolationType::LinearLog } ),
                      { ReactionProduct( id::ParticleID( "n" ), 1 ),
                        ReactionProduct( id::ParticleID( "g" ), 2 ),
                        ReactionProduct( id::ParticleID( "g" ), 3 ) },
                      0, -1 );
      Reaction different( id::ReactionID( "n,Fe56->total" ),
                          { "n,Fe56->elastic", "n,Fe56->2n,Fe55" },
                          TabulatedCrossSection( { 1., 2., 2., 3., 4. },
                                                 { 4., 3., 4., 3., 2. },
                                                 { 1, 4 },
                                                 { InterpolationType::LinearLinear,
                                                   InterpolationType::LinearLog } ) );

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

void verifyChunk( const Reaction& chunk ) {

  // reaction identifier
  CHECK( id::ReactionID( "n,Fe56->n,Fe56_e1" ) == chunk.identifier() );

  // reaction category
  CHECK( ReactionCategory::Primary == chunk.category() );
  CHECK( true == chunk.isPrimaryReaction() );
  CHECK( false == chunk.isSummationReaction() );

  // partial identifiers
  CHECK( std::nullopt == chunk.partialReactionIdentifiers() );
  CHECK( 0 == chunk.numberPartialReactions() );

  // q values
  CHECK_THAT( 0, WithinRel( chunk.massDifferenceQValue().value() ) );
  CHECK_THAT( -1, WithinRel( chunk.reactionQValue().value() ) );

  // cross section
  CHECK( 5 == chunk.crossSection().numberPoints() );
  CHECK( 2 == chunk.crossSection().numberRegions() );
  CHECK( 5 == chunk.crossSection().energies().size() );
  CHECK( 5 == chunk.crossSection().values().size() );
  CHECK( 2 == chunk.crossSection().boundaries().size() );
  CHECK( 2 == chunk.crossSection().interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.crossSection().energies()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().energies()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().energies()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().energies()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().energies()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().values()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().values()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().values()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().values()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().values()[4] ) );
  CHECK( 1 == chunk.crossSection().boundaries()[0] );
  CHECK( 4 == chunk.crossSection().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.crossSection().interpolants()[0] );
  CHECK( InterpolationType::LinearLog == chunk.crossSection().interpolants()[1] );
  CHECK( false == chunk.crossSection().isLinearised() );

  // reaction products
  CHECK( true == chunk.hasProducts() );
  CHECK( true == chunk.hasProduct( id::ParticleID( "n" ) ) );
  CHECK( true == chunk.hasProduct( id::ParticleID( "g" ) ) );
  CHECK( false == chunk.hasProduct( id::ParticleID( "h" ) ) );
  CHECK( 3 == chunk.numberProducts() );
  CHECK( 3 == chunk.products().size() );
  CHECK( 1 == chunk.numberProducts( id::ParticleID( "n" ) ) );
  CHECK( 2 == chunk.numberProducts( id::ParticleID( "g" ) ) );
  CHECK( 0 == chunk.numberProducts( id::ParticleID( "h" ) ) );

  CHECK( 1 == std::get< int >( chunk.product( id::ParticleID( "n" ) ).multiplicity() ) );
  CHECK( 1 == std::get< int >( chunk.product( id::ParticleID( "n" ), 0 ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( id::ParticleID( "g" ) ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( id::ParticleID( "g" ), 0 ).multiplicity() ) );
  CHECK( 3 == std::get< int >( chunk.product( id::ParticleID( "g" ), 1 ).multiplicity() ) );

  CHECK_THROWS( chunk.product( id::ParticleID( "n" ), 1 ) );
  CHECK_THROWS( chunk.product( id::ParticleID( "h" ) ) );
  CHECK_THROWS( chunk.product( id::ParticleID( "h" ), 1 ) );

  // metadata
  CHECK( false == chunk.isLinearised() );
}

void verifySummationChunk( const Reaction& chunk ) {

  // reaction identifier
  CHECK( id::ReactionID( "n,Fe56->total" ) == chunk.identifier() );

  // reaction type
  CHECK( ReactionCategory::Summation == chunk.category() );
  CHECK( false == chunk.isPrimaryReaction() );
  CHECK( true == chunk.isSummationReaction() );

  // partial identifiers
  CHECK( std::nullopt != chunk.partialReactionIdentifiers() );
  CHECK( 2 == chunk.numberPartialReactions() );
  auto partials = chunk.partialReactionIdentifiers().value();
  CHECK( 2 == partials.size() );
  CHECK( id::ReactionID( "n,Fe56->elastic" ) == partials[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55" ) == partials[1] );

  // q values
  CHECK( std::nullopt == chunk.massDifferenceQValue() );
  CHECK( std::nullopt == chunk.reactionQValue() );

  // cross section
  CHECK( 5 == chunk.crossSection().numberPoints() );
  CHECK( 2 == chunk.crossSection().numberRegions() );
  CHECK( 5 == chunk.crossSection().energies().size() );
  CHECK( 5 == chunk.crossSection().values().size() );
  CHECK( 2 == chunk.crossSection().boundaries().size() );
  CHECK( 2 == chunk.crossSection().interpolants().size() );
  CHECK_THAT( 1., WithinRel( chunk.crossSection().energies()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().energies()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().energies()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().energies()[3] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().energies()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().values()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().values()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().values()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().values()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().values()[4] ) );
  CHECK( 1 == chunk.crossSection().boundaries()[0] );
  CHECK( 4 == chunk.crossSection().boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.crossSection().interpolants()[0] );
  CHECK( InterpolationType::LinearLog == chunk.crossSection().interpolants()[1] );
  CHECK( false == chunk.crossSection().isLinearised() );

  // reaction products
  CHECK( false == chunk.hasProducts() );
  CHECK( false == chunk.hasProduct( id::ParticleID( "n" ) ) );
  CHECK( false == chunk.hasProduct( id::ParticleID( "g" ) ) );
  CHECK( 0 == chunk.products().size() );

  // metadata
  CHECK( false == chunk.isLinearised() );
}
