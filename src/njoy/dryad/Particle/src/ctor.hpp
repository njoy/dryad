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
 *  @param[in] id                       the particle identifier
 *  @param[in] mass                     the atomic mass (default is none)
 *  @param[in] spin                     the particle spin (default is none)
 *  @param[in] parity                   the parity (default is none)
 *  @param[in] energy                   the excited state energy (default is none)
 *  @param[in] nuclearMass              the nuclear mass (default is none)
 *  @param[in] massUncertainty          the uncertainty on the atomic mass value (default is none)
 *  @param[in] nuclearMassUncertainty   the uncertainty on the nuclear mass value (default is none)
 *  @param[in] energyUncertainty        the uncertainty on the level energy value (default is none)
 */
Particle( id::ParticleID id,
          std::optional< double > mass = std::nullopt,
          std::optional< double > spin = std::nullopt,
          std::optional< short > parity = std::nullopt,
          std::optional< double > energy = std::nullopt,
          std::optional< double > nuclearMass = std::nullopt,
          std::optional< double > massUncertainty = std::nullopt,
          std::optional< double > nuclearMassUncertainty = std::nullopt,
          std::optional< double > energyUncertainty = std::nullopt ) :
  identifier_( std::move( id ) ),
  mass_( mass ),
  nuclear_mass_( nuclearMass ),
  energy_( energy ),
  mass_uncertainty_( std::move( massUncertainty ) ),
  nuclear_mass_uncertainty_( std::move( nuclearMassUncertainty ) ),
  energy_uncertainty_( std::move( energyUncertainty ) ),
  spin_( spin ), parity_( parity ) {}

