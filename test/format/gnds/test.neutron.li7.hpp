namespace neutron {

// test functions based on n-003_Li_007.endf
namespace li7 {

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "1" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
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

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 537 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 537 == reaction.crossSection().energies().size() );
    CHECK( 537 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 536 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[536] ) );
    CHECK_THAT( 3.254     , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.19328997, WithinRel( reaction.crossSection().values()[536] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyElasticReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "2" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 179 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 179 == reaction.crossSection().energies().size() );
    CHECK( 179 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 178 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[178] ) );
    CHECK_THAT( .97     , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .8637753, WithinRel( reaction.crossSection().values()[178] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "Li7" ) ) );

    auto neutron = reaction.products()[0];
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
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

    auto li7 = reaction.products()[1];
    CHECK( id::ParticleID( "Li7" ) == li7.identifier() );
  }

  void verifyCaptureReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "102" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 2032800, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 362 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 362 == reaction.crossSection().energies().size() );
    CHECK( 362 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 361 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5       , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1.090516E-5, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 16e+6      , WithinRel( reaction.crossSection().energies()[360] ) );
    CHECK_THAT( 20e+6      , WithinRel( reaction.crossSection().energies()[361] ) );
    CHECK_THAT( 2.284      , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 2.18715316 , WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 4.067041E-6, WithinRel( reaction.crossSection().values()[360] ) );
    CHECK_THAT( 4.E-6      , WithinRel( reaction.crossSection().values()[361] ) );

    CHECK( 4 == reaction.numberProducts() );
    CHECK( 3 == reaction.numberProducts( id::ParticleID( "g" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "Li8" ) ) );

    auto li8 = reaction.product( id::ParticleID( "Li8" ) );
    CHECK( id::ParticleID( "Li8" ) == li8.identifier() );

    auto gamma1 = reaction.product( id::ParticleID( "g" ), 0 );
    CHECK( id::ParticleID( "g" ) == gamma1.identifier() );

    auto gamma2 = reaction.product( id::ParticleID( "g" ), 1 );
    CHECK( id::ParticleID( "g" ) == gamma2.identifier() );

    auto gamma3 = reaction.product( id::ParticleID( "g" ), 2 );
    CHECK( id::ParticleID( "g" ) == gamma3.identifier() );
  }

  void verifyLumpedReaction851( const Reaction& reaction ) {

    CHECK( id::ReactionID( "851" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "16" ) == partials[0] );
    CHECK( id::ReactionID( "24" ) == partials[1] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 29 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 29 == reaction.crossSection().energies().size() );
    CHECK( 29 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 28 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 8.29288000e+06, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 8.5e+06       , WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.95e+7       , WithinRel( reaction.crossSection().energies()[27] ) );
    CHECK_THAT( 2e+7          , WithinRel( reaction.crossSection().energies()[28] ) );
    CHECK_THAT( 0.            , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 3.44833400e-04, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 7.20042300e-02, WithinRel( reaction.crossSection().values()[27] ) );
    CHECK_THAT( 7.52300000e-02, WithinRel( reaction.crossSection().values()[28] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction852( const Reaction& reaction ) {

    CHECK( id::ReactionID( "852" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "51" ) == partials[0] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 134 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 134 == reaction.crossSection().energies().size() );
    CHECK( 134 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 133 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 5.46277000e+05, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 5.50000000e+05, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[132] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[133] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 5.90690000e-03, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 3.97335000e-02, WithinRel( reaction.crossSection().values()[132] ) );
    CHECK_THAT( 3.93590000e-02, WithinRel( reaction.crossSection().values()[133] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction853( const Reaction& reaction ) {

    CHECK( id::ReactionID( "853" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 4 == partials.size() );
    CHECK( id::ReactionID( "52" ) == partials[0] );
    CHECK( id::ReactionID( "53" ) == partials[1] );
    CHECK( id::ReactionID( "54" ) == partials[2] );
    CHECK( id::ReactionID( "55" ) == partials[3] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 95 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 95 == reaction.crossSection().energies().size() );
    CHECK( 95 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 94 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 3.14540000e+06, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 3.20000000e+06, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[93] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[94] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 9.67624500e-04, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 1.89748930e-03, WithinRel( reaction.crossSection().values()[93] ) );
    CHECK_THAT( 1.77996460e-03, WithinRel( reaction.crossSection().values()[94] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction854( const Reaction& reaction ) {

    CHECK( id::ReactionID( "854" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "56" ) == partials[0] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 73 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 73 == reaction.crossSection().energies().size() );
    CHECK( 73 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 72 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 5295640.00, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 5300000.00, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 19730000.0, WithinRel( reaction.crossSection().energies()[71] ) );
    CHECK_THAT( 20000000.0, WithinRel( reaction.crossSection().energies()[72] ) );
    CHECK_THAT( 0.0       , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .003490122, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( .078823130, WithinRel( reaction.crossSection().values()[71] ) );
    CHECK_THAT( .078000000, WithinRel( reaction.crossSection().values()[72] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction855( const Reaction& reaction ) {

    CHECK( id::ReactionID( "855" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "57" ) == partials[0] );
    CHECK( id::ReactionID( "58" ) == partials[1] );
    CHECK( id::ReactionID( "59" ) == partials[2] );
    CHECK( id::ReactionID( "60" ) == partials[3] );
    CHECK( id::ReactionID( "61" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 68 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 68 == reaction.crossSection().energies().size() );
    CHECK( 68 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 67 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 5.43290000e+06, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 5.50000000e+06, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[66] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[67] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 7.59054300e-03, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 9.16765500e-03, WithinRel( reaction.crossSection().values()[66] ) );
    CHECK_THAT( 8.56193900e-03, WithinRel( reaction.crossSection().values()[67] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction856( const Reaction& reaction ) {

    CHECK( id::ReactionID( "856" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "62" ) == partials[0] );
    CHECK( id::ReactionID( "63" ) == partials[1] );
    CHECK( id::ReactionID( "64" ) == partials[2] );
    CHECK( id::ReactionID( "65" ) == partials[3] );
    CHECK( id::ReactionID( "66" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 48 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 48 == reaction.crossSection().energies().size() );
    CHECK( 48 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 47 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 8.29230000e+06, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 8.50000000e+06, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[46] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[47] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 8.22307000e-03, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 1.91613490e-02, WithinRel( reaction.crossSection().values()[46] ) );
    CHECK_THAT( 1.79659390e-02, WithinRel( reaction.crossSection().values()[47] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction857( const Reaction& reaction ) {

    CHECK( id::ReactionID( "857" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "67" ) == partials[0] );
    CHECK( id::ReactionID( "68" ) == partials[1] );
    CHECK( id::ReactionID( "69" ) == partials[2] );
    CHECK( id::ReactionID( "70" ) == partials[3] );
    CHECK( id::ReactionID( "71" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 34 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 34 == reaction.crossSection().energies().size() );
    CHECK( 34 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 33 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.11520000e+07, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1.15000000e+07, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[32] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[33] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.02849900e-02, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 2.38844240e-02, WithinRel( reaction.crossSection().values()[32] ) );
    CHECK_THAT( 2.27516480e-02, WithinRel( reaction.crossSection().values()[33] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction858( const Reaction& reaction ) {

    CHECK( id::ReactionID( "858" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "72" ) == partials[0] );
    CHECK( id::ReactionID( "73" ) == partials[1] );
    CHECK( id::ReactionID( "74" ) == partials[2] );
    CHECK( id::ReactionID( "75" ) == partials[3] );
    CHECK( id::ReactionID( "76" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 23 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 23 == reaction.crossSection().energies().size() );
    CHECK( 23 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 22 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.40110000e+07, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1.45000000e+07, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[21] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[22] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.20486300e-02, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 3.05346270e-02, WithinRel( reaction.crossSection().values()[21] ) );
    CHECK_THAT( 2.84387580e-02, WithinRel( reaction.crossSection().values()[22] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction859( const Reaction& reaction ) {

    CHECK( id::ReactionID( "859" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 6 == partials.size() );
    CHECK( id::ReactionID( "77" ) == partials[0] );
    CHECK( id::ReactionID( "78" ) == partials[1] );
    CHECK( id::ReactionID( "79" ) == partials[2] );
    CHECK( id::ReactionID( "80" ) == partials[3] );
    CHECK( id::ReactionID( "81" ) == partials[4] );
    CHECK( id::ReactionID( "82" ) == partials[5] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 13 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 13 == reaction.crossSection().energies().size() );
    CHECK( 13 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 12 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.68710000e+07, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1.70000000e+07, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[11] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[12] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.78534600e-03, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 3.55291340e-02, WithinRel( reaction.crossSection().values()[11] ) );
    CHECK_THAT( 3.76534200e-02, WithinRel( reaction.crossSection().values()[12] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

} // namespace h1
} // namespace neutron
