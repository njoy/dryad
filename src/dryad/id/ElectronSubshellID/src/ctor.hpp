/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ElectronSubshellID() = default;

ElectronSubshellID( const ElectronSubshellID& ) = default;
ElectronSubshellID( ElectronSubshellID&& ) = default;

ElectronSubshellID& operator=( const ElectronSubshellID& ) = default;
ElectronSubshellID& operator=( ElectronSubshellID&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param number   the subshell number
 */
ElectronSubshellID( int number ) : index_( getIndex( number ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the subshell identifier
 */
ElectronSubshellID( const std::string& string ) : index_( getIndex( string ) ) {}
