/**
 *  @brief Retrieve the index to the reaction type information entry
 *
 *  @param mt   the mt number
 */
static std::size_t getIndex( int mt ) {

  try {

    return mt_conversion_dictionary.at( mt );
  }
  catch ( ... ) {

    throw std::out_of_range( "\'" + std::to_string( mt ) + "\' does not define a "
                             "registered mt number" );
  }
}

/**
 *  @brief Retrieve the index to the reaction type information entry
 *
 *  @param string   the reaction type string
 */
static std::size_t getIndex( const std::string& string ) {

  try {

    return string_conversion_dictionary.at( string );
  }
  catch ( ... ) {

    throw std::out_of_range( "\'" + string + "\' does not define a "
                             "registered reaction type string" );
  }
}
