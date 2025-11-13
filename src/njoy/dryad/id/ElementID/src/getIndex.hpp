/**
 *  @brief Retrieve the index to the element information entry
 *
 *  @param number    the element number
 */
static std::size_t getIndex( int number ) {

  if ( ( number < 1 ) || ( number > entries.size() ) ) {

    throw std::invalid_argument( "Not an element number: \'" + std::to_string( number ) + "\'" );
  }

  return static_cast< std::size_t >( number - 1 );
}

/**
 *  @brief Retrieve the index to the element information entry
 *
 *  @param string    the element symbol, name or alternatives
 */
static std::size_t getIndex( const std::string& string ) {

  try {

    return conversion_dictionary.at( string );
  }
  catch ( ... ) {

    throw std::invalid_argument( "Not an element symbol or name: \'" + string + "\'" );
  }
}
