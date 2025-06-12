namespace photoatomic {

// test functions based on photoat-001_H_000.endf
namespace h1 {

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "501" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "502" ) == partials[0] );
    CHECK( id::ReactionID( "504" ) == partials[1] );
    CHECK( id::ReactionID( "515" ) == partials[2] );
    CHECK( id::ReactionID( "517" ) == partials[3] );
    CHECK( id::ReactionID( "534" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 2021 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 2021 == reaction.crossSection().energies().size() );
    CHECK( 2021 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK(  137 == reaction.crossSection().boundaries()[0] );
    CHECK( 2020 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1.   , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().energies()[2020] ) );
    CHECK_THAT( 4.62084E-6, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .020718042, WithinRel( reaction.crossSection().values()[2020] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyCoherentReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "502" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0., WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 361 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 361 == reaction.crossSection().energies().size() );
    CHECK( 361 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 360 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.   , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().energies()[360] ) );
    CHECK_THAT( 4.52522E-6, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 4.6282E-16, WithinRel( reaction.crossSection().values()[360] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );

    auto gamma = reaction.products()[0];
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
    CHECK( true == gamma.isLinearised() );
    CHECK( false == gamma.hasAverageEnergy() );
    CHECK( true == gamma.hasDistributionData() );

    CHECK( true == std::holds_alternative< int >( gamma.multiplicity() ) );
    auto multiplicity = std::get< int >( gamma.multiplicity() );
    CHECK( 1 == multiplicity );

    CHECK( std::nullopt == gamma.averageEnergy() );

    CHECK( std::nullopt != gamma.distributionData() );
    CHECK( true == std::holds_alternative< CoherentDistributionData >( gamma.distributionData().value() ) );
    auto data = std::get< CoherentDistributionData >( gamma.distributionData().value() );

    CHECK( DistributionDataType::Coherent == data.type() );
    CHECK( ReferenceFrame::Laboratory == data.frame() );

    CHECK_THAT( 0.  , WithinRel( data.scatteringFunction().lowerInverseLengthLimit() ) );
    CHECK_THAT( 1e+9, WithinRel( data.scatteringFunction().upperInverseLengthLimit() ) );
    CHECK( 1253 == data.scatteringFunction().inverseLengths().size() );
    CHECK( 1253 == data.scatteringFunction().values().size() );
    CHECK( 1 == data.scatteringFunction().boundaries().size() );
    CHECK( 1 == data.scatteringFunction().interpolants().size() );
    CHECK_THAT( 0.       , WithinRel( data.scatteringFunction().inverseLengths()[0] ) );
    CHECK_THAT( 0.001    , WithinRel( data.scatteringFunction().inverseLengths()[1] ) );
    CHECK_THAT( 512000000, WithinRel( data.scatteringFunction().inverseLengths()[1251] ) );
    CHECK_THAT( 1e+9     , WithinRel( data.scatteringFunction().inverseLengths()[1252] ) );
    CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[0] ) );
    CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[1] ) );
    CHECK_THAT( 1.1908E-37, WithinRel( data.scatteringFunction().values()[1251] ) );
    CHECK_THAT( 8.1829e-39, WithinRel( data.scatteringFunction().values()[1252] ) );
    CHECK( 1252 == data.scatteringFunction().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == data.scatteringFunction().interpolants()[0] );
    CHECK( true == data.scatteringFunction().isLinearised() );

    CHECK( std::nullopt != data.realAnomolousFormFactor() );
    auto factor = data.realAnomolousFormFactor().value();
    CHECK_THAT( 1.  , WithinRel( factor.lowerEnergyLimit() ) );
    CHECK_THAT( 1e+7, WithinRel( factor.upperEnergyLimit() ) );
    CHECK( 297 == factor.energies().size() );
    CHECK( 297 == factor.values().size() );
    CHECK( 1 == factor.boundaries().size() );
    CHECK( 1 == factor.interpolants().size() );
    CHECK_THAT( 1.        , WithinRel( factor.energies()[0] ) );
    CHECK_THAT( 2.        , WithinRel( factor.energies()[1] ) );
    CHECK_THAT( 9549925.86, WithinRel( factor.energies()[295] ) );
    CHECK_THAT( 1e+7      , WithinRel( factor.energies()[296] ) );
    CHECK_THAT( -1.00260813, WithinRel( factor.values()[0] ) );
    CHECK_THAT( -1.01054501, WithinRel( factor.values()[1] ) );
    CHECK_THAT( 2.8024E-11, WithinRel( factor.values()[295] ) );
    CHECK_THAT( 0.        , WithinRel( factor.values()[296] ) );
    CHECK( 296 == factor.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
    CHECK( true == factor.isLinearised() );

    CHECK( std::nullopt != data.imaginaryAnomolousFormFactor() );
    factor = data.imaginaryAnomolousFormFactor().value();
    CHECK_THAT( 1.  , WithinRel( factor.lowerEnergyLimit() ) );
    CHECK_THAT( 1e+7, WithinRel( factor.upperEnergyLimit() ) );
    CHECK( 297 == factor.energies().size() );
    CHECK( 297 == factor.values().size() );
    CHECK( 1 == factor.boundaries().size() );
    CHECK( 1 == factor.interpolants().size() );
    CHECK_THAT( 1.        , WithinRel( factor.energies()[0] ) );
    CHECK_THAT( 2.        , WithinRel( factor.energies()[1] ) );
    CHECK_THAT( 9549925.86, WithinRel( factor.energies()[295] ) );
    CHECK_THAT( 1e+7      , WithinRel( factor.energies()[296] ) );
    CHECK_THAT( 0.        , WithinRel( factor.values()[0] ) );
    CHECK_THAT( 0.        , WithinRel( factor.values()[1] ) );
    CHECK_THAT( 8.9767E-15, WithinRel( factor.values()[295] ) );
    CHECK_THAT( 0.        , WithinRel( factor.values()[296] ) );
    CHECK( 296 == factor.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
    CHECK( true == factor.isLinearised() );
  }

  void verifyIncoherentReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "504" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0., WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 396 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 396 == reaction.crossSection().energies().size() );
    CHECK( 396 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 395 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.   , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().energies()[395] ) );
    CHECK_THAT( 9.56230E-8, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.70420E-5, WithinRel( reaction.crossSection().values()[395] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );

    auto gamma = reaction.products()[0];
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
    CHECK( true == gamma.isLinearised() );
    CHECK( false == gamma.hasAverageEnergy() );
    CHECK( true == gamma.hasDistributionData() );

    CHECK( true == std::holds_alternative< int >( gamma.multiplicity() ) );
    auto multiplicity = std::get< int >( gamma.multiplicity() );
    CHECK( 1 == multiplicity );

    CHECK( std::nullopt == gamma.averageEnergy() );

    CHECK( std::nullopt != gamma.distributionData() );
    CHECK( true == std::holds_alternative< IncoherentDistributionData >( gamma.distributionData().value() ) );
    auto data = std::get< IncoherentDistributionData >( gamma.distributionData().value() );

    CHECK( DistributionDataType::Incoherent == data.type() );
    CHECK( ReferenceFrame::Laboratory == data.frame() );

    CHECK_THAT( 0.  , WithinRel( data.scatteringFunction().lowerInverseLengthLimit() ) );
    CHECK_THAT( 1e+9, WithinRel( data.scatteringFunction().upperInverseLengthLimit() ) );
    CHECK( 398 == data.scatteringFunction().inverseLengths().size() );
    CHECK( 398 == data.scatteringFunction().values().size() );
    CHECK( 1 == data.scatteringFunction().boundaries().size() );
    CHECK( 1 == data.scatteringFunction().interpolants().size() );
    CHECK_THAT( 0.       , WithinRel( data.scatteringFunction().inverseLengths()[0] ) );
    CHECK_THAT( 1e-7     , WithinRel( data.scatteringFunction().inverseLengths()[1] ) );
    CHECK_THAT( 512000000, WithinRel( data.scatteringFunction().inverseLengths()[396] ) );
    CHECK_THAT( 1e+9     , WithinRel( data.scatteringFunction().inverseLengths()[397] ) );
    CHECK_THAT( 0.        , WithinRel( data.scatteringFunction().values()[0] ) );
    CHECK_THAT( 4.4097E-13, WithinRel( data.scatteringFunction().values()[1] ) );
    CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[396] ) );
    CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[397] ) );
    CHECK( 397 == data.scatteringFunction().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == data.scatteringFunction().interpolants()[0] );
    CHECK( true == data.scatteringFunction().isLinearised() );
  }

  void verifyElectronFieldPairProductionReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "515" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -1.022e+6, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 217 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 217 == reaction.crossSection().energies().size() );
    CHECK( 217 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 216 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 2044000., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[216] ) );
    CHECK_THAT( 0.      , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .0111   , WithinRel( reaction.crossSection().values()[216] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyNuclearFieldPairProductionReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "517" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -1.022e+6, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 308 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 308 == reaction.crossSection().energies().size() );
    CHECK( 308 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 307 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1022000., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[307] ) );
    CHECK_THAT( 0.      , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .009601 , WithinRel( reaction.crossSection().values()[307] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyTotalPairProductionReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "516" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "515" ) == partials[0] );
    CHECK( id::ReactionID( "517" ) == partials[1] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 466 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 466 == reaction.crossSection().energies().size() );
    CHECK( 466 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 465 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1022000., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[465] ) );
    CHECK_THAT( 0.      , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .020701 , WithinRel( reaction.crossSection().values()[465] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyIonisationReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "534" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -13.6, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 904 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 904 == reaction.crossSection().energies().size() );
    CHECK( 904 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 903 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 13.6    , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[903] ) );
    CHECK_THAT( 6318358.25, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 7.7360E-15, WithinRel( reaction.crossSection().values()[903] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyTotalIonisationReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "522" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "534" ) == partials[0] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 904 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 904 == reaction.crossSection().energies().size() );
    CHECK( 904 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 903 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 13.6    , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[903] ) );
    CHECK_THAT( 6318358.25, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 7.7360E-15, WithinRel( reaction.crossSection().values()[903] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

} // namespace h1
} // namespace neutron
