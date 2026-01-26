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
 *  @param element     the particle element
 *  @param vacancies   the subshells with a vacancy
 */
ParticleID( ElementID element, std::vector< ElectronSubshellID > vacancies ) :
    index_( getIndex( std::move( element ), std::move( vacancies ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param element   the particle element
 *  @param vacancy   the subshell with a vacancy
 */
ParticleID( ElementID element, ElectronSubshellID vacancy ) :
    ParticleID( std::move( element ), std::vector< ElectronSubshellID >{ std::move( vacancy ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the particle symbol, name or alternative
 */
ParticleID( const std::string& string ) : index_( getIndex( string ) ) {}
