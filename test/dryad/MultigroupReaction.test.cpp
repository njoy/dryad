// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/MultigroupReaction.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const MultigroupReaction& );
void verifySummationChunk( const MultigroupReaction& );

SCENARIO( "MultigroupReaction" ) {

  id::ParticleID g = id::ParticleID::photon();
  id::ParticleID n = id::ParticleID::neutron();
  id::ParticleID a = id::ParticleID::alpha();
  id::ParticleID be8( "Be8" );
  id::ParticleID fe56( "Fe56" );

  GIVEN( "valid data for a primary reaction" ) {

    WHEN( "the data is given explicitly" ) {

      id::ReactionID id( n, fe56, id::ReactionType( 51 ) );
      MultigroupCrossSection xs( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } );
      double mass_q = 0;
      double reaction_q = -1;
      std::vector< MultigroupReactionProduct > products = {

        MultigroupReactionProduct( n, 1 ),
        MultigroupReactionProduct( g, 2 ),
        MultigroupReactionProduct( g, 3 ),
        MultigroupReactionProduct( be8, 1 ),
        MultigroupReactionProduct( a, 2, std::nullopt, std::nullopt, be8, 1 )
      };

      MultigroupReaction chunk( std::move( id ), std::move( xs ),
                                std::move( products ), mass_q, reaction_q );

      verifyChunk( chunk );
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a summation reaction" ) {

    WHEN( "the data is given explicitly" ) {

      id::ReactionID id( n, fe56, id::ReactionType( 1 ) );
      std::vector< id::ReactionID > partials = { id::ReactionID( n, fe56, id::ReactionType::elastic( n ) ),
                                                 id::ReactionID( n, fe56, id::ReactionType( 16 ) ) };
      MultigroupCrossSection xs( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } );

      MultigroupReaction chunk( std::move( id ), std::move( partials ), std::move( xs ) );

      THEN( "a MultigroupReaction can be constructed and members can be tested" ) {

        verifySummationChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of MultigroupReaction is given" ) {

      MultigroupReaction chunk( id::ReactionID( n, fe56, id::ReactionType( 51 ) ),
                                MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } ),
                                { MultigroupReactionProduct( n, 1 ),
                                  MultigroupReactionProduct( g, 2 ),
                                  MultigroupReactionProduct( g, 3 ),
                                  MultigroupReactionProduct( be8, 1 ),
                                  MultigroupReactionProduct( a, 2, std::nullopt, std::nullopt, be8, 1 ) },
                                0, -1 );

      THEN( "the reaction identifier can be changed" ) {

        id::ReactionID newid( n, fe56, id::ReactionType( 90 ) );
        id::ReactionID original( n, fe56, id::ReactionType( 51 ) );

        chunk.identifier( newid );

        CHECK( newid == chunk.identifier() );

        chunk.identifier( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the partial reaction identifiers can be changed" ) {

        std::optional< std::vector< id::ReactionID > > newpartials( { id::ReactionID( n, fe56, id::ReactionType::elastic( n ) ),
                                                                      id::ReactionID( n, fe56, id::ReactionType( 16 ) ) } );
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

        MultigroupCrossSection newxs( { 1., 4. }, { 1. } );
        MultigroupCrossSection original( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } );

        chunk.crossSection( newxs );

        CHECK( newxs == chunk.crossSection() );

        chunk.crossSection( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the products can be changed" ) {

        std::vector< MultigroupReactionProduct > newproducts = { MultigroupReactionProduct( n, 1 ) };
        std::vector< MultigroupReactionProduct > original = { MultigroupReactionProduct( n, 1 ),
                                                               MultigroupReactionProduct( g, 2 ),
                                                               MultigroupReactionProduct( g, 3 ),
                                                               MultigroupReactionProduct( be8, 1 ),
                                                               MultigroupReactionProduct( a, 2, std::nullopt, std::nullopt, be8, 1 ) };

        chunk.products( newproducts );

        CHECK( newproducts == chunk.products() );
        CHECK( 1 == chunk.numberProducts() );

        chunk.products( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of MultigroupReaction are given" ) {

      MultigroupReaction left( id::ReactionID( n, fe56, id::ReactionType( 51 ) ),
                               MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } ),
                               { MultigroupReactionProduct( n, 1 ),
                                 MultigroupReactionProduct( g, 2 ),
                                 MultigroupReactionProduct( g, 3 ) },
                               0, -1 );
      MultigroupReaction equal( id::ReactionID( n, fe56, id::ReactionType( 51 ) ),
                                MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } ),
                                { MultigroupReactionProduct( n, 1 ),
                                  MultigroupReactionProduct( g, 2 ),
                                  MultigroupReactionProduct( g, 3 ) },
                                0, -1 );
      MultigroupReaction different( id::ReactionID( n, fe56, id::ReactionType( 1 ) ),
                                    { id::ReactionID( n, fe56, id::ReactionType::elastic( n ) ),
                                      id::ReactionID( n, fe56, id::ReactionType( 16 ) ) },
                                    MultigroupCrossSection( { 1., 2., 3., 4., 5. }, { 4., 3., 2., 1. } ) );

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

