static double calculateSpinFactor( const ChannelQuantumNumbers& numbers,
                                   const std::optional< ParticlePair >& pair ) {

  if ( pair.has_value() ) {

    const auto J = numbers.totalAngularMomentum();
    const auto ia = pair->lightParticle().spin().has_value()
                    ? pair->lightParticle().spin().value()
                    : 0.;
    const auto ib = pair->heavyParticle().spin().has_value()
                    ? pair->heavyParticle().spin().value()
                    : 0.;
    return  ( 2. * J + 1. ) / ( 2. * ia + 1. )
                            / ( 2. * ib + 1. );
  }
  else {

    return 0.;
  }
}
