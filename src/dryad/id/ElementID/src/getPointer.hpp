/**
 *  @brief Retrieve the pointer to the element information
 *
 *  @param number    the element number
 */
static const Entry* getPointer( int number ) {

  try {

    return std::addressof( elements.at( number ) );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not an element number: \'" + std::to_string( number ) + "\'" );
  }
}

/**
 *  @brief Retrieve the pointer to the element information
 *
 *  @param string    the element symbol or name
 */
static const Entry* getPointer( const std::string& string ) {

  try {

    return conversion_dictionary.at( string );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not an element symbol or name: \'" + string + "\'" );
  }
}
