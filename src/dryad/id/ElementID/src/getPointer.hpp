/**
 *  @brief Retrieve the pointer to the element information
 *
 *  @param number    the element number
 */
static const Entry* getPointer( int number ) {

  return std::addressof( element_dictionary.at( number ) );
}

/**
 *  @brief Retrieve the pointer to the element information
 *
 *  @param string    the element symbol or name
 */
static const Entry* getPointer( const std::string& string ) {

  return getPointer( conversion_dictionary.at( string ) );
}
