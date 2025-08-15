namespace electroatomic {

// test functions based on 1000.12p
namespace eprdata12 {
namespace h {

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::NewReactionID( "e-,H->total[atomic]" ) == reaction.identifier() );
    CHECK( 501 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 4 == partials.size() );
    CHECK( id::NewReactionID( "e-,H->e-,H[total-scattering]" ) == partials[0] );
    CHECK( id::NewReactionID( "e-,H->e-,H[bremsstrahlung]" ) == partials[1] );
    CHECK( id::NewReactionID( "e-,H->e-,H[excitation]" ) == partials[2] );
    CHECK( id::NewReactionID( "e-,H->2e-,H{1s1/2}" ) == partials[3] );
    CHECK( 525 == partials[0].reactionType().mt() );
    CHECK( 507 == partials[1].reactionType().mt() );
    CHECK( 508 == partials[2].reactionType().mt() );
    CHECK( 534 == partials[3].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT(   10., WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 342 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 342 == reaction.crossSection().energies().size() );
    CHECK( 342 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(            10., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(          1e+11, WithinRel( reaction.crossSection().energies()[341] ) );
    CHECK_THAT( 274896029.7832, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 164334.9906341, WithinRel( reaction.crossSection().values()[341] ) );
    CHECK( 341 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

  void verifyTotalIonisationReaction( const Reaction& reaction ) {

    CHECK( id::NewReactionID( "e-,H->2e-,H" ) == reaction.identifier() );
    CHECK( 522 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::NewReactionID( "e-,H->2e-,H{1s1/2}" ) == partials[0] );
    CHECK( 534 == partials[0].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT(   10., WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 342 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 342 == reaction.crossSection().energies().size() );
    CHECK( 342 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(         10., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[341] ) );
    CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 8.289240e+4, WithinRel( reaction.crossSection().values()[341] ) );
    CHECK( 341 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

  void verifyTotalElasticReaction( const Reaction& reaction ) {

    CHECK( id::NewReactionID( "e-,H->e-,H[total-scattering]" ) == reaction.identifier() );
    CHECK( 526 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT(   10., WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 342 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 342 == reaction.crossSection().energies().size() );
    CHECK( 342 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(         10., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[341] ) );
    CHECK_THAT( 2.748960e+8, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.311760e-5, WithinRel( reaction.crossSection().values()[341] ) );
    CHECK( 341 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 1 == reaction.products().size() );
  }

  void verifyBremsstrahlungReaction( const Reaction& reaction ) {

    CHECK( id::NewReactionID( "e-,H->e-,H[bremsstrahlung]" ) == reaction.identifier() );
    CHECK( 507 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT(   10., WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 342 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 342 == reaction.crossSection().energies().size() );
    CHECK( 342 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(         10., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[341] ) );
    CHECK_THAT( 2.978320e+1, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 9.906210e-1, WithinRel( reaction.crossSection().values()[341] ) );
    CHECK( 341 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 2 == reaction.products().size() );
  }

  void verifyExcitationReaction( const Reaction& reaction ) {

    CHECK( id::NewReactionID( "e-,H->e-,H[excitation]" ) == reaction.identifier() );
    CHECK( 508 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT(   10., WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 342 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 342 == reaction.crossSection().energies().size() );
    CHECK( 342 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(         10., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[341] ) );
    CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 8.144160e+4, WithinRel( reaction.crossSection().values()[341] ) );
    CHECK( 341 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 1 == reaction.products().size() );
  }

  void verifyIonisationReaction( const Reaction& reaction ) {

    CHECK( id::NewReactionID( "e-,H->2e-,H{1s1/2}" ) == reaction.identifier() );
    CHECK( 534 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT(   10., WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 342 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 342 == reaction.crossSection().energies().size() );
    CHECK( 342 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT(         10., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[341] ) );
    CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 8.289240e+4, WithinRel( reaction.crossSection().values()[341] ) );
    CHECK( 341 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 1 == reaction.products().size() );
  }

} //namespace h
} // namespace eprdata12
} // namespace electroatomic
