void verifyNeutronTotalReaction( const Reaction& total ) {

  CHECK( id::ReactionID( "1" ) == total.identifier() );
  CHECK( ReactionType::Summation == total.type() );
  CHECK( false == total.hasProducts() );
  CHECK( false == total.isLinearised() );

  CHECK( std::nullopt == total.massDifferenceQValue() );
  CHECK( std::nullopt == total.reactionQValue() );

  CHECK( false == total.crossSection().isLinearised() );
  CHECK( 153 == total.crossSection().numberPoints() );
  CHECK( 2 == total.crossSection().numberRegions() );
  CHECK( 153 == total.crossSection().energies().size() );
  CHECK( 153 == total.crossSection().values().size() );
  CHECK( 2 == total.crossSection().boundaries().size() );
  CHECK( 2 == total.crossSection().interpolants().size() );
  CHECK( 8 == total.crossSection().boundaries()[0] );
  CHECK( 152 == total.crossSection().boundaries()[1] );
  CHECK( InterpolationType::LogLog == total.crossSection().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == total.crossSection().interpolants()[1] );
  CHECK_THAT( 1e-5, WithinRel( total.crossSection().energies()[0] ) );
  CHECK_THAT( 5e-3, WithinRel( total.crossSection().energies()[8] ) );
  CHECK_THAT( 2e+7, WithinRel( total.crossSection().energies()[152] ) );
  CHECK_THAT( 3.716477e+1, WithinRel( total.crossSection().values()[0] ) );
  CHECK_THAT( 2.118421e+1, WithinRel( total.crossSection().values()[8] ) );
  CHECK_THAT( 4.818679e-1, WithinRel( total.crossSection().values()[152] ) );

  CHECK( 0 == total.products().size() );
}

