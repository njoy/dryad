/**
 *  @brief Retrieve the index to the reaction type information entry
 *
 *  This function does not recognise any of the ionisation mt numbers
 *  (522 for total ionisation and 534 through 572 for subshell ionisation)
 *  because electro- and photoinionisation cannot be distinguished by the
 *  mt number alone.
 *
 *  @param mt   the mt number
 */
static std::size_t getIndex( int mt ) {

  try {

    return mt_conversion_dictionary.at( mt );
  }
  catch ( ... ) {

    throw std::invalid_argument( "\'" + std::to_string( mt ) + "\' does not define a "
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

    if      ( projectile == ParticleID::neutron() )  { return 131; }
    else if ( projectile == ParticleID::photon() )   { return 30; }
    else if ( projectile == ParticleID::proton() )   { return 198; }
    else if ( projectile == ParticleID::deuteron() ) { return 264; }
    else if ( projectile == ParticleID::triton() )   { return 322; }
    else if ( projectile == ParticleID::helion() )   { return 383; }
    else if ( projectile == ParticleID::alpha() )    { return 443; }
    else {

      throw std::invalid_argument( "Elastic scattering using mt = 2 for \'" + projectile.symbol() + "\' is not defined" );
    }
  }
  else if ( ( ( mt < 534 ) || ( mt > 572 ) ) && ( mt != 522 ) ) {

    // for anything but ionisation use the previous getIndex function
    return getIndex( mt );
  }
  else {

    std::size_t offset = 0;
    if      ( projectile == ParticleID::electron() ) { offset = 584; }
    else if ( projectile == ParticleID::photon() )   { offset = 534; }
    else {

      throw std::invalid_argument( "Ionisation is not defined for \'" + projectile.symbol() + "\'" );
    }

    if ( mt == 522 ) {

      return offset + 49;
    }
    else {

      return offset + mt - 534;
    }
  }
}

/**
 *  @brief Retrieve the index to the reaction type information entry
 *
 *  Note: this constructor only works for nuclear interactions
 *
 *  @param particles   the outgoing particles
 *  @param level       the level number of the residual
 */
static std::size_t getIndex( const std::map< ParticleID, short >& particles, int level ) {

  // generate the symbol for the reaction entry
  std::int64_t number = 0;

  // generate number based on outgoing particles
  if ( ( particles.size() == 0 ) ||
       ( particles.size() == 1 && particles.find( ParticleID::photon() ) != particles.end() ) ) {

    number = 1000;
  }
  else {

    // note: this can probably be optimised
    auto iter = particles.find( ParticleID::alpha() );
    number = iter != particles.end() ? number * 10 + iter->second : number * 10;
    iter = particles.find( ParticleID::helion() );
    number = iter != particles.end() ? number * 10 + iter->second : number * 10;
    iter = particles.find( ParticleID::triton() );
    number = iter != particles.end() ? number * 10 + iter->second : number * 10;
    iter = particles.find( ParticleID::deuteron() );
    number = iter != particles.end() ? number * 10 + iter->second : number * 10;
    iter = particles.find( ParticleID::proton() );
    number = iter != particles.end() ? number * 10 + iter->second : number * 10;
    iter = particles.find( ParticleID::neutron() );
    number = iter != particles.end() ? number * 10 + iter->second : number * 10;
    number *= 10000;
  }

  // add the level
  if ( ( level >= 0 ) && ( level <= LevelID::all ) ) {

    number += level;
  }
  else {

    throw std::invalid_argument( "Not a level number: \'" + std::to_string( level ) + "\'" );
  }

  try {

    return particles_conversion_dictionary.at( number );
  }
  catch ( ... ) {

    throw std::invalid_argument( "The set of outgoing particles does not define a registered reaction type" );
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

    throw std::invalid_argument( "\'" + string + "\' does not define a "
                                 "registered reaction type string" );
  }
}
