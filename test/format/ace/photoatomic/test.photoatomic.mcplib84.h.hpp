namespace photoatomic {

// test functions based on 1000.12p
namespace mcplib84 {
namespace h {

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->total[atomic]" ) == reaction.identifier() );
    CHECK( 501 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 4 == partials.size() );
    CHECK( id::ReactionID( "g,H->g,H[coherent]" ) == partials[0] );
    CHECK( id::ReactionID( "g,H->g,H[incoherent]" ) == partials[1] );
    CHECK( id::ReactionID( "g,H->pair-production" ) == partials[2] );
    CHECK( id::ReactionID( "g,H->e-,H" ) == partials[3] );
    CHECK( 502 == partials[0].reactionType().mt() );
    CHECK( 504 == partials[1].reactionType().mt() );
    CHECK( 516 == partials[2].reactionType().mt() );
    CHECK( 522 == partials[3].reactionType().mt() );

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

  void verifyCoherentReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->g,H[coherent]" ) == reaction.identifier() );
    CHECK( 502 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.hasProducts() );

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

    CHECK( 1 == reaction.products().size() );

    CHECK( id::ParticleID( "g" ) == reaction.products()[0].identifier() );
    CHECK( false == reaction.products()[0].hasAverageEnergy() );
    CHECK( true == reaction.products()[0].hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( reaction.products()[0].multiplicity() ) );
    auto multiplicity = std::get< int >( reaction.products()[0].multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == reaction.products()[0].averageEnergy() );
    CHECK( std::nullopt != reaction.products()[0].distributionData() );
    CHECK( true == std::holds_alternative< CoherentDistributionData >( reaction.products()[0].distributionData().value() ) );
    auto data = std::get< CoherentDistributionData >( reaction.products()[0].distributionData().value() );
    CHECK( DistributionDataType::Coherent == data.type() );
    CHECK( ReferenceFrame::CentreOfMass == data.frame() );
    CHECK( false == data.hasAnomolousFormFactor() );
    CHECK_THAT( 0., WithinRel( data.scatteringFunction().lowerInverseLengthLimit() ) );
    CHECK_THAT( 6., WithinRel( data.scatteringFunction().upperInverseLengthLimit() ) );
    CHECK( 55 == data.scatteringFunction().inverseLengths().size() );
    CHECK( 55 == data.scatteringFunction().values().size() );
    CHECK( 1 == data.scatteringFunction().boundaries().size() );
    CHECK( 1 == data.scatteringFunction().interpolants().size() );
    CHECK_THAT(          0., WithinRel( data.scatteringFunction().inverseLengths()[0] ) );
    CHECK_THAT(          6., WithinRel( data.scatteringFunction().inverseLengths()[54] ) );
    CHECK_THAT(          1., WithinRel( data.scatteringFunction().values()[0] ) );
    CHECK_THAT( 6.282400e-6, WithinRel( data.scatteringFunction().values()[54] ) );
    CHECK( 54 == data.scatteringFunction().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == data.scatteringFunction().interpolants()[0] );
    CHECK( true == data.scatteringFunction().isLinearised() );
    CHECK( std::nullopt == data.realAnomolousFormFactor() );
    CHECK( std::nullopt == data.imaginaryAnomolousFormFactor() );
  }

  void verifyIncoherentReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->g,H[incoherent]" ) == reaction.identifier() );
    CHECK( 504 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.hasProducts() );

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

    CHECK( 1 == reaction.products().size() );

    CHECK( id::ParticleID( "g" ) == reaction.products()[0].identifier() );
    CHECK( false == reaction.products()[0].hasAverageEnergy() );
    CHECK( true == reaction.products()[0].hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( reaction.products()[0].multiplicity() ) );
    auto multiplicity = std::get< int >( reaction.products()[0].multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == reaction.products()[0].averageEnergy() );
    CHECK( std::nullopt != reaction.products()[0].distributionData() );
    CHECK( true == std::holds_alternative< IncoherentDistributionData >( reaction.products()[0].distributionData().value() ) );
    auto data = std::get< IncoherentDistributionData >( reaction.products()[0].distributionData().value() );
    CHECK( DistributionDataType::Incoherent == data.type() );
    CHECK( ReferenceFrame::CentreOfMass == data.frame() );
    CHECK_THAT( 0., WithinRel( data.scatteringFunction().lowerInverseLengthLimit() ) );
    CHECK_THAT( 8., WithinRel( data.scatteringFunction().upperInverseLengthLimit() ) );
    CHECK( 21 == data.scatteringFunction().inverseLengths().size() );
    CHECK( 21 == data.scatteringFunction().values().size() );
    CHECK( 1 == data.scatteringFunction().boundaries().size() );
    CHECK( 1 == data.scatteringFunction().interpolants().size() );
    CHECK_THAT( 0., WithinRel( data.scatteringFunction().inverseLengths()[0] ) );
    CHECK_THAT( 8., WithinRel( data.scatteringFunction().inverseLengths()[20] ) );
    CHECK_THAT( 0., WithinRel( data.scatteringFunction().values()[0] ) );
    CHECK_THAT( 1., WithinRel( data.scatteringFunction().values()[20] ) );
    CHECK( 20 == data.scatteringFunction().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == data.scatteringFunction().interpolants()[0] );
    CHECK( true == data.scatteringFunction().isLinearised() );
  }

  void verifyPairProductionReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->pair-production" ) == reaction.identifier() );
    CHECK( 516 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

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

  void verifyTotalPhotoElectricReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->e-,H" ) == reaction.identifier() );
    CHECK( 522 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

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

} //namespace h
} // namespace mcplib84
} // namespace photoatomic
