/**
 *  @brief Constructor
 *
 *  @param projectile   the particle identifier
 *  @param target       the target identifier
 *  @param reactions    the reaction data
 *  @param linearised   a flag indicating whether or not the data is
 *                      linearised
 */
ProjectileTarget( ParticleID&& projectile, ParticleID&& target,
                  InteractionType type,
                  std::vector< Reaction >&& reactions,
                  bool linearised ) :
    projectile_id_( std::move( projectile ) ),
    target_id_( std::move( target ) ),
    interaction_( type ),
    reactions_( std::move( reactions ) ),
    linearised_( linearised ) {}

public:

ProjectileTarget( const ProjectileTarget& ) = default;
ProjectileTarget( ProjectileTarget&& ) = default;

ProjectileTarget& operator=( const ProjectileTarget& ) = default;
ProjectileTarget& operator=( ProjectileTarget&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param projectile   the particle identifier
 *  @param target       the target identifier
 *  @param reactions    the reaction data
 */
ProjectileTarget( ParticleID projectile, ParticleID target,
                  InteractionType type,
                  std::vector< Reaction > reactions ) :
    ProjectileTarget( std::move( projectile ),
                      std::move( target ),
                      type,
                      std::move( reactions ),
                      std::all_of( reactions.begin(), reactions.end(),
                                   [] ( auto&& reaction )
                                      { return reaction.isLinearised(); } ) ) {}
