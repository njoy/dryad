namespace neutron {

// test functions based on n-001_H_001.endf
namespace h1 {

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "1" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( false == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "2" ) == partials[0] );
    CHECK( id::ReactionID( "102" ) == partials[1] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( false == reaction.crossSection().isLinearised() );
    CHECK( 153 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 153 == reaction.crossSection().energies().size() );
    CHECK( 153 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK( 8 == reaction.crossSection().boundaries()[0] );
    CHECK( 152 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LogLog == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 5e-3, WithinRel( reaction.crossSection().energies()[8] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[152] ) );
    CHECK_THAT( 3.716477e+1, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 2.118421e+1, WithinRel( reaction.crossSection().values()[8] ) );
    CHECK_THAT( 4.818679e-1, WithinRel( reaction.crossSection().values()[152] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyElasticReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "2" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 153 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 153 == reaction.crossSection().energies().size() );
    CHECK( 153 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 152 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[152] ) );
    CHECK_THAT( 2.043608e+1, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 4.818408e-1, WithinRel( reaction.crossSection().values()[152] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H1" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
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
    CHECK( 153 == angle.numberPoints() );
    CHECK( 1 == angle.numberRegions() );
    CHECK( 153 == angle.grid().size() );
    CHECK( 153 == angle.distributions().size() );
    CHECK( 1 == angle.boundaries().size() );
    CHECK( 1 == angle.interpolants().size() );
    CHECK_THAT( 1e-5   , WithinRel( angle.grid()[0] ) );
    CHECK_THAT( 2e-5   , WithinRel( angle.grid()[1] ) );
    CHECK_THAT( 1.95e+7, WithinRel( angle.grid()[151] ) );
    CHECK_THAT( 2e+7   , WithinRel( angle.grid()[152] ) );
    CHECK( 7 == angle.distributions()[0].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[1].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[151].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[152].pdf().coefficients().size() );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
    CHECK_THAT( -1.7511000E-14  , WithinRel( angle.distributions()[0].pdf().coefficients()[1] ) );
    CHECK_THAT( -2.5280750E-16  , WithinRel( angle.distributions()[0].pdf().coefficients()[2] ) );
    CHECK_THAT( -6.4002050E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.3653765E-16  , WithinRel( angle.distributions()[0].pdf().coefficients()[4] ) );
    CHECK_THAT( -1.7067215E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[5] ) );
    CHECK_THAT(  2.5600835E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
    CHECK_THAT( -3.4846950E-14  , WithinRel( angle.distributions()[1].pdf().coefficients()[1] ) );
    CHECK_THAT( -1.7387225E-16  , WithinRel( angle.distributions()[1].pdf().coefficients()[2] ) );
    CHECK_THAT( -9.1736400E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[3] ) );
    CHECK_THAT( -2.9867625E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[4] ) );
    CHECK_THAT( -3.4134430E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[5] ) );
    CHECK_THAT(  1.8773950E-16  , WithinRel( angle.distributions()[1].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[151].pdf().coefficients()[0] ) );
    CHECK_THAT( -2.4240045E-02  , WithinRel( angle.distributions()[151].pdf().coefficients()[1] ) );
    CHECK_THAT(  1.7942750E-02  , WithinRel( angle.distributions()[151].pdf().coefficients()[2] ) );
    CHECK_THAT( -2.54685165E-03 , WithinRel( angle.distributions()[151].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.54781595E-03 , WithinRel( angle.distributions()[151].pdf().coefficients()[4] ) );
    CHECK_THAT(  4.91773975E-05 , WithinRel( angle.distributions()[151].pdf().coefficients()[5] ) );
    CHECK_THAT(  3.82748535E-05 , WithinRel( angle.distributions()[151].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[152].pdf().coefficients()[0] ) );
    CHECK_THAT( -2.41945200E-02 , WithinRel( angle.distributions()[152].pdf().coefficients()[1] ) );
    CHECK_THAT(  1.95173075E-02 , WithinRel( angle.distributions()[152].pdf().coefficients()[2] ) );
    CHECK_THAT( -2.71943700E-03 , WithinRel( angle.distributions()[152].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.69449750E-03 , WithinRel( angle.distributions()[152].pdf().coefficients()[4] ) );
    CHECK_THAT(  5.25219970E-05 , WithinRel( angle.distributions()[152].pdf().coefficients()[5] ) );
    CHECK_THAT(  4.48370065E-05 , WithinRel( angle.distributions()[152].pdf().coefficients()[6] ) );
    CHECK( true == angle.distributions()[0].hasCdf() );
    CHECK( true == angle.distributions()[1].hasCdf() );
    CHECK( true == angle.distributions()[151].hasCdf() );
    CHECK( true == angle.distributions()[152].hasCdf() );
    CHECK( 8 == angle.distributions()[0].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[1].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[151].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[152].cdf().coefficients().size() );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].cdf().coefficients()[1] ) );
    CHECK_THAT( -5.82785685e-15 , WithinRel( angle.distributions()[0].cdf().coefficients()[2] ) );
    CHECK_THAT( -6.57323500e-17 , WithinRel( angle.distributions()[0].cdf().coefficients()[3] ) );
    CHECK_THAT( -7.59158500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.32015550e-17 , WithinRel( angle.distributions()[0].cdf().coefficients()[5] ) );
    CHECK_THAT( -1.55156500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[6] ) );
    CHECK_THAT(  1.96929500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[7] ) );
    CHECK_THAT( 0.50000000000001, WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].cdf().coefficients()[1] ) );
    CHECK_THAT( -1.16025448e-14 , WithinRel( angle.distributions()[1].cdf().coefficients()[2] ) );
    CHECK_THAT( -3.14558250e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[3] ) );
    CHECK_THAT( -1.00020700e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[4] ) );
    CHECK_THAT( -1.77601250e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[5] ) );
    CHECK_THAT( -3.10313000e-18 , WithinRel( angle.distributions()[1].cdf().coefficients()[6] ) );
    CHECK_THAT(  1.44415000e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[7] ) );
    CHECK_THAT(  5.08080015e-01 , WithinRel( angle.distributions()[151].cdf().coefficients()[0] ) );
    CHECK_THAT(  4.96411450e-01 , WithinRel( angle.distributions()[151].cdf().coefficients()[1] ) );
    CHECK_THAT( -7.71617905e-03 , WithinRel( angle.distributions()[151].cdf().coefficients()[2] ) );
    CHECK_THAT(  3.41657045e-03 , WithinRel( angle.distributions()[151].cdf().coefficients()[3] ) );
    CHECK_THAT( -3.683066225e-04, WithinRel( angle.distributions()[151].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.690353305e-04, WithinRel( angle.distributions()[151].cdf().coefficients()[5] ) );
    CHECK_THAT(  4.47067250e-06 , WithinRel( angle.distributions()[151].cdf().coefficients()[6] ) );
    CHECK_THAT(  2.94421950e-06 , WithinRel( angle.distributions()[151].cdf().coefficients()[7] ) );
    CHECK_THAT(  5.08064840e-01 , WithinRel( angle.distributions()[152].cdf().coefficients()[0] ) );
    CHECK_THAT(  4.960965385e-01, WithinRel( angle.distributions()[152].cdf().coefficients()[1] ) );
    CHECK_THAT( -7.67634900e-03 , WithinRel( angle.distributions()[152].cdf().coefficients()[2] ) );
    CHECK_THAT(  3.71518400e-03 , WithinRel( angle.distributions()[152].cdf().coefficients()[3] ) );
    CHECK_THAT( -3.93265727e-04 , WithinRel( angle.distributions()[152].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.848284995e-04, WithinRel( angle.distributions()[152].cdf().coefficients()[5] ) );
    CHECK_THAT(  4.77472700e-06 , WithinRel( angle.distributions()[152].cdf().coefficients()[6] ) );
    CHECK_THAT(  3.44900050e-06 , WithinRel( angle.distributions()[152].cdf().coefficients()[7] ) );
    CHECK( 152 == angle.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );

    auto h1 = reaction.product( id::ParticleID( "H1" ) );
    CHECK( id::ParticleID( "H1" ) == h1.identifier() );
  }

  void verifyCaptureReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "102" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );
    CHECK( false == reaction.isLinearised() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 2.224648e+6, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( false == reaction.crossSection().isLinearised() );
    CHECK( 153 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 153 == reaction.crossSection().energies().size() );
    CHECK( 153 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK( 32 == reaction.crossSection().boundaries()[0] );
    CHECK( 152 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LogLog == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+4, WithinRel( reaction.crossSection().energies()[32] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[152] ) );
    CHECK_THAT( 1.672869e+1, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 4.950573e-4, WithinRel( reaction.crossSection().values()[32] ) );
    CHECK_THAT( 2.710792e-5, WithinRel( reaction.crossSection().values()[152] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H2" ) ) );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );

    auto deuterium = reaction.product( id::ParticleID( "H2" ) );
    CHECK( id::ParticleID( "H2" ) == deuterium.identifier() );
  }

} // namespace h1
} // namespace neutron
