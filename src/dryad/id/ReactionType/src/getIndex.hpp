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
 *  @param projectile   the projectile
 *  @param mt           the mt number
 */
static std::size_t getIndex( const ParticleID& projectile, int mt ) {

  // Yes, magic numbers. Sue me.

  if ( ( ( mt < 534 ) || ( mt > 572 ) ) && ( mt != 522 ) ) {

    // for anything but ionisation use the previous getIndex function
    return getIndex( mt );
  }
  else {

    std::size_t offset = 21;
    if ( projectile == ParticleID::electron() ) {

      offset = 70;
    }

    if ( mt == 522 ) {

      return offset + 49;
    }
    else {

      return offset + mt - 534;
    }
  }
  throw std::out_of_range( "what?" );
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
