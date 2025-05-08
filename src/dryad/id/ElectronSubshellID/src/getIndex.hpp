/**
 *  @brief Retrieve the index to the subshell information entry
 *
 *  @param number    the subshell number
 */
static std::size_t getIndex( int number ) {

  try {

    return number_conversion_dictionary.at( number );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not a subshell number: \'" + std::to_string( number ) + "\'" );
  }
}

/**
 *  @brief Retrieve the index to the subshell information entry
 *
 *  @param string    the subshell symbol or alternatives
 */
static std::size_t getIndex( const std::string& string ) {

  try {

    return string_conversion_dictionary.at( string );
  }
  catch ( ... ) {

    throw std::out_of_range( "Not a subshell symbol or name: \'" + string + "\'" );
  }
}
