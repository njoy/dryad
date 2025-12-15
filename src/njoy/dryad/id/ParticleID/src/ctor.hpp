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
 *  @param element   the particle element
 *  @param mass      the particle mass number
 *  @param level     the particle level
 */
ParticleID( ElementID element, int mass, LevelID level ) :
    index_( getIndex( std::move( element ), mass, std::move( level ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param element    the particle element
 *  @param subshell   the particle subshell
 */
ParticleID( ElementID element, ElectronSubshellID subshell ) :
    index_( getIndex( std::move( element ), std::move( subshell ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the particle symbol, name or alternative
 */
ParticleID( const std::string& string ) : index_( getIndex( string ) ) {}
