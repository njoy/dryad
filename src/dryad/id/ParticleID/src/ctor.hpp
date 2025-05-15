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
 *  @param za       the particle za number
 *  @param number   the particle level or subshell number (default is zero)
 */
ParticleID( int za, int number = 0 ) : index_( getIndex( za, number ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the particle symbol, name or alternative
 */
ParticleID( const std::string& string ) : index_( getIndex( string ) ) {}
