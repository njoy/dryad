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
ElementID( int number ) : index_( getIndex( number ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the element identifier or element name
 */
ElementID( const std::string& string ) : index_( getIndex( string ) ) {}
