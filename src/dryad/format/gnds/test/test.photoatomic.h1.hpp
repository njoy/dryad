namespace photoatomic {

// test functions based on photoat-001_H_000.endf
namespace h1 {

  void verifyTotalReaction( const Reaction& total ) {

    CHECK( id::ReactionID( "501" ) == total.identifier() );
    CHECK( ReactionType::Summation == total.type() );
    CHECK( false == total.hasProducts() );
    CHECK( true == total.isLinearised() );

    CHECK( std::nullopt != total.partialReactionIdentifiers() );
    auto partials = total.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "502" ) == partials[0] );
    CHECK( id::ReactionID( "504" ) == partials[1] );
    CHECK( id::ReactionID( "515" ) == partials[2] );
    CHECK( id::ReactionID( "517" ) == partials[3] );
    CHECK( id::ReactionID( "534" ) == partials[4] );

    CHECK( std::nullopt == total.massDifferenceQValue() );
    CHECK( std::nullopt == total.reactionQValue() );

    CHECK( true == total.crossSection().isLinearised() );
    CHECK( 2021 == total.crossSection().numberPoints() );
    CHECK( 2 == total.crossSection().numberRegions() );
    CHECK( 2021 == total.crossSection().energies().size() );
    CHECK( 2021 == total.crossSection().values().size() );
    CHECK( 2 == total.crossSection().boundaries().size() );
    CHECK( 2 == total.crossSection().interpolants().size() );
    CHECK(  137 == total.crossSection().boundaries()[0] );
    CHECK( 2020 == total.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == total.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == total.crossSection().interpolants()[1] );
    CHECK_THAT( 1.   , WithinRel( total.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( total.crossSection().energies()[2020] ) );
    CHECK_THAT( 4.62084E-6, WithinRel( total.crossSection().values()[0] ) );
    CHECK_THAT( .020718042, WithinRel( total.crossSection().values()[2020] ) );

    CHECK( 0 == total.products().size() );
  }

  void verifyCoherentReaction( const Reaction& coherent ) {

    CHECK( id::ReactionID( "502" ) == coherent.identifier() );
    CHECK( ReactionType::Primary == coherent.type() );
    CHECK( true == coherent.hasProducts() );
    CHECK( true == coherent.isLinearised() );

    CHECK( std::nullopt == coherent.massDifferenceQValue() );
    CHECK( std::nullopt != coherent.reactionQValue() );
    CHECK_THAT( 0., WithinRel( coherent.reactionQValue().value() ) );

    CHECK( true == coherent.crossSection().isLinearised() );
    CHECK( 361 == coherent.crossSection().numberPoints() );
    CHECK( 1 == coherent.crossSection().numberRegions() );
    CHECK( 361 == coherent.crossSection().energies().size() );
    CHECK( 361 == coherent.crossSection().values().size() );
    CHECK( 1 == coherent.crossSection().boundaries().size() );
    CHECK( 1 == coherent.crossSection().interpolants().size() );
    CHECK( 360 == coherent.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == coherent.crossSection().interpolants()[0] );
    CHECK_THAT( 1.   , WithinRel( coherent.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( coherent.crossSection().energies()[360] ) );
    CHECK_THAT( 4.52522E-6, WithinRel( coherent.crossSection().values()[0] ) );
    CHECK_THAT( 4.6282E-16, WithinRel( coherent.crossSection().values()[360] ) );

    CHECK( 2 == coherent.products().size() );

    auto gamma = coherent.products()[0];
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

    auto hydrogen = coherent.products()[1];
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyIncoherentReaction( const Reaction& incoherent ) {

    CHECK( id::ReactionID( "504" ) == incoherent.identifier() );
    CHECK( ReactionType::Primary == incoherent.type() );
    CHECK( true == incoherent.hasProducts() );
    CHECK( true == incoherent.isLinearised() );

    CHECK( std::nullopt == incoherent.massDifferenceQValue() );
    CHECK( std::nullopt != incoherent.reactionQValue() );
    CHECK_THAT( 0., WithinRel( incoherent.reactionQValue().value() ) );

    CHECK( true == incoherent.crossSection().isLinearised() );
    CHECK( 396 == incoherent.crossSection().numberPoints() );
    CHECK( 1 == incoherent.crossSection().numberRegions() );
    CHECK( 396 == incoherent.crossSection().energies().size() );
    CHECK( 396 == incoherent.crossSection().values().size() );
    CHECK( 1 == incoherent.crossSection().boundaries().size() );
    CHECK( 1 == incoherent.crossSection().interpolants().size() );
    CHECK( 395 == incoherent.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == incoherent.crossSection().interpolants()[0] );
    CHECK_THAT( 1.   , WithinRel( incoherent.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( incoherent.crossSection().energies()[395] ) );
    CHECK_THAT( 9.56230E-8, WithinRel( incoherent.crossSection().values()[0] ) );
    CHECK_THAT( 1.70420E-5, WithinRel( incoherent.crossSection().values()[395] ) );

    CHECK( 2 == incoherent.products().size() );

    auto gamma = incoherent.products()[0];
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

    auto hydrogen = incoherent.products()[1];
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
    }

  void verifyElectronFieldPairProductionReaction( const Reaction& epairproduction ) {

    CHECK( id::ReactionID( "515" ) == epairproduction.identifier() );
    CHECK( ReactionType::Primary == epairproduction.type() );
    CHECK( true == epairproduction.hasProducts() );
    CHECK( true == epairproduction.isLinearised() );

    CHECK( std::nullopt == epairproduction.massDifferenceQValue() );
    CHECK( std::nullopt != epairproduction.reactionQValue() );
    CHECK_THAT( -1.022e+6, WithinRel( epairproduction.reactionQValue().value() ) );

    CHECK( true == epairproduction.crossSection().isLinearised() );
    CHECK( 217 == epairproduction.crossSection().numberPoints() );
    CHECK( 1 == epairproduction.crossSection().numberRegions() );
    CHECK( 217 == epairproduction.crossSection().energies().size() );
    CHECK( 217 == epairproduction.crossSection().values().size() );
    CHECK( 1 == epairproduction.crossSection().boundaries().size() );
    CHECK( 1 == epairproduction.crossSection().interpolants().size() );
    CHECK( 216 == epairproduction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == epairproduction.crossSection().interpolants()[0] );
    CHECK_THAT( 2044000., WithinRel( epairproduction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( epairproduction.crossSection().energies()[216] ) );
    CHECK_THAT( 0.      , WithinRel( epairproduction.crossSection().values()[0] ) );
    CHECK_THAT( .0111   , WithinRel( epairproduction.crossSection().values()[216] ) );

    CHECK( 4 == epairproduction.products().size() );

    auto electron = epairproduction.products()[0];
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    electron = epairproduction.products()[1];
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    auto antielectron = epairproduction.products()[2];
    CHECK( id::ParticleID( "e+" ) == antielectron.identifier() );

    auto hydrogen = epairproduction.products()[3];
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyNuclearFieldPairProductionReaction( const Reaction& npairproduction ) {

    CHECK( id::ReactionID( "517" ) == npairproduction.identifier() );
    CHECK( ReactionType::Primary == npairproduction.type() );
    CHECK( true == npairproduction.hasProducts() );
    CHECK( true == npairproduction.isLinearised() );

    CHECK( std::nullopt == npairproduction.massDifferenceQValue() );
    CHECK( std::nullopt != npairproduction.reactionQValue() );
    CHECK_THAT( -1.022e+6, WithinRel( npairproduction.reactionQValue().value() ) );

    CHECK( true == npairproduction.crossSection().isLinearised() );
    CHECK( 308 == npairproduction.crossSection().numberPoints() );
    CHECK( 1 == npairproduction.crossSection().numberRegions() );
    CHECK( 308 == npairproduction.crossSection().energies().size() );
    CHECK( 308 == npairproduction.crossSection().values().size() );
    CHECK( 1 == npairproduction.crossSection().boundaries().size() );
    CHECK( 1 == npairproduction.crossSection().interpolants().size() );
    CHECK( 307 == npairproduction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == npairproduction.crossSection().interpolants()[0] );
    CHECK_THAT( 1022000., WithinRel( npairproduction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( npairproduction.crossSection().energies()[307] ) );
    CHECK_THAT( 0.      , WithinRel( npairproduction.crossSection().values()[0] ) );
    CHECK_THAT( .009601 , WithinRel( npairproduction.crossSection().values()[307] ) );

    CHECK( 3 == npairproduction.products().size() );

    auto electron = npairproduction.products()[0];
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    auto antielectron = npairproduction.products()[1];
    CHECK( id::ParticleID( "e+" ) == antielectron.identifier() );

    auto hydrogen = npairproduction.products()[2];
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyTotalPairProductionReaction( const Reaction& tpairproduction ) {

    CHECK( id::ReactionID( "516" ) == tpairproduction.identifier() );
    CHECK( ReactionType::Summation == tpairproduction.type() );
    CHECK( false == tpairproduction.hasProducts() );
    CHECK( true == tpairproduction.isLinearised() );

    CHECK( std::nullopt != tpairproduction.partialReactionIdentifiers() );
    auto partials = tpairproduction.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "515" ) == partials[0] );
    CHECK( id::ReactionID( "517" ) == partials[1] );

    CHECK( std::nullopt == tpairproduction.massDifferenceQValue() );
    CHECK( std::nullopt == tpairproduction.reactionQValue() );

    CHECK( true == tpairproduction.crossSection().isLinearised() );
    CHECK( 466 == tpairproduction.crossSection().numberPoints() );
    CHECK( 1 == tpairproduction.crossSection().numberRegions() );
    CHECK( 466 == tpairproduction.crossSection().energies().size() );
    CHECK( 466 == tpairproduction.crossSection().values().size() );
    CHECK( 1 == tpairproduction.crossSection().boundaries().size() );
    CHECK( 1 == tpairproduction.crossSection().interpolants().size() );
    CHECK( 465 == tpairproduction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == tpairproduction.crossSection().interpolants()[0] );
    CHECK_THAT( 1022000., WithinRel( tpairproduction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( tpairproduction.crossSection().energies()[465] ) );
    CHECK_THAT( 0.      , WithinRel( tpairproduction.crossSection().values()[0] ) );
    CHECK_THAT( .020701 , WithinRel( tpairproduction.crossSection().values()[465] ) );

    CHECK( 0 == tpairproduction.products().size() );
  }

  void verifyIonisationReaction( const Reaction& ionisation ) {

    CHECK( id::ReactionID( "534" ) == ionisation.identifier() );
    CHECK( ReactionType::Primary == ionisation.type() );
    CHECK( true == ionisation.hasProducts() );
    CHECK( true == ionisation.isLinearised() );

    CHECK( std::nullopt == ionisation.massDifferenceQValue() );
    CHECK( std::nullopt != ionisation.reactionQValue() );
    CHECK_THAT( -13.6, WithinRel( ionisation.reactionQValue().value() ) );

    CHECK( true == ionisation.crossSection().isLinearised() );
    CHECK( 904 == ionisation.crossSection().numberPoints() );
    CHECK( 1 == ionisation.crossSection().numberRegions() );
    CHECK( 904 == ionisation.crossSection().energies().size() );
    CHECK( 904 == ionisation.crossSection().values().size() );
    CHECK( 1 == ionisation.crossSection().boundaries().size() );
    CHECK( 1 == ionisation.crossSection().interpolants().size() );
    CHECK( 903 == ionisation.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == ionisation.crossSection().interpolants()[0] );
    CHECK_THAT( 13.6    , WithinRel( ionisation.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( ionisation.crossSection().energies()[903] ) );
    CHECK_THAT( 6318358.25, WithinRel( ionisation.crossSection().values()[0] ) );
    CHECK_THAT( 7.7360E-15, WithinRel( ionisation.crossSection().values()[903] ) );

    CHECK( 2 == ionisation.products().size() );

    auto electron = ionisation.products()[0];
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    auto ion = ionisation.products()[1];
    CHECK( id::ParticleID( "H{1s1/2}" ) == ion.identifier() );
  }

  void verifyTotalIonisationReaction( const Reaction& tionisation ) {

    CHECK( id::ReactionID( "522" ) == tionisation.identifier() );
    CHECK( ReactionType::Summation == tionisation.type() );
    CHECK( false == tionisation.hasProducts() );
    CHECK( true == tionisation.isLinearised() );

    CHECK( std::nullopt != tionisation.partialReactionIdentifiers() );
    auto partials = tionisation.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "534" ) == partials[0] );

    CHECK( std::nullopt == tionisation.massDifferenceQValue() );
    CHECK( std::nullopt == tionisation.reactionQValue() );

    CHECK( true == tionisation.crossSection().isLinearised() );
    CHECK( 904 == tionisation.crossSection().numberPoints() );
    CHECK( 1 == tionisation.crossSection().numberRegions() );
    CHECK( 904 == tionisation.crossSection().energies().size() );
    CHECK( 904 == tionisation.crossSection().values().size() );
    CHECK( 1 == tionisation.crossSection().boundaries().size() );
    CHECK( 1 == tionisation.crossSection().interpolants().size() );
    CHECK( 903 == tionisation.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == tionisation.crossSection().interpolants()[0] );
    CHECK_THAT( 13.6    , WithinRel( tionisation.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( tionisation.crossSection().energies()[903] ) );
    CHECK_THAT( 6318358.25, WithinRel( tionisation.crossSection().values()[0] ) );
    CHECK_THAT( 7.7360E-15, WithinRel( tionisation.crossSection().values()[903] ) );

    CHECK( 0 == tionisation.products().size() );
  }

} // namespace h1
} // namespace neutron
