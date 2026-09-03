namespace continuous {

// test functions based on 1001.10c
namespace lib81 {
namespace h1 {

  void verifyParticleDatabase( const ParticleDatabase& particles ) {

    using namespace njoy::constants;

    CHECK( 4 == particles.numberParticles() );

    CHECK( true == particles.hasParticle( id::ParticleID( "g" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "n" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "H1" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "H2[all]" ) ) );

    auto particle = particles.particle( id::ParticleID( "g" ) );
    CHECK( id::ParticleID::photon() == particle.identifier() );
    CHECK_THAT( 0., WithinRel( particle.mass().value() ) );
    CHECK_THAT( 1.0, WithinRel( particle.spin().value() ) );
    CHECK( +1 == particle.parity().value() );
    CHECK( std::nullopt == particle.energy() );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK( std::nullopt == particle.massUncertainty() );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );

    particle = particles.particle( id::ParticleID( "n" ) );
    CHECK( id::ParticleID::neutron() == particle.identifier() );
    CHECK_THAT( neutron_mass, WithinRel( particle.mass().value() ) );
    CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
    CHECK( +1 == particle.parity().value() );
    CHECK( std::nullopt == particle.energy() );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK_THAT( neutron_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );

    particle = particles.particle( id::ParticleID( "H1" ) );
    CHECK( id::ParticleID( "H1" ) == particle.identifier() );
    CHECK_THAT( 0.999167 * neutron_mass, WithinRel( particle.mass().value() ) );
    CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
    CHECK( +1 == particle.parity().value() );
    CHECK_THAT( 0., WithinRel( particle.energy().value() ) );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK( std::nullopt == particle.massUncertainty() );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );

    particle = particles.particle( id::ParticleID( "H2[all]" ) );
    CHECK( id::ParticleID( "H2[all]" ) == particle.identifier() );
    CHECK_THAT( 2.014101777844, WithinRel( particle.mass().value() ) );
    CHECK( std::nullopt == particle.spin() );
    CHECK( std::nullopt == particle.parity() );
    CHECK( std::nullopt == particle.energy() );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK_THAT( 0.000000000015, WithinRel( particle.massUncertainty().value() ) );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );
  }

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,H1->total" ) == reaction.identifier() );
    CHECK( 1 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "n,H1->n,H1" ) == partials[0] );
    CHECK( id::ReactionID( "n,H1->g,H2[all]" ) == partials[1] );
    CHECK( 50 == partials[0].reactionType().mt() );
    CHECK( 102 == partials[1].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 631 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 631 == reaction.crossSection().energies().size() );
    CHECK( 631 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 1177.25787, WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( 4.81867908e-1, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 630 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

  void verifyElasticReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,H1->n,H1" ) == reaction.identifier() );
    CHECK( 50 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( 0. == reaction.reactionQValue() );

    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 631 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 631 == reaction.crossSection().energies().size() );
    CHECK( 631 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 1160.528, WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( .4818408, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 630 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

  void verifyCaptureReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,H1->g,H2[all]" ) == reaction.identifier() );
    CHECK( 102 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( 2.224648e+6 == reaction.reactionQValue() );

    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 631 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 631 == reaction.crossSection().energies().size() );
    CHECK( 631 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 16.72987, WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( 2.710792e-5, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 630 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

} //namespace h1
} // namespace lib81
} // namespace continuous
