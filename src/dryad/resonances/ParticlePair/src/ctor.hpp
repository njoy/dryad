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
 *  @param[in] particle   the light particle
 *  @param[in] residual   the heavy residual
 */
ParticlePair( Particle particle, Particle residual ) :
    particle_( std::move( particle ) ), residual_( std::move( residual ) ) {

  const auto ma = this->particle().mass();
  const auto mb = this->residual().mass();
  this->reduced_mass_ = ma * mb / ( ma + mb );
  this->mass_ratio_ = mb / ( ma + mb );
}

