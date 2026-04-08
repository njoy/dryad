static std::unordered_map< id::ParticleID, Particle >
generateMap( std::vector< Particle >&& particles ) {

  std::unordered_map< id::ParticleID, Particle > map;
  for ( auto&& particle : particles ) {

    map[ particle.identifier() ] = std::move( particle );
  }

  return map;
}
