/**
 *  @brief Constructor
 *
 *  @param pointer    the pointer to the element information entry
 */
ElementID( const Entry* pointer ) : entry_( pointer ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ElementID() = default;

ElementID( const ElementID& ) = default;
ElementID( ElementID&& ) = default;

ElementID& operator=( const ElementID& ) = default;
ElementID& operator=( ElementID&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param number   the element number
 */
ElementID( int number ) : ElementID( getPointer( number ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the element identifier
 */
ElementID( const std::string& string ) : ElementID( getPointer( string ) ) {}
