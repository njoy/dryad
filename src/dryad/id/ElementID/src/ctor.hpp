/**
 *  @brief Constructor
 *
 *  @param index    the index to the element information entry
 */
ElementID( std::size_t index ) : index_( index ) {}

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
ElementID( int number ) : index_( getIndex( number ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the element identifier
 */
ElementID( const std::string& string ) : ElementID( getIndex( string ) ) {}
