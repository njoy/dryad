/**
 *  @brief Private constructor
 */
ProjectileTarget( Documentation&& documentation,
                  id::ParticleID&& projectile,
                  id::ParticleID&& target,
                  InteractionType type,
                  std::optional< ParticleDatabase >&& particles,
                  std::optional< resonances::ResonanceParameters > resonances,
                  std::vector< Reaction >&& reactions,
                  std::optional< covariance::CovarianceData > covariances,
                  bool normalise ) :
    documentation_( std::move( documentation ) ),
    projectile_id_( std::move( projectile ) ),
    target_id_( std::move( target ) ),
    interaction_( type ),
    particles_( std::move( particles ) ),
    resonances_( std::move( resonances ) ),
    reactions_( std::move( reactions ) ),
    covariances_( std::move( covariances ) ) {

  this->resolvePartialIdentifiers();
  if ( normalise ) {

    this->normalise();
  }
}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ProjectileTarget() = default;

ProjectileTarget( const ProjectileTarget& ) = default;
ProjectileTarget( ProjectileTarget&& ) = default;

ProjectileTarget& operator=( const ProjectileTarget& ) = default;
ProjectileTarget& operator=( ProjectileTarget&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param documentation   the documentation
 *  @param projectile      the projectile identifier
 *  @param target          the target identifier
 *  @param type            the interaction type
 *  @param reactions       the reaction data
 *  @param particles     the optional particle data (default: none)
 *  @param resonances      the optional resonance parameters (default: none)
 *  @param covariances     the optional covariance data (default: none)
 *  @param normalise       option to indicate whether or not to normalise
 *                         all probability data (default: no normalisation)
 */
ProjectileTarget( Documentation documentation,
                  id::ParticleID projectile,
                  id::ParticleID target,
                  InteractionType type,
                  std::vector< Reaction > reactions,
                  std::optional< ParticleDatabase > particles = std::nullopt,
                  std::optional< resonances::ResonanceParameters > resonances = std::nullopt,
                  std::optional< covariance::CovarianceData > covariances = std::nullopt,
                  bool normalise = false ) :
    ProjectileTarget( std::move( documentation ),
                      std::move( projectile ),
                      std::move( target ),
                      type,
                      std::move( particles ),
                      std::move( resonances ),
                      std::move( reactions ),
                      std::move( covariances ),
                      normalise ) {}

/**
 *  @brief Constructor
 *
 *  @param projectile    the projectile identifier
 *  @param target        the target identifier
 *  @param type.         the interaction type
 *  @param reactions     the reaction data
 *  @param particles     the optional particle data (default: none)
 *  @param resonances    the optional resonance parameters (default: none)
 *  @param covariances   the optional covariance data (default: none)
 *  @param normalise     option to indicate whether or not to normalise
 *                       all probability data (default: no normalisation)
 */
ProjectileTarget( id::ParticleID projectile,
                  id::ParticleID target,
                  InteractionType type,
                  std::vector< Reaction > reactions,
                  std::optional< ParticleDatabase > particles = std::nullopt,
                  std::optional< resonances::ResonanceParameters > resonances = std::nullopt,
                  std::optional< covariance::CovarianceData > covariances = std::nullopt,
                  bool normalise = false ) :
    ProjectileTarget( {},
                      std::move( projectile ),
                      std::move( target ),
                      type,
                      std::move( particles ),
                      std::move( resonances ),
                      std::move( reactions ),
                      std::move( covariances ),
                      normalise ) {}
