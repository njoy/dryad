/**
 *  @brief Retrieve the pointer to the level information entry
 *
 *  @param number    the level number
 */
static const Entry* getPointer( int number ) {

  try {

    return std::addressof( entries.at( number ) );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not a level number: \'" + std::to_string( number ) + "\'" );
  }
}

/**
 *  @brief Retrieve the pointer to the level information entry
 *
 *  @param string    the level symbol
 */
static const Entry* getPointer( const std::string& string ) {

  try {

    return conversion_dictionary.at( string );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not a level symbol: \'" + string + "\'" );
  }
}
