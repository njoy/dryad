static void verifyEliminatedChannel( const std::vector< Channel >& channels ) {

  if ( channels.front().outgoingParticlePair().has_value() ) {

    if ( channels.front().outgoingParticlePair()->lightParticle().identifier()
         == id::ParticleID::photon() ) {

      return;
    }
  }
  throw std::runtime_error( "The eliminated capture channel is not the first channel" );
}
