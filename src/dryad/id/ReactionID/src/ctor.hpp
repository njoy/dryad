private:

/**
 *  @brief Private constructor taking an index
 */
constexpr ReactionID( std::size_t index ) : index_( index ) {};

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ReactionID() = default;

ReactionID( const ReactionID& ) = default;
ReactionID( ReactionID&& ) = default;

ReactionID& operator=( const ReactionID& ) = default;
ReactionID& operator=( ReactionID&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param projectile   the projectile
 *  @param target       the target
 *  @param type         the reaction type
 */
ReactionID( const ParticleID& projectile, const ParticleID& target,
            const ReactionType& type ) :
  index_( getIndex( projectile, target, type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param projectile   the projectile
 *  @param target       the target
 *  @param mt           the mt number
 */
ReactionID( const ParticleID& projectile, const ParticleID& target, int mt ) :
  ReactionID( projectile, target, ReactionType( projectile, mt, target.e() ) ) {}

/**
 *  @brief Constructor
 *
 *  @param projectile   the projectile
 *  @param target       the target
 *  @param type         the string representing the reaction type
 */
ReactionID( const ParticleID& projectile, const ParticleID& target,
            const std::string& type ) :
  ReactionID( projectile, target, ReactionType( type ) ) {}

// /**
//  *  @brief Constructor
//  *
//  *  @param projectile   the projectile
//  *  @param target       the target
//  *  @param particles    the outgoing particles (excluding the residual)
//  *  @param level        the level number of the residual
//  */
// ReactionID( const ParticleID& projectile, const ParticleID& target,
//                const std::map< ParticleID, short >& particles, int level ) :
//   ReactionID( projectile, target, ReactionType( particles, level ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the reaction symbol
 */
ReactionID( const std::string& symbol ) :
  index_( getIndex( symbol ) ) {}
