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
 *  @param[in] id       the particle identifier
 *  @param[in] mass     the atomic mass
 *  @param[in] spin     the particle spin
 *  @param[in] parity   the parity
 */
ParticlePair( const Particle& particle,
              const Particle& residual ) :
    particle_( std::move( particle ) ), residual_( std::move( residual ) ) {

  const auto ma = this->particle().mass();
  const auto mb = this->residual().mass();
  this->reduced_mass_ = ma * mb / ( ma + mb );
  this->mass_ratio_ = mb / ( ma + mb );
}

