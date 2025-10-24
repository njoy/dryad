/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
Particle() = default;

Particle( const Particle& ) = default;
Particle( Particle&& ) = default;

Particle& operator=( const Particle& ) = default;
Particle& operator=( Particle&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] id       the particle identifier
 *  @param[in] mass     the atomic mass
 *  @param[in] spin     the particle spin
 *  @param[in] parity   the parity
 */
Particle( id::ParticleID id,
          double mass,
          double spin,
          short parity ) :
  identifier_( std::move( id ) ), mass_( mass ),
  spin_( spin ), parity_( parity ) {}

