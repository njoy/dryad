/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ParticlePair() = default;

ParticlePair( const ParticlePair& ) = default;
ParticlePair( ParticlePair&& ) = default;

ParticlePair& operator=( const ParticlePair& ) = default;
ParticlePair& operator=( ParticlePair&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] lightParticle   the light particle
 *  @param[in] heavyParticle   the heavy particle
 */
ParticlePair( Particle lightParticle, Particle heavyParticle ) :
    light_particle_( std::move( lightParticle ) ),
    heavy_particle_( std::move( heavyParticle ) ) {

  const auto ma = this->lightParticle().mass().value();
  const auto mb = this->heavyParticle().mass().value();
  this->reduced_mass_ = ma * mb / ( ma + mb );
  this->mass_ratio_ = mb / ( ma + mb );
}
