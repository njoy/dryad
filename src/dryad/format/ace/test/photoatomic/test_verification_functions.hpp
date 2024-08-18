void verifyMcplib84PhotonTotalReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "501" ) == reaction.identifier() );
  CHECK( ReactionType::Summation == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
  auto partials = reaction.partialReactionIdentifiers().value();
  CHECK( 4 == partials.size() );
  CHECK( id::ReactionID( "502" ) == partials[0] );
  CHECK( id::ReactionID( "504" ) == partials[1] );
  CHECK( id::ReactionID( "516" ) == partials[2] );
  CHECK( id::ReactionID( "522" ) == partials[3] );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT( 1000., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 278 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 278 == reaction.crossSection().energies().size() );
  CHECK( 278 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(       1000., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[277], 1e-10 ) );
  CHECK_THAT( 1.207455e+1, WithinRel( reaction.crossSection().values()[0], 1e-6 ) );
  CHECK_THAT( 2.071804e-2, WithinRel( reaction.crossSection().values()[277], 1e-6 ) );
  CHECK( 277 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyMcplib84PhotonCoherentReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "502" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT( 1000., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 278 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 278 == reaction.crossSection().energies().size() );
  CHECK( 278 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1000., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(          1e+11, WithinRel( reaction.crossSection().energies()[277], 1e-10 ) );
  CHECK_THAT( 5.817904841e-1, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT(    4.62616e-16, WithinRel( reaction.crossSection().values()[277], 1e-10 ) );
  CHECK( 277 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyMcplib84PhotonIncoherentReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "504" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT( 1000., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 278 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 278 == reaction.crossSection().energies().size() );
  CHECK( 278 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(       1000., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[277], 1e-10 ) );
  CHECK_THAT( 8.434300e-2, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 1.704200e-5, WithinRel( reaction.crossSection().values()[277], 1e-10 ) );
  CHECK( 277 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyMcplib84PhotonPairProductionReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "516" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT( 1000., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 278 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 278 == reaction.crossSection().energies().size() );
  CHECK( 278 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(       1000., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[277], 1e-10 ) );
  CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 2.070100e-2, WithinRel( reaction.crossSection().values()[277], 1e-10 ) );
  CHECK( 277 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyMcplib84PhotonTotalPhotoElectricReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "522" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT( 1000., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 278 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 278 == reaction.crossSection().energies().size() );
  CHECK( 278 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(        1000., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(        1e+11, WithinRel( reaction.crossSection().energies()[277], 1e-10 ) );
  CHECK_THAT( 11.408415496, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT(  7.73600e-15, WithinRel( reaction.crossSection().values()[277], 1e-10 ) );
  CHECK( 277 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata12PhotonTotalReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "501" ) == reaction.identifier() );
  CHECK( ReactionType::Summation == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
  auto partials = reaction.partialReactionIdentifiers().value();
  CHECK( 4 == partials.size() );
  CHECK( id::ReactionID( "502" ) == partials[0] );
  CHECK( id::ReactionID( "504" ) == partials[1] );
  CHECK( id::ReactionID( "516" ) == partials[2] );
  CHECK( id::ReactionID( "534" ) == partials[3] );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(           1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(        1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT(  9.983176e-6, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 2.0718042e-2, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata12PhotonCoherentReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "502" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT( 9.887553e-6, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 4.62616e-16, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata12PhotonIncoherentReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "504" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT( 9.562300e-8, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 1.704200e-5, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata12PhotonPairProductionReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "516" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 2.070100e-2, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata12PhotonTotalPhotoElectricReaction( const Reaction& reaction ) {

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

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 7.73600e-15, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata12PhotonPhotoElectricReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "534" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 7.73600e-15, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata14PhotonTotalReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "501" ) == reaction.identifier() );
  CHECK( ReactionType::Summation == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
  auto partials = reaction.partialReactionIdentifiers().value();
  CHECK( 4 == partials.size() );
  CHECK( id::ReactionID( "502" ) == partials[0] );
  CHECK( id::ReactionID( "504" ) == partials[1] );
  CHECK( id::ReactionID( "516" ) == partials[2] );
  CHECK( id::ReactionID( "534" ) == partials[3] );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(           1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(        1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT(  9.983176e-6, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 2.0718042e-2, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata14PhotonCoherentReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "502" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT( 9.887553e-6, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 4.62616e-16, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata14PhotonIncoherentReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "504" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT( 9.562300e-8, WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 1.704200e-5, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata14PhotonPairProductionReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "516" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 2.070100e-2, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata14PhotonTotalPhotoElectricReaction( const Reaction& reaction ) {

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

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 7.73600e-15, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}

void verifyEprdata14PhotonPhotoElectricReaction( const Reaction& reaction ) {

  CHECK( id::ReactionID( "534" ) == reaction.identifier() );
  CHECK( ReactionType::Primary == reaction.type() );
  CHECK( false == reaction.hasProducts() );
  CHECK( true == reaction.isLinearised() );

  CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

  CHECK( std::nullopt == reaction.massDifferenceQValue() );
  CHECK( std::nullopt == reaction.reactionQValue() );

  CHECK_THAT(    1., WithinRel( reaction.crossSection().lowerEnergyLimit(), 1e-10 ) );
  CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().upperEnergyLimit(), 1e-10 ) );
  CHECK( 647 == reaction.crossSection().numberPoints() );
  CHECK( 1 == reaction.crossSection().numberRegions() );
  CHECK( 647 == reaction.crossSection().energies().size() );
  CHECK( 647 == reaction.crossSection().values().size() );
  CHECK( 1 == reaction.crossSection().boundaries().size() );
  CHECK( 1 == reaction.crossSection().interpolants().size() );
  CHECK_THAT(          1., WithinRel( reaction.crossSection().energies()[0], 1e-10 ) );
  CHECK_THAT(       1e+11, WithinRel( reaction.crossSection().energies()[646], 1e-10 ) );
  CHECK_THAT(          0., WithinRel( reaction.crossSection().values()[0], 1e-10 ) );
  CHECK_THAT( 7.73600e-15, WithinRel( reaction.crossSection().values()[646], 1e-10 ) );
  CHECK( 646 == reaction.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
  CHECK( true == reaction.crossSection().isLinearised() );

  CHECK( 0 == reaction.products().size() );
}
