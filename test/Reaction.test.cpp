// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/Reaction.hpp"

// other includes
#include "dryad/TwoBodyDistributionData.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const Reaction&, bool );
void verifySummationChunk( const Reaction& );

SCENARIO( "Reaction" ) {

  id::ParticleID g = id::ParticleID::photon();
  id::ParticleID n = id::ParticleID::neutron();
  id::ParticleID fe56( 26056 );

  GIVEN( "valid data for a primary reaction" ) {

    WHEN( "the data is given explicitly" ) {

      id::ReactionID id( n, fe56, id::ReactionType( 51 ) );
      TabulatedCrossSection xs( { 1., 2., 2., 3., 4. },
                                { 4., 3., 4., 3., 2. },
                                { 1, 4 },
                                { InterpolationType::LinearLinear,
                                  InterpolationType::LinearLog } );
      double mass_q = 0;
      double reaction_q = -1;
      std::vector< ReactionProduct > products = {

        ReactionProduct( n, 1,
                         TwoBodyDistributionData ( ReferenceFrame::CentreOfMass,
                                                   LegendreAngularDistributions(
                                                     { 1e-5, 20. },
                                                     { { { 1.0 } }, { { 1.0, 0.2 } } } ) ) ),
        ReactionProduct( g, 2 ),
        ReactionProduct( g, 3 )
      };

      Reaction chunk1( id, xs ,
                       products, mass_q, reaction_q, false );
      Reaction chunk2( std::move( id ), std::move( xs ),
                       std::move( products ), mass_q, reaction_q, true );

      verifyChunk( chunk1, false );
      verifyChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyChunk( chunk1, true );
      verifyChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a summation reaction" ) {

    WHEN( "the data is given explicitly" ) {

      id::ReactionID id( n, fe56, id::ReactionType( 1 ) );
      std::vector< id::ReactionID > partials = { id::ReactionID( n, fe56, id::ReactionType::elastic( n ) ),
                                                 id::ReactionID( n, fe56, id::ReactionType( 16 ) ) };
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

      Reaction chunk( id::ReactionID( n, fe56, id::ReactionType( 51 ) ),
                      TabulatedCrossSection( { 1., 2., 2., 3., 4. },
                                             { 4., 3., 4., 3., 2. },
                                             { 1, 4 },
                                             { InterpolationType::LinearLinear,
                                               InterpolationType::LinearLog } ),
                      { ReactionProduct( n, 1,
                                         TwoBodyDistributionData( ReferenceFrame::CentreOfMass,
                                                                  LegendreAngularDistributions(
                                                                    { 1e-5, 20. },
                                                                    { { { 1.0 } }, { { 1.0, 0.2 } } } ) ) ),
                        ReactionProduct( g, 2 ),
                        ReactionProduct( g, 3 ) },
                      0, -1 );

      THEN( "the reaction identifier can be changed" ) {

        id::ReactionID newid( n, fe56, id::ReactionType( 90 ) );
        id::ReactionID original( n, fe56, id::ReactionType( 51 ) );

        chunk.identifier( newid );

        CHECK( newid == chunk.identifier() );

        chunk.identifier( original );

        verifyChunk( chunk, false );
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

        verifyChunk( chunk, false );
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

        verifyChunk( chunk, false );
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

        chunk.crossSection( original );

        verifyChunk( chunk, false );
      } // THEN

      THEN( "the products can be changed" ) {

        std::vector< ReactionProduct > newproducts = { ReactionProduct( n, 1 ) };
        std::vector< ReactionProduct > original = { ReactionProduct( n, 1,
                                                                     TwoBodyDistributionData( ReferenceFrame::CentreOfMass,
                                                                                              LegendreAngularDistributions(
                                                                                                { 1e-5, 20. },
                                                                                                { { { 1.0 } }, { { 1.0, 0.2 } } } ) ) ),
                                                    ReactionProduct( g, 2 ),
                                                    ReactionProduct( g, 3 ) };

        chunk.products( newproducts );

        CHECK( newproducts == chunk.products() );
        CHECK( 1 == chunk.numberProducts() );

        chunk.products( original );

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Reaction are given" ) {

      Reaction left( id::ReactionID( n, fe56, id::ReactionType( 51 ) ),
                     TabulatedCrossSection( { 1., 2., 2., 3., 4. },
                                            { 4., 3., 4., 3., 2. },
                                            { 1, 4 },
                                            { InterpolationType::LinearLinear,
                                              InterpolationType::LinearLog } ),
                     { ReactionProduct( n, 1 ),
                       ReactionProduct( g, 2 ),
                       ReactionProduct( g, 3 ) },
                     0, -1 );
      Reaction equal( id::ReactionID( n, fe56, id::ReactionType( 51 ) ),
                      TabulatedCrossSection( { 1., 2., 2., 3., 4. },
                                             { 4., 3., 4., 3., 2. },
                                             { 1, 4 },
                                             { InterpolationType::LinearLinear,
                                               InterpolationType::LinearLog } ),
                      { ReactionProduct( n, 1 ),
                        ReactionProduct( g, 2 ),
                        ReactionProduct( g, 3 ) },
                      0, -1 );
      Reaction different( id::ReactionID( n, fe56, id::ReactionType( 1 ) ),
                          { id::ReactionID( n, fe56, id::ReactionType::elastic( n ) ),
                            id::ReactionID( n, fe56, id::ReactionType( 16 ) ) },
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

void verifyChunk( const Reaction& chunk, bool normalise ) {

  id::ParticleID g = id::ParticleID::photon();
  id::ParticleID n = id::ParticleID::neutron();
  id::ParticleID h = id::ParticleID::helion();
  id::ParticleID fe56( 26056 );

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
  CHECK( true == chunk.hasProduct( n ) );
  CHECK( true == chunk.hasProduct( g ) );
  CHECK( false == chunk.hasProduct( h ) );
  CHECK( 3 == chunk.numberProducts() );
  CHECK( 3 == chunk.products().size() );
  CHECK( 1 == chunk.numberProducts( n ) );
  CHECK( 2 == chunk.numberProducts( g ) );
  CHECK( 0 == chunk.numberProducts( h ) );

  CHECK( 1 == std::get< int >( chunk.product( n ).multiplicity() ) );
  CHECK( 1 == std::get< int >( chunk.product( n, 0 ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( g ).multiplicity() ) );
  CHECK( 2 == std::get< int >( chunk.product( g, 0 ).multiplicity() ) );
  CHECK( 3 == std::get< int >( chunk.product( g, 1 ).multiplicity() ) );

  auto distribution = chunk.product( id::ParticleID( "n" ) ).distributionData();
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

  CHECK_THROWS( chunk.product( n, 1 ) );
  CHECK_THROWS( chunk.product( h ) );
  CHECK_THROWS( chunk.product( h, 1 ) );
}

void verifySummationChunk( const Reaction& chunk ) {

  id::ParticleID g = id::ParticleID::photon();
  id::ParticleID n = id::ParticleID::neutron();
  id::ParticleID fe56( 26056 );

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
  CHECK( false == chunk.hasProduct( n ) );
  CHECK( false == chunk.hasProduct( g ) );
  CHECK( 0 == chunk.products().size() );
}
