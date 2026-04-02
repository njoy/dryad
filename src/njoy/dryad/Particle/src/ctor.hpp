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
 *  @param[in] id                  the particle identifier
 *  @param[in] mass                the atomic mass
 *  @param[in] spin                the particle spin
 *  @param[in] parity              the parity
 *  @param[in] energy              the excited state energy (default is 0)
 *  @param[in] massUncertainty     the uncertainty on the atomic mass value (default is none)
 *  @param[in] energyUncertainty   the uncertainty on the level energy value (default is none)
 */
Particle( id::ParticleID id,
          double mass,
          double spin,
          short parity,
          double energy = 0.,
          std::optional< double > massUncertainty = std::nullopt,
          std::optional< double > energyUncertainty = std::nullopt ) :
  identifier_( std::move( id ) ),
  mass_( mass ), energy_( energy ),
  mass_uncertainty_( std::move( massUncertainty ) ),
  energy_uncertainty_( std::move( energyUncertainty ) ),
  spin_( spin ), parity_( parity ) {}