void verifyChunk( const MultigroupReaction& chunk ) {

  id::ParticleID g = id::ParticleID::photon();
  id::ParticleID n = id::ParticleID::neutron();
  id::ParticleID h = id::ParticleID::helion();
  id::ParticleID a = id::ParticleID::alpha();
  id::ParticleID be8( "Be8" );
  id::ParticleID fe56( "Fe56" );

  // reaction identifier
  CHECK( "n,Fe56->n,Fe56_e1" == chunk.identifier().symbol() );

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
  CHECK( 4 == chunk.crossSection().numberGroups() );
  CHECK( 5 == chunk.crossSection().boundaries().size() );
  CHECK( 4 == chunk.crossSection().values().size() );
  CHECK_THAT( 1., WithinRel( chunk.crossSection().boundaries()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().boundaries()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().boundaries()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().boundaries()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.crossSection().boundaries()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().values()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().values()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().values()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.crossSection().values()[3] ) );

  // reaction products
  CHECK( true == chunk.hasProducts() );
  CHECK( true == chunk.hasProduct( n ) );
  CHECK( true == chunk.hasProduct( g ) );
  CHECK( true == chunk.hasProduct( a ) );
  CHECK( true == chunk.hasProduct( be8 ) );
  CHECK( false == chunk.hasProduct( h ) );
  CHECK( 5 == chunk.numberProducts() );
  CHECK( 5 == chunk.products().size() );
  // total number of products
  CHECK( 1 == chunk.numberProducts( n ) );
  CHECK( 2 == chunk.numberProducts( g ) );
  CHECK( 1 == chunk.numberProducts( be8 ) );
  CHECK( 1 == chunk.numberProducts( a ) );
  CHECK( 0 == chunk.numberProducts( h ) );
  // number of products by chain index, chain = 0
  CHECK( 1 == chunk.numberProducts( n, 0 ) );
  CHECK( 2 == chunk.numberProducts( g, 0 ) );
  CHECK( 1 == chunk.numberProducts( be8, 0 ) );
  CHECK( 0 == chunk.numberProducts( a, 0 ) );
  CHECK( 0 == chunk.numberProducts( h, 0 ) );
  // number of products by chain index, chain = 1
  CHECK( 0 == chunk.numberProducts( n, 1 ) );
  CHECK( 0 == chunk.numberProducts( g, 1 ) );
  CHECK( 0 == chunk.numberProducts( be8, 1 ) );
  CHECK( 1 == chunk.numberProducts( a, 1 ) );
  CHECK( 0 == chunk.numberProducts( h, 1 ) );
  // number of products by chain index, chain = 2
  CHECK( 0 == chunk.numberProducts( n, 2 ) );
  CHECK( 0 == chunk.numberProducts( g, 2 ) );
  CHECK( 0 == chunk.numberProducts( be8, 2 ) );
  CHECK( 0 == chunk.numberProducts( a, 2 ) );
  CHECK( 0 == chunk.numberProducts( h, 2 ) );

  CHECK( 1 == std::get< int >( chunk.product( n ).multiplicity() ) );
  CHECK( 1 == std::get< int >( chunk.product( n, 0 ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( g ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( g, 0 ).multiplicity() ) );
  CHECK( 3 == std::get< int >( chunk.product( g, 1 ).multiplicity() ) );
  CHECK( 1 == std::get< int >( chunk.product( be8 ).multiplicity() ) );
  CHECK( 1 == std::get< int >( chunk.product( be8, 0 ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( a ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( a, 0 ).multiplicity() ) );

  CHECK( 1 == std::get< int >( chunk.product( n, 0, 0 ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( g, 0, 0 ).multiplicity() ) );
  CHECK( 3 == std::get< int >( chunk.product( g, 0, 1 ).multiplicity() ) );
  CHECK( 1 == std::get< int >( chunk.product( be8, 0, 0 ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( a, 1, 0 ).multiplicity() ) );

  CHECK_THROWS( chunk.product( n, 1, 0 ) ); // no neutrons in chain 1
  CHECK_THROWS( chunk.product( g, 1, 0 ) ); // no gammas in chain 1
  CHECK_THROWS( chunk.product( g, 1, 1 ) ); // no gammas in chain 1
  CHECK_THROWS( chunk.product( be8, 1, 0 ) ); // no be8 in chain 1
  CHECK_THROWS( chunk.product( a, 0, 0 ) ); // no alpha in chain 0
  CHECK_THROWS( chunk.product( a, 1, 1 ) ); // only one alpha in chain 1

  CHECK_THROWS( chunk.product( n, 1 ) );
  CHECK_THROWS( chunk.product( h ) );
  CHECK_THROWS( chunk.product( h, 1 ) );
}

void verifySummationChunk( const MultigroupReaction& chunk ) {

  id::ParticleID g = id::ParticleID::photon();
  id::ParticleID n = id::ParticleID::neutron();
  id::ParticleID fe56( "Fe56" );

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
  CHECK( id::ReactionID( "n,Fe56->n,Fe56" ) == partials[0] );
  CHECK( id::ReactionID( "n,Fe56->2n,Fe55[all]" ) == partials[1] );

  // q values
  CHECK( std::nullopt == chunk.massDifferenceQValue() );
  CHECK( std::nullopt == chunk.reactionQValue() );

  // cross section
  CHECK( 4 == chunk.crossSection().numberGroups() );
  CHECK( 5 == chunk.crossSection().boundaries().size() );
  CHECK( 4 == chunk.crossSection().values().size() );
  CHECK_THAT( 1., WithinRel( chunk.crossSection().boundaries()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().boundaries()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().boundaries()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().boundaries()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.crossSection().boundaries()[4] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSection().values()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.crossSection().values()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSection().values()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.crossSection().values()[3] ) );

  // reaction products
  CHECK( false == chunk.hasProducts() );
  CHECK( false == chunk.hasProduct( n ) );
  CHECK( false == chunk.hasProduct( g ) );
  CHECK( 0 == chunk.products().size() );
}
