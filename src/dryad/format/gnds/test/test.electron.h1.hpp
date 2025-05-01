namespace electron {

// e-001_H_000.endf and e-001_H_000-endf80.endf
namespace h1 {

  void verifyTotalReaction( const Reaction& total ) {

    CHECK( id::ReactionID( "501" ) == total.identifier() );
    CHECK( ReactionType::Summation == total.type() );
    CHECK( false == total.hasProducts() );
    CHECK( true == total.isLinearised() );

    CHECK( std::nullopt != total.partialReactionIdentifiers() );
    auto partials = total.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID(  "525" ) == partials[0] );
    CHECK( id::ReactionID( "-526" ) == partials[1] );
    CHECK( id::ReactionID(  "527" ) == partials[2] );
    CHECK( id::ReactionID(  "528" ) == partials[3] );
    CHECK( id::ReactionID(  "534" ) == partials[4] );

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

  void verifyTotalIonisationReaction( const Reaction& ionisation ) {

    CHECK( id::ReactionID( "522" ) == ionisation.identifier() );
    CHECK( ReactionType::Summation == ionisation.type() );
    CHECK( false == ionisation.hasProducts() );
    CHECK( true == ionisation.isLinearised() );

    CHECK( std::nullopt != ionisation.partialReactionIdentifiers() );
    auto partials = ionisation.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "534" ) == partials[0] );

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

  void verifyElasticReaction( const Reaction& elastic ) {

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

    CHECK( 2 == elastic.products().size() );

    auto electron = elastic.products()[0];
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );
    CHECK( true == electron.isLinearised() );
    CHECK( false == electron.hasAverageEnergy() );
    CHECK( true == electron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( electron.multiplicity() ) );
    auto multiplicity = std::get< int >( electron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == electron.averageEnergy() );
    CHECK( std::nullopt != electron.distributionData() );
    CHECK( true == std::holds_alternative< TwoBodyDistributionData >( electron.distributionData().value() ) );
    auto data = std::get< TwoBodyDistributionData >( electron.distributionData().value() );
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
    CHECK(  2 == angle.distributions()[0].pdf().cosines().size() );
    CHECK(  2 == angle.distributions()[0].pdf().values().size() );
    CHECK( 30 == angle.distributions()[1].pdf().cosines().size() );
    CHECK( 30 == angle.distributions()[1].pdf().values().size() );
    CHECK( 95 == angle.distributions()[14].pdf().cosines().size() );
    CHECK( 95 == angle.distributions()[14].pdf().values().size() );
    CHECK( 96 == angle.distributions()[15].pdf().cosines().size() );
    CHECK( 96 == angle.distributions()[15].pdf().values().size() );

    // dryad normalises distributions upon construction
    // the numbers in the tests given below are the values as found in the test
    // file so they need to be normalised. the following values are the scaling
    // factors that need to be applied (calculated by integrating the distributions
    // in excel).
    double scale00 = 2. / 1.999999;
    double scale01 = 1. / 1.00000016366000;
    double scale14 = 1. / 1.00000048323214;
    double scale15 = 1. / 1.00000000937718;

    CHECK_THAT(           -1.         , WithinRel( angle.distributions()[0].pdf().cosines()[0] ) );
    CHECK_THAT(            0.999999   , WithinRel( angle.distributions()[0].pdf().cosines()[1] ) );
    CHECK_THAT( scale00 *  0.5        , WithinRel( angle.distributions()[0].pdf().values()[0] ) );
    CHECK_THAT( scale00 *  0.5        , WithinRel( angle.distributions()[0].pdf().values()[1] ) );
    CHECK_THAT(           -1.         , WithinRel( angle.distributions()[1].pdf().cosines()[0] ) );
    CHECK_THAT(           -0.93       , WithinRel( angle.distributions()[1].pdf().cosines()[1] ) );
    CHECK_THAT(            0.9962001  , WithinRel( angle.distributions()[1].pdf().cosines()[28] ) );
    CHECK_THAT(            0.999999   , WithinRel( angle.distributions()[1].pdf().cosines()[29] ) );
    CHECK_THAT( scale01 *  0.00293923 , WithinRel( angle.distributions()[1].pdf().values()[0] ) );
    CHECK_THAT( scale01 *  0.00314865 , WithinRel( angle.distributions()[1].pdf().values()[1] ) );
    CHECK_THAT( scale01 * 42.358      , WithinRel( angle.distributions()[1].pdf().values()[28] ) );
    CHECK_THAT( scale01 * 62.1102     , WithinRel( angle.distributions()[1].pdf().values()[29] ) );
    CHECK_THAT(           -1.         , WithinRel( angle.distributions()[14].pdf().cosines()[0] ) );
    CHECK_THAT(           -0.995      , WithinRel( angle.distributions()[14].pdf().cosines()[1] ) );
    CHECK_THAT(            0.9999989  , WithinRel( angle.distributions()[14].pdf().cosines()[93] ) );
    CHECK_THAT(            0.999999   , WithinRel( angle.distributions()[14].pdf().cosines()[94] ) );
    CHECK_THAT( scale14 *  1.51157e-11, WithinRel( angle.distributions()[14].pdf().values()[0] ) );
    CHECK_THAT( scale14 *  6.43040e-10, WithinRel( angle.distributions()[14].pdf().values()[1] ) );
    CHECK_THAT( scale14 *   8.14179e+5, WithinRel( angle.distributions()[14].pdf().values()[93] ) );
    CHECK_THAT( scale14 *   9.84753e+5, WithinRel( angle.distributions()[14].pdf().values()[94] ) );
    CHECK_THAT(           -1.         , WithinRel( angle.distributions()[15].pdf().cosines()[0] ) );
    CHECK_THAT(           -0.9999     , WithinRel( angle.distributions()[15].pdf().cosines()[1] ) );
    CHECK_THAT(            0.9999989  , WithinRel( angle.distributions()[15].pdf().cosines()[94] ) );
    CHECK_THAT(            0.999999   , WithinRel( angle.distributions()[15].pdf().cosines()[95] ) );
    CHECK_THAT( scale15 *  6.25670e-13, WithinRel( angle.distributions()[15].pdf().values()[0] ) );
    CHECK_THAT( scale15 *  1.25808e-11, WithinRel( angle.distributions()[15].pdf().values()[1] ) );
    CHECK_THAT( scale15 *   8.15658e+5, WithinRel( angle.distributions()[15].pdf().values()[94] ) );
    CHECK_THAT( scale15 *   9.86945e+5, WithinRel( angle.distributions()[15].pdf().values()[95] ) );
    CHECK( false == angle.distributions()[0].hasCdf() );
    CHECK( false == angle.distributions()[1].hasCdf() );
    CHECK( false == angle.distributions()[14].hasCdf() );
    CHECK( false == angle.distributions()[15].hasCdf() );
    CHECK_THROWS( angle.distributions()[0].cdf() );
    CHECK_THROWS( angle.distributions()[1].cdf() );
    CHECK_THROWS( angle.distributions()[14].cdf() );
    CHECK_THROWS( angle.distributions()[15].cdf() );
    CHECK( 15 == angle.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );

    auto hydrogen = elastic.products()[1];
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyTotalElasticReaction( const Reaction& telastic ) {

    CHECK( id::ReactionID( "526" ) == telastic.identifier() );
    CHECK( ReactionType::Summation == telastic.type() );
    CHECK( false == telastic.hasProducts() );
    CHECK( true == telastic.isLinearised() );

    CHECK( std::nullopt != telastic.partialReactionIdentifiers() );
    auto partials = telastic.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID(  "525" ) == partials[0] );
    CHECK( id::ReactionID( "-526" ) == partials[1] );

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

  void verifyBremsstrahlungReaction( const Reaction& bremsstrahlung ) {

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

    CHECK( 3 == bremsstrahlung.products().size() );

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
    CHECK(  17 == energy.distributions()[0].pdf().energies().size() );
    CHECK(  17 == energy.distributions()[0].pdf().values().size() );
    CHECK(  19 == energy.distributions()[1].pdf().energies().size() );
    CHECK(  19 == energy.distributions()[1].pdf().values().size() );
    CHECK(  85 == energy.distributions()[8].pdf().energies().size() );
    CHECK(  85 == energy.distributions()[8].pdf().values().size() );
    CHECK( 111 == energy.distributions()[9].pdf().energies().size() );
    CHECK( 111 == energy.distributions()[9].pdf().values().size() );

    // dryad normalises distributions upon construction
    // the numbers in the tests given below are the values as found in the test
    // file so they need to be normalised. the following values are the scaling
    // factors that need to be applied (calculated by integrating the distributions
    // in excel).
    double scale00 = 1. / 0.99999998809250;
    double scale01 = 1. / 0.99999998353900;
    double scale08 = 1. / 0.99999973884057;
    double scale09 = 1. / 0.99999993564706;

    CHECK_THAT(             0.1       , WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
    CHECK_THAT(             0.133352  , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
    CHECK_THAT(             9.9       , WithinRel( energy.distributions()[0].pdf().energies()[15] ) );
    CHECK_THAT(            10.        , WithinRel( energy.distributions()[0].pdf().energies()[16] ) );
    CHECK_THAT( scale00 *  2.1394     , WithinRel( energy.distributions()[0].pdf().values()[0] ) );
    CHECK_THAT( scale00 *  1.60421    , WithinRel( energy.distributions()[0].pdf().values()[1] ) );
    CHECK_THAT( scale00 *   .0214392  , WithinRel( energy.distributions()[0].pdf().values()[15] ) );
    CHECK_THAT( scale00 *   .0212245  , WithinRel( energy.distributions()[0].pdf().values()[16] ) );
    CHECK_THAT(            0.1        , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
    CHECK_THAT(            0.14608    , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
    CHECK_THAT(           20.5286     , WithinRel( energy.distributions()[1].pdf().energies()[17] ) );
    CHECK_THAT(           20.736      , WithinRel( energy.distributions()[1].pdf().energies()[18] ) );
    CHECK_THAT( scale01 *  1.84823    , WithinRel( energy.distributions()[1].pdf().values()[0] ) );
    CHECK_THAT( scale01 * 1.26507     , WithinRel( energy.distributions()[1].pdf().values()[1] ) );
    CHECK_THAT( scale01 *  .00885527  , WithinRel( energy.distributions()[1].pdf().values()[17] ) );
    CHECK_THAT( scale01 *  .00876641  , WithinRel( energy.distributions()[1].pdf().values()[18] ) );
    CHECK_THAT(           .100000000  , WithinRel( energy.distributions()[8].pdf().energies()[0] ) );
    CHECK_THAT(           .128640000  , WithinRel( energy.distributions()[8].pdf().energies()[1] ) );
    CHECK_THAT(            9981470.   , WithinRel( energy.distributions()[8].pdf().energies()[83] ) );
    CHECK_THAT(            1e+7       , WithinRel( energy.distributions()[8].pdf().energies()[84] ) );
    CHECK_THAT( scale08 * .608334000  , WithinRel( energy.distributions()[8].pdf().values()[0] ) );
    CHECK_THAT( scale08 * .472898000  , WithinRel( energy.distributions()[8].pdf().values()[1] ) );
    CHECK_THAT( scale08 * 9.28343e-12 , WithinRel( energy.distributions()[8].pdf().values()[83] ) );
    CHECK_THAT( scale08 * 5.8374e-12  , WithinRel( energy.distributions()[8].pdf().values()[84] ) );
    CHECK_THAT(            .100000000 , WithinRel( energy.distributions()[9].pdf().energies()[0] ) );
    CHECK_THAT(            .148551000 , WithinRel( energy.distributions()[9].pdf().energies()[1] ) );
    CHECK_THAT(           9.99082E+10 , WithinRel( energy.distributions()[9].pdf().energies()[109] ) );
    CHECK_THAT(                 1e+11 , WithinRel( energy.distributions()[9].pdf().energies()[110] ) );
    CHECK_THAT( scale09 *  .365591000 , WithinRel( energy.distributions()[9].pdf().values()[0] ) );
    CHECK_THAT( scale09 *  .246105000 , WithinRel( energy.distributions()[9].pdf().values()[1] ) );
    CHECK_THAT( scale09 * 9.06486E-16 , WithinRel( energy.distributions()[9].pdf().values()[109] ) );
    CHECK_THAT( scale09 * 5.16344E-16 , WithinRel( energy.distributions()[9].pdf().values()[110] ) );
    CHECK( false == energy.distributions()[0].hasCdf() );
    CHECK( false == energy.distributions()[1].hasCdf() );
    CHECK( false == energy.distributions()[8].hasCdf() );
    CHECK( false == energy.distributions()[9].hasCdf() );
    CHECK_THROWS( energy.distributions()[0].cdf() );
    CHECK_THROWS( energy.distributions()[1].cdf() );
    CHECK_THROWS( energy.distributions()[8].cdf() );
    CHECK_THROWS( energy.distributions()[9].cdf() );
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

    auto hydrogen = bremsstrahlung.products()[2];
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyExcitationReaction( const Reaction& subionisation ) {

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

    CHECK( 2 == subionisation.products().size() );

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

    auto hydrogen = subionisation.products()[1];
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifySubshellIonisationReaction( const Reaction& subionisation ) {

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

    CHECK( 3 == subionisation.products().size() );

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
    CHECK(  2 == energy.distributions()[0].pdf().energies().size() );
    CHECK(  2 == energy.distributions()[0].pdf().values().size() );
    CHECK(  2 == energy.distributions()[1].pdf().energies().size() );
    CHECK(  2 == energy.distributions()[1].pdf().values().size() );
    CHECK( 100 == energy.distributions()[6].pdf().energies().size() );
    CHECK( 100 == energy.distributions()[6].pdf().values().size() );
    CHECK( 147 == energy.distributions()[7].pdf().energies().size() );
    CHECK( 147 == energy.distributions()[7].pdf().values().size() );

    // dryad normalises distributions upon construction
    // the numbers in the tests given below are the values as found in the test
    // file so they need to be normalised. the following values are the scaling
    // factors that need to be applied (calculated by integrating the distributions
    // in excel).
    double scale00 = 1. / 0.99999899991000;
    double scale01 = 1. / 0.99999975554820;
    double scale06 = 1. / 1.00000040584089;
    double scale07 = 1. / 1.00000007405513;

    CHECK_THAT(            0.00279866, WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
    CHECK_THAT(            0.0279866 , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
    CHECK_THAT( scale00 * 39.7015    , WithinRel( energy.distributions()[0].pdf().values()[0] ) );
    CHECK_THAT( scale00 * 39.7015    , WithinRel( energy.distributions()[0].pdf().values()[1] ) );
    CHECK_THAT(            .00279866 , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
    CHECK_THAT(            .279866   , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
    CHECK_THAT( scale01 * 3.67711    , WithinRel( energy.distributions()[1].pdf().values()[0] ) );
    CHECK_THAT( scale01 * 3.54135    , WithinRel( energy.distributions()[1].pdf().values()[1] ) );
    CHECK_THAT(           .100000000 , WithinRel( energy.distributions()[6].pdf().energies()[0] ) );
    CHECK_THAT(           .630957000 , WithinRel( energy.distributions()[6].pdf().energies()[1] ) );
    CHECK_THAT(            19952600. , WithinRel( energy.distributions()[6].pdf().energies()[98] ) );
    CHECK_THAT(            25059400  , WithinRel( energy.distributions()[6].pdf().energies()[99] ) );
    CHECK_THAT( scale06 * .161903    , WithinRel( energy.distributions()[6].pdf().values()[0] ) );
    CHECK_THAT( scale06 *  .143109000, WithinRel( energy.distributions()[6].pdf().values()[1] ) );
    CHECK_THAT( scale06 * 1.22367E-14, WithinRel( energy.distributions()[6].pdf().values()[98] ) );
    CHECK_THAT( scale06 * 1.09273E-14, WithinRel( energy.distributions()[6].pdf().values()[99] ) );
    CHECK_THAT(            .100000000, WithinRel( energy.distributions()[7].pdf().energies()[0] ) );
    CHECK_THAT(            .630957000, WithinRel( energy.distributions()[7].pdf().energies()[1] ) );
    CHECK_THAT(           3.98107E+10, WithinRel( energy.distributions()[7].pdf().energies()[145] ) );
    CHECK_THAT(                 5e+10, WithinRel( energy.distributions()[7].pdf().energies()[146] ) );
    CHECK_THAT( scale07 *  .161897000, WithinRel( energy.distributions()[7].pdf().values()[0] ) );
    CHECK_THAT( scale07 *  .143104000, WithinRel( energy.distributions()[7].pdf().values()[1] ) );
    CHECK_THAT( scale07 * 3.10545E-21, WithinRel( energy.distributions()[7].pdf().values()[145] ) );
    CHECK_THAT( scale07 *  2.7755E-21, WithinRel( energy.distributions()[7].pdf().values()[146] ) );
    CHECK( false == energy.distributions()[0].hasCdf() );
    CHECK( false == energy.distributions()[1].hasCdf() );
    CHECK( false == energy.distributions()[6].hasCdf() );
    CHECK( false == energy.distributions()[7].hasCdf() );
    CHECK_THROWS( energy.distributions()[0].cdf() );
    CHECK_THROWS( energy.distributions()[1].cdf() );
    CHECK_THROWS( energy.distributions()[6].cdf() );
    CHECK_THROWS( energy.distributions()[7].cdf() );
    CHECK( 7 == energy.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );

    electron = subionisation.products()[1];
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    auto ion = subionisation.products()[2];
    CHECK( id::ParticleID( "H{1s1/2}" ) == ion.identifier() );
  }

  void verifyElasticDeficitReaction( const Reaction& deficit ) {

    CHECK( id::ReactionID( "-526" ) == deficit.identifier() );
    CHECK( ReactionType::Primary == deficit.type() );
    CHECK( false == deficit.hasProducts() );
    CHECK( true == deficit.isLinearised() );

    CHECK( std::nullopt == deficit.partialReactionIdentifiers() );

    CHECK( std::nullopt == deficit.massDifferenceQValue() );
    CHECK( std::nullopt != deficit.reactionQValue() );

    CHECK( true == deficit.crossSection().isLinearised() );

    CHECK( 0 == deficit.products().size() );
  }

} // namespace h1
} // namespace electron
