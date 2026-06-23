static ConversionFactor
selectWidthConversionFactor( unsigned int l,
                             double reference_energy,
                             const std::optional< ParticlePair >& outgoing ) {

  if ( outgoing.has_value() ) {

    if ( outgoing->lightParticle().identifier() == id::ParticleID::neutron() ) {

      return ReducedWidthConversion( l, reference_energy);
    }
  }
  return 1.;
} 

#endif
