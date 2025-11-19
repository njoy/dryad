namespace continuous {

// test functions based on 1001.10c
namespace lib81 {
namespace h1 {

  void verifyElasticReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,H1->n,H1" ) == reaction.identifier() );
    CHECK( 50 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 631 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 631 == reaction.crossSection().energies().size() );
    CHECK( 631 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 16.72987, WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( 2.710792e-5, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 630 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

  void verifyCaptureReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,H1->g,H2[all]" ) == reaction.identifier() );
    CHECK( 102 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 631 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 631 == reaction.crossSection().energies().size() );
    CHECK( 631 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 16.72987, WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( 2.710792e-5, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 630 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

} //namespace h1
} // namespace lib81
} // namespace continuous
