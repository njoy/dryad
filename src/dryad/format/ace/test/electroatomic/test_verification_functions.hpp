void verifyEprdata12ElectronTotalReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "501" ) == reaction.identifier() );
  CHECK( ReactionType::Summation == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
  auto partials = reaction.partialReactionIdentifiers().value();
  CHECK( 4 == partials.size() );
  CHECK( id::ReactionID( "526" ) == partials[0] );
  CHECK( id::ReactionID( "527" ) == partials[1] );
  CHECK( id::ReactionID( "528" ) == partials[2] );
  CHECK( id::ReactionID( "534" ) == partials[3] );

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

void verifyEprdata12ElectronTotalIonisationReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "522" ) == reaction.identifier() );
  CHECK( ReactionType::Summation == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
  auto partials = reaction.partialReactionIdentifiers().value();
  CHECK( 1 == partials.size() );
  CHECK( id::ReactionID( "534" ) == partials[0] );

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

void verifyEprdata12ElectronTotalElasticReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "526" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( true == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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

void verifyEprdata12ElectronBremsstrahlungReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "527" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( true == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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

void verifyEprdata12ElectronExcitationReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "528" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( true == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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

void verifyEprdata12ElectronIonisationReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "534" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( true == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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

void verifyEprdata14ElectronTotalReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "501" ) == reaction.identifier() );
  CHECK( ReactionType::Summation == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
  auto partials = reaction.partialReactionIdentifiers().value();
  CHECK( 5 == partials.size() );
  CHECK( id::ReactionID( "525" ) == partials[0] );
  CHECK( id::ReactionID( "527" ) == partials[1] );
  CHECK( id::ReactionID( "528" ) == partials[2] );
  CHECK( id::ReactionID( "534" ) == partials[3] );
  CHECK( id::ReactionID( "-526" ) == partials[4] );

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

void verifyEprdata14ElectronTotalIonisationReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "522" ) == reaction.identifier() );
  CHECK( ReactionType::Summation == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
  auto partials = reaction.partialReactionIdentifiers().value();
  CHECK( 1 == partials.size() );
  CHECK( id::ReactionID( "534" ) == partials[0] );

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

void verifyEprdata14ElectronLargeAngleElasticReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "525" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( true == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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

void verifyEprdata14ElectronTotalElasticReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "526" ) == reaction.identifier() );
  CHECK( ReactionType::Summation == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
  auto partials = reaction.partialReactionIdentifiers().value();
  CHECK( 2 == partials.size() );
  CHECK( id::ReactionID( "525" ) == partials[0] );
  CHECK( id::ReactionID( "-526" ) == partials[1] );

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
  CHECK_THAT( 1.298710e+4, WithinRel( reaction.crossSection().values()[341] ) );
  CHECK( 341 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata14ElectronBremsstrahlungReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "527" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( true == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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

void verifyEprdata14ElectronExcitationReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "528" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( true == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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

void verifyEprdata14ElectronIonisationReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "534" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( true == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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

void verifyEprdata14ElectronElasticReactionDeficit( const Reaction& reaction ) {

  CHECK( id::ReactionID( "-526" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

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
  CHECK_THAT(                   10., WithinRel( reaction.crossSection().energies()[0] ) );
  CHECK_THAT(                 1e+11, WithinRel( reaction.crossSection().energies()[341] ) );
  CHECK_THAT(                    0., WithinRel( reaction.crossSection().values()[0] ) );
  CHECK_THAT( 12987.1 - 1.311760e-5, WithinRel( reaction.crossSection().values()[341] ) );
  CHECK( 341 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}
