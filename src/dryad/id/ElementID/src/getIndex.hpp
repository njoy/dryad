/**
 *  @brief Retrieve the pointer to the element information entry
 *
 *  @param number    the element number
 */
static const Entry* getPointer( int number ) {

  try {

    return std::addressof( entries.at( number ) );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not an element number: \'" + std::to_string( number ) + "\'" );
  }
}

/**
 *  @brief Retrieve the pointer to the element information entry
 *
 *  @param string    the element symbol, name or alternatives
 */
static const Entry* getPointer( const std::string& string ) {

  try {

    return conversion_dictionary.at( string );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not an element symbol or name: \'" + string + "\'" );
  }
}
