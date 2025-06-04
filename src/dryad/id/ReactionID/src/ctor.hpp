private:

/**
 *  @brief Private constructor taking an index
 */
constexpr NewReactionID( std::size_t index ) : index_( index ) {};

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
NewReactionID() = default;

NewReactionID( const NewReactionID& ) = default;
NewReactionID( NewReactionID&& ) = default;

NewReactionID& operator=( const NewReactionID& ) = default;
NewReactionID& operator=( NewReactionID&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param projectile   the projectile
 *  @param target       the target
 *  @param type         the reaction type
 */
NewReactionID( const ParticleID& projectile, const ParticleID& target,
               const ReactionType& type ) : 
  index_( getIndex( projectile, target, type ) ) {}

// these are shortcuts to the previous constructor 
// /**
//  *  @brief Constructor
//  *
//  *  @param projectile   the projectile
//  *  @param target       the target
//  *  @param mt           the mt number
//  */
// NewReactionID( const ParticleID& projectile, const ParticleID& target, int mt ) : 
//   NewReactionID( projectile, target, ReactionType( projectile, mt ) ) {}
// 
// /**
//  *  @brief Constructor
//  *
//  *  @param projectile   the projectile
//  *  @param target       the target
//  *  @param string       the reaction type
//  */
// NewReactionID( const ParticleID& projectile, const ParticleID& target, 
//                const std::string& string ) : 
//   NewReactionID( projectile, target, ReactionType( string ) ) {}
// 
// /**
//  *  @brief Constructor
//  *
//  *  @param projectile   the projectile
//  *  @param target       the target
//  *  @param particles    the outgoing particles (excluding the residual)
//  *  @param level        the level number of the residual
//  */
// NewReactionID( const ParticleID& projectile, const ParticleID& target, 
//                const std::map< ParticleID, short >& particles, int level ) : 
//   NewReactionID( projectile, target, ReactionType( particles, level ) ) {}

  /**
 *  @brief Constructor
 *
 *  @param string   the reaction symbol
 */
NewReactionID( const std::string& symbol ) : 
  index_( getIndex( symbol ) ) {}
