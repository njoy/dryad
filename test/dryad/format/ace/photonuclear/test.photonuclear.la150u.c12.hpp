namespace photonuclear {

// test functions based on 6012.24cc
namespace la150u {
namespace c12 {

  void verifyParticleDatabase( const ParticleDatabase& particles ) {

    using namespace njoy::constants;

    CHECK( 6 == particles.numberParticles() );

    CHECK( true == particles.hasParticle( id::ParticleID( "g" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "n" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "p" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "B11" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "C11" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "C12" ) ) );

    auto particle = particles.particle( id::ParticleID( "g" ) );
    CHECK( id::ParticleID::photon() == particle.identifier() );
    CHECK_THAT( 0., WithinRel( particle.mass().value() ) );
    CHECK_THAT( 1.0, WithinRel( particle.spin().value() ) );
    CHECK( -1 == particle.parity().value() );
    CHECK( std::nullopt == particle.energy() );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK_THAT( 0., WithinRel( particle.massUncertainty().value() ) );
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

    particle = particles.particle( id::ParticleID( "p" ) );
    CHECK( id::ParticleID::proton() == particle.identifier() );
    CHECK_THAT( proton_mass, WithinRel( particle.mass().value() ) );
    CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
    CHECK( +1 == particle.parity().value() );
    CHECK( std::nullopt == particle.energy() );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK_THAT( proton_mass_uncertainty, WithinRel( particle.massUncertainty().value() ) );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );

    particle = particles.particle( id::ParticleID( "B11" ) );
    CHECK( id::ParticleID( "B11" ) == particle.identifier() );
    CHECK_THAT( 11.009305166, WithinRel( particle.mass().value() ) );
    CHECK_THAT( 1.5, WithinRel( particle.spin().value() ) );
    CHECK( -1 == particle.parity().value() );
    CHECK_THAT( 0., WithinRel( particle.energy().value() ) );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK_THAT( 0.000000013, WithinRel( particle.massUncertainty().value() ) );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );

    particle = particles.particle( id::ParticleID( "C11" ) );
    CHECK( id::ParticleID( "C11" ) == particle.identifier() );
    CHECK_THAT( 11.011432597, WithinRel( particle.mass().value() ) );
    CHECK_THAT( 1.5, WithinRel( particle.spin().value() ) );
    CHECK( -1 == particle.parity().value() );
    CHECK_THAT( 0., WithinRel( particle.energy().value() ) );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK_THAT( 0.000000064, WithinRel( particle.massUncertainty().value() ) );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );

    particle = particles.particle( id::ParticleID( "C12" ) );
    CHECK( id::ParticleID( "C12" ) == particle.identifier() );
    CHECK_THAT( 11.89691 * neutron_mass, WithinRel( particle.mass().value() ) );
    CHECK_THAT( 0.0, WithinRel( particle.spin().value() ) );
    CHECK( +1 == particle.parity().value() );
    CHECK_THAT( 0., WithinRel( particle.energy().value() ) );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK( std::nullopt == particle.massUncertainty() );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );
  }

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,C12->total" ) == reaction.identifier() );
    CHECK( 1 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 3 == partials.size() );
    CHECK( id::ReactionID( "g,C12->anything" ) == partials[0] );
    CHECK( id::ReactionID( "g,C12->n,C11" ) == partials[1] );
    CHECK( id::ReactionID( "g,C12->p,B11" ) == partials[2] );
    CHECK( 5 == partials[0].reactionType().mt() );
    CHECK( 50 == partials[1].reactionType().mt() );
    CHECK( 600 == partials[2].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK_THAT( 7.366593e+6, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1.5e+8, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 98 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 98 == reaction.crossSection().energies().size() );
    CHECK( 98 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 7.366593e+6, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 1.5e+8, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( 1.0447981e-3, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 97 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

  void verifyAnythingReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,C12->anything" ) == reaction.identifier() );
    CHECK( 5 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( -7.3666e+6 == reaction.reactionQValue() );

    CHECK_THAT( 7.3666e+6, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1.5e+8, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 97 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 97 == reaction.crossSection().energies().size() );
    CHECK( 97 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 7.3666e+6, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 1.5e+8, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( 1.03876e-3, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 96 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

  void verifyNeutronReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,C12->n,C11" ) == reaction.identifier() );
    CHECK( 50 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( -1.872201e+7 == reaction.reactionQValue() );

    CHECK_THAT( 1.872201e+7, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1.5e+8, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 72 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 72 == reaction.crossSection().energies().size() );
    CHECK( 72 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 1.872201e+7, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 1.5e+8, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( 3.01905e-6, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 71 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

  void verifyProtonReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,C12->p,B11" ) == reaction.identifier() );
    CHECK( 600 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( -1.595708e+7 == reaction.reactionQValue() );

    CHECK_THAT( 1.595708e+7, WithinRel( reaction.crossSection().lowerEnergyLimit() ) );
    CHECK_THAT( 1.5e+8, WithinRel( reaction.crossSection().upperEnergyLimit() ) );
    CHECK( 79 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 79 == reaction.crossSection().energies().size() );
    CHECK( 79 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK_THAT( 1.595708e+7, WithinRel( reaction.crossSection().energies().front() ) );
    CHECK_THAT( 1.5e+8, WithinRel( reaction.crossSection().energies().back() ) );
    CHECK_THAT( 0., WithinRel( reaction.crossSection().values().front() ) );
    CHECK_THAT( 3.01905e-6, WithinRel( reaction.crossSection().values().back() ) );
    CHECK( 78 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( true == reaction.crossSection().isLinearised() );

    CHECK( 0 == reaction.products().size() );
  }

} //namespace c12
} // namespace la150u
} // namespace photonuclear
