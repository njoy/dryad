/**
 *  @brief Retrieve the index to the level information entry
 *
 *  @param number    the level number
 */
static std::size_t getIndex( int number ) {

  if ( ( number < 0 ) || ( number >= entries.size() ) ) {

    throw std::out_of_range( "Not a level number: \'" + std::to_string( number ) + "\'" );
  }

  return static_cast< std::size_t >( number );
}

/**
 *  @brief Retrieve the index to the level information entry
 *
 *  @param string    the level symbol
 */
static std::size_t getIndex( const std::string& string ) {

  try {

    return conversion_dictionary.at( string );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not an element symbol or name: \'" + string + "\'" );
  }
}