void verifyNeutronElasticReaction( const Reaction& elastic ) {

  CHECK( id::ReactionID( "2" ) == elastic.identifier() );
  CHECK( ReactionType::Primary == elastic.type() );
  CHECK( false == elastic.hasProducts() );
  CHECK( true == elastic.isLinearised() );

  CHECK( std::nullopt != elastic.massDifferenceQValue() );
  CHECK( std::nullopt != elastic.reactionQValue() );
  CHECK_THAT( 0, WithinRel( elastic.massDifferenceQValue().value() ) );
  CHECK_THAT( 0, WithinRel( elastic.reactionQValue().value() ) );

  CHECK( true == elastic.crossSection().isLinearised() );
  CHECK( 153 == elastic.crossSection().numberPoints() );
  CHECK( 1 == elastic.crossSection().numberRegions() );
  CHECK( 153 == elastic.crossSection().energies().size() );
  CHECK( 153 == elastic.crossSection().values().size() );
  CHECK( 1 == elastic.crossSection().boundaries().size() );
  CHECK( 1 == elastic.crossSection().interpolants().size() );
  CHECK( 152 == elastic.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == elastic.crossSection().interpolants()[0] );
  CHECK_THAT( 1e-5, WithinRel( elastic.crossSection().energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( elastic.crossSection().energies()[152] ) );
  CHECK_THAT( 2.043608e+1, WithinRel( elastic.crossSection().values()[0] ) );
  CHECK_THAT( 4.818408e-1, WithinRel( elastic.crossSection().values()[152] ) );

  CHECK( 0 == elastic.products().size() );
}

void verifyNeutronCaptureReaction( const Reaction& capture ) {

  CHECK( id::ReactionID( "102" ) == capture.identifier() );
  CHECK( ReactionType::Primary == capture.type() );
  CHECK( true == capture.hasProducts() );
  CHECK( false == capture.isLinearised() );

  CHECK( std::nullopt != capture.massDifferenceQValue() );
  CHECK( std::nullopt != capture.reactionQValue() );
  CHECK_THAT( 2.224648e+6, WithinRel( capture.massDifferenceQValue().value() ) );
  CHECK_THAT( 2.224648e+6, WithinRel( capture.reactionQValue().value() ) );

  CHECK( false == capture.crossSection().isLinearised() );
  CHECK( 153 == capture.crossSection().numberPoints() );
  CHECK( 2 == capture.crossSection().numberRegions() );
  CHECK( 153 == capture.crossSection().energies().size() );
  CHECK( 153 == capture.crossSection().values().size() );
  CHECK( 2 == capture.crossSection().boundaries().size() );
  CHECK( 2 == capture.crossSection().interpolants().size() );
  CHECK( 32 == capture.crossSection().boundaries()[0] );
  CHECK( 152 == capture.crossSection().boundaries()[1] );
  CHECK( InterpolationType::LogLog == capture.crossSection().interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == capture.crossSection().interpolants()[1] );
  CHECK_THAT( 1e-5, WithinRel( capture.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+4, WithinRel( capture.crossSection().energies()[32] ) );
  CHECK_THAT( 2e+7, WithinRel( capture.crossSection().energies()[152] ) );
  CHECK_THAT( 1.672869e+1, WithinRel( capture.crossSection().values()[0] ) );
  CHECK_THAT( 4.950573e-4, WithinRel( capture.crossSection().values()[32] ) );
  CHECK_THAT( 2.710792e-5, WithinRel( capture.crossSection().values()[152] ) );

  CHECK( 2 == capture.products().size() );
  auto gamma = capture.products()[0];
  CHECK( id::ParticleID( "g" ) == gamma.identifier() );
  auto deuterium = capture.products()[1];
  CHECK( id::ParticleID( "d" ) == deuterium.identifier() );
}

void verifyElectronTotalReaction( const Reaction& total ) {

  CHECK( id::ReactionID( "501" ) == total.identifier() );
  CHECK( ReactionType::Summation == total.type() );
  CHECK( false == total.hasProducts() );
  CHECK( true == total.isLinearised() );

  CHECK( std::nullopt == total.massDifferenceQValue() );
  CHECK( std::nullopt == total.reactionQValue() );

  CHECK( true == total.crossSection().isLinearised() );
  CHECK( 349 == total.crossSection().numberPoints() );
  CHECK( 1 == total.crossSection().numberRegions() );
  CHECK( 349 == total.crossSection().energies().size() );
  CHECK( 349 == total.crossSection().values().size() );
  CHECK( 1 == total.crossSection().boundaries().size() );
  CHECK( 1 == total.crossSection().interpolants().size() );
  CHECK( 348 == total.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == total.crossSection().interpolants()[0] );
  CHECK_THAT( 10., WithinRel( total.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( total.crossSection().energies()[348] ) );
  CHECK_THAT( 274896030., WithinRel( total.crossSection().values()[0] ) );
  CHECK_THAT( 177322.091, WithinRel( total.crossSection().values()[348] ) );

  CHECK( 0 == total.products().size() );
}

void verifyElectronTotalIonisationReaction( const Reaction& ionisation ) {

  CHECK( id::ReactionID( "522" ) == ionisation.identifier() );
  CHECK( ReactionType::Summation == ionisation.type() );
  CHECK( false == ionisation.hasProducts() );
  CHECK( true == ionisation.isLinearised() );

  CHECK( std::nullopt == ionisation.massDifferenceQValue() );
  CHECK( std::nullopt == ionisation.reactionQValue() );

  CHECK( true == ionisation.crossSection().isLinearised() );
  CHECK( 35 == ionisation.crossSection().numberPoints() );
  CHECK( 1 == ionisation.crossSection().numberRegions() );
  CHECK( 35 == ionisation.crossSection().energies().size() );
  CHECK( 35 == ionisation.crossSection().values().size() );
  CHECK( 1 == ionisation.crossSection().boundaries().size() );
  CHECK( 1 == ionisation.crossSection().interpolants().size() );
  CHECK( 34 == ionisation.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == ionisation.crossSection().interpolants()[0] );
  CHECK_THAT( 13.6, WithinRel( ionisation.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( ionisation.crossSection().energies()[34] ) );
  CHECK_THAT( 0., WithinRel( ionisation.crossSection().values()[0] ) );
  CHECK_THAT( 82892.4, WithinRel( ionisation.crossSection().values()[34] ) );

  CHECK( 0 == ionisation.products().size() );
}

void verifyElectronElasticReaction( const Reaction& elastic ) {

  CHECK( id::ReactionID( "525" ) == elastic.identifier() );
  CHECK( ReactionType::Primary == elastic.type() );
  CHECK( true == elastic.hasProducts() );
  CHECK( true == elastic.isLinearised() );

  CHECK( std::nullopt == elastic.massDifferenceQValue() );
  CHECK( std::nullopt != elastic.reactionQValue() );
  CHECK_THAT( 0, WithinRel( elastic.reactionQValue().value() ) );

  CHECK( true == elastic.crossSection().isLinearised() );
  CHECK( 101 == elastic.crossSection().numberPoints() );
  CHECK( 1 == elastic.crossSection().numberRegions() );
  CHECK( 101 == elastic.crossSection().energies().size() );
  CHECK( 101 == elastic.crossSection().values().size() );
  CHECK( 1 == elastic.crossSection().boundaries().size() );
  CHECK( 1 == elastic.crossSection().interpolants().size() );
  CHECK( 100 == elastic.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == elastic.crossSection().interpolants()[0] );
  CHECK_THAT( 10., WithinRel( elastic.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( elastic.crossSection().energies()[100] ) );
  CHECK_THAT( 274896000., WithinRel( elastic.crossSection().values()[0] ) );
  CHECK_THAT( 1.31176e-5, WithinRel( elastic.crossSection().values()[100] ) );

  CHECK( 1 == elastic.products().size() );
  auto photon = elastic.products()[0];
  CHECK( id::ParticleID( "e-" ) == photon.identifier() );
  CHECK( true == photon.isLinearised() );
  CHECK( false == photon.hasAverageEnergy() );
  CHECK( true == photon.hasDistributionData() );
  CHECK( true == std::holds_alternative< int >( photon.multiplicity() ) );
  auto multiplicity = std::get< int >( photon.multiplicity() );
  CHECK( 1 == multiplicity );
  CHECK( std::nullopt == photon.averageEnergy() );
  CHECK( std::nullopt != photon.distributionData() );
  CHECK( true == std::holds_alternative< TwoBodyDistributionData >( photon.distributionData().value() ) );
  auto data = std::get< TwoBodyDistributionData >( photon.distributionData().value() );
  CHECK( DistributionDataType::TwoBody == data.type() );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributions >( data.angle() ) );
  auto angle = std::get< TabulatedAngularDistributions >( data.angle() );
  CHECK( 16 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 16 == angle.grid().size() );
  CHECK( 16 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT(       10., WithinRel( angle.grid()[0] ) );
  CHECK_THAT(     1000., WithinRel( angle.grid()[1] ) );
  CHECK_THAT( 66250000., WithinRel( angle.grid()[14] ) );
  CHECK_THAT(     1e+11, WithinRel( angle.grid()[15] ) );
  CHECK(  2 == angle.distributions()[0].cosines().size() );
  CHECK(  2 == angle.distributions()[0].values().size() );
  CHECK( 30 == angle.distributions()[1].cosines().size() );
  CHECK( 30 == angle.distributions()[1].values().size() );
  CHECK( 95 == angle.distributions()[14].cosines().size() );
  CHECK( 95 == angle.distributions()[14].values().size() );
  CHECK( 96 == angle.distributions()[15].cosines().size() );
  CHECK( 96 == angle.distributions()[15].values().size() );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[0].cosines()[0] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[0].cosines()[1] ) );
  CHECK_THAT(  0.5         , WithinRel( angle.distributions()[0].values()[0] ) );
  CHECK_THAT(  0.5         , WithinRel( angle.distributions()[0].values()[1] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[1].cosines()[0] ) );
  CHECK_THAT( -0.93        , WithinRel( angle.distributions()[1].cosines()[1] ) );
  CHECK_THAT(  0.9962001   , WithinRel( angle.distributions()[1].cosines()[28] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[1].cosines()[29] ) );
  CHECK_THAT(  0.00293923  , WithinRel( angle.distributions()[1].values()[0] ) );
  CHECK_THAT(  0.00314865  , WithinRel( angle.distributions()[1].values()[1] ) );
  CHECK_THAT( 42.358       , WithinRel( angle.distributions()[1].values()[28] ) );
  CHECK_THAT( 62.1102      , WithinRel( angle.distributions()[1].values()[29] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[14].cosines()[0] ) );
  CHECK_THAT( -0.995       , WithinRel( angle.distributions()[14].cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( angle.distributions()[14].cosines()[93] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[14].cosines()[94] ) );
  CHECK_THAT(  1.51157e-11 , WithinRel( angle.distributions()[14].values()[0] ) );
  CHECK_THAT(  6.43040e-10 , WithinRel( angle.distributions()[14].values()[1] ) );
  CHECK_THAT(   8.14179e+5 , WithinRel( angle.distributions()[14].values()[93] ) );
  CHECK_THAT(   9.84753e+5 , WithinRel( angle.distributions()[14].values()[94] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[15].cosines()[0] ) );
  CHECK_THAT( -0.9999      , WithinRel( angle.distributions()[15].cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( angle.distributions()[15].cosines()[94] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[15].cosines()[95] ) );
  CHECK_THAT(  6.25670e-13 , WithinRel( angle.distributions()[15].values()[0] ) );
  CHECK_THAT(  1.25808e-11 , WithinRel( angle.distributions()[15].values()[1] ) );
  CHECK_THAT(   8.15658e+5 , WithinRel( angle.distributions()[15].values()[94] ) );
  CHECK_THAT(   9.86945e+5 , WithinRel( angle.distributions()[15].values()[95] ) );
  CHECK( 15 == angle.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );
}

void verifyElectronTotalElasticReaction( const Reaction& telastic ) {

  CHECK( id::ReactionID( "526" ) == telastic.identifier() );
  CHECK( ReactionType::Summation == telastic.type() );
  CHECK( false == telastic.hasProducts() );
  CHECK( true == telastic.isLinearised() );

  CHECK( std::nullopt == telastic.massDifferenceQValue() );
  CHECK( std::nullopt == telastic.reactionQValue() );

  CHECK( true == telastic.crossSection().isLinearised() );
  CHECK( 101 == telastic.crossSection().numberPoints() );
  CHECK( 1 == telastic.crossSection().numberRegions() );
  CHECK( 101 == telastic.crossSection().energies().size() );
  CHECK( 101 == telastic.crossSection().values().size() );
  CHECK( 1 == telastic.crossSection().boundaries().size() );
  CHECK( 1 == telastic.crossSection().interpolants().size() );
  CHECK( 100 == telastic.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == telastic.crossSection().interpolants()[0] );
  CHECK_THAT( 10., WithinRel( telastic.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( telastic.crossSection().energies()[100] ) );
  CHECK_THAT( 274896000., WithinRel( telastic.crossSection().values()[0] ) );
  CHECK_THAT( 12987.1, WithinRel( telastic.crossSection().values()[100] ) );

  CHECK( 0 == telastic.products().size() );
}

void verifyElectronBremsstrahlungReaction( const Reaction& bremsstrahlung ) {

  CHECK( id::ReactionID( "527" ) == bremsstrahlung.identifier() );
  CHECK( ReactionType::Primary == bremsstrahlung.type() );
  CHECK( true == bremsstrahlung.hasProducts() );
  CHECK( true == bremsstrahlung.isLinearised() );

  CHECK( std::nullopt == bremsstrahlung.massDifferenceQValue() );
  CHECK( std::nullopt != bremsstrahlung.reactionQValue() );
  CHECK_THAT( 0, WithinRel( bremsstrahlung.reactionQValue().value() ) );

  CHECK( true == bremsstrahlung.crossSection().isLinearised() );
  CHECK( 96 == bremsstrahlung.crossSection().numberPoints() );
  CHECK( 1 == bremsstrahlung.crossSection().numberRegions() );
  CHECK( 96 == bremsstrahlung.crossSection().energies().size() );
  CHECK( 96 == bremsstrahlung.crossSection().values().size() );
  CHECK( 1 == bremsstrahlung.crossSection().boundaries().size() );
  CHECK( 1 == bremsstrahlung.crossSection().interpolants().size() );
  CHECK( 95 == bremsstrahlung.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == bremsstrahlung.crossSection().interpolants()[0] );
  CHECK_THAT( 10., WithinRel( bremsstrahlung.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( bremsstrahlung.crossSection().energies()[95] ) );
  CHECK_THAT( 29.7832 , WithinRel( bremsstrahlung.crossSection().values()[0] ) );
  CHECK_THAT( 0.990621, WithinRel( bremsstrahlung.crossSection().values()[95] ) );

  CHECK( 2 == bremsstrahlung.products().size() );
  auto gamma = bremsstrahlung.products()[0];
  CHECK( id::ParticleID( "g" ) == gamma.identifier() );
  CHECK( true == gamma.isLinearised() );
  CHECK( false == gamma.hasAverageEnergy() );
  CHECK( true == gamma.hasDistributionData() );
  CHECK( true == std::holds_alternative< int >( gamma.multiplicity() ) );
  auto multiplicity = std::get< int >( gamma.multiplicity() );
  CHECK( 1 == multiplicity );
  CHECK( std::nullopt == gamma.averageEnergy() );
  CHECK( std::nullopt != gamma.distributionData() );
  CHECK( true == std::holds_alternative< UncorrelatedDistributionData >( gamma.distributionData().value() ) );
  auto data = std::get< UncorrelatedDistributionData >( gamma.distributionData().value() );
  CHECK( DistributionDataType::Uncorrelated == data.type() );
  CHECK( true == std::holds_alternative< IsotropicAngularDistributions >( data.angle() ) );
  CHECK( true == std::holds_alternative< TabulatedEnergyDistributions >( data.energy() ) );
  auto energy = std::get< TabulatedEnergyDistributions >( data.energy() );
  CHECK( 10 == energy.numberPoints() );
  CHECK( 1 == energy.numberRegions() );
  CHECK( 10 == energy.grid().size() );
  CHECK( 10 == energy.distributions().size() );
  CHECK( 1 == energy.boundaries().size() );
  CHECK( 1 == energy.interpolants().size() );
  CHECK_THAT(   10.   , WithinRel( energy.grid()[0] ) );
  CHECK_THAT(   20.736, WithinRel( energy.grid()[1] ) );
  CHECK_THAT(   1e+7  , WithinRel( energy.grid()[8] ) );
  CHECK_THAT(   1e+11 , WithinRel( energy.grid()[9] ) );
  CHECK(  17 == energy.distributions()[0].energies().size() );
  CHECK(  17 == energy.distributions()[0].values().size() );
  CHECK(  19 == energy.distributions()[1].energies().size() );
  CHECK(  19 == energy.distributions()[1].values().size() );
  CHECK(  85 == energy.distributions()[8].energies().size() );
  CHECK(  85 == energy.distributions()[8].values().size() );
  CHECK( 111 == energy.distributions()[9].energies().size() );
  CHECK( 111 == energy.distributions()[9].values().size() );
  CHECK_THAT(  0.1       , WithinRel( energy.distributions()[0].energies()[0] ) );
  CHECK_THAT(  0.133352  , WithinRel( energy.distributions()[0].energies()[1] ) );
  CHECK_THAT(  9.9       , WithinRel( energy.distributions()[0].energies()[15] ) );
  CHECK_THAT( 10.        , WithinRel( energy.distributions()[0].energies()[16] ) );
  CHECK_THAT( 2.1394     , WithinRel( energy.distributions()[0].values()[0] ) );
  CHECK_THAT( 1.60421    , WithinRel( energy.distributions()[0].values()[1] ) );
  CHECK_THAT(  .0214392  , WithinRel( energy.distributions()[0].values()[15] ) );
  CHECK_THAT(  .0212245  , WithinRel( energy.distributions()[0].values()[16] ) );
  CHECK_THAT(  0.1       , WithinRel( energy.distributions()[1].energies()[0] ) );
  CHECK_THAT(  0.14608   , WithinRel( energy.distributions()[1].energies()[1] ) );
  CHECK_THAT( 20.5286    , WithinRel( energy.distributions()[1].energies()[17] ) );
  CHECK_THAT( 20.736     , WithinRel( energy.distributions()[1].energies()[18] ) );
  CHECK_THAT( 1.84823    , WithinRel( energy.distributions()[1].values()[0] ) );
  CHECK_THAT( 1.26507    , WithinRel( energy.distributions()[1].values()[1] ) );
  CHECK_THAT(  .00885527 , WithinRel( energy.distributions()[1].values()[17] ) );
  CHECK_THAT(  .00876641 , WithinRel( energy.distributions()[1].values()[18] ) );
  CHECK_THAT( .100000000 , WithinRel( energy.distributions()[8].energies()[0] ) );
  CHECK_THAT( .128640000 , WithinRel( energy.distributions()[8].energies()[1] ) );
  CHECK_THAT(  9981470.  , WithinRel( energy.distributions()[8].energies()[83] ) );
  CHECK_THAT(  1e+7      , WithinRel( energy.distributions()[8].energies()[84] ) );
  CHECK_THAT( .608334000 , WithinRel( energy.distributions()[8].values()[0] ) );
  CHECK_THAT( .472898000 , WithinRel( energy.distributions()[8].values()[1] ) );
  CHECK_THAT( 9.28343e-12, WithinRel( energy.distributions()[8].values()[83] ) );
  CHECK_THAT( 5.8374e-12 , WithinRel( energy.distributions()[8].values()[84] ) );
  CHECK_THAT(  .100000000, WithinRel( energy.distributions()[9].energies()[0] ) );
  CHECK_THAT(  .148551000, WithinRel( energy.distributions()[9].energies()[1] ) );
  CHECK_THAT( 9.99082E+10, WithinRel( energy.distributions()[9].energies()[109] ) );
  CHECK_THAT(       1e+11, WithinRel( energy.distributions()[9].energies()[110] ) );
  CHECK_THAT(  .365591000, WithinRel( energy.distributions()[9].values()[0] ) );
  CHECK_THAT(  .246105000, WithinRel( energy.distributions()[9].values()[1] ) );
  CHECK_THAT( 9.06486E-16, WithinRel( energy.distributions()[9].values()[109] ) );
  CHECK_THAT( 5.16344E-16, WithinRel( energy.distributions()[9].values()[110] ) );
  CHECK( 9 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
  auto electron = bremsstrahlung.products()[1];
  CHECK( id::ParticleID( "e-" ) == electron.identifier() );
  CHECK( true == electron.isLinearised() );
  CHECK( true == electron.hasAverageEnergy() );
  CHECK( false == electron.hasDistributionData() );
  CHECK( true == std::holds_alternative< int >( electron.multiplicity() ) );
  multiplicity = std::get< int >( electron.multiplicity() );
  CHECK( 1 == multiplicity );
  CHECK( std::nullopt != electron.averageEnergy() );
  auto average = electron.averageEnergy().value();
  CHECK( true == average.isLinearised() );
  CHECK( 82 == average.numberPoints() );
  CHECK( 1 == average.numberRegions() );
  CHECK( 82 == average.energies().size() );
  CHECK( 82 == average.values().size() );
  CHECK( 1 == average.boundaries().size() );
  CHECK( 1 == average.interpolants().size() );
  CHECK( 81 == average.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == average.interpolants()[0] );
  CHECK_THAT( 10.        , WithinRel( average.energies()[0] ) );
  CHECK_THAT( 14.4       , WithinRel( average.energies()[1] ) );
  CHECK_THAT( 7.86876E+10, WithinRel( average.energies()[80] ) );
  CHECK_THAT(       1e+11, WithinRel( average.energies()[81] ) );
  CHECK_THAT(  10.         - 2.14426   , WithinRel( average.values()[0] ) );
  CHECK_THAT(  14.4        - 2.87181   , WithinRel( average.values()[1] ) );
  CHECK_THAT(  7.86876E+10 - 2.11850E+9, WithinRel( average.values()[80] ) );
  CHECK_THAT(  1e+11       - 2.66810E+9, WithinRel( average.values()[81] ) );
  CHECK( std::nullopt == electron.distributionData() );
}

void verifyElectronExcitationReaction( const Reaction& subionisation ) {

  CHECK( id::ReactionID( "528" ) == subionisation.identifier() );
  CHECK( ReactionType::Primary == subionisation.type() );
  CHECK( true == subionisation.hasProducts() );
  CHECK( true == subionisation.isLinearised() );

  CHECK( std::nullopt == subionisation.massDifferenceQValue() );
  CHECK( std::nullopt != subionisation.reactionQValue() );
  CHECK_THAT( 0., WithinRel( subionisation.reactionQValue().value() ) );

  CHECK( true == subionisation.crossSection().isLinearised() );
  CHECK( 170 == subionisation.crossSection().numberPoints() );
  CHECK( 1 == subionisation.crossSection().numberRegions() );
  CHECK( 170 == subionisation.crossSection().energies().size() );
  CHECK( 170 == subionisation.crossSection().values().size() );
  CHECK( 1 == subionisation.crossSection().boundaries().size() );
  CHECK( 1 == subionisation.crossSection().interpolants().size() );
  CHECK( 169 == subionisation.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == subionisation.crossSection().interpolants()[0] );
  CHECK_THAT( 13.6, WithinRel( subionisation.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( subionisation.crossSection().energies()[169] ) );
  CHECK_THAT( 0. , WithinRel( subionisation.crossSection().values()[0] ) );
  CHECK_THAT( 81441.6, WithinRel( subionisation.crossSection().values()[169] ) );

  CHECK( 1 == subionisation.products().size() );
  auto electron = subionisation.products()[0];
  CHECK( id::ParticleID( "e-" ) == electron.identifier() );
  CHECK( true == electron.isLinearised() );
  CHECK( true == electron.hasAverageEnergy() );
  CHECK( false == electron.hasDistributionData() );
  CHECK( true == std::holds_alternative< int >( electron.multiplicity() ) );
  auto multiplicity = std::get< int >( electron.multiplicity() );
  CHECK( 1 == multiplicity );
  CHECK( std::nullopt != electron.averageEnergy() );
  auto average = electron.averageEnergy().value();
  CHECK( true == average.isLinearised() );
  CHECK( 170 == average.numberPoints() );
  CHECK( 1 == average.numberRegions() );
  CHECK( 170 == average.energies().size() );
  CHECK( 170 == average.values().size() );
  CHECK( 1 == average.boundaries().size() );
  CHECK( 1 == average.interpolants().size() );
  CHECK( 169 == average.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == average.interpolants()[0] );
  CHECK_THAT( 13.6       , WithinRel( average.energies()[0] ) );
  CHECK_THAT( 13.7740142 , WithinRel( average.energies()[1] ) );
  CHECK_THAT(       9e+10, WithinRel( average.energies()[168] ) );
  CHECK_THAT(       1e+11, WithinRel( average.energies()[169] ) );
  CHECK_THAT(  13.6        - 13.6      , WithinRel( average.values()[0] ) );
  CHECK_THAT(  13.7740142  - 13.6069279, WithinRel( average.values()[1] ) );
  CHECK_THAT(  9e+10       - 21.0777000, WithinRel( average.values()[168] ) );
  CHECK_THAT(  1e+11       - 21.0777000, WithinRel( average.values()[169] ) );
  CHECK( std::nullopt == electron.distributionData() );
}

void verifyElectronSubshellIonisationReaction( const Reaction& subionisation ) {

  CHECK( id::ReactionID( "534" ) == subionisation.identifier() );
  CHECK( ReactionType::Primary == subionisation.type() );
  CHECK( true == subionisation.hasProducts() );
  CHECK( true == subionisation.isLinearised() );

  CHECK( std::nullopt == subionisation.massDifferenceQValue() );
  CHECK( std::nullopt != subionisation.reactionQValue() );
  CHECK_THAT( -13.6, WithinRel( subionisation.reactionQValue().value() ) );

  CHECK( true == subionisation.crossSection().isLinearised() );
  CHECK( 35 == subionisation.crossSection().numberPoints() );
  CHECK( 1 == subionisation.crossSection().numberRegions() );
  CHECK( 35 == subionisation.crossSection().energies().size() );
  CHECK( 35 == subionisation.crossSection().values().size() );
  CHECK( 1 == subionisation.crossSection().boundaries().size() );
  CHECK( 1 == subionisation.crossSection().interpolants().size() );
  CHECK( 34 == subionisation.crossSection().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == subionisation.crossSection().interpolants()[0] );
  CHECK_THAT( 13.6, WithinRel( subionisation.crossSection().energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( subionisation.crossSection().energies()[34] ) );
  CHECK_THAT( 0. , WithinRel( subionisation.crossSection().values()[0] ) );
  CHECK_THAT( 82892.4, WithinRel( subionisation.crossSection().values()[34] ) );

  CHECK( 1 == subionisation.products().size() );
  auto electron = subionisation.products()[0];
  CHECK( id::ParticleID( "e-" ) == electron.identifier() );
  CHECK( true == electron.isLinearised() );
  CHECK( false == electron.hasAverageEnergy() );
  CHECK( true == electron.hasDistributionData() );
  CHECK( true == std::holds_alternative< int >( electron.multiplicity() ) );
  auto multiplicity = std::get< int >( electron.multiplicity() );
  CHECK( 1 == multiplicity );
  CHECK( std::nullopt == electron.averageEnergy() );
  CHECK( std::nullopt != electron.distributionData() );
  CHECK( true == std::holds_alternative< UncorrelatedDistributionData >( electron.distributionData().value() ) );
  auto data = std::get< UncorrelatedDistributionData >( electron.distributionData().value() );
  CHECK( DistributionDataType::Uncorrelated == data.type() );
  CHECK( true == std::holds_alternative< IsotropicAngularDistributions >( data.angle() ) );
  CHECK( true == std::holds_alternative< TabulatedEnergyDistributions >( data.energy() ) );
  auto energy = std::get< TabulatedEnergyDistributions >( data.energy() );
  CHECK( 8 == energy.numberPoints() );
  CHECK( 1 == energy.numberRegions() );
  CHECK( 8 == energy.grid().size() );
  CHECK( 8 == energy.distributions().size() );
  CHECK( 1 == energy.boundaries().size() );
  CHECK( 1 == energy.interpolants().size() );
  CHECK_THAT(   13.6  , WithinRel( energy.grid()[0] ) );
  CHECK_THAT(   14.28 , WithinRel( energy.grid()[1] ) );
  CHECK_THAT( 50118700, WithinRel( energy.grid()[6] ) );
  CHECK_THAT(   1e+11 , WithinRel( energy.grid()[7] ) );
  CHECK(  2 == energy.distributions()[0].energies().size() );
  CHECK(  2 == energy.distributions()[0].values().size() );
  CHECK(  2 == energy.distributions()[1].energies().size() );
  CHECK(  2 == energy.distributions()[1].values().size() );
  CHECK( 100 == energy.distributions()[6].energies().size() );
  CHECK( 100 == energy.distributions()[6].values().size() );
  CHECK( 147 == energy.distributions()[7].energies().size() );
  CHECK( 147 == energy.distributions()[7].values().size() );
  CHECK_THAT(  0.00279866, WithinRel( energy.distributions()[0].energies()[0] ) );
  CHECK_THAT(  0.0279866  , WithinRel( energy.distributions()[0].energies()[1] ) );
  CHECK_THAT( 39.7015    , WithinRel( energy.distributions()[0].values()[0] ) );
  CHECK_THAT( 39.7015    , WithinRel( energy.distributions()[0].values()[1] ) );
  CHECK_THAT(  .00279866 , WithinRel( energy.distributions()[1].energies()[0] ) );
  CHECK_THAT(  .279866   , WithinRel( energy.distributions()[1].energies()[1] ) );
  CHECK_THAT( 3.67711    , WithinRel( energy.distributions()[1].values()[0] ) );
  CHECK_THAT( 3.54135    , WithinRel( energy.distributions()[1].values()[1] ) );
  CHECK_THAT( .100000000 , WithinRel( energy.distributions()[6].energies()[0] ) );
  CHECK_THAT( .630957000 , WithinRel( energy.distributions()[6].energies()[1] ) );
  CHECK_THAT(  19952600. , WithinRel( energy.distributions()[6].energies()[98] ) );
  CHECK_THAT(  25059400  , WithinRel( energy.distributions()[6].energies()[99] ) );
  CHECK_THAT( .161903    , WithinRel( energy.distributions()[6].values()[0] ) );
  CHECK_THAT(  .143109000, WithinRel( energy.distributions()[6].values()[1] ) );
  CHECK_THAT( 1.22367E-14, WithinRel( energy.distributions()[6].values()[98] ) );
  CHECK_THAT( 1.09273E-14, WithinRel( energy.distributions()[6].values()[99] ) );
  CHECK_THAT(  .100000000, WithinRel( energy.distributions()[7].energies()[0] ) );
  CHECK_THAT(  .630957000, WithinRel( energy.distributions()[7].energies()[1] ) );
  CHECK_THAT( 3.98107E+10, WithinRel( energy.distributions()[7].energies()[145] ) );
  CHECK_THAT(       5e+10, WithinRel( energy.distributions()[7].energies()[146] ) );
  CHECK_THAT(  .161897000, WithinRel( energy.distributions()[7].values()[0] ) );
  CHECK_THAT(  .143104000, WithinRel( energy.distributions()[7].values()[1] ) );
  CHECK_THAT( 3.10545E-21, WithinRel( energy.distributions()[7].values()[145] ) );
  CHECK_THAT(  2.7755E-21, WithinRel( energy.distributions()[7].values()[146] ) );
  CHECK( 7 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
}
