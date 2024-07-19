/**
 *  @brief Constructor
 *
 *  @param pointer    the pointer to the element information
 */
ElementID( const Entry* pointer ) : entry_( pointer ) {}

public:

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
