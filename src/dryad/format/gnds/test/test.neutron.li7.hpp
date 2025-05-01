namespace neutron {

// test functions based on n-003_Li_007.endf
namespace li7 {

  void verifyTotalReaction( const Reaction& total ) {

    CHECK( id::ReactionID( "1" ) == total.identifier() );
    CHECK( ReactionType::Summation == total.type() );
    CHECK( false == total.hasProducts() );
    CHECK( true == total.isLinearised() );

    CHECK( std::nullopt != total.partialReactionIdentifiers() );
    auto partials = total.partialReactionIdentifiers().value();
    CHECK( 38 == partials.size() );
    CHECK( id::ReactionID(   "2" ) == partials[0] );
    CHECK( id::ReactionID(  "51" ) == partials[1] );
    CHECK( id::ReactionID(  "52" ) == partials[2] );
    CHECK( id::ReactionID(  "53" ) == partials[3] );
    CHECK( id::ReactionID(  "54" ) == partials[4] );
    CHECK( id::ReactionID(  "55" ) == partials[5] );
    CHECK( id::ReactionID(  "56" ) == partials[6] );
    CHECK( id::ReactionID(  "57" ) == partials[7] );
    CHECK( id::ReactionID(  "58" ) == partials[8] );
    CHECK( id::ReactionID(  "59" ) == partials[9] );
    CHECK( id::ReactionID(  "60" ) == partials[10] );
    CHECK( id::ReactionID(  "61" ) == partials[11] );
    CHECK( id::ReactionID(  "62" ) == partials[12] );
    CHECK( id::ReactionID(  "63" ) == partials[13] );
    CHECK( id::ReactionID(  "64" ) == partials[14] );
    CHECK( id::ReactionID(  "65" ) == partials[15] );
    CHECK( id::ReactionID(  "66" ) == partials[16] );
    CHECK( id::ReactionID(  "67" ) == partials[17] );
    CHECK( id::ReactionID(  "68" ) == partials[18] );
    CHECK( id::ReactionID(  "69" ) == partials[19] );
    CHECK( id::ReactionID(  "70" ) == partials[20] );
    CHECK( id::ReactionID(  "71" ) == partials[21] );
    CHECK( id::ReactionID(  "72" ) == partials[22] );
    CHECK( id::ReactionID(  "73" ) == partials[23] );
    CHECK( id::ReactionID(  "74" ) == partials[24] );
    CHECK( id::ReactionID(  "75" ) == partials[25] );
    CHECK( id::ReactionID(  "76" ) == partials[26] );
    CHECK( id::ReactionID(  "77" ) == partials[27] );
    CHECK( id::ReactionID(  "78" ) == partials[28] );
    CHECK( id::ReactionID(  "79" ) == partials[29] );
    CHECK( id::ReactionID(  "80" ) == partials[30] );
    CHECK( id::ReactionID(  "81" ) == partials[31] );
    CHECK( id::ReactionID(  "82" ) == partials[32] );
    CHECK( id::ReactionID(  "16" ) == partials[33] );
    CHECK( id::ReactionID( "102" ) == partials[34] );
    CHECK( id::ReactionID(  "24" ) == partials[35] );
    CHECK( id::ReactionID(  "25" ) == partials[36] );
    CHECK( id::ReactionID( "104" ) == partials[37] );

    CHECK( std::nullopt == total.massDifferenceQValue() );
    CHECK( std::nullopt == total.reactionQValue() );

    CHECK( true == total.crossSection().isLinearised() );
    CHECK( 537 == total.crossSection().numberPoints() );
    CHECK( 1 == total.crossSection().numberRegions() );
    CHECK( 537 == total.crossSection().energies().size() );
    CHECK( 537 == total.crossSection().values().size() );
    CHECK( 1 == total.crossSection().boundaries().size() );
    CHECK( 1 == total.crossSection().interpolants().size() );
    CHECK( 536 == total.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == total.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( total.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( total.crossSection().energies()[536] ) );
    CHECK_THAT( 3.254     , WithinRel( total.crossSection().values()[0] ) );
    CHECK_THAT( 1.19328997, WithinRel( total.crossSection().values()[536] ) );

    CHECK( 0 == total.products().size() );
  }

  void verifyElasticReaction( const Reaction& elastic ) {

    CHECK( id::ReactionID( "2" ) == elastic.identifier() );
    CHECK( ReactionType::Primary == elastic.type() );
    CHECK( true == elastic.hasProducts() );
    CHECK( true == elastic.isLinearised() );

    CHECK( std::nullopt == elastic.massDifferenceQValue() );
    CHECK( std::nullopt != elastic.reactionQValue() );
    CHECK_THAT( 0, WithinRel( elastic.reactionQValue().value() ) );

    CHECK( true == elastic.crossSection().isLinearised() );
    CHECK( 179 == elastic.crossSection().numberPoints() );
    CHECK( 1 == elastic.crossSection().numberRegions() );
    CHECK( 179 == elastic.crossSection().energies().size() );
    CHECK( 179 == elastic.crossSection().values().size() );
    CHECK( 1 == elastic.crossSection().boundaries().size() );
    CHECK( 1 == elastic.crossSection().interpolants().size() );
    CHECK( 178 == elastic.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == elastic.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( elastic.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( elastic.crossSection().energies()[178] ) );
    CHECK_THAT( .97     , WithinRel( elastic.crossSection().values()[0] ) );
    CHECK_THAT( .8637753, WithinRel( elastic.crossSection().values()[178] ) );

    CHECK( 2 == elastic.products().size() );

    auto neutron = elastic.products()[0];
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( true == neutron.isLinearised() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( true == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt != neutron.distributionData() );
    CHECK( true == std::holds_alternative< TwoBodyDistributionData >( neutron.distributionData().value() ) );
    auto data = std::get< TwoBodyDistributionData >( neutron.distributionData().value() );
    CHECK( DistributionDataType::TwoBody == data.type() );
    CHECK( true == std::holds_alternative< LegendreAngularDistributions >( data.angle() ) );
    auto angle = std::get< LegendreAngularDistributions >( data.angle() );
    CHECK( 75 == angle.numberPoints() );
    CHECK( 1 == angle.numberRegions() );
    CHECK( 75 == angle.grid().size() );
    CHECK( 75 == angle.distributions().size() );
    CHECK( 1 == angle.boundaries().size() );
    CHECK( 1 == angle.interpolants().size() );
    CHECK_THAT( 1e-5   , WithinRel( angle.grid()[0] ) );
    CHECK_THAT( 1e+4   , WithinRel( angle.grid()[1] ) );
    CHECK_THAT( 19e+6, WithinRel( angle.grid()[73] ) );
    CHECK_THAT( 20e+6, WithinRel( angle.grid()[74] ) );
    CHECK(  1 == angle.distributions()[0].pdf().coefficients().size() );
    CHECK(  1 == angle.distributions()[1].pdf().coefficients().size() );
    CHECK( 19 == angle.distributions()[73].pdf().coefficients().size() );
    CHECK( 19 == angle.distributions()[74].pdf().coefficients().size() );
    CHECK_THAT( 0.5         , WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
    CHECK_THAT( 0.5         , WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
    CHECK_THAT( 0.5         , WithinRel( angle.distributions()[73].pdf().coefficients()[0] ) );
    CHECK_THAT( 1.188585    , WithinRel( angle.distributions()[73].pdf().coefficients()[1] ) );
    CHECK_THAT( 1.829625e-07, WithinRel( angle.distributions()[73].pdf().coefficients()[17] ) );
    CHECK_THAT( 3.59381e-08 , WithinRel( angle.distributions()[73].pdf().coefficients()[18] ) );
    CHECK_THAT( 0.5         , WithinRel( angle.distributions()[74].pdf().coefficients()[0] ) );
    CHECK_THAT( 1.202805    , WithinRel( angle.distributions()[74].pdf().coefficients()[1] ) );
    CHECK_THAT( 3.224725e-07, WithinRel( angle.distributions()[74].pdf().coefficients()[17] ) );
    CHECK_THAT( 6.63336e-08 , WithinRel( angle.distributions()[74].pdf().coefficients()[18] ) );
    CHECK( true == angle.distributions()[0].hasCdf() );
    CHECK( true == angle.distributions()[1].hasCdf() );
    CHECK( true == angle.distributions()[73].hasCdf() );
    CHECK( true == angle.distributions()[74].hasCdf() );
    CHECK( 2 == angle.distributions()[0].cdf().coefficients().size() );
    CHECK( 2 == angle.distributions()[1].cdf().coefficients().size() );
    CHECK( 20 == angle.distributions()[73].cdf().coefficients().size() );
    CHECK( 20 == angle.distributions()[74].cdf().coefficients().size() );
    CHECK_THAT( 0.5       , WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5       , WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.103805  , WithinRel( angle.distributions()[73].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.22273   , WithinRel( angle.distributions()[73].cdf().coefficients()[1] ) );
    CHECK_THAT( 5.2275e-09, WithinRel( angle.distributions()[73].cdf().coefficients()[18] ) );
    CHECK_THAT( 9.713e-10 , WithinRel( angle.distributions()[73].cdf().coefficients()[19] ) );
    CHECK_THAT( 0.099065  , WithinRel( angle.distributions()[74].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.21624   , WithinRel( angle.distributions()[74].cdf().coefficients()[1] ) );
    CHECK_THAT( 9.2135e-09, WithinRel( angle.distributions()[74].cdf().coefficients()[18] ) );
    CHECK_THAT( 1.7928e-09, WithinRel( angle.distributions()[74].cdf().coefficients()[19] ) );
    CHECK( 74 == angle.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );

    auto li7 = elastic.products()[1];
    CHECK( id::ParticleID( "Li7" ) == li7.identifier() );
  }

  void verifyCaptureReaction( const Reaction& capture ) {

    CHECK( id::ReactionID( "102" ) == capture.identifier() );
    CHECK( ReactionType::Primary == capture.type() );
    CHECK( true == capture.hasProducts() );
    CHECK( true == capture.isLinearised() );

    CHECK( std::nullopt == capture.massDifferenceQValue() );
    CHECK( std::nullopt != capture.reactionQValue() );
    CHECK_THAT( 2032800, WithinRel( capture.reactionQValue().value() ) );

    CHECK( true == capture.crossSection().isLinearised() );
    CHECK( 362 == capture.crossSection().numberPoints() );
    CHECK( 1 == capture.crossSection().numberRegions() );
    CHECK( 362 == capture.crossSection().energies().size() );
    CHECK( 362 == capture.crossSection().values().size() );
    CHECK( 1 == capture.crossSection().boundaries().size() );
    CHECK( 1 == capture.crossSection().interpolants().size() );
    CHECK( 361 == capture.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == capture.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5       , WithinRel( capture.crossSection().energies()[0] ) );
    CHECK_THAT( 1.090516E-5, WithinRel( capture.crossSection().energies()[1] ) );
    CHECK_THAT( 16e+6      , WithinRel( capture.crossSection().energies()[360] ) );
    CHECK_THAT( 20e+6      , WithinRel( capture.crossSection().energies()[361] ) );
    CHECK_THAT( 2.284      , WithinRel( capture.crossSection().values()[0] ) );
    CHECK_THAT( 2.18715316 , WithinRel( capture.crossSection().values()[1] ) );
    CHECK_THAT( 4.067041E-6, WithinRel( capture.crossSection().values()[360] ) );
    CHECK_THAT( 4.E-6      , WithinRel( capture.crossSection().values()[361] ) );

    CHECK( 4 == capture.products().size() );

    auto li8 = capture.products()[0];
    CHECK( id::ParticleID( "Li8" ) == li8.identifier() );

    auto gamma1 = capture.products()[1];
    CHECK( id::ParticleID( "g" ) == gamma1.identifier() );

    auto gamma2 = capture.products()[1];
    CHECK( id::ParticleID( "g" ) == gamma2.identifier() );

    auto gamma3 = capture.products()[1];
    CHECK( id::ParticleID( "g" ) == gamma3.identifier() );
  }

  void verifyLumpedReaction851( const Reaction& lumped ) {

    CHECK( id::ReactionID( "851" ) == lumped.identifier() );
    CHECK( ReactionType::Summation == lumped.type() );
    CHECK( false == lumped.hasProducts() );
    CHECK( true == lumped.isLinearised() );

    CHECK( std::nullopt != lumped.partialReactionIdentifiers() );
    auto partials = lumped.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "16" ) == partials[0] );
    CHECK( id::ReactionID( "24" ) == partials[1] );

    CHECK( std::nullopt == lumped.massDifferenceQValue() );
    CHECK( std::nullopt == lumped.reactionQValue() );

    CHECK( true == lumped.crossSection().isLinearised() );
    CHECK( 29 == lumped.crossSection().numberPoints() );
    CHECK( 1 == lumped.crossSection().numberRegions() );
    CHECK( 29 == lumped.crossSection().energies().size() );
    CHECK( 29 == lumped.crossSection().values().size() );
    CHECK( 1 == lumped.crossSection().boundaries().size() );
    CHECK( 1 == lumped.crossSection().interpolants().size() );
    CHECK( 28 == lumped.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == lumped.crossSection().interpolants()[0] );
    CHECK_THAT( 8.29288000e+06, WithinRel( lumped.crossSection().energies()[0] ) );
    CHECK_THAT( 8.5e+06       , WithinRel( lumped.crossSection().energies()[1] ) );
    CHECK_THAT( 1.95e+7       , WithinRel( lumped.crossSection().energies()[27] ) );
    CHECK_THAT( 2e+7          , WithinRel( lumped.crossSection().energies()[28] ) );
    CHECK_THAT( 0.            , WithinRel( lumped.crossSection().values()[0] ) );
    CHECK_THAT( 3.44833400e-04, WithinRel( lumped.crossSection().values()[1] ) );
    CHECK_THAT( 7.20042300e-02, WithinRel( lumped.crossSection().values()[27] ) );
    CHECK_THAT( 7.52300000e-02, WithinRel( lumped.crossSection().values()[28] ) );

    CHECK( 0 == lumped.products().size() );
  }

  void verifyLumpedReaction852( const Reaction& lumped ) {

    CHECK( id::ReactionID( "852" ) == lumped.identifier() );
    CHECK( ReactionType::Summation == lumped.type() );
    CHECK( false == lumped.hasProducts() );
    CHECK( true == lumped.isLinearised() );

    CHECK( std::nullopt != lumped.partialReactionIdentifiers() );
    auto partials = lumped.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "51" ) == partials[0] );

    CHECK( std::nullopt == lumped.massDifferenceQValue() );
    CHECK( std::nullopt == lumped.reactionQValue() );

    CHECK( true == lumped.crossSection().isLinearised() );
    CHECK( 134 == lumped.crossSection().numberPoints() );
    CHECK( 1 == lumped.crossSection().numberRegions() );
    CHECK( 134 == lumped.crossSection().energies().size() );
    CHECK( 134 == lumped.crossSection().values().size() );
    CHECK( 1 == lumped.crossSection().boundaries().size() );
    CHECK( 1 == lumped.crossSection().interpolants().size() );
    CHECK( 133 == lumped.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == lumped.crossSection().interpolants()[0] );
    CHECK_THAT( 5.46277000e+05, WithinRel( lumped.crossSection().energies()[0] ) );
    CHECK_THAT( 5.50000000e+05, WithinRel( lumped.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( lumped.crossSection().energies()[132] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( lumped.crossSection().energies()[133] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( lumped.crossSection().values()[0] ) );
    CHECK_THAT( 5.90690000e-03, WithinRel( lumped.crossSection().values()[1] ) );
    CHECK_THAT( 3.97335000e-02, WithinRel( lumped.crossSection().values()[132] ) );
    CHECK_THAT( 3.93590000e-02, WithinRel( lumped.crossSection().values()[133] ) );

    CHECK( 0 == lumped.products().size() );
  }

  void verifyLumpedReaction853( const Reaction& lumped ) {

    CHECK( id::ReactionID( "853" ) == lumped.identifier() );
    CHECK( ReactionType::Summation == lumped.type() );
    CHECK( false == lumped.hasProducts() );
    CHECK( true == lumped.isLinearised() );

    CHECK( std::nullopt != lumped.partialReactionIdentifiers() );
    auto partials = lumped.partialReactionIdentifiers().value();
    CHECK( 4 == partials.size() );
    CHECK( id::ReactionID( "52" ) == partials[0] );
    CHECK( id::ReactionID( "53" ) == partials[1] );
    CHECK( id::ReactionID( "54" ) == partials[2] );
    CHECK( id::ReactionID( "55" ) == partials[3] );

    CHECK( std::nullopt == lumped.massDifferenceQValue() );
    CHECK( std::nullopt == lumped.reactionQValue() );

    CHECK( true == lumped.crossSection().isLinearised() );
    CHECK( 95 == lumped.crossSection().numberPoints() );
    CHECK( 1 == lumped.crossSection().numberRegions() );
    CHECK( 95 == lumped.crossSection().energies().size() );
    CHECK( 95 == lumped.crossSection().values().size() );
    CHECK( 1 == lumped.crossSection().boundaries().size() );
    CHECK( 1 == lumped.crossSection().interpolants().size() );
    CHECK( 94 == lumped.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == lumped.crossSection().interpolants()[0] );
    CHECK_THAT( 3.14540000e+06, WithinRel( lumped.crossSection().energies()[0] ) );
    CHECK_THAT( 3.20000000e+06, WithinRel( lumped.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( lumped.crossSection().energies()[93] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( lumped.crossSection().energies()[94] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( lumped.crossSection().values()[0] ) );
    CHECK_THAT( 9.67624500e-04, WithinRel( lumped.crossSection().values()[1] ) );
    CHECK_THAT( 1.89748930e-03, WithinRel( lumped.crossSection().values()[93] ) );
    CHECK_THAT( 1.77996460e-03, WithinRel( lumped.crossSection().values()[94] ) );

    CHECK( 0 == lumped.products().size() );
  }

} // namespace h1
} // namespace neutron
