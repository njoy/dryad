/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ParticleDatabase() = default;

ParticleDatabase( const ParticleDatabase& ) = default;
ParticleDatabase( ParticleDatabase&& ) = default;

ParticleDatabase& operator=( const ParticleDatabase& ) = default;
ParticleDatabase& operator=( ParticleDatabase&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] particles   the particle information
 */
ParticleDatabase( std::vector< Particle > particles ) :
  particles_( std::move( particles ) ) {

  this->sort();
}
