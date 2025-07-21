/**
 *  @brief Constructor
 *
 *  @param projectile   the projectile identifier
 *  @param target       the target identifier
 *  @param reactions    the reaction data
 *  @param linearised   a flag indicating whether or not the data is
 *                      linearised
 */
ProjectileTarget( id::ParticleID&& projectile,
                  id::ParticleID&& target,
                  InteractionType type,
                  std::optional< resonances::ResonanceParameters > resonances,
                  std::vector< Reaction >&& reactions ) :
    projectile_id_( std::move( projectile ) ),
    target_id_( std::move( target ) ),
    interaction_( type ),
    resonances_( std::move( resonances ) ),
    reactions_( std::move( reactions ) ) {}

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
 *  @param projectile   the projectile identifier
 *  @param target       the target identifier
 *  @param reactions    the reaction data
 */
ProjectileTarget( id::ParticleID projectile,
                  id::ParticleID target,
                  InteractionType type,
                  std::vector< Reaction > reactions ) :
    ProjectileTarget( std::move( projectile ),
                      std::move( target ),
                      type,
                      std::nullopt,
                      std::move( reactions ) ) {}
