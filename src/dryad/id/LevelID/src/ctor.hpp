/**
 *  @brief Constructor
 *
 *  @param pointer    the pointer to the level information entry
 */
LevelID( const Entry* pointer ) : entry_( pointer ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
LevelID() = default;

LevelID( const LevelID& ) = default;
LevelID( LevelID&& ) = default;

LevelID& operator=( const LevelID& ) = default;
LevelID& operator=( LevelID&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param number   the level number
 */
LevelID( int number ) : LevelID( getPointer( number ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the level identifier
 */
LevelID( const std::string& string ) : LevelID( getPointer( string ) ) {}
