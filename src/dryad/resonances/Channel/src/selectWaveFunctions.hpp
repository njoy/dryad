static Penetrability
selectPenetrabilityFunction( unsigned int l,
                             const std::optional< ParticlePair >& outgoing ) {

  if ( outgoing.has_value() ) {

    if ( outgoing->particle().identifier() == id::ParticleID::neutron() ) {

      return HardSpherePenetrability( l );
    }
    //! @todo add charged particle channels
  }
  return 1;
}

static ShiftFactor
selectShiftFactorFunction( unsigned int l,
                           const std::optional< ParticlePair >& outgoing ) {

  if ( outgoing.has_value() ) {

    if ( outgoing->particle().identifier() == id::ParticleID::neutron() ) {

      return HardSphereShiftFactor( l );
    }
    //! @todo add charged particle channels
  }
  return 1;
}

static PhaseShift
selectPhaseShiftFunction( unsigned int l,
                          const std::optional< ParticlePair >& outgoing ) {

  if ( outgoing.has_value() ) {

    if ( outgoing->particle().identifier() == id::ParticleID::neutron() ) {

      return HardSpherePhaseShift( l );
    }
    //! @todo add charged particle channels
  }
  return 1;
}
