static Penetrability
selectPenetrabilityFunction( unsigned int l,
                             const std::optional< ParticlePair >& outgoing ) {

  if ( outgoing.has_value() ) {

    if ( outgoing->particle().identifier() == id::ParticleID::neutron() ) {

      return HardSpherePenetrability( l );
    }
    else if ( outgoing->particle().charge() > 0 ) {

      return CoulombPenetrability( l );
    }
  }
  return 1.;
}

static ShiftFactor
selectShiftFactorFunction( unsigned int l,
                           const std::optional< ParticlePair >& outgoing ) {

  if ( outgoing.has_value() ) {

    if ( outgoing->particle().identifier() == id::ParticleID::neutron() ) {

      return HardSphereShiftFactor( l );
    }
    else if ( outgoing->particle().charge() > 0 ) {

      return CoulombShiftFactor( l );
    }
  }
  return 0.;
}

static PhaseShift
selectPhaseShiftFunction( unsigned int l,
                          const std::optional< ParticlePair >& outgoing ) {

  if ( outgoing.has_value() ) {

    if ( outgoing->particle().identifier() == id::ParticleID::neutron() ) {

      return HardSpherePhaseShift( l );
    }
    else if ( outgoing->particle().charge() > 0 ) {

      return CoulombPhaseShift( l );
    }
  }
  return 0.;
}
