static ConversionFactor
selectWidthConversionFactor( const std::optional< ParticlePair >& outgoing ) {

  if ( outgoing.has_value() ) {

    if ( outgoing->lightParticle().identifier() == id::ParticleID::neutron() ) {

      return NeutronWidthConversion();
    }
  }
  return ConstantWidthConversion();
} 

#endif
