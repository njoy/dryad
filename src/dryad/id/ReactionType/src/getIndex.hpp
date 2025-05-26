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

  if ( mt == 2 ) {

    if      ( projectile == ParticleID::neutron() )  { return 111; }
    else if ( projectile == ParticleID::photon() )   { return 10; }
    else if ( projectile == ParticleID::proton() )   { return 178; }
    else if ( projectile == ParticleID::deuteron() ) { return 244; }
    else if ( projectile == ParticleID::triton() )   { return 302; }
    else if ( projectile == ParticleID::helion() )   { return 363; }
    else if ( projectile == ParticleID::alpha() )    { return 423; }
    else {

      Log::error( "Elastic scattering using mt = 2 for \'{}\' is not defined", projectile.symbol() );
      throw std::exception();
    }
  }
  else if ( ( ( mt < 534 ) || ( mt > 572 ) ) && ( mt != 522 ) ) {

    // for anything but ionisation use the previous getIndex function
    return getIndex( mt );
  }
  else {

    std::size_t offset = 0;
    if      ( projectile == ParticleID::electron() ) { offset = 564; }
    else if ( projectile == ParticleID::photon() )   { offset = 514; }
    else {

      Log::error( "Ionisation is not defined for \'{}\'", projectile.symbol() );
      throw std::exception();
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
