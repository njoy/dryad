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
