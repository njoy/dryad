/**
 *  @brief Private constructor
 */
ProjectileTarget( Documentation&& documentation,
                  id::ParticleID&& projectile,
                  id::ParticleID&& target,
                  InteractionType type,
                  std::optional< resonances::ResonanceParameters > resonances,
                  std::vector< Reaction >&& reactions,
                  bool normalise ) :
    documentation_( std::move( documentation ) ),
    projectile_id_( std::move( projectile ) ),
    target_id_( std::move( target ) ),
    interaction_( type ),
    resonances_( std::move( resonances ) ),
    reactions_( std::move( reactions ) ) {

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
 *  @param type         the interaction type
 *  @param type            the interaction type
 *  @param reactions       the reaction data
 *  @param normalise       option to indicate whether or not to normalise
 *                         all probability data (default: no normalisation)
 */
ProjectileTarget( Documentation documentation,
                  id::ParticleID projectile,
                  id::ParticleID target,
                  InteractionType type,
                  std::vector< Reaction > reactions,
                  bool normalise = false ) :
    ProjectileTarget( std::move( documentation ),
                      std::move( projectile ),
                      std::move( target ),
                      type,
                      std::nullopt,
                      std::move( reactions ),
                      normalise ) {}

/**
 *  @brief Constructor
 *
 *  @param projectile   the projectile identifier
 *  @param target       the target identifier
 *  @param type.        the interaction type
 *  @param reactions    the reaction data
 *  @param normalise    option to indicate whether or not to normalise
 *                      all probability data (default: no normalisation)
 */
ProjectileTarget( id::ParticleID projectile,
                  id::ParticleID target,
                  InteractionType type,
                  std::vector< Reaction > reactions,
                  bool normalise = false ) :
    ProjectileTarget( {},
                      std::move( projectile ),
                      std::move( target ),
                      type,
                      std::nullopt,
                      std::move( reactions ),
                      normalise ) {}
