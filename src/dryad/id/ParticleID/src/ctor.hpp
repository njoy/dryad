private:

/**
 *  @brief Private constructor taking an index
 */
constexpr ParticleID( std::size_t index ) : index_( index ) {};

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ParticleID() = default;

ParticleID( const ParticleID& ) = default;
ParticleID( ParticleID&& ) = default;

ParticleID& operator=( const ParticleID& ) = default;
ParticleID& operator=( ParticleID&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param za      the particle za number
 *  @param level   the particle level number (default is zero)
 */
ParticleID( int za, int level = 0 ) : index_( getIndex( za, level ) ) {}

/**
 *  @brief Constructor
 *
 *  @param particle   the particle identifier
 */
ParticleID( const std::string& particle ) : index_( getIndex( particle ) ) {}
