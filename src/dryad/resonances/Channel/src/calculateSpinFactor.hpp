static double calculateSpinFactor( const ChannelQuantumNumbers& numbers,
                                   const std::optional< ParticlePair >& pair ) {


  if ( pair.has_value() ) {

    const auto J = numbers.totalAngularMomentum();
    const auto ia = pair->particle().spin();
    const auto ib = pair->residual().spin();
    return  ( 2. * J + 1. ) / ( 2. * ia + 1. )
                            / ( 2. * ib + 1. );
  }
  else {

    return 0.;
  }
}
