static double calculateSpinFactor( const ChannelQuantumNumbers& numbers,
                                   const std::optional< ParticlePair >& pair ) {


  if ( pair.has_value() ) {

    const auto J = numbers.totalAngularMomentum();
    const auto ia = pair->lightParticle().spin().value();
    const auto ib = pair->heavyParticle().spin().value();
    return  ( 2. * J + 1. ) / ( 2. * ia + 1. )
                            / ( 2. * ib + 1. );
  }
  else {

    return 0.;
  }
}
